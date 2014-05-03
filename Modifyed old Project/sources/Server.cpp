#include "..\headers\Client.h"
#include "..\headers\Server.h"






    CServer :: CServer()
    {

        number_of_clients = 0;
        for(int i = 1; i < MAX_CLIENTS; i++)
        {
            clients[i].number = i;
            clients[i].occupied = false;
            clients[i].packets_sended = 0;
        }
        my_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        if (my_sock == INVALID_SOCKET)
          {
              perror("socket");
          }

        memset((char *) &myaddr, 0, sizeof(myaddr));
        myaddr.sin_family = AF_INET;
        myaddr.sin_port = htons(6400);
        myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
        if (bind(my_sock ,(const sockaddr *) &myaddr, sizeof(myaddr)) == -1)
        {
            perror("bind");
        }

    }
    bool CServer :: think()
    {
            sockaddr_in tempaddr;
            int slen;
            my_message msg, anws;
            if (recvfrom(my_sock,(char *) &msg, sizeof(my_message), 0, (sockaddr *)&tempaddr, &slen) == -1)
            {
             perror("recfrom");
            }

            if(msg.type == REGISTER_PLAYER)
            {
                if(number_of_clients == MAX_CLIENTS - 1)
                {
                    anws.type = DISCONNECT;
                    sprintf(anws.buff, "Server is full");
                    anws.cl_num = 0;
                    anws.length = sizeof("Server is full");
                    anws.pack_num = 0;
                    sendto(my_sock,(char *) &anws, sizeof(my_message), 0, (struct sockaddr *) &tempaddr, sizeof(tempaddr));
                    return true;
                }

                number_of_clients++;
                for(int i = 1; i< MAX_CLIENTS; i++)
                    {
                        if(clients[i].occupied == false)
                        {
                            clients[i].occupied = true;
                            clients[i].packets_sended = 0;
                            clients[i].addr = tempaddr;
                            break;
                        }
                    }
            }



        return true;
    }


    bool CServer :: broadcast()
    {

    }


     CServer :: ~CServer()
     {
         closesocket(my_sock);
     }
