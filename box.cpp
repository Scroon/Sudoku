#include "application.hpp"
#include "widget.hpp"
#include "graphics.hpp"
#include "box.hpp"

#include <iostream>

using namespace genv;

strBOX::strBOX(const int posx, const int posy, const int sizex, const int sizey, bool IsFrame, application *parent, std::string value, std::string ID, bool IsInbox) : widget(posx,posy,sizex,sizey,IsFrame,parent,value,ID), IsInbox(IsInbox) {}

numBOX::numBOX(const int posx, const int posy, const int sizex, const int sizey, bool IsFrame, application *parent, std::string value, std::string ID, bool IsInbox) : strBOX(posx,posy,sizex,sizey,IsFrame,parent,value,ID,IsInbox) {
    convertToNum();
}

void strBOX::draw(){
    if(IsInbox){
        if(IsInFocus || selected){
            if(IsFrame) gout<<move_to(px-2,py-2)<<color(255,100,0)<<box(sx+4,sy+4);
            gout<<move_to(px,py)<<color(255,255,255)<<box(sx,sy);

        }
        else{
            if(IsFrame) gout<<move_to(px-2,py-2)<<color(100,100,255)<<box(sx+4,sy+4);
            gout<<move_to(px,py)<<color(255,255,255)<<box(sx,sy);
        }

        if(gout.twidth(value)>sx-16){
            gout<<move_to(px+2,py+15)<<color(0,0,0)<<text(value.substr(value.size()-(sx-8)/8,value.size()));
        }
        else{
            gout<<move_to(px+2,py+15)<<color(0,0,0)<<text(value);
        }
    }
    else{
        if(IsFrame) gout<<move_to(px-2,py-2)<<color(50,50,50)<<box(sx+4,sy+4)<<move_to(px-1,py-1)<<color(0,0,0)<<box(sx+2,sy+2);
        gout<<move_to(px,py+15)<<color(255,255,255)<<text(value);
    }
}

void strBOX::add(char c){
    if(c==8) value=value.substr(0,value.size()-1);
    else value+=c;
}

void strBOX::add(std::string s){
    value=s;
}

void strBOX::NewEvent(event e){
    if(e.type==ev_mouse) focus(e.pos_x,e.pos_y);
    if(e.type==ev_timer) draw();

    if(e.button==btn_left && IsInbox && IsInFocus) selected=true;
    else if(e.button==btn_left) selected=false;

    if((e.keycode==8 || (e.keycode>=32 && e.keycode<=126)) && selected) {
        add(e.keycode);
    }
}

void numBOX::NewEvent(event e){
    if(e.type==ev_mouse) focus(e.pos_x,e.pos_y);
    if(e.type==ev_timer) draw();

    if(e.button==btn_left && IsInbox && IsInFocus) selected=true;
    else if(e.button==btn_left) selected=false;

    if((e.keycode==8 || e.keycode==46 || (e.keycode>=48 && e.keycode<=57)) && selected) {
        add(e.keycode);
    }
}

void numBOX::convertToNum(){
    ss<<value;
    ss>>num;
    ss.clear();
}

void numBOX::convertToStr(){
    ss<<num;
    ss>>value;
    ss.clear();
}
