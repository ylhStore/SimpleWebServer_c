#ifndef WEBSERVERHANDLERPROCESS_H
#define WEBSERVERHANDLERPROCESS_H
#include"reactor.h"

enum CHECK_STATE{
    CHECK_STATE_REQUESTLINE         =   0   ,//Parsing line
    CHECK_STATE_HEADER                      //Parsing head
};

enum LINE_STATUS{
    LINE_OK             =   0,//Get full line
    LINE_BAD                ,//Line error
    LINE_OPEN               ,//Continue reading
};

enum HTTP_CODE{
    NO_REQUEST              =   0,//
    GET_REQUEST                 ,//Get full line
    BAD_REQUEST                 ,//Request error
    FORBIDDEN_REQUEST           ,//Client permission denied
    INTERNAL_ERROR              ,//Server error
    CLOSED_CONNECTION           ,//Client close connection
};
#define HTTP_GET    ("GET")
#define HTTP_POST   ("POST")

#define SUPPORT_HTTP_VERSION    ("HTTP/1.1")

class webServerHandlerProcess:public Tcp,virtual public ReactorInterface
{
#define MAX_CLNT_SIZE       (1024)
#define MAX_BUFFER_LENGTH   (4096)
public:
//    webServerHandlerProcess();
     REACTOR_ERROR_TYPE InputProcess(int clntfd);
     REACTOR_ERROR_TYPE OutputProcess(int clntfd);
     REACTOR_ERROR_TYPE HangupProcess(int clntfd);
     REACTOR_ERROR_TYPE CheackClientProcess(sockaddr_in* clnt_addr,int clntfd);
//     ~webServerHandlerProcess(){}
public:
     LINE_STATUS parse_line(char* bufffer,int& checked_index,int& read_index);
     HTTP_CODE parse_requestline(char* temp,CHECK_STATE& checkstate);
     HTTP_CODE parse_headers(char* temp);
     HTTP_CODE parse_content(char* buffer,int& check_index,CHECK_STATE& checkstate,int& read_index,int& start_line);
private:
     char _buffer[MAX_BUFFER_LENGTH];
     int _clntfds[MAX_CLNT_SIZE];
};

#endif // WEBSERVERHANDLERPROCESS_H











































