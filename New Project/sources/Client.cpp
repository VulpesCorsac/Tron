
#include "stdafx.h"
#include "..\headers\Client.h"
#include "..\headers\Server.h"
#include "..\headers\gengine.h"


const double dt = 1.0f / 60.0f;

void init_network()
{
    WORD ver = MAKEWORD(2,2);
    WSADATA wsaData;

    WSAStartup(ver,(LPWSADATA)&wsaData);
}


CClient::CClient()
{
	connected = 0;
	game_started = false;
	for (int j = 0; j < MAX_CLIENTS; j++)
	for (int i = 0; i < 100000; i++)
	{
	//	last_frame_action[j] = 0;
		act[j][i].cadr = i;
		act[j][i].start_bomb = false;
		act[j][i].start_rocket = false;
		act[j][i].turn = NO_TURN;
		act[j][i].received = false;
	}
	stepped = 0;
	frames_wtanws = 0;
}

CClient::CClient(CGEngine * _game, Game_Engine *_ggame)
{
	 game = _game;
	 ggame = _ggame;
	 connected = 0;
	 game_started = false;
	 for (int j = 0; j < MAX_CLIENTS; j++)
	 for (int i = 0; i < 100000; i++)
	 {
	//	 last_frame_action[j] = 0;
		 act[j][i].cadr = i;
		 act[j][i].start_bomb = false;
		 act[j][i].start_rocket = false;
		 act[j][i].turn = NO_TURN;
		 act[j][i].received = false;
	 }
	 stepped = 0;
	 frames_wtanws = 0;
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
	act->turn = NO_TURN;
	act->start_bomb = false;
	act->start_rocket = false;
	bool a = false;
	if (game->isKeyJustPressed(VK_LEFT))
	{
		act->turn = TURN_LEFT;
		a = true;
	} else
	if (game->isKeyJustPressed(VK_RIGHT))
	{
		act->turn = TURN_RIGHT;
		a = true;
	} else
	{
		act->turn = NO_TURN;
	}
	if (game->isKeyJustPressed(VK_SPACE))
	{
		act->start_bomb = true;
		a = true;
	}
	if (game->isKeyJustPressed(VK_CONTROL))
	{
		act->start_rocket = true;
		a = true;
	}
	return a;
}


void CClient :: goback(int frame)
{
	int i = 0;
	if (frame > cadr)
		return;
	while ((i < ggame->Current_Game.Walls.size()) && (ggame->Current_Game.Walls[i].Wall_Number >= 0))
	{
		i++;
	}
	i++;
	ggame->Current_Game.Walls.resize(i);
}

void CClient::goforward(int frame)
{
	for (int j = 0; j < cadr - frame; j++)
	{
		for (int i = 0; i < number_of_clients; i++)
		if (act[i][j + frame].received == true)
			ggame->PLayer_Turn_Client(i, act[i][j].turn == TURN_LEFT);
		ggame->UPD_Client(dt);
	}

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

	sendto(my_sock, (char *)&msg, sizeof(my_message)-2048, 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    while(((msg_size = recvfrom(my_sock, (char*) &msg, sizeof(my_message), 0, (struct sockaddr *) &anyaddr, &len)) == -1) && (lol_size < 1000))
    {
		lol_size++;
		Sleep(1);
    }
	if (lol_size == 1000)
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


Game* CClient::getGame_r()
{
	if (!game_started) return NULL;
	return &ggame->Current_Game;
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
			ggame->Start_Game_Client(beg_state);
			cadr = 0;
			game_started = true;
		}

		if ((msg.type == PLAYER_ACTION) && (msg.cl_num != my_num))
		{
			Actions rec_act;
			int * p = (int *)msg.buff;
			rec_act.cadr = *(p++);
			rec_act.start_bomb = *(p++);
			rec_act.start_rocket = *(p++);
			rec_act.turn = *(p++);
			rec_act.received = true;
			act[msg.cl_num - 1][msg.pack_num] = rec_act;
			


			if (rec_act.received != false)
			{
				if (cadr > rec_act.cadr)
				{	
					
					ggame->Current_Game.Players[msg.cl_num - 1].UPD(-dt *(cadr - rec_act.cadr));
					ggame->Wall_Prolong(msg.cl_num - 1);

					if (rec_act.start_bomb == true)
						ggame->Bomb_Place(msg.cl_num - 1);
					if (rec_act.start_rocket == true)
						ggame->Rocket_Place(msg.cl_num - 1);
					if (rec_act.turn != NO_TURN)
					ggame->PLayer_Turn_Client(msg.cl_num - 1, rec_act.turn == TURN_LEFT);
					ggame->Current_Game.Players[msg.cl_num - 1].UPD(dt *(cadr - rec_act.cadr));
				}
				else ggame->PLayer_Turn_Client(msg.cl_num - 1, rec_act.turn == TURN_LEFT);
			}
		}

		if (msg.type == UPD_GAME_STATE_ACC)
		{
			Changes temp_changes;
			read_changes(&msg, &temp_changes);
		//	here comes the msg.buf parsing to temp_changes
			ggame->Update_Changes_ACC(temp_changes);
		}

		if (msg.type == UPD_GAME_STATE_NACC)
		{
			int curcadr;
			State temp_state;
			curcadr = msg.pack_num;
			read_state(&msg, &temp_state);
			number_of_clients = temp_state.Players.size();
			goback(curcadr);
			ggame->Update_Changes_NACC(temp_state);
			goforward(cadr);
			//here comes the sg.buf parsing to temp_state
		}
	}

	if (game_started)
	{
		Actions curact;
		curact.cadr = cadr;
		if (check_for_actions(&curact) || (frames_wtanws >=5))
		{
			int * p = (int *)msg.buff;
			msg.type = PLAYER_ACTION;
			msg.cl_num = getPID() + 1;
			msg.pack_num = stepped;
			*(p++) = curact.cadr;
			*(p++) = curact.start_bomb;
			*(p++) = curact.start_rocket;
			*(p++) = curact.turn;
			
			sendto(my_sock, (char *)&msg, sizeof(my_message)- 2000, 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
			frames_wtanws = 0;

			if (curact.turn != NO_TURN)
				ggame->PLayer_Turn_Client(getPID(), curact.turn == TURN_LEFT);
			if (curact.start_bomb == true)
				ggame->Bomb_Place(getPID());
			if (curact.start_rocket == true)
				ggame->Rocket_Place(getPID());
		}
		else frames_wtanws++;


		ggame->UPD_Client(dt);
	}
//	if ()
	return true;
}

CClient:: ~CClient()
{


    closesocket(my_sock);
}

