#include "graphics.hpp"
#include "application.hpp"
#include "widget.hpp"

#include <iostream>

using namespace genv;

application::application(const int windowX, const int windowY, bool fullscreen): windowX(windowX), windowY(windowY), fullscreen(fullscreen) {
    open=true;
}

void application::NewWidget(widget *w){
    ws.push_back(w);
}

void application::run(){
    gout.open(windowX,windowY,fullscreen);
    event ev;
    gin.timer(40);
    while(gin >> ev && open){
        for(unsigned int i=0; i<ws.size(); i++){
            ws[i]->NewEvent(ev);
        }
        gout<<refresh;
    }
}
