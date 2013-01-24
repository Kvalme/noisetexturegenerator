#include <QtGui/QApplication>
#include "mainwindow.h"
#include <iostream>
int main(int argc, char *argv[])
{
    try
    {
        QApplication a(argc, argv);
        MainWindow w;
        w.show();

        return a.exec();
    }
    catch(...)
    {
        std::cerr<<"Unexpected error!"<<std::endl;
    }
}
