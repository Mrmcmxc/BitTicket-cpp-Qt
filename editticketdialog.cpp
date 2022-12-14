#include "editticketdialog.h"
#include "ui_editticketdialog.h"

#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QListView>
#include <QTextStream>

editticketdialog::editticketdialog(Ticket* editTicket,QWidget *parent) : QDialog(parent), ui(new Ui::editticketdialog)
{
    ui->setupUi(this);

    //population of combo box for Incident Category
    incident.push_back("Hardware");
    incident.push_back("Software");
    incident.push_back("Account Management");
    incident.push_back("Applications");
    incident.push_back("Finance");
    incident.push_back("Human Resources");
    incident.push_back("Networking");
    incident.push_back("Other");
    incident.push_back("");
    ui->comboBox_5->addItems(incident);
    ui->comboBox_5->setCurrentIndex(8);
    qobject_cast<QListView *>(ui->comboBox_5->view())->setRowHidden(8, true);

    //Add items to data model
    //agent.push_back("");
    agent.push_back("Mark");
    agent.push_back("Alex");
    agent.push_back("Steve");
    agent.push_back("Luke");

    //ui->comboBox_A->addItems(agent);

    for (int i = 0; i < agent.size(); i++)
    {
        ui->comboBox_A->addItem(agent.at(i));
    }

    ui->comboBox_A->setEditable(true);
    ui->comboBox_A->insertItem(0, "New Entry");

    //population of combo box for Impact
    impact.push_back("Low");
    impact.push_back("Medium");
    impact.push_back("High");
    impact.push_back("");
    ui->comboBox_6->addItems(impact);
    ui->comboBox_6->setCurrentIndex(3);
    qobject_cast<QListView *>(ui->comboBox_6->view())->setRowHidden(3, true);

    //population of combo box for Urgency
    urgency.push_back("Low");
    urgency.push_back("Medium");
    urgency.push_back("High");
    urgency.push_back("");
    ui->comboBox_3->addItems(urgency);
    ui->comboBox_3->setCurrentIndex(3);
    qobject_cast<QListView *>(ui->comboBox_3->view())->setRowHidden(3, true);

    //population of combo box for Priority
    priority.push_back("None");
    priority.push_back("Low");
    priority.push_back("Medium");
    priority.push_back("High");
    priority.push_back("Critical");
    priority.push_back("");
    ui->comboBox_2->addItems(priority);
    ui->comboBox_2->setCurrentIndex(5);
    qobject_cast<QListView *>(ui->comboBox_2->view())->setRowHidden(6, true);

    //population of combo box for Level of support
    level.push_back("Tier 1");
    level.push_back("Tier 2");
    level.push_back("Tier 3");
    level.push_back("");
    ui->comboBox->addItems(level);
    ui->comboBox->setCurrentIndex(3);
    qobject_cast<QListView *>(ui->comboBox->view())->setRowHidden(3, true);


    //Ticket status
    status.push_back("Closed");
    status.push_back("Re-opened");
    status.push_back("");
    ui->comboBox_TS1->addItems(status);
    ui->comboBox_TS1->setCurrentIndex(2);
     qobject_cast<QListView *>(ui->comboBox_TS1->view())->setRowHidden(2, true);

    //Incident Status
    incstatus.push_back("Solved");
    incstatus.push_back("Not Solved");
    incstatus.push_back("Ongoing");
    incstatus.push_back("");
    ui->comboBox_IS1->addItems(incstatus);
    ui->comboBox_IS1->setCurrentIndex(3);
    qobject_cast<QListView *>(ui->comboBox_IS1->view())->setRowHidden(3, true);

    //population of combo box for Rating
    rating.push_back("");
    rating.push_back("0 Stars");
    rating.push_back("1 Stars");
    rating.push_back("2 Stars");
    rating.push_back("3 Stars");
    rating.push_back("4 Stars");
    rating.push_back("5 Stars");
    ui->comboBox_R->addItems(rating);
    ui->comboBox_R->setCurrentIndex(0);
    qobject_cast<QListView*>(ui->comboBox_R->view())->setRowHidden(0, true);

    this->editTicket = editTicket;

    if (editTicket != nullptr)
    {
        ui->lb_ticket_num->setText(editTicket->getTickId());
        ui->comboBox_5->setCurrentText(editTicket->getIncidentCat());
        ui->lineEdit_Tag->setText(editTicket->getTickTag());
        ui->comboBox_6->setCurrentText(editTicket->getTickImpact());
        ui->comboBox_3->setCurrentText(editTicket->getTickUrgency());
        ui->comboBox_2->setCurrentText(editTicket->getTickPriority());
        ui->comboBox->setCurrentText(editTicket->getTickLevel());
        ui->lineEdit_4->setText(editTicket->getTickSymptoms());
        ui->comboBox_R->setCurrentText(editTicket->getTickRating());
        ui->lineEdit_10->setText(editTicket->getTickName());
        ui->lineEdit_11->setText(editTicket->getTickPhone());
        ui->lineEdit_12->setText(editTicket->getTickEmail());
        ui->comboBox_A->setCurrentText(editTicket->getAgent());
        ui->comboBox_TS1->setCurrentText(editTicket->getTickStatus());
        ui->comboBox_IS1->setCurrentText(editTicket->getIncStatus());

        QPixmap pixmap(editTicket->getImageFilePath());
        ui->lblImage->setPixmap(pixmap);
        ui->lblImage->setScaledContents(true);
        imageFilePath = editTicket->getImageFilePath();
    }
    //connection
    connect(ui->pushButton, &QPushButton::clicked,this, &editticketdialog::confirmUpdate);
    connect(ui->pushButton_2, &QPushButton::clicked,this, &editticketdialog::loadItemImage);
}

