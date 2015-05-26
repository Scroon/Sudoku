#include "widget.hpp"
#include "application.hpp"

widget::widget(const int posx, const int posy, const int sizex, const int sizey, bool IsFrame, application *parent, std::string value, std::string ID) : px(posx), py(posy), sx(sizex), sy(sizey), IsFrame(IsFrame), app(parent), value(value), ID(ID) {
    app->NewWidget(this);
}

void widget::focus(int ex, int ey){
    if(ex>px && ey>py && ex<px+sx && ey<py+sy) IsInFocus=true;
    else IsInFocus=false;
}
