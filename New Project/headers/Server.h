#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED
#define MAX_CLIENTS 12

#define DISCONNECT 0
#define REGISTER_PLAYER 1
#define ACCEPT_CONNECTION 2
#define TEXT_MESSAGE 3
#define UPD_GAME_STATE_NACC 4
#define UPD_GAME_STATE_ACC 5
#define PLAYER_ACTION 6
#define CHANGE_IN_NUM 7
#define START_GAME 8
#define START_COUNTDOWN 9
#define GAME_RESTART 10

//typedef int type = {};


#define COUNTDOWN_TIME (60*4)
#define BUFF_SIZE 2800
#define FRAMES_PER_BONUS 100

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
	int sizeofmsg;
    char buff[BUFF_SIZE];

};

struct Actions
{
	bool received;
	int cadr;
	int turn;
	bool start_rocket;
	bool start_bomb;
};

struct client_info
{
    sockaddr_in addr;
	int count;
    int packets_sended;
    int number;
    bool occupied;
	bool alive;
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
	int frameswtbonus;
	int stepped, cSendNum[MAX_CLIENTS], cRecvNum[MAX_CLIENTS];
	Actions act[MAX_CLIENTS][100000];
	int last_frame_action[MAX_CLIENTS];

	CGEngine *game;
	Game_Engine *ggame;

	bool gameFinish;
	bool Line_up();
	int countTime;

public:

    CServer();
	CServer(CGEngine * _game, Game_Engine *_ggame);
	int getPlCount();
	bool startgame();
    bool think();
	void gotoframe(int);
	bool check_frame();
    bool broadcast(my_message);
    ~CServer();
};



#endif // SERVER_H_INCLUDED
