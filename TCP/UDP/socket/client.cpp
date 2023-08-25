#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <poll.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>

const std::string SERVER_ADDRRSS = { "127.0.0.1" };
const int         SERVER_PORT    = 9212;
const std::string SEND_DATA      = { "helloWorld" };

int main( int argc, char* argv[] ) {
    int clientfd = socket( AF_INET, SOCK_STREAM, 0 );
    if ( clientfd == -1 ) {
        std::cout << "creat client socket error." << std::endl;
        return -1;
    }

    // 将clientfd设置成非阻塞模式
    int oldSocketFlag = fcntl( clientfd, F_GETFL, 0 );
    int newSocketFlag = oldSocketFlag | O_NONBLOCK;
    if ( fcntl( clientfd, F_SETFL, newSocketFlag ) == -1 ) {
        close( clientfd );
        std::cout << "set socket to nonblock error." << std::endl;
        return -1;
    }

    // 连接服务器
    struct sockaddr_in serveraddr;
    serveraddr.sin_family      = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr( SERVER_ADDRRSS.c_str() );
    serveraddr.sin_port        = htons( SERVER_PORT );
    for ( ;; ) {
        int ret = connect( clientfd, ( struct sockaddr* )&serveraddr, sizeof( serveraddr ) );
        if ( ret == 0 ) {
            std::cout << "connect to server successfully." << std::endl;
            close( clientfd );
            return 0;
        }
        else if ( ret == -1 ) {
            if ( errno == EINTR ) {
                // connect动作信号被中断，重试connect
                std::cout << "connecting interruptted by signal, try again." << std::endl;
                continue;
            }
            else if ( errno == EINPROGRESS ) {
                // 连接正在尝试中
                break;
            }
            else {
                // 出错
                close( clientfd );
                return -1;
            }
        }
    }
    pollfd event;
    event.fd     = clientfd;
    event.events = POLLOUT;
    int timeout  = 3000;
    if ( poll( &event, 1, timeout ) != 1 ) {
        close( clientfd );
        std::cout << "[poll] connect to server error." << std::endl;
        return -1;
    }

    if ( !( event.revents & POLLOUT ) ) {
        close( clientfd );
        std::cout << "[POLLOUT] connect to server error." << std::endl;
        return -1;
    }

    int       err;
    socklen_t len = static_cast< socklen_t >( sizeof err );
    if (::getsockopt( clientfd, SOL_SOCKET, SO_ERROR, &err, &len ) < 0 ) {
        return -1;
    }
    if ( err == 0 ) {
        std::cout << "connect to server successfully." << std::endl;
    }
    else {
        std::cout << "connect to server error." << std::endl;
    }
    close( clientfd );
    return 0;
}