#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED
#define MAX_CLIENTS 12

#define DISCONNECT 0
#define REGISTER_PLAYER 1
#define ACCEPT_CONNECTION 2
#define TEXT_MESSAGE 3
#define UPD_GAME_STATE 4
#define PLAYER_ACTION 5
#define VOVAN 6


//typedef int type = {};

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
    int packets_sended;
    int number;
    bool occupied;
	Actions a;
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
	long long cadr;
	long long stepped;


public:

    CServer();
	bool startgame();
    bool think();
    bool broadcast(my_message);
    ~CServer();
};



#endif // SERVER_H_INCLUDED
