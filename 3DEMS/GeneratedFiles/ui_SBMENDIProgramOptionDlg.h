/********************************************************************************
** Form generated from reading UI file 'SBMENDIProgramOptionDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SBMENDIPROGRAMOPTIONDLG_H
#define UI_SBMENDIPROGRAMOPTIONDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SBMENDIProgramOptionDlg
{
public:
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox_3;
    QCheckBox *checkBox_ReportWhileTracking;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *checkBox_BeepOnError;
    QLabel *label_3;
    QSpinBox *spinBox_BeepOnErrorNum;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *checkBox_BeepOnWarning;
    QLabel *label_2;
    QSpinBox *spinBox_BeepOnWarningNum;
    QGroupBox *groupBox;
    QCheckBox *checkBox_LogToFile;
    QCheckBox *checkBox_DateStamp;
    QCheckBox *checkBox_ClearlogFile;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_FileName;
    QPushButton *pushButton_Browser;

    void setupUi(QDialog *SBMENDIProgramOptionDlg)
    {
        if (SBMENDIProgramOptionDlg->objectName().isEmpty())
            SBMENDIProgramOptionDlg->setObjectName(QStringLiteral("SBMENDIProgramOptionDlg"));
        SBMENDIProgramOptionDlg->resize(675, 481);
        buttonBox = new QDialogButtonBox(SBMENDIProgramOptionDlg);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setGeometry(QRect(420, 440, 193, 28));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        groupBox_3 = new QGroupBox(SBMENDIProgramOptionDlg);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(70, 330, 541, 101));
        checkBox_ReportWhileTracking = new QCheckBox(groupBox_3);
        checkBox_ReportWhileTracking->setObjectName(QStringLiteral("checkBox_ReportWhileTracking"));
        checkBox_ReportWhileTracking->setGeometry(QRect(10, 20, 541, 81));
        groupBox_2 = new QGroupBox(SBMENDIProgramOptionDlg);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(70, 200, 541, 121));
        layoutWidget = new QWidget(groupBox_2);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(31, 30, 491, 71));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        checkBox_BeepOnError = new QCheckBox(layoutWidget);
        checkBox_BeepOnError->setObjectName(QStringLiteral("checkBox_BeepOnError"));

        horizontalLayout_3->addWidget(checkBox_BeepOnError);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_3->addWidget(label_3);

        spinBox_BeepOnErrorNum = new QSpinBox(layoutWidget);
        spinBox_BeepOnErrorNum->setObjectName(QStringLiteral("spinBox_BeepOnErrorNum"));
        spinBox_BeepOnErrorNum->setMaximum(5);

        horizontalLayout_3->addWidget(spinBox_BeepOnErrorNum);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        checkBox_BeepOnWarning = new QCheckBox(layoutWidget);
        checkBox_BeepOnWarning->setObjectName(QStringLiteral("checkBox_BeepOnWarning"));

        horizontalLayout_2->addWidget(checkBox_BeepOnWarning);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        spinBox_BeepOnWarningNum = new QSpinBox(layoutWidget);
        spinBox_BeepOnWarningNum->setObjectName(QStringLiteral("spinBox_BeepOnWarningNum"));
        spinBox_BeepOnWarningNum->setMaximum(5);

        horizontalLayout_2->addWidget(spinBox_BeepOnWarningNum);


        verticalLayout->addLayout(horizontalLayout_2);

        groupBox = new QGroupBox(SBMENDIProgramOptionDlg);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(70, 40, 541, 151));
        checkBox_LogToFile = new QCheckBox(groupBox);
        checkBox_LogToFile->setObjectName(QStringLiteral("checkBox_LogToFile"));
        checkBox_LogToFile->setGeometry(QRect(13, 28, 307, 19));
        checkBox_DateStamp = new QCheckBox(groupBox);
        checkBox_DateStamp->setObjectName(QStringLiteral("checkBox_DateStamp"));
        checkBox_DateStamp->setGeometry(QRect(13, 91, 171, 19));
        checkBox_ClearlogFile = new QCheckBox(groupBox);
        checkBox_ClearlogFile->setObjectName(QStringLiteral("checkBox_ClearlogFile"));
        checkBox_ClearlogFile->setGeometry(QRect(13, 117, 307, 19));
        layoutWidget1 = new QWidget(groupBox);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(14, 55, 501, 30));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget1);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEdit_FileName = new QLineEdit(layoutWidget1);
        lineEdit_FileName->setObjectName(QStringLiteral("lineEdit_FileName"));

        horizontalLayout->addWidget(lineEdit_FileName);

        pushButton_Browser = new QPushButton(layoutWidget1);
        pushButton_Browser->setObjectName(QStringLiteral("pushButton_Browser"));

        horizontalLayout->addWidget(pushButton_Browser);


        retranslateUi(SBMENDIProgramOptionDlg);
        QObject::connect(buttonBox, SIGNAL(accepted()), SBMENDIProgramOptionDlg, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SBMENDIProgramOptionDlg, SLOT(reject()));

        QMetaObject::connectSlotsByName(SBMENDIProgramOptionDlg);
    } // setupUi

    void retranslateUi(QDialog *SBMENDIProgramOptionDlg)
    {
        SBMENDIProgramOptionDlg->setWindowTitle(QApplication::translate("SBMENDIProgramOptionDlg", "NDI Program options", 0));
        groupBox_3->setTitle(QApplication::translate("SBMENDIProgramOptionDlg", "Message options", 0));
        checkBox_ReportWhileTracking->setText(QApplication::translate("SBMENDIProgramOptionDlg", "Display error messages while in tracking mode\n"
"System needs to restart tracking for setting to take affect", 0));
        groupBox_2->setTitle(QApplication::translate("SBMENDIProgramOptionDlg", "Beep options", 0));
        checkBox_BeepOnError->setText(QApplication::translate("SBMENDIProgramOptionDlg", "Beep system on ERROR return", 0));
        label_3->setText(QApplication::translate("SBMENDIProgramOptionDlg", "Nunbers of:", 0));
        checkBox_BeepOnWarning->setText(QApplication::translate("SBMENDIProgramOptionDlg", "Beep system on WARNING return", 0));
        label_2->setText(QApplication::translate("SBMENDIProgramOptionDlg", "Nunbers of:", 0));
        groupBox->setTitle(QApplication::translate("SBMENDIProgramOptionDlg", "Logging to a file", 0));
        checkBox_LogToFile->setText(QApplication::translate("SBMENDIProgramOptionDlg", "Log COM port communications to file", 0));
        checkBox_DateStamp->setText(QApplication::translate("SBMENDIProgramOptionDlg", "Include time stamp", 0));
        checkBox_ClearlogFile->setText(QApplication::translate("SBMENDIProgramOptionDlg", "Clear file on system initialization", 0));
        label->setText(QApplication::translate("SBMENDIProgramOptionDlg", "File:", 0));
        pushButton_Browser->setText(QApplication::translate("SBMENDIProgramOptionDlg", "Browser", 0));
    } // retranslateUi

};

namespace Ui {
    class SBMENDIProgramOptionDlg: public Ui_SBMENDIProgramOptionDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SBMENDIPROGRAMOPTIONDLG_H
