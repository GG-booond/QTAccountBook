#ifndef BACKGROUND_H
#define BACKGROUND_H
#include<QMainWindow>
#include<vector>
#include"oneBill.h"
class background{
public:
    static QString file_path;
    background(){}
    static void change_path(QString new_path){//将path更换为新的
        file_path=new_path;
    }
};


#endif // BACKGROUND_H
