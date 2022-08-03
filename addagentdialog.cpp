#include "addagentdialog.h"
#include "ui_addagentdialog.h"

#include <QDir>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QListView>

addagentdialog::addagentdialog(Ticket*& newAgent, QWidget* parent) : QDialog(parent), ui(new Ui::addagentdialog)
{
    ui->setupUi(this);
    this->newAgent = &newAgent;
 
    connect(ui->pushButton, &QPushButton::clicked, this, &addagentdialog::save);
   

addagentdialog::~addagentdialog()
{
    delete ui;
}



void addagentdialog::save()
{
    QString filename = "C:/Users/alexh/Desktop/BitTicket (2)/BitTicket/build-BitTicketMain-Desktop_Qt_5_12_11_MinGW_64_bit-Debug/Agents.txt";
    QFile file(filename);
    if (file.open(QIODevice::ReadWrite)) {
        QTextStream stream(&file);
        stream << "something" << endl;
    }
}
