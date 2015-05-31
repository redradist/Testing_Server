#include "view.h"

extern SenseSystem::SysInfoType  SysInfo;
extern SenseSystem::Config  config;

/*
 * Constructor console task
 */
Console::Console(int argc, char **argv) :
    QCoreApplication(argc, argv)
{
    // Функция предварительной настройки пользовательского интерфейса
    server = new SenseSystem::MyServer(config.port);
    // Checking if server is started ?
    if(server != NULL)
    {
        // Set text to the text browser
        outStream("Server is working!                       \r\n");
        outStream("UTC: "+QString::number(QDateTime::currentDateTimeUtc().toTime_t()).toStdString()+"\r\n");
    }
    // If server isn't working
    else
    {
        // Set text to the text browser
        outStream("Server isn\'t working!!!\r\n");
        outStream("Please check the internet connection\r\n");
    }
}

/*
 * Destructor of class MainWindow
 */
Console::~Console()
{
    delete server;
}
