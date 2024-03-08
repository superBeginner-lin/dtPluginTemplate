#ifndef _AGENT_INTERFACE_H
#define _AGENT_INTERFACE_H

#include <string>

class AgentInterface
{
public:
    virtual void* getPlugin(std::string pluginName) = 0;
};


#endif


