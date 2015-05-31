#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QTimer>
#include <QTableWidgetItem>
#include <QLocalSocket>
#include <QListWidgetItem>
#include "stdint.h"
#include "server.h"
#include "console.h"
#include "help.h"
//#include "easyloggingpp++/easylogging++.h"

namespace Ui {
    class MainWindow;
}

/*
 * MainWindow in visual mode of server
 */
class MainWindow : public QMainWindow,  public View
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    std::string inStream(void); 

private:
    Ui::MainWindow *ui;

    Help *hlp;
    void changeAnswerClient(bool select);
    QListWidgetItem* findListOfClients(int IDSocket);

signals:
    void println(QString str);

public slots:
    void outStream(QString str);
    void addClientToList(int IDSocket);
    void removeClientFromList(int IDSocket);
    void displayInfoOfClient(int IDSocket);
    void displayAllClient();

private slots:
    void OpenHelp();
    void on_buttonStart_clicked();
    void on_buttonStop_clicked();
    void on_sendClient_clicked();
    void on_clear_clicked();
    void on_listClients_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);
    void on_deleteClient_clicked();
    void on_listClients_itemDoubleClicked(QListWidgetItem *item);
};

#endif // MAINWINDOW_H
