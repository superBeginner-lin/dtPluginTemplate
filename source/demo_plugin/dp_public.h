#ifndef _DEMO_PLUGIN_PUBLIC_INTERFACE_H
#define _DEMO_PLUGIN_PUBLIC_INTERFACE_H

#include <iostream>
#include <string>
class DemoPluginProxy
{
public:
    virtual int add(int a,int b) =0;
    virtual void alert(std::string info) = 0;
    virtual void testAgent() = 0;
};




#endif