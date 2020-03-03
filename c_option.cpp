#include "c_option.h"

c_option* c_option::Instance(void)
{
    return CSingleton<c_option>::Instance();
}

void c_option::decode(int argc, char **argv)
{
    _mParam.clear();
    vector<string> v;
    for(int i = 1;i < argc;++ i){
        v.push_back(argv[i]);
    }
    for (size_t i = 0; i < v.size(); i++)
    {
        if (v[i].length() > 2 && v[i].substr(0, 2) == "--")
        {
            parse(v[i]);
        }
        else
        {
            _vSingle.push_back(v[i]);
        }
    }
}

void c_option::parse(const string& s)
{
    string::size_type pos = s.find('=');
    if (pos != string::npos)
    {
        _mParam[s.substr(2, pos - 2)] = s.substr(pos + 1);
    }
    else
    {
        _mParam[s.substr(2, pos - 2)] = "";
    }
}

string c_option::getValue(const string& sName)
{
    if (_mParam.find(sName) != _mParam.end())
    {
        return _mParam[sName];
    }
    return "";
}

bool c_option::hasParam(const string& sName)
{
    return _mParam.find(sName) != _mParam.end();
}

vector<string>& c_option::getSingle()
{
    return _vSingle;
}

map<string, string>& c_option::getMulti()
{
    return _mParam;
}
