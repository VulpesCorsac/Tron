#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED
#include "Server.h"

#define TURN_RIGHT 1
#define TURN_LEFT 2
#define NO_TURN 0


class CGEngine;
class Game_Engine;

struct state;
struct changes;

void init_network();




class CClient
{
private:
    SOCKET my_sock;
    sockaddr_in serv_addr, anyaddr;
    bool connected;
	bool game_started;
    my_message msg, msg_anw;
	int my_num;
	long long cadr;
	long long stepped;
	CGEngine *game;
	Game_Engine *ggame;

	bool check_for_actions(Actions *);

public:

	//also, put here a func to get Game for rendering

	CClient();
	CClient(CGEngine * _game, Game_Engine *ggame);
	bool think();
	int get_num();
	int getPID();	//get player id	----------- TO DO, vovan
    bool connect(const char *ip);
    ~CClient();



};


#endif // CLIENT_H_INCLUDED
