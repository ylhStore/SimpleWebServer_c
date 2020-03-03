#ifndef C_OPTION_H
#define C_OPTION_H

#include"csingleton.h"

#include<string>
#include<vector>
#include<map>
#include<sstream>
using namespace std;

class c_option
{
public:
    c_option(){};
    static c_option* Instance(void);

    void decode(int argc,char* argv[]);
    void decode(int size,char* argv);
    bool hasParam(const string& sName);
    string getValue(const string& sName);
    map<string,string>& getMulti();
    vector<string>& getSingle();
protected:
    void parse(const string& s);
    map<string,string> _mParam;
    vector<string> _vSingle;
};

#endif // C_OPTION_H
