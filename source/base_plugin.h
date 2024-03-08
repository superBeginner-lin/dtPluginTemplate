#ifndef _BASE_PLUGIN_H
#define _BASE_PLUGIN_H

#include "agent_interface.h"
#include "plugin_interface.h"
#include <queue>
#include <pthread.h>

class BasePlugin:public PluginInterface{
public:

    void create(void* _agent) override{
        agent = (AgentInterface*) _agent;
        pthread_create(&rec_thread,NULL,BasePlugin::run,this);
        onCreate();
    }
    void start() override{
        onStarted();
        running = true;
    }
    void stop() override{
        running = false;
        onStop();
    }
    void free() override{
        freed = true;
        pthread_mutex_lock(&thread_lock);
        pthread_cond_signal(&thread_cond);
        pthread_mutex_unlock(&thread_lock);
    }
    void *getProxy() override{
        return getPublicMethodProxy();
    }
    void receiveMessage(void * message) override {
        if (running){
            pthread_mutex_lock(&queue_lock);
            messageQueue.push(message);
            pthread_mutex_unlock(&queue_lock);

            pthread_mutex_lock(&thread_lock);
            pthread_cond_signal(&thread_cond);
            pthread_mutex_unlock(&thread_lock);
        }
    }
    std::list<int> getRegistMessageType() override{
        return getRegistType();
    }

    AgentInterface* getAgent(){
        return agent;
    }
private:
    pthread_t rec_thread;
    AgentInterface* agent;
    bool running = false;
    bool freed = false;
    std::queue<void *> messageQueue;
    pthread_cond_t thread_cond = PTHREAD_COND_INITIALIZER;
    pthread_mutex_t thread_lock = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_t queue_lock = PTHREAD_MUTEX_INITIALIZER;
    static void* run(void * instance){
        BasePlugin *_this = (BasePlugin *)instance;
        while(1 && !_this->freed){
            pthread_mutex_lock(&_this->thread_lock);
            pthread_cond_wait(&_this->thread_cond,&_this->thread_lock);
            pthread_mutex_unlock(&_this->thread_lock);
            if (_this->freed) break;

            while(_this->messageQueue.size()>0){
                if (_this->freed) break;
                pthread_mutex_lock(&_this->thread_lock);
                void* message = _this->messageQueue.front();
                _this->messageQueue.pop();
                pthread_mutex_unlock(&_this->thread_lock);

                if (_this->freed) break;
                _this->onMessage(message);
            }
        }

        _this->onFree();
        return NULL;
    }
    
    virtual void onCreate(){};
    virtual void onStarted(){};
    virtual void onStop(){};
    virtual void onFree(){};
    virtual void onMessage(void *message) =0;
    virtual void *getPublicMethodProxy(){
        return NULL;
    }
    virtual std::list<int> getRegistType(){
        return std::list<int>();
    }
};

#endif