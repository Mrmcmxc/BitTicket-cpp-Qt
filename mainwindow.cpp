#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QStringList>
#include <QListWidget>
#include <QAction>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "addticketdialog.h"
#include "editticketdialog.h"
#include "addagentdialog.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::handleMenuTicketNew);
    //connect(ui->actionAdd_Agent, &QAction::triggered, this, &MainWindow::handleAgentNew);


    connect(ui->actionLoad, &QAction::triggered, this, &MainWindow::handleLoadTickets);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::handleSaveTickets);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::handleMenuExit);
    connect(ui->pb_remove, &QPushButton::clicked, this, &MainWindow::removeSelectedTicket);
    connect(ui->lst_tickets, &QListWidget::itemClicked, this, &MainWindow::handleTicketClick);
    connect(ui->pb_modify, &QPushButton::clicked, this, &MainWindow::handleMenuTicketEdit);
    connect(ui->actionModify_Ticket, &QAction::triggered, this, &MainWindow::handleMenuTicketEdit);
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::searchProduct);
    connect(ui->actionSpyBot, &QAction::triggered,this, &MainWindow::handleThemeDarkmode);
    connect(ui->actionGravira, &QAction::triggered,this, &MainWindow::handleThemeLightmode);

    handleLoadTickets();
    ui->lst_tickets->setCurrentRow(0);
    handleTicketClick();

}

MainWindow::~MainWindow()
{
    //free up ticket list memory
    for (int i=0; i<ticketList.size(); i++)
    {
        delete ticketList.at(i);
    }

    ticketList.clear();
    delete ui;
}

void MainWindow::handleMenuTicketNew()
{
    Ticket* newTicket = nullptr;
    this->hide();
    addticketdialog addTicketDialog(newTicket, nullptr);
    addTicketDialog.setModal(true);
    addTicketDialog.exec();
    this->show();

    if (newTicket != nullptr)
    {
        ticketList.push_back(newTicket);
        ui->lst_tickets->addItem(newTicket->getTickId());
    }
} //end handleMenuItemNew



void MainWindow::removeSelectedTicket()
{
    int index = ui->lst_tickets->currentRow();

    if (index >= 0)
    {
        //remove from vector
        Ticket* theItem = ticketList.at(index);
        delete theItem;
        ticketList.removeAt(index);

        //remove from list widget in the UI
        delete ui->lst_tickets->currentItem();
    }

    //ticket details set to ""
    ui->lb_display_ticketnum->setText("");
    ui->lb_display_Incidentcat->setText("");
    ui->lb_display_impact->setText("");
    ui->lb_display_levelsupport->setText("");
    ui->lb_display_priority->setText("");
    ui->lb_display_symptoms->setText("");
    ui->lb_display_tags->setText("");
    ui->lb_display_timestamp->setText("");
    ui->lb_display_urgency->setText("");
    ui->lb_display_rating->setText("");
    ui->lb_display_Agent->setText("");
    ui->lblImage->setText("");
 
    //User details set to ""
    ui->lb_display_name->setText("");
    ui->lb_display_phone->setText("");
    ui->lb_display_email->setText("");

    QPixmap pixmap("./images/none.png");
    ui->lblImage->setPixmap(pixmap);

} //end removeSelectedProduct

void MainWindow::handleTicketClick()
{
    int index = ui->lst_tickets->currentRow();

    if (index != -1)
    {
        Ticket* theTicket = ticketList.at(index);
        ui->lb_display_ticketnum->setText(theTicket->getTickId());
        ui->lb_display_Incidentcat->setText(theTicket->getIncidentCat());
        ui->lb_display_impact->setText(theTicket->getTickImpact());
        ui->lb_display_levelsupport->setText(theTicket->getTickLevel());
        ui->lb_display_priority->setText(theTicket->getTickPriority());
        ui->lb_display_symptoms->setText(theTicket->getTickSymptoms());
        ui->lb_display_tags->setText(theTicket->getTickTag());
        ui->lb_display_timestamp->setText(theTicket->getTickTime());
        ui->lb_display_urgency->setText(theTicket->getTickUrgency());
        ui->lb_display_rating->setText(theTicket->getTickRating());
        ui->lb_display_name->setText(theTicket->getTickName());
        ui->lb_display_phone->setText(theTicket->getTickPhone());
        ui->lb_display_email->setText(theTicket->getTickEmail());
        ui->lb_display_Agent->setText(theTicket->getAgent());
        ui->lb_display_Tickstatus->setText(theTicket->getTickStatus());
        ui->lb_display_Incstatus->setText(theTicket->getIncStatus());
        ui->lb_display_Channel->setText(theTicket->getChannel());
        QPixmap pixmap(theTicket->getImageFilePath());
        ui->lblImage->setPixmap(pixmap);
        ui->lblImage->setScaledContents(true);

     } //end if
}// end handle item click

