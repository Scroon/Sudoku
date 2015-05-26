#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

#include "graphics.hpp"
#include "widget.hpp"

class exitBTN : public widget{
public:
    exitBTN(const int posx, const int posy, const int sizex, const int sizey, bool IsFrame, application *parent, std::string value, std::string ID);
    virtual void action() {app->shutdown();}
    void draw();
    virtual void NewEvent(genv::event e);
};

#endif // BUTTON_HPP_INCLUDED
