/********************************************************************************
** Form generated from reading UI file 'SBMENDISystemFeaturesDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SBMENDISYSTEMFEATURESDLG_H
#define UI_SBMENDISYSTEMFEATURESDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SBMENDISystemFeaturesDlg
{
public:
    QPushButton *OkButton;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QTextBrowser *VersionInfoBrowser;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout;
    QLabel *label_2;
    QLCDNumber *lcdNumber_4;
    QLabel *label_4;
    QLCDNumber *lcdNumber_3;
    QLabel *label_3;
    QLCDNumber *lcdNumber_1;
    QLabel *label_1;
    QLCDNumber *lcdNumber_2;

    void setupUi(QDialog *SBMENDISystemFeaturesDlg)
    {
        if (SBMENDISystemFeaturesDlg->objectName().isEmpty())
            SBMENDISystemFeaturesDlg->setObjectName(QStringLiteral("SBMENDISystemFeaturesDlg"));
        SBMENDISystemFeaturesDlg->resize(384, 388);
        OkButton = new QPushButton(SBMENDISystemFeaturesDlg);
        OkButton->setObjectName(QStringLiteral("OkButton"));
        OkButton->setGeometry(QRect(300, 360, 75, 23));
        layoutWidget = new QWidget(SBMENDISystemFeaturesDlg);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 0, 361, 351));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(layoutWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        VersionInfoBrowser = new QTextBrowser(groupBox);
        VersionInfoBrowser->setObjectName(QStringLiteral("VersionInfoBrowser"));
        VersionInfoBrowser->setGeometry(QRect(10, 20, 341, 151));

        verticalLayout->addWidget(groupBox);

        groupBox_2 = new QGroupBox(layoutWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        layoutWidget1 = new QWidget(groupBox_2);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(20, 20, 331, 141));
        gridLayout = new QGridLayout(layoutWidget1);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget1);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lcdNumber_4 = new QLCDNumber(layoutWidget1);
        lcdNumber_4->setObjectName(QStringLiteral("lcdNumber_4"));

        gridLayout->addWidget(lcdNumber_4, 3, 1, 1, 1);

        label_4 = new QLabel(layoutWidget1);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        lcdNumber_3 = new QLCDNumber(layoutWidget1);
        lcdNumber_3->setObjectName(QStringLiteral("lcdNumber_3"));

        gridLayout->addWidget(lcdNumber_3, 2, 1, 1, 1);

        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        lcdNumber_1 = new QLCDNumber(layoutWidget1);
        lcdNumber_1->setObjectName(QStringLiteral("lcdNumber_1"));

        gridLayout->addWidget(lcdNumber_1, 0, 1, 1, 1);

        label_1 = new QLabel(layoutWidget1);
        label_1->setObjectName(QStringLiteral("label_1"));

        gridLayout->addWidget(label_1, 0, 0, 1, 1);

        lcdNumber_2 = new QLCDNumber(layoutWidget1);
        lcdNumber_2->setObjectName(QStringLiteral("lcdNumber_2"));

        gridLayout->addWidget(lcdNumber_2, 1, 1, 1, 1);


        verticalLayout->addWidget(groupBox_2);

        layoutWidget->raise();
        OkButton->raise();

        retranslateUi(SBMENDISystemFeaturesDlg);

        QMetaObject::connectSlotsByName(SBMENDISystemFeaturesDlg);
    } // setupUi

    void retranslateUi(QDialog *SBMENDISystemFeaturesDlg)
    {
        SBMENDISystemFeaturesDlg->setWindowTitle(QApplication::translate("SBMENDISystemFeaturesDlg", "NDI System Features", 0));
        OkButton->setText(QApplication::translate("SBMENDISystemFeaturesDlg", "Ok", 0));
        groupBox->setTitle(QApplication::translate("SBMENDISystemFeaturesDlg", "Version Infomation", 0));
        groupBox_2->setTitle(QApplication::translate("SBMENDISystemFeaturesDlg", "System Infomation", 0));
        label_2->setText(QApplication::translate("SBMENDISystemFeaturesDlg", "TextLabel", 0));
        label_4->setText(QApplication::translate("SBMENDISystemFeaturesDlg", "TextLabel", 0));
        label_3->setText(QApplication::translate("SBMENDISystemFeaturesDlg", "TextLabel", 0));
        label_1->setText(QApplication::translate("SBMENDISystemFeaturesDlg", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class SBMENDISystemFeaturesDlg: public Ui_SBMENDISystemFeaturesDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SBMENDISYSTEMFEATURESDLG_H
