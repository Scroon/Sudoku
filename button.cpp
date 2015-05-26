#include "button.hpp"
#include "widget.hpp"
#include "graphics.hpp"
#include "application.hpp"

using namespace genv;

exitBTN::exitBTN(const int posx, const int posy, const int sizex, const int sizey, bool IsFrame, application *parent, std::string value, std::string ID) : widget(posx,posy,sizex,sizey,IsFrame,parent,value,ID) {}

void exitBTN::draw(){
    if(IsInFocus){
        if(IsFrame) gout<<move_to(px-2,py-2)<<color(255,100,0)<<box(sx+4,sy+4);
        gout<<move_to(px,py)<<color(10,10,10)<<box(sx,sy);
    }
    else{
        if(IsFrame) gout<<move_to(px-2,py-2)<<color(100,100,100)<<box(sx+4,sy+4);
        gout<<move_to(px,py)<<color(10,10,10)<<box(sx,sy);
    }

    gout<<move_to(px+(sx/2-gout.twidth(value)/2),py+15)<<color(255,255,255)<<text(value);
}

void exitBTN::NewEvent(event e){
    if(e.type==ev_mouse) focus(e.pos_x,e.pos_y);
    if(e.type==ev_timer) draw();

    if(e.button==btn_left && IsInFocus){
        action();
    }
}
