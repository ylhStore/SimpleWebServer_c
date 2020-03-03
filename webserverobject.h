#ifndef WEBSERVEROBJECT_H
#define WEBSERVEROBJECT_H

#include"webserverhandlerprocess.h"
class WebServerObject
{
public:
    WebServerObject();
    WebServerObject(webServerHandlerProcess* binder,Reactor* reactor):_binder(binder),_reactor(reactor){}
    int init(webServerHandlerProcess* binder,Reactor* reactor);
    void runEventLoop();

private:
    webServerHandlerProcess*        _binder;
    Reactor*    _reactor;
};

#endif // WEBSERVEROBJECT_H
