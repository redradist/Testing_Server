#include <stdint.h>
#include "config.h"
#include "server.h"

#include "client.h"
#include "console.h"
#include "mainwindow.h"
#include "CRC/CRC16.h"

#include <QtEndian>

extern int numberofFile();
extern union Graphic type;
extern SenseSystem::Config          config;

/*
 * Constructor of server application
 */
SenseSystem::TechServer::TechServer(int port, QObject *parent) :
    QObject(parent),
    server_port(port)
{
    tcpServer = new QTcpServer(this);

    // Try to start server
    if (!tcpServer->listen(QHostAddress::Any, server_port)) {
        // Sever is not working
        qDebug() <<  QObject::tr("Unable to start the server: %d.").arg(tcpServer->errorString());
    }
    else {
        // Sever is working
        qDebug() << QString::fromUtf8("Server is working!");
        qDebug() << tcpServer->isListening() << "TCPSocket is listening on port" << server_port;
        connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newclient()));
    }
}

/*
 * Destructor of server application
 */
SenseSystem::TechServer::~TechServer()
{
    disconnect(tcpServer, SIGNAL(newConnection()), this, SLOT(newclient()));
    // If server is working
    foreach(int i,client.keys()){
        QTextStream os;
        os.setAutoDetectUnicode(true);
        os << i << QDateTime::currentDateTime().toString() << "\n";
        // If socket is existing
        if(client[i] != NULL)
        {
            removeClient(i);
            removeMap(i);
        }
    }
    tcpServer->close();
    tcpServer->deleteLater();

    qDebug() << QString::fromUtf8("Server is stoped!");
}

/*
 * New client connection
 */
void SenseSystem::TechServer::newclient()
{
    // If server started
    qDebug() << QString::fromUtf8("New connection!!!");

    qintptr IDSocket = tcpServer->nextPendingConnection()->socketDescriptor();

    QThread *thread = new QThread();
    Client *client = new Client(IDSocket);
    client->moveToThread(thread);
    // Соединяем сигнал started потока, со слотом process "рабочего" класса, т.е. начинается выполнение нужной работы.
    connect(thread,SIGNAL(started()),client,SLOT(process()));
    connect(thread,SIGNAL(finished()),thread,SLOT(deleteLater()));
    // По завершению выходим из потока, и удаляем рабочий класс
    connect(client,SIGNAL(finished()),thread,SLOT(quit()));
    connect(client,SIGNAL(finished()),client,SLOT(deleteLater()));
    // Удаляем поток, после выполнения операции
    if(config.typeView == CONSOLE)
    {
        connect(client,SIGNAL(println(QString)),((Console *)config.display),SLOT(outStream(QString)));
        connect(client,SIGNAL(addClientToList(int)),((Console *)config.display),SLOT(addClientToList(int)));
    }
    else if(config.typeView == WINDOW)
    {
        connect(client,SIGNAL(println(QString)),((MainWindow *)config.display),SLOT(outStream(QString)));
        connect(client,SIGNAL(addClientToList(int)),((MainWindow *)config.display),SLOT(addClientToList(int)));
    }
    connect(client,SIGNAL(removeClientFromList(int)),this,SLOT(removeMap(int)));

    SenseSystem::TechServer::client.insert(IDSocket,client);
    thread->start();
}

/*
 * Remove client connection
 */
void SenseSystem::TechServer::removeClient(int IDSocket)
{
    // If server started
    qDebug() << QString::fromUtf8("Remove client from process ") << IDSocket;
    // Send finished signal to client
    QEvent *event = new QEvent((QEvent::Type)(QEvent::User));
    QCoreApplication::postEvent(client.value(IDSocket),event);
}

/*
 * Remove client from map of clients
 */
void SenseSystem::TechServer::removeMap(int IDSocket)
{
    config.display->removeClientFromList(IDSocket);
    client.remove(IDSocket);
}
