#ifndef SOCKET_H
#define SOCKET_H

#include <QApplication>
#include <QtNetwork>
#include <QTcpSocket>
#include <QThread>
#include <QMutex>
#include <QByteArray>
#include <QDebug>
#include "stdint.h"

namespace SenseSystem {
    // Answer to modem
    class Client : public QObject
    {
        Q_OBJECT

    public:
        explicit Client(qintptr socketDescriptor);
        ~Client();

    private:
        void deleteClient(int IDSocket);
        void closeClient(int IDSocket);
        void removeClient(int IDSocket);

        QTimer              *autoriz;
        QTimer              *timer;
        QTimer              *timModem;
        QTimer              *timAlive;
        QTimer              *timBufClear;
        QTcpSocket          *clientSocket;

        int                 comCount;
        int                 IDSystem;
        QString             imei;
        const qintptr       socketDescriptor;

        // Client information
        bool autorizationClient;
        QByteArray buffer;
        unsigned char multiplexNum;
        QByteArray multiplexFromClient;
        bool answerClient;
        QByteArray payloadToClient;

    signals:
        void finished();
        void println(QString str);
        void addClientToList(int IDSocket);
        void removeClientFromList(int IDSocket);
        void error(QString err);

    public slots:
        void process(void);
        void customEvent(QEvent *pe);
        void bufferClear(void);
        void finishThread(void);
        void clientChangeState(void);
        void socketReadClient(void);
        void socketErrorClient(void);
        void socketRemoveClient(void);
    };
}

#endif // SOCKET_H
