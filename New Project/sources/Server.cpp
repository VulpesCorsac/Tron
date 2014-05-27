#include "stdafx.h"
#include "../headers/Client.h"
#include "../headers/Server.h"


void write_state(my_message * msg, State * some_state, Game* game)
{
	int number_of_players;
	number_of_players =(int) some_state->Players.size();
	int* p = (int*)msg->buff;
	*(p++) = number_of_players;


	for (int i = 0; i < number_of_players; i++)

	{
		*(p++) = some_state->Players[i].Alive;
		*(p++) = some_state->Players[i].Bomb_Ammount;
		*(p++) = some_state->Players[i].Player_Number;
		*(p++) = some_state->Players[i].Rocket_Ammount;
		*(p++) = some_state->Players[i].Team_Number;
		*((double*)p) = some_state->Players[i].MyCycle.Current_Point.x;
			p += 2;
		*((double*)p) = some_state->Players[i].MyCycle.Current_Point.y;
			p += 2;
		*((double*)p) = some_state->Players[i].MyCycle.Direction.x;
			p += 2;
		*((double*)p) = some_state->Players[i].MyCycle.Direction.y;
			p += 2;
		*((double*)p) = some_state->Players[i].MyCycle.Speed;
			p += 2;

		*((double*)p) = game->Walls[i].Segment.A.x;
		p += 2;
		*((double*)p) = game->Walls[i].Segment.A.y;
		p += 2;
	}
	msg->sizeofmsg = (p - (int *)msg->buff + 1) * 4;
}

void read_state(my_message * msg, State * some_state, Game* game)
{
	int number_of_players;
	int* p = (int*)msg->buff;
	number_of_players = *(p++);
	some_state->Players.resize(number_of_players);

	for (int i = 0; i < number_of_players; i++)
	{
		some_state->Players[i].Alive = *(p++);
		some_state->Players[i].Bomb_Ammount = *(p++);
		some_state->Players[i].Player_Number = *(p++);
		some_state->Players[i].Rocket_Ammount = *(p++);
		some_state->Players[i].Team_Number = *(p++);
		some_state->Players[i].MyCycle.Current_Point.x = *((double*)p);
		p += 2;
		some_state->Players[i].MyCycle.Current_Point.y = *((double*)p);
		p += 2;
		some_state->Players[i].MyCycle.Direction.x = *((double*)p);
		p += 2;
		some_state->Players[i].MyCycle.Direction.y = *((double*)p);
		p += 2;  
		some_state->Players[i].MyCycle.Speed = *((double*)p);
		p += 2;

		if (game->Walls.size() > i) game->Walls[i].Segment.A.x = *((double*)p);
		p += 2;
		if (game->Walls.size() > i) game->Walls[i].Segment.A.y = *((double*)p);
		p += 2;
	}
}

