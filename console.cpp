#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <math.h>
#include <QHeaderView>
#include <QDesktopServices>
#include "config.h"
#include "console.h"
#include "CRC/CRC16.h"
#include "server.h"
#include <iostream>

extern SenseSystem::Config  config;

/*
 * Constructor console task
 */
Console::Console(QStringList agruments,QObject *parent) :
        QObject(parent)
{
    Console::agruments = agruments;
    // Function of fetch of user interface
    server = new SenseSystem::TechServer(config.port,this);
    connect(this,SIGNAL(println(QString)),this,SLOT(outStream(QString)));
    // Checking if server is started ?
    if(server != NULL)
    {
        // Set text to the text browser
        println("Server is working!\r\n");
        println("UTC: "+QDateTime::currentDateTimeUtc().toString()+"\r\n");
    }
    // If server isn't working
    else
    {
        // Set text to the text browser
        println("Server isn\'t working!!!\r\n");
        println("Please check the internet connection\r\n");
    }
}

/*
 * Destructor of class MainWindow
 */
Console::~Console()
{
    delete server;
}

/*
 * InPut stream data
 */
std::string Console::inStream(void)
{
    std::string temp;
    std::cin >> temp;
    return temp;
}

/*
 * OutPut stream datac
 */
void Console::outStream(QString str)
{
    std::cout << str.toStdString() << std::endl;
    std::cout.flush();
}

void Console::addClientToList(int IDSocket)
{

}

void Console::removeClientFromList(int IDSocket)
{

}

void Console::displayInfoOfClient(int IDSocket)
{

}

void Console::displayAllClient()
{

}
