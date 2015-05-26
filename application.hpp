#ifndef APPLICATION_HPP_INCLUDED
#define APPLICATION_HPP_INCLUDED

#include <vector>

class widget;

class application{
protected:
    int windowX,windowY;
    bool fullscreen, open;
    std::vector<widget*> ws;
public:
    application(const int windowX, const int windowY, bool fullscreen);
    virtual void action(bool b){}
    void shutdown(){open=false;}
    void NewWidget(widget *w);
    void run();
};

#endif // APPLICATION_HPP_INCLUDED
