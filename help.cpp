#include "help.h"
#include "ui_help.h"
#include "config.h"

bool Help::exist = false;

/*
 *  Constructor of a douter window program
 */
Help::Help(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::Help)
{
    /*
     *  Function of preview settings of output window graphics
     */
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose, true);
    this->setWindowFlags(Qt::Dialog | Qt::WindowFullscreenButtonHint);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    //setWindowFlags();
    exist = true;
    ui->label_Date->setText(QString("Дата релиза: ")+__DATE__);
    ui->label_Date->setFont(QFont("MS Shell Dlg 2",10,400));
}

/*
 * Destructor of a douter window program
 */
Help::~Help()
{
    close();
    delete ui;
    exist = false;
}