void write_changes(my_message * msg, Changes * some_changes)
{
	int len;
	int * p = (int *)msg->buff;
	*(p++) = len = some_changes->Killed_Players.size();
	for (int i = 0; i < len; i++)
		*(p++) = some_changes->Killed_Players[i];


	*(p++) = len = some_changes->Modifyed_Walls.size();
	assert(len < 30);
	for (int i = 0; i < len; i++)
	{
		*(p++) = some_changes->Modifyed_Walls[i].first.Player_Number;
		*(p++) = some_changes->Modifyed_Walls[i].first.Wall_Number;
		*((double *)p) = some_changes->Modifyed_Walls[i].first.Segment.A.x;
		p = p + 2;
		*((double *)p) = some_changes->Modifyed_Walls[i].first.Segment.A.y;
		p = p + 2;
		*((double *)p) = some_changes->Modifyed_Walls[i].first.Segment.B.x;
		p = p + 2;
		*((double *)p) = some_changes->Modifyed_Walls[i].first.Segment.B.y;
		p = p + 2;

		*(p++) = some_changes->Modifyed_Walls[i].second.Player_Number;
		*((double *)p) = some_changes->Modifyed_Walls[i].second.Segment.A.x;
		p = p + 2;
		*((double *)p) = some_changes->Modifyed_Walls[i].second.Segment.A.y;
		p = p + 2;
		*((double *)p) = some_changes->Modifyed_Walls[i].second.Segment.B.x;
		p = p + 2;
		*((double *)p) = some_changes->Modifyed_Walls[i].second.Segment.B.y;
		p = p + 2;
		*(p++) = some_changes->Modifyed_Walls[i].second.Wall_Number;

	}

	*(p++) = len = some_changes->New_Walls.size();
	for (int i = 0; i < len; i++)
	{
		*(p++) = some_changes->New_Walls[i].Player_Number;
		*((double *)p) = some_changes->New_Walls[i].Segment.A.x;
		p = p + 2;
		*((double *)p) = some_changes->New_Walls[i].Segment.A.y;
		p = p + 2;
		*((double *)p) = some_changes->New_Walls[i].Segment.B.x;
		p = p + 2;
		*((double *)p) = some_changes->New_Walls[i].Segment.B.y;
		p = p + 2;
		*(p++) = some_changes->New_Walls[i].Wall_Number;
	}

//	len = some_changes->Exploded_Bombs.size();
	*(p++) = len = some_changes->Placed_Bonuses.size();
	for (int i = 0; i < len; i++)
	{
		*(p++) = some_changes->Placed_Bonuses[i].Bomb;
		*(p++) = some_changes->Placed_Bonuses[i].Rocket;
		*(p) = some_changes->Placed_Bonuses[i].Point.x;
		p = p + 2;
		*(p) = some_changes->Placed_Bonuses[i].Point.y;
		p = p + 2;
	}
	
	*(p++) = len = some_changes->Collected_Bonuses.size();
	for (int i = 0; i < len; i++)
	{
		*(p++) = some_changes->Collected_Bonuses[i];
	}


	msg->sizeofmsg = (p - (int *)msg->buff + 1) * 4;
}

void read_changes(my_message * msg, Changes * some_changes)
{
	int len;
	int  *p = (int *)msg->buff;
	len = *(p++);
	some_changes->Killed_Players.resize(len);
	for (int i = 0; i < len; i++)
	some_changes->Killed_Players[i] = *(p++);
	

	len = *(p++);
	some_changes->Modifyed_Walls.resize(len);
	assert(len < 30);
	for (int i = 0; i < len; i++)
	{
		some_changes->Modifyed_Walls[i].first.Player_Number = *(p++);
		some_changes->Modifyed_Walls[i].first.Wall_Number = *(p++);
		some_changes->Modifyed_Walls[i].first.Segment.A.x = *((double *)p);
		p = p + 2;
		some_changes->Modifyed_Walls[i].first.Segment.A.y = *((double *)p);
		p = p + 2;
		some_changes->Modifyed_Walls[i].first.Segment.B.x = *((double *)p);
		p = p + 2;
		some_changes->Modifyed_Walls[i].first.Segment.B.y = *((double *)p);
		p = p + 2;


		some_changes->Modifyed_Walls[i].second.Player_Number = *(p++);
		some_changes->Modifyed_Walls[i].second.Segment.A.x = *((double *)p);
		p = p + 2;
		some_changes->Modifyed_Walls[i].second.Segment.A.y = *((double *)p);
		p = p + 2;
		some_changes->Modifyed_Walls[i].second.Segment.B.x = *((double *)p);
		p = p + 2;
		some_changes->Modifyed_Walls[i].second.Segment.B.y = *((double *)p);
		p = p + 2;
		some_changes->Modifyed_Walls[i].second.Wall_Number = *(p++);

	}

	len = *(p++);
	some_changes->New_Walls.resize(len);
	for (int i = 0; i < len; i++)
	{
		some_changes->New_Walls[i].Player_Number = *(p++);
		some_changes->New_Walls[i].Segment.A.x = *((double *)p);
		p = p + 2;
		some_changes->New_Walls[i].Segment.A.y = *((double *)p);
		p = p + 2;
		some_changes->New_Walls[i].Segment.B.x = *((double *)p);
		p = p + 2;
		some_changes->New_Walls[i].Segment.B.y = *((double *)p);
		p = p + 2;
		some_changes->New_Walls[i].Wall_Number = *(p++);
	}


	len = *(p++);
	some_changes->Placed_Bonuses.resize(len);
	for (int i = 0; i < len; i++)
	{
		some_changes->Placed_Bonuses[i].Bomb = *(p++);
		some_changes->Placed_Bonuses[i].Rocket = *(p++);
		some_changes->Placed_Bonuses[i].Point.x = *(p);
		p = p + 2;
		some_changes->Placed_Bonuses[i].Point.y = *(p);
		p = p + 2;
	}

	len = *(p++);
	some_changes->Collected_Bonuses.resize(len);
	for (int i = 0; i < len; i++)
	{
		some_changes->Collected_Bonuses[i] = *(p++);
	}



}



