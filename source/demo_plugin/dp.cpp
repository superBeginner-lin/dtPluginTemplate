#include "dp.h"

void DemoPlugin::onCreate(){
    std::cout<<"DemoPlugin::onCreate"<<std::endl;
}
void DemoPlugin::onStarted(){
    std::cout<<"DemoPlugin::onStarted"<<std::endl;
}
void DemoPlugin::onStop(){
    std::cout<<"DemoPlugin::onStop"<<std::endl;
};
void DemoPlugin::onFree(){
    std::cout<<"DemoPlugin::onFree"<<std::endl;
};
void DemoPlugin::onMessage(void *message){
    std::cout<<"DemoPlugin::onMessage"<<std::endl;
};
void* DemoPlugin::getPublicMethodProxy(){
    std::cout<<"DemoPlugin::getPublicMethodProxy"<<std::endl;
    return (DemoPluginProxy*)this;
};
std::list<int> DemoPlugin::getRegistType(){
    std::list<int> types;
    return types;
};



int DemoPlugin::add(int a,int b){
    std::cout<<"DemoPlugin::add"<<a<<"+"<<b<<std::endl;
    return a+b;
}
void DemoPlugin::alert(std::string info){
    std::cout<<"DemoPlugin::alert"<<info<<std::endl;
    std::cout<<info<<std::endl;
}
void DemoPlugin::testAgent(){
    std::cout<<"DemoPlugin::testAgent"<<std::endl;
    this->getAgent()->getPlugin("!!!!!!!!!!!");
}


#ifdef __cplusplus
extern "C"{
#endif
void* CreateInstance(){
    return new DemoPlugin();
}
#ifdef __cplusplus
}
#endif