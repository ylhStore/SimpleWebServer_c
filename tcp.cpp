#include "tcp.h"

Tcp::Tcp()
{

}
Tcp::~Tcp()
{
    close(_netfd);
}

int Tcp::bind()
{
    int flag;
    int reuse_addr = 1;

    setsockopt(_netfd,SOL_SOCKET,SO_REUSEADDR,&reuse_addr,sizeof(reuse_addr));
    setsockopt(_netfd,SOL_TCP,TCP_DEFER_ACCEPT,&reuse_addr,sizeof(reuse_addr));
    setsockopt(_netfd,SOL_TCP,TCP_NODELAY,&reuse_addr,sizeof(reuse_addr));

    flag = ::bind(_netfd,(sockaddr*)&serv_addr,sizeof(serv_addr));
    if(flag < 0)
    {
        perror("bind error! \n");
        return -1;
    }
    printf("bind successful\n");

    flag = listen(_netfd,_backlog);
    if(flag < 0)
    {
        perror("listen error ! \n");
        return -1;
    }
    printf("listen successful\n");
    return 1;
}

void Tcp::init(in_addr_t ip, int port, int backlog)
{
    _str_ip = "";
    _port = port;
    _backlog = backlog;
    _netfd = socket(AF_INET,SOCK_STREAM,0);
    _in_ip = htonl(ip);
    if(_netfd < 0)
    {
        perror("socket error !\n");
        return;
    }
    bzero(&serv_addr,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(_port);
    serv_addr.sin_addr.s_addr = _in_ip;

}

void Tcp::init(string ip, int port, int backlog)
{
    _str_ip = ip;
    _port = port;
    _backlog = backlog;
    _netfd = socket(AF_INET,SOCK_STREAM,0);
    _in_ip = -1;
    if(_netfd < 0)
    {
        perror("socket error !\n");
        return;
    }
    bzero(&serv_addr,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(_port);
    if(inet_aton(ip.c_str(),(in_addr*)&serv_addr.sin_addr.s_addr) < 0)
    {
        printf("inet_aton error ! ip[%s]\n",ip.c_str());
    }
}
