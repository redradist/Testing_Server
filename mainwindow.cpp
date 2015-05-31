#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "CRC/CRC16.h"

#include "help.h"
#include "config.h"
#include "server.h"
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QHeaderView>
#include <QDesktopServices>

extern SenseSystem::Config config;

/*
 * Constructor of MainWindow
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Function of a preview settings for the user interface
    ui->setupUi(this);

    changeAnswerClient(false);
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(OpenHelp()));

    ui->portIP->setText(QString::number(config.port));
    server = new SenseSystem::TechServer(config.port,this);
    connect(this,SIGNAL(println(QString)),this,SLOT(outStream(QString)));
    // Checking server is started
    if(server != NULL)
    {
        // If server is started
        ui->buttonStart->setDisabled(true);
        ui->buttonStop->setEnabled(true);
        ui->portIP->setDisabled(true);
        // Set text to the text browser
        println("Server is working!\r\n");
        println("UTC: "+QDateTime::currentDateTimeUtc().toString()+"\r\n\r\n");
        connect(ui->buttonStart, SIGNAL(clicked()), this, SLOT(on_buttonStart_clicked()));
        connect(ui->buttonStop, SIGNAL(clicked()), this, SLOT(on_buttonStop_clicked()));
        connect(ui->clear, SIGNAL(clicked()), this, SLOT(on_clear_clicked()));
    }
    else
    {
        // Server isn't started
        println("Server isn\'t working!!!\r\n");
        println("Please check the internet connection\r\n");
    }
}

/*
 * Destructor of class MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * Add string to log information
 */
std::string MainWindow::inStream(void)
{

}

/*
 * Add string to log information
 */
void MainWindow::outStream(QString str)
{
    if(ui->Testing->toPlainText().length() >= 2000)
    {
        ui->Testing->clear();
    }
    ui->Testing->setText(ui->Testing->toPlainText()+str);
}

/*
 * Changing state of buttons for commnad to a client
 */
void MainWindow::changeAnswerClient(bool select)
{
    // If no current
    if(select == false)
    {
        ui->portIP->setDisabled(true);
        ui->sendClient->setDisabled(true);
    }
    // If is current
    else
    {
        ui->portIP->setEnabled(true);
        ui->sendClient->setEnabled(true);
    }
}

/*
 * Open help about this program
 */
void MainWindow::OpenHelp()
{
    if(!Help::exist)
    {
        hlp = new Help();
        hlp->show();
    }
}

/*
 * Find recor about client in the list
 */
QListWidgetItem* MainWindow::findListOfClients(int IDSocket)
{
    QList<QListWidgetItem *> listClients = ui->listClients->findItems(QString("Client [")+QString::number(IDSocket)+"] is authorized",Qt::MatchFixedString);
    // If list is not empty
    if(listClients.empty() == false)
    {
        qDebug() << listClients.at(0)->text();
        return listClients.at(0);
    }
    // else if list is empty
    else
        return NULL;
}

/*
 * Add record about client to list
 */
void MainWindow::addClientToList(int IDSocket)
{
    QList<QListWidgetItem*> listClients = ui->listClients->findItems(QString("Client [")+QString::number(IDSocket)+"] is authorized",Qt::MatchFixedString);
    // If list of clients is empty
    if(listClients.empty() == true)
    {
        ui->listClients->addItem(QString("Client [")+QString::number(IDSocket)+"] is authorized");
    }
    // else if list of clients is not empty
    else
    {
        // If client is autorized
        listClients.at(0)->setText(QString("Client [")+QString::number(IDSocket)+"] is authorized");
    }
}

/*
 * Remove record about client from list
 */
void MainWindow::removeClientFromList(int IDSocket)
{
    QList<QListWidgetItem*> listClients = ui->listClients->findItems(QString("Client [")+QString::number(IDSocket)+"] is authorized",Qt::MatchFixedString);
    // If list of clients is empty
    if(listClients.empty() == false)
    {
        delete listClients.at(0);
    }
}

void MainWindow::displayInfoOfClient(int IDSocket)
{

}

void MainWindow::displayAllClient()
{

}

/*
 * Starting the server
 */
void MainWindow::on_buttonStart_clicked()
{
    // If server is not started
    if(server == NULL)
    {
        server = new SenseSystem::TechServer(ui->portIP->text().toInt());
        ui->buttonStart->setDisabled(true);
        ui->buttonStop->setEnabled(true);
        ui->portIP->setDisabled(true);
        // Set text to the text browser
        println("                       Server is started                       \r\n");
    }
}

/*
 * Stop the server
 */
void MainWindow::on_buttonStop_clicked()
{
    // If server is not stoped
    if(server != NULL)
    {
        ui->buttonStart->setEnabled(true);
        ui->buttonStop->setDisabled(true);
        ui->portIP->setDisabled(true);
        server->deleteLater();
        server = NULL;
        // Set text to the text browser
        println("                       Server is stoped                       \r\n");
    }
}

/*
 * Clear log screen
 */
void MainWindow::on_clear_clicked()
{
    ui->Testing->clear();
}

/*
 * Send to the client a command
 */
void MainWindow::on_sendClient_clicked()
{
    // Finding client by IDSocket
    foreach(int i,server->client.keys()){
        // If current client is select
        if(ui->listClients->currentItem() == findListOfClients(i))
        {
            ;
        }
    }
}

/*
 * Check current items
 */
void MainWindow::on_listClients_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    // If no current
    if(current == NULL)
    {
        changeAnswerClient(false);
        ui->deleteClient->setDisabled(true);
    }
    // If is current
    else
    {
        bool select = false;
        // Search client ID
        foreach(int i,server->client.keys()){
            if(current == findListOfClients(i))
            {
                select = true;
            }
        }
        changeAnswerClient(select);
        ui->deleteClient->setEnabled(select);
    }
    ui->listClients->setCurrentItem(current);
}

/*
 * Check current items
 */
void MainWindow::on_listClients_itemDoubleClicked(QListWidgetItem *item)
{
    // If no current
    if(item == NULL)
    {
        changeAnswerClient(false);
        ui->deleteClient->setDisabled(true);
    }
    // If is current
    else
    {
        bool select = false;
        // Search client ID
        foreach(int i,server->client.keys()){
            if(item == findListOfClients(i))
            {
                select = true;
            }
        }
        changeAnswerClient(select);
        ui->deleteClient->setEnabled(select);
    }
    ui->listClients->setCurrentItem(item);
}

/*
 * Delete client
 */
void MainWindow::on_deleteClient_clicked()
{
    // Search client ID
    foreach(int i,server->client.keys()){
        if(ui->listClients->currentItem() == findListOfClients(i))
        {
            server->removeClient(i);
        }
    }
}