void MainWindow::handleMenuTicketEdit()
{
    int index = ui->lst_tickets->currentRow();

    if (index != -1)
    {
        Ticket* currentItem = ticketList.at(index);

        if (currentItem != nullptr)
        {
            editticketdialog editticketdialog(currentItem, nullptr);
            editticketdialog.exec();

            ui->lb_display_ticketnum->setText(currentItem->getTickId());
            ui->lb_display_Incidentcat->setText(currentItem->getIncidentCat());
            ui->lb_display_impact->setText(currentItem->getTickImpact());
            ui->lb_display_levelsupport->setText(currentItem->getTickLevel());
            ui->lb_display_priority->setText(currentItem->getTickPriority());
            ui->lb_display_symptoms->setText(currentItem->getTickSymptoms());
            ui->lb_display_tags->setText(currentItem->getTickTag());
            ui->lb_display_timestamp->setText(currentItem->getTickTime());
            ui->lb_display_urgency->setText(currentItem->getTickUrgency());
            ui->lb_display_name->setText(currentItem->getTickName());
            ui->lb_display_phone->setText(currentItem->getTickPhone());
            ui->lb_display_email->setText(currentItem->getTickEmail());
            ui->lb_display_Agent->setText(currentItem->getAgent());
            ui->lb_display_Tickstatus->setText(currentItem->getTickStatus());
            ui->lb_display_Incstatus->setText(currentItem->getIncStatus());
            ui->lb_display_Channel->setText(currentItem->getChannel());
            QPixmap pixmap(currentItem->getImageFilePath());
            ui->lblImage->setPixmap(pixmap);
            ui->lblImage->setScaledContents(true);

        } //end inner if
    } //end if

} //end handleMenuItemEdit

void MainWindow::handleMenuExit()
{
     this->close();
}

void MainWindow::handleSaveTickets()
{
    QFile outputFile("Tickets.txt");
    outputFile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&outputFile);

    for(Ticket* product:ticketList)
    {
        out << product->getTickId()<<",";
        out << product->getIncidentCat()<<",";
        out << product->getTickTag()<<",";
        out << product->getTickImpact()<<",";
        out << product->getTickUrgency()<<",";
        out << product->getTickPriority()<<",";
        out << product->getTickTime()<<",";
        out << product->getTickSymptoms()<<",";
        out << product->getTickLevel()<<",";
        out << product->getTickRating()<<",";
        out << product->getTickName()<<",";
        out << product->getTickEmail()<<",";
        out << product->getTickPhone()<<",";
        out << product->getAgent()<<",";
        out << product->getTickStatus()<<",";
        out << product->getIncStatus()<<",";
        out << product->getImageFilePath()<<",";
        out << product->getChannel() << "\n";
    }
}

void MainWindow::handleLoadTickets()
{

    QFile inputFile("Tickets.txt");
    inputFile.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream in(&inputFile);

    //clear current list and vector
    for (Ticket* temp:ticketList)
        {
            delete temp;
        }

    ticketList.clear(); //clear data model
    ui->lst_tickets->clear(); // view / ui

    while(!in.atEnd())
        {
            QString line = in.readLine();
            QStringList info = line.split(",");

            //handle list of products ui
            ui->lst_tickets->addItem(info.at(0));

            //handle vector
            Ticket* product = new Ticket(info.at(0), info.at(1),info.at(2), info.at(3),info.at(4),
                                         info.at(5),info.at(6), info.at(7),info.at(8), info.at(9), 
                                         info.at(10),info.at(11), info.at(12), info.at(13), 
                                         info.at(14), info.at(15), info.at(16), info.at(17));

            ticketList.push_back(product);

        } //end while

    in.flush();
    inputFile.close();

}

void MainWindow::searchProduct()
{
    QString search=ui->lineEdit->text();
    if (search != "")
    {

        QList<QListWidgetItem *> list = ui->lst_tickets->findItems(search, Qt::MatchContains);
        //for ( QListWidgetItem *item : list)
        for (int i=0; i<list.count(); i++)
        {
            QListWidgetItem* item = list.at(i);
            item->setBackground(Qt::red);
        }
    }
    else
    {
        for(int i = 0; i < ui->lst_tickets->count(); i++)
        {
            QListWidgetItem* item = ui->lst_tickets->item(i);
            item->setBackground(Qt::transparent);
        }
    }
}

void MainWindow::handleThemeDarkmode()
{

    //open qss file
    QFile file(":/new/res/images/Darkmode.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet { QLatin1String(file.readAll()) };

    //setup stylesheet
    setStyleSheet(styleSheet);

    //run
    show();

}

void MainWindow::handleThemeLightmode()
{
    //open qss file
    QFile file(":/new/res/images/Lightmode.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet { QLatin1String(file.readAll()) };

    //setup stylesheet
    setStyleSheet(styleSheet);

    //run
    show();
}

//void MainWindow::handleAgentNew()
//{
//    Ticket* newAgent = nullptr;
//    this->hide();
//    addagentdialog addagentdialog(newAgent, nullptr);
//    addagentdialog.setModal(true);
//    addagentdialog.exec();
//    this->show();
//
//}

void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this);
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::about(this, "About",
                       "This is the BitTicket System \n"
                       "developed for the CS106 group assignment.\n\n"
                       "Tools & Technologies used:\n"
                       "C++\n"
                       "Qt\n\n"
                       "Developers:\n"
                       "Alex Hughes\n"
                       "Mark Pepere");

}


