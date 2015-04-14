#include <QApplication>
#include "mainwindow.h"
#include <iostream>
int main(int argc, char *argv[])
{
    try
    {
        QApplication a(argc, argv);
        QCoreApplication::setOrganizationName("NSWS");
        QCoreApplication::setOrganizationDomain("nsws.ru");
        QCoreApplication::setApplicationName("Noise Texture Generator");
        QCoreApplication::setApplicationVersion("0.2.0");

        MainWindow w;
        w.show();

        return a.exec();
    }
    catch(...)
    {
        std::cerr<<"Unexpected error!"<<std::endl;
    }
}
