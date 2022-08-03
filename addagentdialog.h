#ifndef ADDAGENTDIALOG_H
#define ADDAGENTDIALOG_H

#include <QDialog>
#include "ticket.h"


namespace Ui {
    class addagentdialog;
}

class addagentdialog : public QDialog
{
    Q_OBJECT

public:
    explicit addagentdialog(Ticket*& newAgent, QWidget* parent = nullptr);
    ~addagentdialog();

    void save();
    

private:
    Ui::addagentdialog* ui;
    Ticket** newAgent;

    QStringList agent;

};

#endif // ADDTICKETDIALOG_H