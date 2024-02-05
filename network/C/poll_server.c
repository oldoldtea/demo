#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <poll.h>
#include <errno.h>
#include <sys/time.h>

#define MAX 1000
#define PORT 8000
#define IP "192.168.1.41"

struct sockaddr_in addr;

/*
实现poll水平触发下的消息回射
*/

int init(){
    int lfd=socket(AF_INET,SOCK_STREAM,0);
    addr.sin_port=htons(PORT);
    addr.sin_family=AF_INET;
    inet_pton(AF_INET,IP,&addr.sin_addr);
    bind(lfd,(const struct sockaddr *)&addr,sizeof(addr));
    listen(lfd,64);
    return lfd;
}

int main(){
    socklen_t len;
    char message[1024];
    int lfd=init();
    struct pollfd p[MAX];
    for(int i=0;i<MAX;i++) p[i].fd=-1;
    p[0].fd=lfd;
    p[0].events=POLLIN;
    int nfd=1;
    while(1){
        int cnt=poll(p,nfd,-1);
        if(cnt<0){
            perror("poll监听异常");
            exit(1);
        }
        if(p[0].revents&POLLIN&&cnt--){
            len=sizeof(addr);
            int cfd=accept(lfd,(struct sockaddr *)&addr,&len);
            if(cfd<0){
                perror("接收到异常的连接");
                exit(1);
            }
            for(int i=1;i<MAX;i++){
                if(p[i].fd==-1){
                    p[i].fd=cfd;
                    p[i].events=POLLIN;
                    if(nfd<i+1) nfd=i+1;
                    break;
                }
            }
        }
        for(int i=1;i<nfd&&cnt;i++){
            if(p[i].fd==-1) continue;
            if(p[i].revents&POLLIN){
                int ret=read(p[i].fd,message,sizeof(message));
                if(ret<0){
                    perror("读取数据异常");
                    exit(1);
                }
                else if(!ret){
                    close(p[i].fd);
                    p[i].fd=-1;
                    p[i].events=0;
                }
                write(p[i].fd,message,ret);
                cnt--;
            }
        }
    }
}