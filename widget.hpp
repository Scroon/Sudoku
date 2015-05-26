#ifndef WIDGET_HPP_INCLUDED
#define WIDGET_HPP_INCLUDED

#include "application.hpp"
#include "graphics.hpp"

class application;

class widget{
protected:
    int px,py,sx,sy;
    bool IsInFocus,IsFrame;
    application *app;
    std::string value;
    std::string ID;
public:
    widget(const int posx, const int posy, const int sizex, const int sizey, bool IsFrame, application *parent, std::string value, std::string ID);
    virtual void action(){}
    virtual void NewEvent(genv::event e){}
    virtual void draw(){}
    void focus(int ex, int ey);
    std::string reval(){
        return value;
    }
    virtual void del(){
        value="";
    }
};

#endif // WIDGET_HPP_INCLUDED
