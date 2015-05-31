#include <stdint.h>
#include "config.h"
#include "client.h"
#include "mainwindow.h"
#include "CRC/CRC16.h"

#include <QtEndian>

extern int numberofFile();

/*
 * Constructor of server application
 */
SenseSystem::Client::Client(qintptr socketDescriptor) :
    socketDescriptor(socketDescriptor)
{
    clientSocket = NULL;
    multiplexNum = 0;
    autorizationClient = false;
    answerClient = false;
    comCount = 0;
}

/*
 * Destructor of server application
 */
SenseSystem::Client::~Client()
{
    // Remove client from list of the objects
    removeClientFromList(socketDescriptor);

    // Display message on the display
    QString strSocket;
    strSocket += QString("[") + QString::number(socketDescriptor) + "] Connection  is stoped\r\n";
    println(strSocket);

    // Delete pointer to the socket
    clientSocket->deleteLater();
    autoriz->deleteLater();
    timer->deleteLater();
    timModem->deleteLater();
    timAlive->deleteLater();

    // Debug message
    qDebug() << QString::fromUtf8("Socket is stoped!");
}

/*
 * Run the thread
 */
void SenseSystem::Client::process(void)
{
    clientSocket = new QTcpSocket();
    // Trying to connect to socket descriptor
    if (!clientSocket->setSocketDescriptor(socketDescriptor))
    {
        // Can't connect to socket descriptor
        finished();
    }
    else
    {
        // Initiolization settings for system
        timer = new QTimer(this);
        // setup signal and slot
        connect(timer,SIGNAL(timeout()),this,SLOT(readCommand()));
        // Reading command from MySQL
        timer->start(2000);

        // Initiolization settings for system
        autoriz = new QTimer(this);
        // setup signal and slot
        connect(autoriz,SIGNAL(timeout()),this,SLOT(finishThread()));
        // Reading command from MySQL
        autoriz->start(20000);

        // Initiolization settings for system
        timAlive = new QTimer(this);
        // setup signal and slot
        connect(timAlive,SIGNAL(timeout()),this,SLOT(finishThread()));
        // Reading command from MySQL
        timAlive->start(600000);

        timModem = new QTimer(this);
        // setup signal and slot
        connect(timModem,SIGNAL(timeout()),this,SLOT(readModem()));
        // Reading command from MySQL
        timModem->start(50000);

        timBufClear = new QTimer(this);
        // setup signal and slot
        connect(timBufClear,SIGNAL(timeout()),this,SLOT(bufferClear()));

        // Starting the thread of socket to execute events
        connect(clientSocket,SIGNAL(readyRead()),this, SLOT(socketReadClient()));
        connect(clientSocket,SIGNAL(stateChanged(QAbstractSocket::SocketState)),this, SLOT(clientChangeState()));
        connect(clientSocket,SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(socketErrorClient()));
        connect(clientSocket,SIGNAL(disconnected()),this, SLOT(socketRemoveClient()));

        // String to window
        QString strSocket;
        strSocket += QString("[") + QString::number(socketDescriptor) + "] New connection!!!" + "\r\n\r\n";
        // Set text to the text browser
        println(strSocket);
    }
}

/*
 * Recive of the request to the server
 */
void SenseSystem::Client::socketReadClient(void)
{
    if(clientSocket->bytesAvailable() == 0)
        return;
    qDebug() << "Recieved some data";
}

/*
 * Close client socket
 */
void SenseSystem::Client::closeClient(int socketDescriptor)
{
    // If client socket is not removed
    if(clientSocket->socketDescriptor() != -1)
        clientSocket->close();
}

/*
 * Remove client client from list
 */
void SenseSystem::Client::removeClient(int socketDescriptor)
{
    // If client socket is not removed
    if(clientSocket->socketDescriptor() != -1)
        clientSocket->close();
    // Type of display is window application
    removeClientFromList(socketDescriptor);
    finished();
}

/*
 * Signal state of connection
 */
void SenseSystem::Client::clientChangeState()
{
    QString strSocket("");
    strSocket += QString("[") + QString::number(socketDescriptor) + "] State is";
    // Displayed the socket type of connnection
    switch(clientSocket->state())
    {
        case QAbstractSocket::UnconnectedState:
        {
            strSocket += " Unconnected\r\n";
            // Type of display is window application
            removeClientFromList(socketDescriptor);
            finished();
        }
            break;
        case QAbstractSocket::HostLookupState:
            strSocket += " HostLookup\r\n";
            break;
        case QAbstractSocket::ConnectingState:
            strSocket += " Connecting\r\n";
            break;
        case QAbstractSocket::ConnectedState:
            strSocket += " Connected\r\n";
            break;
        case QAbstractSocket::BoundState:
            strSocket += " Bound\r\n";
            break;
        case QAbstractSocket::ListeningState:
            strSocket += " Listening\r\n";
            break;
        case QAbstractSocket::ClosingState:
        {
            strSocket += " Closing\r\n";
            // Type of display is window application
            removeClientFromList(socketDescriptor);
            finished();
        }
            break;
    }
    // Set text to the text browser
    println(strSocket);
}

/*
 * Error connection
 */
void SenseSystem::Client::socketErrorClient()
{
    QTcpSocket* socket = (QTcpSocket*)sender();
    int socketDescriptor = socket->socketDescriptor();
    QString strSocket("");
    strSocket += QString("[") + QString::number(socketDescriptor) + "]" + " ERROR: " +
            socket->errorString() + "\r\n";
    println(strSocket);
}

/*
 * Disconnection
 */
void SenseSystem::Client::socketRemoveClient()
{
    // If connnection is close
    if(clientSocket->socketDescriptor() == -1)
    {
        // Type of display is window application
        removeClientFromList(socketDescriptor);
    }
    // Set text to the text browser
    QString strSocket("");
    strSocket += QString("[") + QString::number(socketDescriptor) + "] Connection  is removed\r\n";
    println(strSocket);
    finished();
}

/*
 * Handler of the events
 */
void SenseSystem::Client::customEvent(QEvent *pe)
{
    // Checking if this is the event for thread
    if ((int)pe->type() >= QEvent::User &&
        (int)pe->type() <= (QEvent::User))
    {
        ;
    }
    // Close the thread
    else if((int)pe->type() == (QEvent::User))
    {
        finished();
    }
    QObject::customEvent(pe);
}

/*
 * Handler of the events
 */
void SenseSystem::Client::finishThread(void)
{
    finished();
}

/*
 * Request to system about modem state
 */
void SenseSystem::Client::bufferClear(void)
{
    buffer.clear();
}
