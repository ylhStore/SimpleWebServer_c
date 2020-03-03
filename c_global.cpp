#include "c_global.h"
//clib_log*       c_global::g_pErrorLog             = NULL;
//clib_log*       c_global::g_pDebugLog             = NULL;
//clib_log*       c_global::g_pBootLog              = NULL;
//clib_log*       c_global::g_pProtoLog             = NULL;
//clib_log*       c_global::g_pStatsLog             = NULL;
//SSL_CTX*        c_global::g_ctx                   = NULL;

string c_global::_ip = "::ffff:0.0.0.0";
string c_global::_inner_ip = "127.0.0.1";
int c_global::_port = 10000;
int c_global::_svid = 1;
int c_global::_zone_id = 1;
//int c_global::_svrd_type = EN_Node_Unknown;
bool c_global::_background = false;
int c_global::_group_id = 1;
int c_global::_state = 0;
int c_global::_argc = -1;
int c_global::_target_port = -1;
char** c_global::_pargv = NULL;
int c_global::_level = 0;
int c_global::_maxClient = 4;

int& c_global::_node_id = c_global::_svid;
//int& c_global::_node_type = c_global::_svrd_type;
