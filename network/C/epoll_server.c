#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <errno.h>

#define PORT 8000
#define IP "192.168.1.41"

struct sockaddr_in addr;

/*
实现epoll水平触发下的消息回射
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
    struct epoll_event event,events[1024];
    event.data.fd=lfd;
    event.events=EPOLLIN;
    int epoll=epoll_create(100);
    epoll_ctl(epoll,EPOLL_CTL_ADD,lfd,&event);
    while(1){
        int cnt=epoll_wait(epoll,events,sizeof(events)/sizeof(event),-1);
        if(cnt<0) {
            perror("epoll监听异常");
            exit(-1);
        }
        for(int i=0;i<cnt;i++){
            int fd=events[i].data.fd;
            if(fd==lfd){
                len=sizeof(addr);
                int cfd=accept(fd,(struct sockaddr *)&addr,&len);
                if(cfd<0) {
                    perror("接收到异常的连接请求");
                    exit(-1);
                }
                event.data.fd=cfd;
                event.events=EPOLLIN;
                epoll_ctl(epoll,EPOLL_CTL_ADD,cfd,&event);
            }
            else{
                int ret=read(fd,message,sizeof(message));
                if(ret<0) {
                    perror("读取数据异常");
                    exit(-1);
                }
                else if(!ret){
                    close(fd);
                    epoll_ctl(epoll,EPOLL_CTL_DEL,fd,NULL);
                }
                write(fd,message,ret);
            }
        }
    }
}