CServer::CServer(CGEngine * _game, Game_Engine *_ggame)
{

	fori(i, MAX_CLIENTS)
	{
		cSendNum[i] = 0;
		cRecvNum[i] = 0;
	}
	frameswtbonus = 0;

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

	gameFinish = false;
	game = _game;
	ggame = _ggame;
	cadr = 0;
	game_started = false;
	perm_to_connect = true;
	number_of_clients = 0;
	for (int i = 1; i < MAX_CLIENTS; i++)
	{
		clients[i].alive = false;
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
	frameswtbonus = 0;
	stepped = 0;


	cadr = 0;
	game_started = false;
	perm_to_connect = true;
	number_of_clients = 0;
	for (int i = 1; i < MAX_CLIENTS; i++)
	{
		clients[i].alive = false;
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



	void CServer::gotoframe(int mframe)
{
	double dt = 1.0f / 60.0f;
	int tostep;
	int startframe = stepped;
	tostep = mframe - stepped;
	for (int i = startframe; i < mframe; i++)
	{
		for (int j = 0; j < number_of_clients ; j++)
			if (act[j][i].received == true)
			{
				if (act[j][i].start_bomb == true)
					ggame->Bomb_Place(j);

				if (act[j][i].start_rocket == true)
					ggame->Rocket_Place(j);

				if (act[j][i].turn != NO_TURN)   //vovan << check here
					ggame->Player_Turn(j, act[j][i].turn == TURN_LEFT);
			}
			ggame->UPD(dt);
			frameswtbonus++;
			stepped++;
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
			msg.length = cSendNum[i]++;
			clients[i].addr = clients[j].addr;
			clients[i].number = j;
			clients[i].occupied = true;
			clients[j].occupied = false;
			sprintf(msg.buff, "%d", i);
			msg.sizeofmsg = 4;
			sendto(my_sock, (char *)&msg, sizeof(my_message) - BUFF_SIZE + msg.sizeofmsg, 0, (sockaddr *)&clients[i].addr, sizeof(sockaddr));
			break;
		}
	}
	for (int i = 1; i < MAX_CLIENTS; i++)
	{
		clients[i].alive = clients[i].occupied;
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
	for (int j = stepped + 1; j < stepped + 200; j++)
	{
		if (act[i][j].received == true)
			received[i] = 1;
		if ((act[i][j].received == true) && (max_frame[i] < j))
			max_frame[i] = j;
	}

	for (int i = 0; i < number_of_clients; i++)
	if ((mframe > max_frame[i]) && (clients[i+1].alive == true)) mframe = max_frame[i];


	
	if (mframe > stepped && !gameFinish)
	{
		gotoframe(mframe);

		if (frameswtbonus > FRAMES_PER_BONUS)
		{
			frameswtbonus = 0;
			ggame->Bonus_Place();
		}


		Changes acc;
		State nacc;

		ggame->Get_Changes_ACC(acc);
		ggame->Get_Changes_NACC(nacc);

	//	ggame->Update_Changes_ACC(acc);

		my_message msg;

		msg.cl_num = 0;
		msg.length = 0;
		msg.type = UPD_GAME_STATE_ACC;
		write_changes(&msg, &acc);
		broadcast(msg);

		msg.cl_num = 0;
		msg.length = 0;
		msg.pack_num = mframe;
		msg.type = UPD_GAME_STATE_NACC;
		write_state(&msg, &nacc, &ggame->Current_Game);
		broadcast(msg);

		for (int i = 0; i < number_of_clients; i++)
		{
			if (nacc.Players[i].Alive == false)
				clients[i+1].alive = false;
		}

		int win_team = -1;
		if (!(number_of_clients == 1 && clients[1].alive) && ggame->Game_Over(win_team))
		{
			gameFinish = true;
			msg.cl_num = win_team;
			msg.length = 0;
			msg.type = START_COUNTDOWN;
			*((int*)msg.buff) = COUNTDOWN_TIME;
			countTime = COUNTDOWN_TIME;
			msg.sizeofmsg = 4;
			broadcast(msg);
		}

		
		return true;
	}
	else if (gameFinish)
	{
		countTime--;
		Sleep(1000/60);
		if (countTime < 0)
		{
			startgame();
		}
	}
	return false;
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
						anws.sizeofmsg = 4;
						sendto(my_sock, (char *)&anws, sizeof(my_message) - BUFF_SIZE + anws.sizeofmsg, 0, (struct sockaddr *) &tempaddr, sizeof(tempaddr));
					}
					else
					{
						number_of_clients++;
						for (int i = 1; i < MAX_CLIENTS; i++)
						{
							if (clients[i].occupied == false)
							{
								clients[i].alive = true;
								clients[i].occupied = true;
								clients[i].packets_sended = 0;
								clients[i].addr = tempaddr;
								anws.type = ACCEPT_CONNECTION;
								sprintf(anws.buff, "%d", i);
								anws.cl_num = 0;
								anws.length = 4;
								anws.pack_num = 0;
								anws.sizeofmsg = 4;
								sendto(my_sock, (char *)&anws, sizeof(my_message) - BUFF_SIZE + anws.sizeofmsg, 0, (struct sockaddr *) &clients[i].addr, sizeof(tempaddr));
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
					anws.sizeofmsg = 4;
					broadcast(anws);
					clients[msg.cl_num].occupied = 0;
					clients[msg.cl_num].packets_sended = 0;
					clients[msg.cl_num].number = 0;
					clients[msg.cl_num].alive = false;
				}

				if (msg.type == PLAYER_ACTION)
				{
					int curfr;
					int * p = (int *)msg.buff;
					clients[msg.cl_num].count++;
					
					if (msg.length != cRecvNum[msg.cl_num]++)
					{
						cRecvNum[msg.cl_num] = msg.length + 1;
					}

					curfr = *(p++);
					act[msg.cl_num - 1][curfr].received = true;
					act[msg.cl_num - 1][curfr].start_bomb = *(p++);
					act[msg.cl_num - 1][curfr].start_rocket = *(p++);
					act[msg.cl_num - 1][curfr].turn = *(p++);
					msg.sizeofmsg = sizeof(Actions);
					broadcast(msg);
				}
			}
			
		if (game_started)
			check_frame();
		
		return true;
    }


    bool CServer :: broadcast(my_message msg)
    {
		int len = sizeof(clients[0].addr);
		for (int i = 1; i < MAX_CLIENTS; i++)
		{
			if (clients[i].occupied == true)
			{
				msg.length = cSendNum[i]++;
				sendto(my_sock, (char *) &msg, sizeof(my_message) - BUFF_SIZE + msg.sizeofmsg, 0, (sockaddr *)&clients[i].addr, len);
			}
		}
		return true;
    }

	int CServer::getPlCount()
	{
		return number_of_clients;
	}



	bool CServer::startgame()
	{


		if (number_of_clients < 1)
			return false;
		Line_up();

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
		frameswtbonus = 0;

		game_started = true;
		perm_to_connect = false;
		gameFinish = false;

		ggame->Current_Game.Clear();

		State beg_state;	//vovan << check here
		ggame->Start_Game(number_of_clients, beg_state);
		cadr = 0;
		stepped = 0;

//		ggame->Get_Changes_NACC( beg_state); 

		my_message msg;
		msg.cl_num = 0;
		msg.type = START_GAME;
		
		write_state(&msg, &beg_state, &ggame->Current_Game);

		broadcast(msg);
		return true;
	}


     CServer :: ~CServer()
     {
         closesocket(my_sock);
     }
