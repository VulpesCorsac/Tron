#include "../headers/Client.h"
#include "../headers/Server.h"
#include "stdafx.h"


CServer::CServer(CGEngine * _game, Game_Engine *_ggame)
{



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
		for (int j = 0; j < 100; j++)
			clients[i].my_actions[j].cadr = 0;
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
			for (int j = 0; j < 100; j++)
			clients[i].my_actions[j].cadr = 0;
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

	for (int i = 0; i < MAX_CLIENTS; i++)
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
			break;
		}
	}
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
						return true;
					}

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
					
					clients[msg.cl_num].count++;
					sscanf(msg.buff, "%d",  clients[msg.cl_num].my_actions[clients[msg.cl_num].count % 100].cadr);
					sscanf(msg.buff, "%d", clients[msg.cl_num].my_actions[clients[msg.cl_num].count % 100].turn);
					sscanf(msg.buff, "%d", clients[msg.cl_num].my_actions[clients[msg.cl_num].count % 100].start_rocket);
					sscanf(msg.buff, "%d", clients[msg.cl_num].my_actions[clients[msg.cl_num].count % 100].start_bomb);
				}


			

			}


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

	bool CServer::startgame()
	{

		if (number_of_clients < 1)
			return false;
		game_started = true;
		perm_to_connect = false;





		return true;
	}


     CServer :: ~CServer()
     {
         closesocket(my_sock);
     }
