#include "..\headers\Client.h"
#include "..\headers\Server.h"
#include "stdafx.h"


void init_network()
{
    WORD ver = MAKEWORD(2,2);
    WSADATA wsaData;

    WSAStartup(ver,(LPWSADATA)&wsaData);
}



CClient :: CClient()
{
     connected = 0;
}


int CClient::get_num()
{
	return my_num;
}


bool CClient :: connect(const char *ip)
{
    my_sock = socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    u_long iMode=1;
    ioctlsocket(my_sock, FIONBIO, &iMode);
    if (my_sock == INVALID_SOCKET)
    {
        perror("socket");
    }

    memset((char *)&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_port = htons(8400);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ip);

    anyaddr.sin_port = htons(9400);
    anyaddr.sin_family = AF_INET;
    anyaddr.sin_addr.s_addr = INADDR_ANY;

    if( bind(my_sock,(sockaddr *) &anyaddr, sizeof(serv_addr)) == -1)
    {
        perror("bind");
        exit(1);
    }

    msg.cl_num = 0;
    msg.type = REGISTER_PLAYER;
    msg.pack_num = 0;
    msg.length = 0;
    int len = sizeof(sockaddr_in);
    int msg_size;

    sendto(my_sock,(char *) &msg, sizeof(my_message), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    while((msg_size = recvfrom(my_sock, (char*) &msg, sizeof(my_message), 0, (struct sockaddr *) &anyaddr, &len)) == -1)
    {
    }
    if(msg_size > 0){
        if(msg.type == ACCEPT_CONNECTION)
        {
            connected = 1;
            sscanf( msg.buff, "%d", &my_num);
            printf("%d ",msg_size);
            return true;
        }

        if(msg.type == DISCONNECT)
            return false;
    }
  //  recvfrom(my_sock,
}


CClient:: ~CClient()
{
    closesocket(my_sock);
}

