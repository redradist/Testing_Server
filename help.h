#ifndef HELP_H
#define HELP_H

#include <QDialog>

namespace Ui {
class Help;
}

class Help : public QDialog
{
    Q_OBJECT

public:
    explicit Help(QDialog *parent = 0);
    ~Help();

    static bool exist;

private:
    Ui::Help *ui;
};

#endif // HELP_H
