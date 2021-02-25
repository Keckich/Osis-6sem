#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <iostream>

using namespace std;

#define PORT    7
#define MAXLINE 1024 
  
// Driver code 
int main(int argc, char** argv) { 
    int sockfd; 
    //string buffer;
    char buffer[MAXLINE]; 
    string hello = argv[1]; 
    struct sockaddr_in     servaddr; 
  
    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("Socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
    else {
        cout<<"Socket created successfully!"<<endl;
    }
  
    memset(&servaddr, 0, sizeof(servaddr)); 
      
    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = INADDR_ANY; 
      
    socklen_t len;
    int n; 
      
    sendto(sockfd, hello.c_str(), hello.length(), 
        MSG_CONFIRM, (const struct sockaddr *) &servaddr,  
            sizeof(servaddr)); 
    cout<<"Your message sent."<<endl; 
          
    n = recvfrom(sockfd, (char*)buffer, MAXLINE,  
                MSG_WAITALL, (struct sockaddr *) &servaddr, 
                &len); 
    buffer[n] = '\0'; 
    cout<<"Server: "<<buffer<<endl;
    //printf("Server : %s\n", buffer); 
  
    close(sockfd); 
    return 0; 
} 