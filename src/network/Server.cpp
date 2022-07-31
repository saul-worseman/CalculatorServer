#include"Server.h"

#include <stdio.h> 
#include <string.h>   //strlen 
#include <stdlib.h> 
#include <errno.h> 
#include <unistd.h>   //close 
#include <arpa/inet.h>    //close 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros 
     
#define TRUE   1 
#define FALSE  0 
#define PORT 8080

const int maxClients = 30;

void Server::start(int port){   
    char buffer[1025];  //data buffer of 1K 
         
    //set of socket descriptors 
    fd_set readfds;  
     
    //initialise all client_socket[] to 0 so not checked
    int clientSocket[30]; 
    for (int i = 0; i < maxClients; i++){  
        clientSocket[i] = 0;  
    }  
         
    //create a master socket
    int masterSocket; 
    if( (masterSocket = socket(AF_INET, SOCK_STREAM, 0)) == 0){  
        perror("socket failed");  
        exit(EXIT_FAILURE);  
    }  
     
    //set master socket to allow multiple connections , 
    //this is just a good habit, it will work without this 
    int opt = TRUE; 
    if(setsockopt(masterSocket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt)) < 0 )  {  
        perror("setsockopt");  
        exit(EXIT_FAILURE);  
    }  
     
    //type of socket created
    struct sockaddr_in address; 
    address.sin_family = AF_INET;  
    address.sin_addr.s_addr = INADDR_ANY;  
    address.sin_port = htons( PORT );  
         
    //bind the socket to localhost port 8080
    if (bind(masterSocket, (struct sockaddr *)&address, sizeof(address))<0)  {  
        perror("bind failed");  
        exit(EXIT_FAILURE);  
    }  
    printf("Listener on port %d \n", PORT);  
         
    //try to specify maximum of 3 pending connections for the master socket 
    if (listen(masterSocket, 3) < 0)  {  
        perror("listen");  
        exit(EXIT_FAILURE);  
    }  
         
    //accept the incoming connection
    int addrlen = sizeof(addrlen); 
    puts("Waiting for connections ...");  

    int SocketDescriptorNum = 0;
    Logger logger;
    while(true){  
        //clear the socket set 
        FD_ZERO(&readfds);  
     
        //add master socket to set 
        FD_SET(masterSocket, &readfds);  
        SocketDescriptorNum = masterSocket;  
             
        //add child sockets to set 
        for (int i = 0 ; i < maxClients ; i++){  
            //socket descriptor 
            int socketDescriptor = clientSocket[i];  
                 
            //if valid socket descriptor then add to read list 
            if(socketDescriptor > 0){  
                FD_SET(socketDescriptor, &readfds);  
            }
                 
            //highest file descriptor number, need it for the select function 
            if(socketDescriptor > SocketDescriptorNum){  
                SocketDescriptorNum = socketDescriptor;
            }  
        }  
     
        //wait for an activity on one of the sockets , timeout is NULL , 
        //it will wait indefinitely 
        int activity = select(SocketDescriptorNum + 1 , &readfds , NULL , NULL , NULL);  
       
        if ((activity < 0) && (errno != EINTR)){  
            printf("select error");  
        }  
             
        //If something happened on the master socket , 
        //then its an incoming connection 
        if (FD_ISSET(masterSocket, &readfds)){
            int newSocket;  
            if ((newSocket = accept(masterSocket, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0){  
                perror("accept");  
                exit(EXIT_FAILURE);  
            }  
             
            //inform user of socket number - used in send and receive commands 
            printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , newSocket , inet_ntoa(address.sin_addr) , ntohs(address.sin_port));  
                 
            // puts("Welcome message sent successfully");  
                 
            //add new socket to array of sockets 
            for (int i = 0; i < maxClients; i++){  
                //if position is empty 
                if(clientSocket[i] == 0){  
                    clientSocket[i] = newSocket;  
                    printf("Adding to list of sockets as %d\n" , i);  
                    break;  
                }  
            }  
        }  
             
        //else its some IO operation on some other socket
        for (int i = 0; i < maxClients; i++){  
            int socketDescriptor = clientSocket[i];  
                 
            if (FD_ISSET(socketDescriptor , &readfds)){  
                //Check if it was for closing , and also read the incoming message 
                int valread;
                if ((valread = read(socketDescriptor , buffer, 1024)) == 0){  
                    //Somebody disconnected , get his details and print 
                    getpeername(socketDescriptor , (struct sockaddr*)&address, (socklen_t*)&addrlen);  
                    printf("Host disconnected , ip %s , port %d \n", inet_ntoa(address.sin_addr), ntohs(address.sin_port));  
                         
                    //Close the socket and mark as 0 in list for reuse 
                    close(socketDescriptor);  
                    clientSocket[i] = 0;  
                }
                     
                //send back the message
                else{  
                    //set the string terminating NULL byte on the end of the data read 
                    buffer[valread] = '\0';
                    string request(buffer);
                    Message message = this->parseRequest(request);
                    string ans = this->processMessage(message);
                    logger.log(request, inet_ntoa(address.sin_addr) , ntohs(address.sin_port));  
                    send(socketDescriptor, ans.c_str(), strlen(buffer), 0);  
                }  
            }  
        }  
    }  
        
}