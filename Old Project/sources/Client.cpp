#include "..\headers\Client.h"
#include "..\headers\Server.h"


CClient :: CClient()
{
     connected = 0;
}

bool CClient :: connect(const char *ip)
{
    my_sock = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (my_sock == INVALID_SOCKET)
    {
        perror("socket");
    }

    memset((char *)&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_port = htons(6400);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ip);

    if( bind(my_sock,(sockaddr *) &serv_addr, sizeof(serv_addr)) == -1)
    {
        perror("bind");
        exit(1);
    }

    msg.cl_num = 0;
    msg.type = REGISTER_PLAYER;
    msg.pack_num = 0;
    msg.length = 0;

    int len;
    sockaddr_in anyaddr;

    anyaddr.sin_port = htons(6400);
    anyaddr.sin_family = AF_INET;
    anyaddr.sin_addr.s_addr = inet_addr(INADDR_ANY);

    sendto(my_sock,(char *) &msg, sizeof(my_message), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    recvfrom(my_sock, (char*) &msg, sizeof(my_message), 0, (struct sockaddr *) &anyaddr, &len);
  //  recvfrom(my_sock,
}


CClient:: ~CClient()
{
    closesocket(my_sock);
}

