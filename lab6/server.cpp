#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <iostream>
#include "server.h"

using namespace std;
  
#define PORT    7
#define MAXLINE 1024 


void response_udp(int &sockfd, sockaddr_in &cliaddr, char buffer[]) {
    socklen_t len = sizeof(cliaddr); //len is value/resuslt  
    int n; 
    string hello;
    n = recvfrom(sockfd, (char*)buffer, MAXLINE,  
                MSG_WAITALL, (struct sockaddr *) &cliaddr, 
                &len); 
    buffer[n] = '\0'; 
    cout<<endl<<"Client: "<<(char*)buffer<<endl;
    hello = buffer;
    sendto(sockfd, hello.c_str(), hello.length(),  
        MSG_CONFIRM, (const struct sockaddr *) &cliaddr, 
            len); 
    cout<<"Server response(udp) sent."<<endl;
    
}

void response_tcp(int &sockfd, sockaddr_in &servaddr, sockaddr_in cliaddr) {
    string hello;
    char buffer[MAXLINE];
    socklen_t len = sizeof(cliaddr);
    //cout<<endl<<"INRESPONSE"<<endl;
    int new_socket = accept(sockfd, (struct sockaddr *)&cliaddr,  
                        &len);
    //cout<<"after newsocket"<<endl;
    bzero(buffer, sizeof(buffer));
    //bzero(buffer, sizeof(buffer));
    read(new_socket, buffer, sizeof(buffer)); 
    //cout<<"after reading"<<endl;
        
    //cout<<endl<<"Client: "<<(char*)buffer<<endl;
    printf("Client: %s", buffer);
    //hello = buffer;
    //send(new_socket, hello.c_str(), hello.length(), 0); 
    //write(new_socket, hello.c_str(), hello.length());
    write(new_socket, buffer, sizeof(buffer));
    cout<<"Server response(tcp) sent."<<endl;
    close(new_socket);   
    //close(sockfd);
    
}

void tcp_connect(int &sockfd, int opt, sockaddr_in &servaddr) {
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == 0) { 
        perror("socket failed"); 
        exit(EXIT_FAILURE); 
    } 
       
    // Forcefully attaching socket to the port 8080 
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, 
                                                  &opt, sizeof(opt))) { 
        perror("setsockopt"); 
        exit(EXIT_FAILURE); 
    } 
    else {
        cout<<"Socket created successfully!"<<endl;
    }   
       
    // Forcefully attaching socket to the port 8080 
    if (bind(sockfd, (struct sockaddr *)&servaddr,  
                                 sizeof(servaddr))<0) { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    else {
        cout<<"Bind was successfull!"<<endl;
    }
    if (listen(sockfd, 3) < 0) { 
        perror("listen"); 
        exit(EXIT_FAILURE); 
    } 
    else {
        cout<<"Listening..."<<endl;
    }
}

void udp_connect(int &sockfd, int opt, sockaddr_in &servaddr) {
     
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("Socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
    else {
        cout<<"Socket created successfully!"<<endl;
    }
  
   
    
    if (setsockopt (sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof (opt)) == -1) {
        perror("setsockopt");
        exit(EXIT_FAILURE); 
    }


    // Bind the socket with the server address 
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,  
            sizeof(servaddr)) < 0 ) { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
    else {
        cout<<"Bind was successfull!"<<endl;
    }

    
}

int max(int x, int y) 
{ 
    return (x > y) ? x : y;
} 

// Driver code 
void start_server() { 
    int sock_tcp, sock_udp, new_socket; 
    struct sockaddr_in servaddr, cliaddr; 
    int opt = 1; 
    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 
      
    // Filling server information 
    servaddr.sin_family    = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
    servaddr.sin_port = htons(PORT);
    
    
    char buffer[MAXLINE]; 
    
    udp_connect(sock_udp, opt, servaddr);
    tcp_connect(sock_tcp, opt, servaddr);
    
    fd_set rfd;
    FD_ZERO(&rfd);
    int maxfdp1 = max(sock_tcp, sock_udp) + 1;
    while (true) {
        
        FD_SET(sock_tcp, &rfd);
        FD_SET(sock_udp, &rfd);

        int ret = select(maxfdp1, &rfd, NULL, NULL, NULL);
        if (FD_ISSET(sock_tcp, &rfd)) {
            //cout<<endl<<"IN TCP IF"<<endl;
            response_tcp(sock_tcp, servaddr, cliaddr); 
        }
        if (FD_ISSET(sock_udp, &rfd)) {
            //cout<<endl<<"IN UDP IF"<<endl;
            response_udp(sock_udp, cliaddr, buffer);
        }
    }
    close(sock_tcp);
    return; 
} 



