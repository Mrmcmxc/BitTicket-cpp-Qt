/********************************************************************************
** Form generated from reading UI file 'addagentdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDAGENTDIALOG_H
#define UI_ADDAGENTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QLabel *label_2;
    QPushButton *save;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *lb_incident_cat_3;
    QLineEdit *lineEdit_2;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(490, 252);
        label_2 = new QLabel(Form);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(160, 10, 171, 21));
        QFont font;
        font.setPointSize(14);
        font.setBold(true);
        font.setUnderline(true);
        font.setWeight(75);
        label_2->setFont(font);
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(2, 173, 237);"));
        save = new QPushButton(Form);
        save->setObjectName(QString::fromUtf8("save"));
        save->setGeometry(QRect(130, 120, 241, 31));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        save->setFont(font1);
        layoutWidget = new QWidget(Form);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(110, 60, 271, 22));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        lb_incident_cat_3 = new QLabel(layoutWidget);
        lb_incident_cat_3->setObjectName(QString::fromUtf8("lb_incident_cat_3"));

        horizontalLayout->addWidget(lb_incident_cat_3);

        lineEdit_2 = new QLineEdit(layoutWidget);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));
        QFont font2;
        font2.setBold(false);
        font2.setWeight(50);
        lineEdit_2->setFont(font2);

        horizontalLayout->addWidget(lineEdit_2);


        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        label_2->setText(QCoreApplication::translate("Form", "ADD NEW AGENT", nullptr));
        save->setText(QCoreApplication::translate("Form", "Save ", nullptr));
        lb_incident_cat_3->setText(QCoreApplication::translate("Form", "New Agent", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDAGENTDIALOG_H
