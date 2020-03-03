#include "reactor.h"

Reactor::Reactor()
{

}
void Reactor::delete_event(int fd, int state)
{
    ev.data.fd = fd;
    ev.events = state | EPOLLET;
    epoll_ctl(_epfd,EPOLL_CTL_DEL,fd,&ev);
}

void Reactor::add_event(int fd, int state)
{
    ev.data.fd = fd;
    ev.events = state | EPOLLET;
    epoll_ctl(_epfd,EPOLL_CTL_ADD,fd,&ev);
}

void Reactor::modify_event(int fd, int state)
{
    ev.data.fd = fd;
    ev.events = state | EPOLLET;
    epoll_ctl(_epfd,EPOLL_CTL_MOD,fd,&ev);
}

int Reactor::bind(const int sockfd){
    _sockfd = sockfd;
    ev.data.fd = _sockfd;
    ev.events = EPOLLET | EPOLLIN;
    epoll_ctl(_epfd,EPOLL_CTL_ADD,_sockfd,&ev);
}

int Reactor::bind(ReactorInterface& binder)
{
    _binder = &binder;
//    bind(_binder.getNetfd());
}

int Reactor::init(int maxPoller)
{
    _maxPoller = maxPoller;
    _epfd = epoll_create(_maxPoller);
    _nfds = -1;
    events = (epoll_event*)calloc(_maxPoller,sizeof(epoll_event));
    return 1;
}

Reactor::~Reactor()
{
    close(_sockfd);
    close(_epfd);
    free(events);
}

void Reactor::WaitEpollEvents()
{
    _nfds = epoll_wait(_epfd,events,_maxPoller,-1);
}

int Reactor::runEventLoop()
{
    int i = 0;
    int clntfd;
    sockaddr_in clnt_addr;
    const int buffer_lenth = 1024;
    char recev_buffer[buffer_lenth];
    char send_buffer[buffer_lenth] = "welcome to myserver!";
    int tmp_N;
    char* clnt_ip_str;
    int flag;
    int clnt_addr_len = sizeof(sockaddr_in);
    int cnt1 = 0,cnt2 = 0;
    printf("debug1\n");
//    while(1)
//    {
        WaitEpollEvents();
        printf("debug2\n");
        for(i = 0;i < _nfds;++ i)
        {
            if(events[i].data.fd == _sockfd)
            {
                clntfd = accept(_sockfd,(sockaddr*)&clnt_addr,(socklen_t*)&clnt_addr_len);
                if(clntfd < 0)
                {
                    perror("accept error\n");
                    continue;
                }

                //Cheack
                if(_binder->CheackClientProcess(&clnt_addr,clntfd) == ERROR_TYPE_ERROR)
                {//can not connect
                    close(clntfd);
                    continue;
                }

                printf("accept\n");
                clnt_ip_str = inet_ntoa(clnt_addr.sin_addr);
                printf("accept the client ip: %s\n",clnt_ip_str);
                add_event(clntfd,EPOLLIN);
            }else if(events[i].events & EPOLLOUT){

                printf("EPOLLOUT cnt1[%d]\n",cnt1);
                ++cnt1;
                if((clntfd = events[i].data.fd) < 0)
                {
                    continue;
                }
                flag = _binder->OutputProcess(clntfd);
                if(flag == ERROR_TYPE_ERROR)
                {
                    close(clntfd);
                    delete_event(clntfd,EPOLLOUT);
                    printf("-------------EPOLLOUT error---------\n");
                    printf("close client, fd[%d] \n",clntfd);
                }else if(flag == ERROR_TYPE_FINISH)
                {
                    close(clntfd);
                    delete_event(clntfd,EPOLLOUT);
                    printf("-------------EPOLLOUT finish---------\n");
                    printf("close client, fd[%d] \n",clntfd);
                }else if(flag == ERROR_TYPE_CONTINUE)
                {
                    printf("-------------EPOLLOUT finish and continue connect---------\n");
                    modify_event(clntfd,EPOLLIN);
                }else if(flag == ERROR_TYPE_TEST_CONTINUE)
                {
                    printf("-------------EPOLLOUT Test OutputProcess and continue connect---------\n");
                    flag = write(clntfd,send_buffer,buffer_lenth);
                    if(flag < 0)
                    {
                        perror("write error!\n");
                        continue;
                    }
                    modify_event(clntfd,EPOLLIN);
                }

            }else if(events[i].events & EPOLLIN)
            {
                printf("EPOLLIN cnt2[%d]\n",cnt2);
                ++cnt2;
                if((clntfd = events[i].data.fd) < 0){
                    continue;
                }
                flag = _binder->InputProcess(clntfd);
                if(flag == ERROR_TYPE_TEST_CONTINUE)
                {
                    printf("-------------EPOLLIN Test InputProcess and continue connect---------\n");
                    bzero(recev_buffer,sizeof(recev_buffer));
                    printf("recev_buffer : [%s]\n",recev_buffer);
                    if((tmp_N = read(clntfd,recev_buffer,buffer_lenth)) < 0)
                    {
                        if(errno == ECONNRESET)
                        {
                            close(clntfd);
                            delete_event(clntfd,EPOLLIN);
                            printf("errno ECONRESET! \n");
                        }else{
                            perror("readbuffer error!\n");
                        }
                    }else if(tmp_N == 0)
                    {
                        close(clntfd);
                        delete_event(clntfd,EPOLLIN);
                        printf("client close\n");
                    }
                    if(recev_buffer[0] != 0)
                    {
                        printf("recv msg:%s bufferlen[%d]\n",recev_buffer,(int32_t)strlen(recev_buffer));
                        modify_event(clntfd,EPOLLOUT);
                    }
                }else if(flag == ERROR_TYPE_FINISH)
                {
                    close(clntfd);
                    delete_event(clntfd,EPOLLIN);
                    printf("-------------EPOLLIN finish---------\n");
                    printf("close client, fd[%d] \n",clntfd);
                }else if(flag == ERROR_TYPE_CONTINUE)
                {
                    printf("-------------EPOLLIN finish and continue connect---------\n");
                    modify_event(clntfd,EPOLLOUT);
                }else if(flag == ERROR_TYPE_ERROR)
                {
                    close(clntfd);
                    delete_event(clntfd,EPOLLIN);
                    printf("-------------EPOLLIN error---------\n");
                    printf("close client, fd[%d] \n",clntfd);
                }

            }
        }
//    }
}
