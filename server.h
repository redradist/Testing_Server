#ifndef TECHSERVER_H
#define TECHSERVER_H

#include <QApplication>
#include <QtNetwork>
#include <QTcpSocket>
#include <QDir>
#include <QByteArray>
#include <QDebug>
#include "stdint.h"
#include "client.h"

#define	VARIANTPRICE            3
#define	PASSWORD_LEN            4
#define STR_LEN                 30
#define MODEM_PACKET_LEN        1460
#define SETTINGS_LEN            2500
#define RECORDS_LOG_ANSWER      50

namespace SenseSystem {
    // Answer to modem
    class TechServer : public QObject
    {
        Q_OBJECT

    public:
        explicit TechServer(int port, QObject *parent = 0);
        ~TechServer();

        QMap<int,Client *> client;

        void removeClient(int IDSocket);

    private:
        const int   server_port;
        QTcpServer  *tcpServer;

    private slots:
        void newclient();
        void removeMap(int IDSocket);
    };
}

#endif // TECHSERVER_H
