#include <QApplication>
#include <QCoreApplication>
#include <QtCore>
#include <QStringList>
#include "config.h"
#include "server.h"
#include "console.h"
#include "mainwindow.h"

extern SenseSystem::Config config;

/*
 * Main function started program
 */
int main(int argc, char *argv[])
{
    int temp = 0;
    // Checkling arguments of Application
    while(temp < argc)
    {
        // Chwecking number of port that listening server
        if(QString(argv[temp]).indexOf("--configfile=",0) != -1)
        {
            config.configFile = QString(argv[temp]).mid(QString("--configfile=").length());
            if(SenseSystem::parserConfig())
                break;
        }
        // If need console user interface of the application
        else if(QString(argv[temp]).indexOf("--view=",0) != -1)
        {
            // If we need to stqart application in console mode
            if(QString(argv[temp]).indexOf("console",0) != -1)
            {
                config.typeView = SenseSystem::CONSOLE;
            }
            // If we need to start application in test window mode
            else if(QString(argv[temp]).indexOf("window",0) != -1)
            {
                config.typeView = SenseSystem::WINDOW;
            }
        }
        // Chwecking number of port that listening server
        else if(QString(argv[temp]).indexOf("--port=",0) != -1)
        {
            config.port = QString(argv[temp]).mid(QString("--port=").length()).toInt();
        }
        temp++;
    }

    // Checking if we need console application
    if(config.typeView == SenseSystem::CONSOLE)
    {
        QCoreApplication app(argc, argv);
        config.display = new Console(app.arguments());
        // Return end of application
        return app.exec();
    }
    // Checking if we need window application
    else
    {
        QApplication app(argc, argv);
        config.display = new MainWindow();
        ((MainWindow *) config.display)->show();
        // Return end of application
        return app.exec();
    }
}


