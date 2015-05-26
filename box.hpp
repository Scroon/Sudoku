#ifndef BOX_HPP_INCLUDED
#define BOX_HPP_INCLUDED

#include "graphics.hpp"
#include "widget.hpp"
#include <sstream>

class strBOX : public widget{
protected:
    bool IsInbox, selected;
public:
    strBOX(const int posx, const int posy, const int sizex, const int sizey, bool IsFrame, application *parent, std::string value, std::string ID, bool IsInbox);
    virtual void NewEvent(genv::event e);
    void add(std::string s);
    void add(char c);
    void draw();
};

class numBOX : public strBOX{
protected:
    float num;
    std::stringstream ss;
public:
    numBOX(const int posx, const int posy, const int sizex, const int sizey, bool IsFrame, application *parent, std::string value, std::string ID, bool IsInbox);
    void NewEvent(genv::event e);
    void convertToNum();
    void convertToStr();

};

#endif // BOX_HPP_INCLUDED
