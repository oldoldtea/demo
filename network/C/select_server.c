#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <errno.h>
#include <sys/time.h>

#define PORT 8000
#define IP "192.168.1.41"

struct sockaddr_in addr;

/*
实现select水平触发下的消息回射
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
    fd_set all,cur;
    FD_ZERO(&all);
    FD_ZERO(&cur);
    FD_SET(lfd,&all);
    int nfd=lfd+1;
    while(1){
        cur=all;
        int cnt=select(nfd,&cur,NULL,NULL,NULL);
        if(cnt<0){
            perror("select监听异常");
            exit(1);
        }
        if(FD_ISSET(lfd,&cur)&&cnt--){
            len=sizeof(addr);
            int cfd=accept(lfd,(struct sockaddr *)&addr,&len);
            if(cfd<0){
                perror("接收到异常的连接");
                exit(1);
            }
            FD_SET(cfd,&all);
            if(nfd<=cfd+1) nfd=cfd+1;
            cnt--;
        }
        for(int i=lfd+1;i<nfd&&cnt;i++){
            if(FD_ISSET(i,&cur)){
                int ret=read(i,message,sizeof(message));
                if(ret<0){
                    perror("读取数据异常");
                    exit(1);
                }
                else if(!ret){
                    close(i);
                    FD_CLR(i,&all);
                }
                write(i,message,ret);
                cnt--;
            }
        }
    }
}