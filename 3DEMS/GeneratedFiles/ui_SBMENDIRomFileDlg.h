/********************************************************************************
** Form generated from reading UI file 'SBMENDIRomFileDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SBMENDIROMFILEDLG_H
#define UI_SBMENDIROMFILEDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SBMENDIRomFileDlg
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidget_RomFile;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEdit_PortID;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QLineEdit *lineEdit_RomFileName;
    QPushButton *pushButton_Browse;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_Save;
    QPushButton *pushButton_Close;

    void setupUi(QDialog *SBMENDIRomFileDlg)
    {
        if (SBMENDIRomFileDlg->objectName().isEmpty())
            SBMENDIRomFileDlg->setObjectName(QStringLiteral("SBMENDIRomFileDlg"));
        SBMENDIRomFileDlg->resize(587, 445);
        layoutWidget = new QWidget(SBMENDIRomFileDlg);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(11, 11, 561, 361));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tableWidget_RomFile = new QTableWidget(layoutWidget);
        tableWidget_RomFile->setObjectName(QStringLiteral("tableWidget_RomFile"));

        verticalLayout->addWidget(tableWidget_RomFile);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        lineEdit_PortID = new QLineEdit(layoutWidget);
        lineEdit_PortID->setObjectName(QStringLiteral("lineEdit_PortID"));
        lineEdit_PortID->setReadOnly(true);

        horizontalLayout_2->addWidget(lineEdit_PortID);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        lineEdit_RomFileName = new QLineEdit(layoutWidget);
        lineEdit_RomFileName->setObjectName(QStringLiteral("lineEdit_RomFileName"));
        lineEdit_RomFileName->setReadOnly(true);

        horizontalLayout->addWidget(lineEdit_RomFileName);

        pushButton_Browse = new QPushButton(layoutWidget);
        pushButton_Browse->setObjectName(QStringLiteral("pushButton_Browse"));

        horizontalLayout->addWidget(pushButton_Browse);


        verticalLayout->addLayout(horizontalLayout);

        layoutWidget1 = new QWidget(SBMENDIRomFileDlg);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(310, 390, 195, 30));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        pushButton_Save = new QPushButton(layoutWidget1);
        pushButton_Save->setObjectName(QStringLiteral("pushButton_Save"));

        horizontalLayout_3->addWidget(pushButton_Save);

        pushButton_Close = new QPushButton(layoutWidget1);
        pushButton_Close->setObjectName(QStringLiteral("pushButton_Close"));

        horizontalLayout_3->addWidget(pushButton_Close);


        retranslateUi(SBMENDIRomFileDlg);

        QMetaObject::connectSlotsByName(SBMENDIRomFileDlg);
    } // setupUi

    void retranslateUi(QDialog *SBMENDIRomFileDlg)
    {
        SBMENDIRomFileDlg->setWindowTitle(QApplication::translate("SBMENDIRomFileDlg", "NDI Rom File Settings", 0));
        label->setText(QApplication::translate("SBMENDIRomFileDlg", "PortID:", 0));
        label_2->setText(QApplication::translate("SBMENDIRomFileDlg", "RomFile:", 0));
        pushButton_Browse->setText(QApplication::translate("SBMENDIRomFileDlg", "Browse", 0));
        pushButton_Save->setText(QApplication::translate("SBMENDIRomFileDlg", "Save", 0));
        pushButton_Close->setText(QApplication::translate("SBMENDIRomFileDlg", "Close", 0));
    } // retranslateUi

};

namespace Ui {
    class SBMENDIRomFileDlg: public Ui_SBMENDIRomFileDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SBMENDIROMFILEDLG_H
