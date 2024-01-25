#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#define PORT 8000
#define IP "192.168.0.123"
int main(){
    int lfd=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in addr;
    addr.sin_port=htons(PORT);
    addr.sin_family=AF_INET;
    addr.sin_addr=htons(IP);
    bind()
    listen(lfd,64);
}