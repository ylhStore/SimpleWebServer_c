#include"c_option.h"
#include"tcp.h"
#include"reactor.h"
#include"c_global.h"
#include"webserverobject.h"
#include"webserverhandlerprocess.h"
#include <iostream>
using namespace std;

int main(int argc,char** argv)
{
    c_option::Instance()->decode(argc,argv);
    if(c_option::Instance()->hasParam("help"))
    {
        cout<<"Usage:"<<endl;
        exit(0);
    }
    c_global::_argc = argc;
    c_global::_pargv = argv;
    c_global::_ip = c_option::Instance()->getValue("ip");
    c_global::_port = atoi(c_option::Instance()->getValue("port").c_str());
    c_global::_maxClient = atoi(c_option::Instance()->getValue("maxClient").c_str());
    c_global::_background = atoi(c_option::Instance()->getValue("background").c_str());

//    Tcp _listenTcp;
//    _listenTcp.init(c_global::_ip,c_global::_port,c_global::_background);
//    _listenTcp.bind();

    webServerHandlerProcess web_handler;
    web_handler.init(c_global::_ip,c_global::_port,c_global::_background);
    web_handler.bind();

    Reactor _reactor;
    _reactor.init(c_global::_maxClient);
    _reactor.bind(web_handler);
    _reactor.bind(web_handler.getNetfd());

    WebServerObject _webServerObject(&web_handler,&_reactor);
    _webServerObject.runEventLoop();
    return 0;
}
