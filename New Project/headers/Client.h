#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED
#include "..\headers\Server.h"


class CClient
{
private:
    SOCKET my_sock;
    sockaddr_in serv_addr;
    bool connected;
    my_message msg, msg_anw;

public:
    CClient();
    bool connect(const char *ip);
    ~CClient();


};


#endif // CLIENT_H_INCLUDED
