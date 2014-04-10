#ifndef SERVER_H_INCLUDED
#define SERVER_H_INCLUDED
#define MAX_CLIENTS 12

#define DISCONNECT 0
#define REGISTER_PLAYER 1
#define ACCEPT_CONNECTION 2
#define TEXT_MESSAGE 3
#define HEEE 4


//typedef int type = {};

struct my_message
{
    int type;
    int cl_num;
    int pack_num;
    int length;
    char buff[1024];

};

struct client_info
{
    sockaddr_in addr;
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
    bool perm_to_connect;

public:

    CServer();
    bool think();
    bool broadcast();
    ~CServer();
};



#endif // SERVER_H_INCLUDED
