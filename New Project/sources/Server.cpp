#include "stdafx.h"
#include "../headers/Client.h"
#include "../headers/Server.h"


CServer::CServer(CGEngine * _game, Game_Engine *_ggame)
{

	for (int j = 0; j < MAX_CLIENTS; j++)
	for (int i = 0; i < 100000; i++)
	{
		last_frame_action[j] = 0;
		act[j][i].cadr = i;
		act[j][i].start_bomb = false;
		act[j][i].start_rocket = false;
		act[j][i].turn = NO_TURN;
		act[j][i].received = false;
	}
	stepped = 0;


	game = _game;
	ggame = _ggame;
	cadr = 0;
	game_started = false;
	perm_to_connect = true;
	number_of_clients = 0;
	for (int i = 1; i < MAX_CLIENTS; i++)
	{
		clients[i].number = i;
		clients[i].occupied = false;
		clients[i].packets_sended = 0;
	}
	my_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	u_long iMode = 1;
	ioctlsocket(my_sock, FIONBIO, &iMode);

	if (my_sock == INVALID_SOCKET)
	{
		perror("socket");
	}

	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(8400);
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(my_sock, (const sockaddr *)&myaddr, sizeof(myaddr)) == -1)
	{
		perror("bind");
	}

}


CServer :: CServer()
{


		cadr = 0;
		game_started = false;
		perm_to_connect = true;
        number_of_clients = 0;
		clients[0].occupied = true;
        for(int i = 1; i < MAX_CLIENTS; i++)
        {
            clients[i].number = i;
            clients[i].occupied = false;
            clients[i].packets_sended = 0;

        }
        my_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

        u_long iMode=1;
        ioctlsocket(my_sock, FIONBIO, &iMode);

        if (my_sock == INVALID_SOCKET)
          {
             perror("socket");
          }

        memset((char *) &myaddr, 0, sizeof(myaddr));
        myaddr.sin_family = AF_INET;
        myaddr.sin_port = htons(8400);
        myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        if (bind(my_sock ,(const sockaddr *) &myaddr, sizeof(myaddr)) == -1)
        {
            perror("bind");
        }

    }



bool CServer::Line_up()
{
	my_message msg;
	msg.type = CHANGE_IN_NUM;
	msg.cl_num = 0;
	msg.length = 1;

	for (int i = 1; i < MAX_CLIENTS; i++)
	{
		if (clients[i].occupied == false)
		for (int j = i+1; j < MAX_CLIENTS; j++)
		if (clients[j].occupied == true)
		{
			clients[i].addr = clients[j].addr;
			clients[i].number = j;
			clients[i].occupied = true;
			clients[j].occupied = false;
			sprintf(msg.buff, "%d", i);
			sendto(my_sock, (char *)&msg, sizeof(my_message), 0, (sockaddr *)&clients[i].addr, sizeof(sockaddr));
			break;
		}
	}
	return true;
}

bool CServer :: check_frame()
{

	int max_frame[MAX_CLIENTS], received[MAX_CLIENTS];
	for (int i = 0; i < MAX_CLIENTS; i++)
	{
		max_frame[i] = stepped;
		received[i] = 0;
	}
	int mframe = 100000;

	for (int i = 0; i < number_of_clients; i++)
	for (int j = stepped + 1; j < stepped + 20; j++)
	{
		if (act[i][j].received == true)
			received[i] = 1;
		if ((act[i][j].received == true) && (max_frame[i] < j))
			max_frame[i] = j;
	}

	for (int i = 0; i < number_of_clients; i++)
	if (mframe > max_frame[i]) mframe = max_frame[i];



	return true;
}




    bool CServer :: think()
    {
            sockaddr_in tempaddr;
            int slen = sizeof(sockaddr_in);
            my_message msg, anws;
			if (game_started)
			{
				cadr++;
			}
			while (recvfrom(my_sock, (char *)&msg, sizeof(my_message), 0, (struct sockaddr *) &tempaddr, &slen) != -1)
			{

				if ((msg.type == REGISTER_PLAYER) && (perm_to_connect))
				{
					if (number_of_clients == MAX_CLIENTS - 1)
					{
						anws.type = DISCONNECT;
						sprintf(anws.buff, "%d", 12);
						anws.cl_num = 0;
						anws.length = 1;
						anws.pack_num = 0;
						sendto(my_sock, (char *)&anws, sizeof(my_message), 0, (struct sockaddr *) &tempaddr, sizeof(tempaddr));
					}
					else
					{
						number_of_clients++;
						for (int i = 1; i < MAX_CLIENTS; i++)
						{
							if (clients[i].occupied == false)
							{
								clients[i].occupied = true;
								clients[i].packets_sended = 0;
								clients[i].addr = tempaddr;
								anws.type = ACCEPT_CONNECTION;
								sprintf(anws.buff, "%d", i);
								anws.cl_num = 0;
								anws.length = 4;
								anws.pack_num = 0;
								sendto(my_sock, (char *)&anws, sizeof(my_message), 0, (struct sockaddr *) &clients[i].addr, sizeof(tempaddr));
								break;
							}
						}
					}
				}




				if (msg.type == DISCONNECT)
				{
					number_of_clients--;
					sprintf(anws.buff, "%d", msg.cl_num);
					anws.type = DISCONNECT;
					anws.cl_num = 0;
					anws.length = 1;
					broadcast(anws);
					clients[msg.cl_num].occupied = 0;
					clients[msg.cl_num].packets_sended = 0;
					clients[msg.cl_num].number = 0;
				}

				if (msg.type == PLAYER_ACTION)
				{
					int curfr;
					clients[msg.cl_num].count++;
					
					sscanf(msg.buff, "%d",  &curfr);
					act[msg.cl_num][curfr].received = true;
					sscanf(msg.buff, "%d", &act[msg.cl_num][curfr].start_bomb);
					sscanf(msg.buff, "%d", &act[msg.cl_num][curfr].start_rocket);
					sscanf(msg.buff, "%d", &act[msg.cl_num][curfr].turn);
					broadcast(msg);
				}
			}


			//check_frame();

        return true;
    }


    bool CServer :: broadcast(my_message msg)
    {
		int len = sizeof(clients[0].addr);
		for (int i = 0; i < MAX_CLIENTS; i++)
		{
			if (clients[i].occupied == true)
			{
				sendto(my_sock, (char *) &msg, sizeof(my_message), 0, (sockaddr *)&clients[i].addr, len);
			}
		}
		return true;
    }

	int CServer::getPlCount()
	{
		return number_of_clients;
	}


	void write_state(my_message * msg, state * some_state)
	{

	}

	void read_state(my_message * msg, state * some_state)
	{

	}

	void write_changes(my_message * msg, changes * some_changes)
	{

	}

	void read_changes(my_message * msg, changes * some_changes)
	{

	}

	bool CServer::startgame()
	{

		if (number_of_clients < 1)
			return false;
		Line_up();
		game_started = true;
		perm_to_connect = false;

		state beg_state;
		ggame->Start_Game(number_of_clients, &beg_state);
		cadr = 0;

		my_message msg;
		msg.cl_num = 0;
		msg.type = START_GAME;
		sprintf(msg.buff, "%d", number_of_clients);
		
		write_state( &msg, &beg_state);

		broadcast(msg);
		return true;
	}


     CServer :: ~CServer()
     {
         closesocket(my_sock);
     }
