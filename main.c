#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define IPSTR "192.168.128.98"
#define PORT 80
#define BUFSIZE 1024

int main(int argc, char **argv) {
    int sockfd, ret, i, h;
    struct sockaddr_in servaddr;
    char str1[4096], buf[BUFSIZE];
    socklen_t len;
    fd_set   t_set1;
    struct timeval  tv;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
        printf("network connection failure, end this process---socket error!\n");
        exit(0);
    };

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, IPSTR, &servaddr.sin_addr) <= 0 ){
        printf("network connection failure, end this process----inet_pton error!\n");
        exit(0);
    };

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0){
        printf("failed to connect to server ---- connect error!\n");
        exit(0);
    }
    printf("connected to remote server\n");

    memset(str1, 0, 4096);
    strcat(str1, "GET /index.html?");
    strcat(str1, "Host: 192.168.128.98");
    strcat(str1, "Connection: keep-alive&");
    strcat(str1, "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8&");
    strcat(str1, "User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/43.0.2357.125 Safari/537.36&");
    strcat(str1, "Accept-Encoding: gzip, deflate, sdch&");
    strcat(str1, "Accept-Language: en-GB,en;q=0.8,en-US;q=0.6,zh-CN;q=0.4,zh;q=0.2,zh-TW;q=0.2,ja;q=0.2,de;q=0.2,fr;q=0.2&");
    strcat(str1, "Content-Length: ");
    //strcat(str1, "\n\n");
    strcat(str1, "\r\n\r\n");
    printf("%s\n",str1);

    ret = write(sockfd, str1, strlen(str1));
    if (ret < 0) {
        printf("failed to send！error code: %d， error msg: '%s'\n", errno, strerror(errno));
        exit(0);
    }else{
        printf("successfully send data，bytes in total: %d！\n\n", ret);
    }

    FD_ZERO(&t_set1);
    FD_SET(sockfd, &t_set1);

    while(1){
        sleep(2);
        tv.tv_sec= 0;
        tv.tv_usec= 0;
        h = 0;
        printf("--------------->1");
        h= select(sockfd +1, &t_set1, NULL, NULL, &tv);
        printf("--------------->2");

        if (h == 0) continue;

        if (h < 0) {
            close(sockfd);
            printf("this process is ended, caused by: SELECT detected exceptions when reading packets\n");
            return -1;
        };

        if (h > 0){
            memset(buf, 0, 4096);
            i= read(sockfd, buf, 4096);
            if (i==0){
                close(sockfd);
                printf("this process is ended, caused by: remote side is closed when reading packets\n");
                return -1;
            }
            printf("%s\n", buf);
        }
    }
    close(sockfd);


    return 0;
}
