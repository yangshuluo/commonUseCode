#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h> /* See NOTES */
#include <unistd.h>

#define IP "127.0.0.1"
#define PORT "9212"

int main(int argc, char** argv) {
    int s_fd;
    int c_fd;
    int n_read;
    int mark = 0;

    char readBuf[128];
    char msg[128] = { 0 };

    struct sockaddr_in s_addr;
    struct sockaddr_in c_addr;

    memset(&s_addr, 0, sizeof(struct sockaddr_in));  //清空s_addr
    memset(&c_addr, 0, sizeof(struct sockaddr_in));  //清空c_addr

    s_fd = socket(AF_INET, SOCK_STREAM, 0);  //创建套接字

    if (s_fd == -1)  //判断是否创建成功
    {
        perror("socket");
        exit(-1);
    }
    s_addr.sin_family = AF_INET;            //赋值协议
    s_addr.sin_port   = htons(atoi(PORT));  //字节序小端转大端
    inet_aton(IP, &s_addr.sin_addr);        //将IP地址转化网络能识别的格式

    bind(s_fd, ( struct sockaddr* )&s_addr, sizeof(struct sockaddr_in));  //将IP等信息录入其中

    listen(s_fd, 10);  //监听请求

    socklen_t clen = sizeof(struct sockaddr_in);
    while (1) {
        c_fd = accept(s_fd, ( struct sockaddr* )&c_addr, &clen);  //接受请求

        if (c_fd != -1)  //判断是否接受成功
        {
            perror("accept");
        }
        printf("get connect:%s\n", inet_ntoa(c_addr.sin_addr));  //打印本机IP地址

        if (fork() == 0) {  //建立父子进程

            if (fork() == 0) {

                while (1) {
                    sprintf(msg, "welcome NO.%d client\n", mark);
                    write(c_fd, msg, strlen(msg));  //写数据
                    sleep(3);
                }
            }

            while (1) {
                memset(readBuf, 0, sizeof(readBuf));  //清空读区

                n_read = read(c_fd, readBuf, 256);  //读取数据

                if (n_read == -1)  //判断是否读取成功
                {
                    perror("read");
                }
                else {
                    printf("get message:%d,%s\n", n_read, readBuf);
                }
            }
            break;
        }
    }
    return 0;
}