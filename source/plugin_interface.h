#ifndef _PLUGIN_INTERFACE_H
#define _PLUGIN_INTERFACE_H
#include <list>

class PluginInterface{
public:
    virtual void create(void* agent) =0;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void free() = 0;
    virtual void *getProxy() =0;

    virtual std::list<int> getRegistMessageType() =0;
    virtual void receiveMessage(void * message) =0;

};

#endif