#ifndef _DEMO_PLUGIN_H
#define _DEMO_PLUGIN_H

#include "dp_public.h"
#include "../base_plugin.h"
#include <iostream>

class DemoPlugin : public BasePlugin,public DemoPluginProxy{
public:
    DemoPlugin(){};
    int add(int a,int b) override;
    void alert(std::string info) override;
    void testAgent() override;
    
private:
    void onCreate() override;
    void onStarted() override;
    void onStop() override;
    void onFree() override;
    void onMessage(void *message) override;
    void *getPublicMethodProxy() override;
    std::list<int> getRegistType() override;
};

#endif