editticketdialog::~editticketdialog()
{
    delete ui;
}

void editticketdialog::confirmUpdate()
{
    //connection
    QString incident = ui->comboBox_5->currentText();
    QString tag = ui->lineEdit_Tag->text();
    QString impact = ui->comboBox_6->currentText();
    QString urgency = ui->comboBox_3->currentText();
    QString priority = ui->comboBox_2->currentText();
    QString symptoms = ui->lineEdit_4->text();
    QString level = ui->comboBox->currentText();
    QString rating  = ui->comboBox_R->currentText();
    QString name = ui->lineEdit_10->text();
    QString email = ui->lineEdit_11->text();
    QString phone  = ui->lineEdit_12->text();
    QString agent = ui->comboBox_A->currentText();
    QString status = ui->comboBox_TS1->currentText();
    QString incstatus = ui->comboBox_IS1->currentText();

    //checking conditions
    if (!(incident.isEmpty()))
    {
        editTicket->setIncidentCat(incident);
        editTicket->setTickTag(tag);
        editTicket->setTickImpact(impact);
        editTicket->setTickUrgency(urgency);
        editTicket->setTickPriority(priority);
        editTicket->setTickSymptoms(symptoms);
        editTicket->setTickLevel(level);
        editTicket->setTickRating(rating);
        editTicket->setTickName(name);
        editTicket->setTickEmail(email);
        editTicket->setTickPhone(phone);
        editTicket->setAgent(agent);
        editTicket->setTickStatus(status);
        editTicket->setIncStatus(incstatus);
        editTicket->setImageFilePath(imageFilePath);
        this->close();
    }

    else
    {

        QString message(tr("All information is required, Please complete the form to proceed."));
        QMessageBox::information(this, tr("Add Ticket"), message); //passing and closing

    }
}
void editticketdialog::loadItemImage()
{
    QString filename;

    filename = QFileDialog::getOpenFileName(this,"Open Image", "./", "Image Files (*.png *.jpg)");

    if (filename != "")
    {
        int lastSlash = filename.lastIndexOf("/");
        QString shortName = filename.right(filename.size() - lastSlash - 1);

        QFile::copy(filename, "./images/" + shortName);
        QPixmap pixmap("./images/" + shortName);

        ui->lblImage->setPixmap(pixmap);
        ui->lblImage->setScaledContents(true);

        //update internal data
        imageFilePath = "./images/" + shortName;
    } //end if
}//end loadItemImage
