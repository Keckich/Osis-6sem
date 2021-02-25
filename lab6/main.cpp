#include <syslog.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
#include <unistd.h>
#include "server.h"
#include "daemon.h"


int main() { 
    start_daemon();
    start_server();
    return 0; 
} 



