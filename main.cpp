#include <QApplication>
#include <QDesktopWidget>

#include <function.h>
#include <iostream>
#include <map>

#include "mainwindow.h"



int main(int argc, char *argv[])
{

    QApplication app(argc,argv);
    MainWindow w;

    QDesktopWidget dw;
    int x = dw.width() * 0.9;
    int y = dw.height() * 0.9;
    w.setFixedSize(x,y);
    w.show();






    return app.exec();

}
