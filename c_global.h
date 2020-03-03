#ifndef C_GLOBAL_H
#define C_GLOBAL_H

#include<string>
using namespace std;
class c_global
{
public:
//    static clib_log*        g_pErrorLog;
//    static clib_log*        g_pDebugLog;
//    static clib_log*        g_pBootLog;
//    static clib_log*        g_pProtoLog;
//    static clib_log*        g_pStatsLog;
public:
//    static SSL_CTX* g_ctx;
public:
    static string _ip;
    static string _inner_ip;
    static int _port;
    static int _svid;
//    static int _svrd_type;
    static bool _background;
    static int _group_id;
    static int _zone_id;
    static int _state;
    static int _level;
    static int _target_port;
    static int _maxClient;
    static int _argc;
    static char**  _pargv;
    static int& _node_id;
//    static int& _node_type;
private: //no impl
    c_global(void);
    ~c_global(void);
    c_global(const c_global&);
    const c_global& operator= (const c_global&);
};

#endif // C_GLOBAL_H
