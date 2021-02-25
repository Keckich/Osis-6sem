void response_udp(int &sockfd, sockaddr_in &cliaddr, char buffer[]);
void response_tcp(int &sockfd, sockaddr_in &servaddr, sockaddr_in cliaddr);
void tcp_connect(int &sockfd, int opt, sockaddr_in &servaddr);
void udp_connect(int &sockfd, int opt, sockaddr_in &servaddr);
int max(int x, int y);
void start_server();
