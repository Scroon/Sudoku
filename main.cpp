#include "application.hpp"
#include "button.hpp"
#include "box.hpp"
#include "graphics.hpp"

#include <time.h>
#include <random>
#include <iostream>
#include <fstream>

using namespace genv;

std::string ConvertIntToString(int i){
    std::stringstream ss;
    std::string s;
    ss<<i;
    ss>>s;
    ss.clear();
    return s;
}

class elbtn : public exitBTN{
private:
    bool ellenorzes=false;
public:
    elbtn(const int posx, const int posy, const int sizex, const int sizey, bool IsFrame, application *parent, std::string value, std::string ID) : exitBTN(posx,posy,sizex,sizey,IsFrame,parent,value,ID) {}
    void action(){
        ellenorzes=!ellenorzes;
        app->action(ellenorzes);
    }
    void draw(){
        if(IsInFocus || ellenorzes){
            if(IsFrame) gout<<move_to(px-2,py-2)<<color(255,100,0)<<box(sx+4,sy+4);
            gout<<move_to(px,py)<<color(10,10,10)<<box(sx,sy);
        }
        else{
            if(IsFrame) gout<<move_to(px-2,py-2)<<color(100,100,100)<<box(sx+4,sy+4);
            gout<<move_to(px,py)<<color(10,10,10)<<box(sx,sy);
        }
        gout<<move_to(px+(sx/2-gout.twidth(value)/2),py+15)<<color(255,255,255)<<text(value);
    }
};

class btn : public exitBTN{
protected:
    bool fix;
    int num,s,o,b;
public:
    bool warn=false;
    btn(const int posx, const int posy, const int sizex, const int sizey, bool IsFrame, application *parent, std::string value, std::string ID, int num, bool fix,int s,int o,int b) : exitBTN(posx,posy,sizex,sizey,IsFrame,parent,value,ID), num(num), fix(fix), s(s), o(o), b(b) {}
    void action(){
        num++;
        if(num>9)num=0;
    }
    void befix(){
        fix=true;
    }
    void draw(){
        if (warn && !IsInFocus && !fix){
            gout<<move_to(px,py)<<color(150,150,150)<<box(sx,sy);
            gout<<move_to(px+1,py+1)<<color(200,5,5)<<box(sx-2,sy-2);
            gout<<move_to(px+(sx/2-gout.twidth(value)/2),py+15)<<color(255,255,255)<<text(value);
        }
        else if (!warn && IsInFocus && !fix){
            gout<<move_to(px,py)<<color(255,100,0)<<box(sx,sy);
            gout<<move_to(px+1,py+1)<<color(200,200,200)<<box(sx-2,sy-2);
            gout<<move_to(px+(sx/2-gout.twidth(value)/2),py+15)<<color(0,0,0)<<text(value);
        }
        else if(warn && IsInFocus && !fix){
            gout<<move_to(px,py)<<color(255,100,0)<<box(sx,sy);
            gout<<move_to(px+1,py+1)<<color(200,5,5)<<box(sx-2,sy-2);
            gout<<move_to(px+(sx/2-gout.twidth(value)/2),py+15)<<color(255,255,255)<<text(value);
        }
        else if(warn && fix){
            gout<<move_to(px,py)<<color(150,150,150)<<box(sx,sy);
            gout<<move_to(px+1,py+1)<<color(100,5,5)<<box(sx-2,sy-2);
            gout<<move_to(px+(sx/2-gout.twidth(value)/2),py+15)<<color(255,255,255)<<text(value);
        }
        else if(!fix){
            gout<<move_to(px,py)<<color(150,150,150)<<box(sx,sy);
            gout<<move_to(px+1,py+1)<<color(200,200,200)<<box(sx-2,sy-2);
            gout<<move_to(px+(sx/2-gout.twidth(value)/2),py+15)<<color(0,0,0)<<text(value);
        }
        else{
            gout<<move_to(px,py)<<color(150,150,150)<<box(sx,sy);
            gout<<move_to(px+1,py+1)<<color(180,180,180)<<box(sx-2,sy-2);
            gout<<move_to(px+(sx/2-gout.twidth(value)/2),py+15)<<color(0,0,0)<<text(value);
        }
    }
    void NewEvent(event e){
        if(e.type==ev_mouse) focus(e.pos_x,e.pos_y);
        if(e.type==ev_timer){
            if(num==0)value="";
            else value=ConvertIntToString(num);
            draw();
        }
        if(e.button==btn_wheelup && IsInFocus && !fix){
            num++;
            if(num>9)num=0;
        }
        if(e.button==btn_wheeldown && IsInFocus && !fix){
            num--;
            if(num<0)num=9;
        }
        if(e.button==btn_left && IsInFocus && !fix){
            action();
        }
        if(e.button==btn_right && IsInFocus && !fix){
            num=0;
        }
        if(e.keycode<=57 && e.keycode>=49 && IsInFocus && !fix){
            char c=e.keycode;
            num=c;
        }
    }
};


