#include "webserverobject.h"

WebServerObject::WebServerObject()
{
    _reactor    = nullptr;
    _binder     = nullptr;
}

int WebServerObject::init(webServerHandlerProcess *binder, Reactor *reactor)
{
    _reactor    = reactor;
    _binder     = binder;
}
void WebServerObject::runEventLoop()
{
    int cnt = 1;
    int MAXN = 1000;
    while(1)
    {
        _reactor->runEventLoop();
        if(cnt++ >= MAXN)
        {
            printf("WebServerObject cnt[%d]\n",cnt);
            break;
        }
    }
}
