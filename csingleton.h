#ifndef CSINGLETON_H
#define CSINGLETON_H

template<typename T>
class CSingleton
{
public:
    static T* Instance()
    {
        return &Reference();
    }
    static T& Reference()
    {
        static T _Instance;
        return _Instance;
    }
protected:
    CSingleton(){}
    CSingleton(CSingleton const&){};
};

#endif // CSINGLETON_H
