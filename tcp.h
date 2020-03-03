#ifndef TCP_H
#define TCP_H

#include<string>
#include<string.h>
#include<unistd.h>

#include<sys/socket.h>
#include<cstdlib>
#include<netinet/in.h>
#include<netinet/tcp.h>
#include<arpa/inet.h>
using namespace  std;

class Tcp
{
public:
    Tcp();
    ~Tcp();
    void init(in_addr_t ip,int port,int backlog);
    void init(string ip,int port,int backlog);
    int bind();
//    virtual int InputProcess();
//    virtual int OutputProcess();
    int getNetfd()const {
        return _netfd;
    }
private:
    int proc_accept();
    int proc_request();
    int _netfd;
    int _port;
    in_addr_t _in_ip;
    string _str_ip;
    int _backlog;
    sockaddr_in serv_addr;
};

#endif // TCP_H
