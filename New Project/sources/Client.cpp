
#include "stdafx.h"
#include "..\headers\Client.h"
#include "..\headers\Server.h"
#include "..\headers\gengine.h"


void init_network()
{
    WORD ver = MAKEWORD(2,2);
    WSADATA wsaData;

    WSAStartup(ver,(LPWSADATA)&wsaData);
}


CClient::CClient()
{
	connected = 0;
}

CClient::CClient(CGEngine * _game, Game_Engine *_ggame)
{
	 game = _game;
	 ggame = _ggame;
     connected = 0;
}

int CClient::getPID()
{
	return get_num() - 1;
}

int CClient::get_num()
{
	return my_num;
}


void write_state(my_message * msg, State * some_state);

void read_state(my_message * msg, State * some_state);

void write_changes(my_message * msg, Changes * some_changes);

void read_changes(my_message * msg, Changes * some_changes);






bool CClient :: check_for_actions(Actions *act)
{
	bool a = false;
	if (game->isKeyPressed(VK_LEFT))
	{
		act->turn = TURN_LEFT;
		a = true;
	}
	if (game->isKeyPressed(VK_RIGHT))
	{
		act->turn = TURN_RIGHT;
		a = true;
	}

	if (!(game->isKeyPressed(VK_RIGHT) || game->isKeyPressed(VK_LEFT)))
	{
		act->turn = NO_TURN;
	}
	if (game->isKeyPressed(VK_SPACE))
	{
		act->start_bomb = true;
		a = true;
	}
	if (game->isKeyPressed(VK_CONTROL))
	{
		act->start_rocket = true;
		a = true;
	}
	return a;
}


bool CClient :: connect(const char *ip)
{
    my_sock = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    u_long iMode=1;
    ioctlsocket(my_sock, FIONBIO, &iMode);
    if (my_sock == INVALID_SOCKET)
    {
        perror("socket");
    }

    memset((char *)&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_port = htons(8400);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ip);

    anyaddr.sin_port = htons(9400);
    anyaddr.sin_family = AF_INET;
    anyaddr.sin_addr.s_addr = INADDR_ANY;
	/*
    if( bind(my_sock,(sockaddr *) &anyaddr, sizeof(serv_addr)) == -1)
    {
        perror("bind");
        exit(1);
    }
	*/
    msg.cl_num = 0;
    msg.type = REGISTER_PLAYER;
    msg.pack_num = 0;
    msg.length = 0;
    int len = sizeof(sockaddr_in);
    int msg_size;
	int lol_size = 0;

    sendto(my_sock,(char *) &msg, sizeof(my_message), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    while(((msg_size = recvfrom(my_sock, (char*) &msg, sizeof(my_message), 0, (struct sockaddr *) &anyaddr, &len)) == -1) && (lol_size < 100000))
    {
		lol_size++;
    }
	if (lol_size = 10000)
		perror("TIMED OUT");
    if(msg_size > 0){
        if(msg.type == ACCEPT_CONNECTION)
        {
            connected = 1;
            sscanf( msg.buff, "%d", &my_num);
            printf("%d ",msg_size);
            return true;
        }

        if(msg.type == DISCONNECT)
            return false;
    }
  //  recvfrom(my_sock,
}



bool CClient::think()
{
	if (game_started)
	{
		cadr++;
	}

	int len = sizeof(sockaddr_in);
	int msg_size;

	while ((msg_size = recvfrom(my_sock, (char*)&msg, sizeof(my_message), 0, (struct sockaddr *) &anyaddr, &len) != -1))
	{

		if (msg.type == CHANGE_IN_NUM)
		{ 
			sscanf(msg.buff, "%d", &my_num);
		}

		if (msg.type == DISCONNECT)
		{
			//kill player
		}

		if (msg.type == START_GAME)
		{	
			State beg_state;
			read_state(&msg, &beg_state);
			ggame->Update_Changes_NACC(&beg_state);
			cadr = 0;
			game_started = true;
		}

		if ((msg.type == PLAYER_ACTION) && (msg.cl_num != my_num))
		{
			Actions rec_act;
			sscanf(msg.buff, "%d %d %d %d", &rec_act.cadr, &rec_act.start_bomb, &rec_act.start_rocket, &rec_act.turn);
//			if (rec_act.start_bomb == true)

//			if (rec_act.start_rocket == true)
				

			if (rec_act.turn != NO_TURN)
				ggame->Turn_Player(rec_act.turn, msg.cl_num - 1);
		}


		if (msg.type == UPD_GAME_STATE_ACC)
		{
			Changes temp_changes;
			read_changes(&msg, &temp_changes);
		//	here comes the msg.buf parsing to temp_changes
			ggame->Update_Changes_ACC(&temp_changes);
		}

		if (msg.type == UPD_GAME_STATE_NACC)
		{
			State temp_state;
			read_state(&msg, &temp_state);
			//here comes the sg.buf parsing to temp_state
			ggame->Update_Changes_NACC(&temp_state);
		}

	}

	Actions curact;
	curact.cadr = cadr;
	if (check_for_actions(&curact) || (frames_wtanws >=5))
	{
		msg_anw.type = PLAYER_ACTION;
		msg.cl_num = getPID();
		sprintf(msg.buff, "%d %d %d %d", curact.cadr, curact.start_bomb, curact.start_rocket, curact.turn);
		sendto(my_sock, (char *)&msg, sizeof(my_message), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
		frames_wtanws = 0;

		if (curact.turn != NO_TURN)
			ggame->Turn_Player(curact.turn, getPID() - 1);
	}
	else frames_wtanws++;


	const double dt = 1.0f / 60.0f;
	ggame->UPD(dt);
//	if ()
	return true;
}

CClient:: ~CClient()
{
    closesocket(my_sock);
}

