#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED
#define MAX_CLIENTS 12

#define DISCONNECT 0
#define REGISTER_PLAYER 1
#define ACCEPT_CONNECTION 2
#define TEXT_MESSAGE 3
#define UPD_GAME_STATE_NACC 4
#define UPD_GAME_STATE_ACC 6
#define PLAYER_ACTION 6
#define CHANGE_IN_NUM 7
#define START_GAME 8


//typedef int type = {};

class CGEngine;
class Game_Engine;

struct changes;
struct state;

struct my_message
{
    int type;
    int cl_num;
    int pack_num;
    int length;
    char buff[1024];

};

struct Actions
{
	int cadr;
	int turn;
	bool start_rocket;
	bool start_bomb;
};

struct client_info
{
    sockaddr_in addr;
	Actions my_actions[100];
	int count;
    int packets_sended;
    int number;
    bool occupied;
};



class CServer
{
private:

    SOCKET my_sock;
    sockaddr_in myaddr;
    client_info clients[MAX_CLIENTS];
    int number_of_clients;
	bool game_started;
    bool perm_to_connect;
	int cadr;
	int stepped;

	CGEngine *game;
	Game_Engine *ggame;


	bool Line_up();


public:

    CServer();
	CServer(CGEngine * _game, Game_Engine *_ggame);
	bool startgame();
    bool think();
    bool broadcast(my_message);
    ~CServer();
};



#endif // SERVER_H_INCLUDED
