#ifndef REACTOR_H
#define REACTOR_H
#include"tcp.h"
#include<cstdio>
#include<unistd.h>
#include<cstdlib>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/errno.h>
#include<string.h>
#include<sys/epoll.h>
#include<stdarg.h>
#include<map>
#include<set>

enum REACTOR_ERROR_TYPE{
    ERROR_TYPE_OK       =   0   ,
    ERROR_TYPE_ERROR            ,
    ERROR_TYPE_CONTINUE         ,
    ERROR_TYPE_FINISH           ,
    ERROR_TYPE_TEST_CONTINUE    ,
    ERROR_TYPE_TEST_DONE        ,
};

class ReactorInterface{
public:
    virtual REACTOR_ERROR_TYPE InputProcess(int clntfd)=0;
    virtual REACTOR_ERROR_TYPE OutputProcess(int clntfd)=0;
    virtual REACTOR_ERROR_TYPE HangupProcess(int clntfd)=0;
    virtual REACTOR_ERROR_TYPE CheackClientProcess(sockaddr_in* clnt_addr,int clntfd)=0;
//    virtual ~ReactorInterface(){}
    friend class Reactor;
};

class Reactor
{
public:
    Reactor();
public:
    friend class ReactorObject;
    virtual ~Reactor();
    int init(int maxPoller);
    int bind(const int sockfd);
    int bind(ReactorInterface& tcp_tmp);
    int runEventLoop();
    void WaitEpollEvents();
    void delete_event(int fd,int state);
    void add_event(int fd,int state = EPOLLIN);
    void modify_event(int fd,int state = EPOLLOUT);

public:
//    virtual void InputProcess(void);
//    virtual void OutputProcess(void);
//    virtual void ConnectProcess(void);
private:
    int _epfd,_nfds;
    int _maxPoller;
    epoll_event ev;
    epoll_event* events;

    int _sockfd;
    ReactorInterface* _binder;
};

#endif // REACTOR_H