class sudoku : public application{
protected:
    std::ifstream f;
    btn* BTN;
    btn* s[9][9];
    btn* o[9][9];
    btn* b[9][9];
    int sor,seged;
    bool rdy;
public:
    sudoku(int windowX,int windowY,bool fullscreen) : application(windowX,windowY,fullscreen){

        sor=9;
        f.open("sudoku9.txt");

        new elbtn(windowX-150,windowY-140,100,20,true,this,"Ellenorzes","ellen");
        new exitBTN(windowX-150,windowY-70,100,20,true,this,"Exit","exit");

        for(int i=0; i<sor; i++){
            for(int j=0; j<sor; j++){
                f>>seged;
                if(seged!=0) BTN=new btn(j*20+50+j/3,i*20+50+i/3,20,20,false,this,"","",seged,true,i,j,((i/3)+1)*((j/3)+1)-1);
                else BTN=new btn(j*20+50+j/3,i*20+50+i/3,20,20,false,this,"","",seged,false,j,i,((i/3)+1)*((j/3)+1)-1);
                s[i][j]=BTN;
                o[j][i]=BTN;
                b[(j/3)+(i/3)*3][(j%3)+(i%3)*3]=BTN;
            }
        }

        f.close();
    }
    void action(bool bo){
        if(bo){
            for(int i=0; i<9; i++){
                for(int j=0; j<9; j++){
                    for(int k=0; k<9; k++){
                        if(k!=j){
                            if(s[i][j]->reval()==s[i][k]->reval() && s[i][k]->reval()!="" && s[i][k]->reval()!=""){
                                s[i][j]->warn=true;
                                s[i][k]->warn=true;
                            }
                            if(o[i][j]->reval()==o[i][k]->reval() && o[i][k]->reval()!="" && o[i][k]->reval()!=""){
                                o[i][j]->warn=true;
                                o[i][k]->warn=true;
                            }
                            if(b[i][j]->reval()==b[i][k]->reval() && b[i][k]->reval()!="" && b[i][k]->reval()!=""){
                                b[i][j]->warn=true;
                                b[i][k]->warn=true;
                            }
                        }
                    }
                }
            }
            for(int i=0; i<9; i++){
                for(int j=0; j<9; j++){
                    if(s[i][j]->reval()=="" || o[i][j]->reval()=="" || b[i][j]->reval()=="" || s[i][j]->warn==true || o[i][j]->warn==true || b[i][j]->warn==true)
                    {
                        rdy=false;
                        break;
                    }
                    else rdy=true;
                }
                if(!rdy) break;
            }
        }
        if(!bo){
            for(int i=0; i<9; i++){
                for(int j=0; j<9; j++){
                    s[i][j]->warn=false;
                    o[i][j]->warn=false;
                    b[i][j]->warn=false;
                }
            }
        }
        if(rdy){
            for(int i=0; i<9; i++){
                for(int j=0; j<9; j++){
                    b[i][j]->befix();
                }
            }
        }
    }
};

int main()
{
    srand(time(NULL));
    sudoku MyApp(500,300,false);
    MyApp.run();
    return 0;
}
