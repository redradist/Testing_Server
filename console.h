#ifndef CONSOLE_H
#define CONSOLE_H

#include "stdint.h"
#include "view.h"
//#include "easyloggingpp++/easylogging++.h"

class Console : public QObject, public View
{
    Q_OBJECT

public:
    explicit Console(QStringList agruments, QObject *parent = 0);
    ~Console();

    std::string inStream(void);

signals:
    void println(QString str);

public slots:
    void outStream(QString str);
    void addClientToList(int IDSocket);
    void removeClientFromList(int IDSocket);
    void displayInfoOfClient(int IDSocket);
    void displayAllClient();

private:
    QStringList agruments;
};

#endif // CONSOLE_H
