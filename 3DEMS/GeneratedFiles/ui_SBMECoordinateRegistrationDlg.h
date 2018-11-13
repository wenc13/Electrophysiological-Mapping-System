/********************************************************************************
** Form generated from reading UI file 'SBMECoordinateRegistrationDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SBMECOORDINATEREGISTRATIONDLG_H
#define UI_SBMECOORDINATEREGISTRATIONDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SBMECoordinateRegistrationDlg
{
public:
    QLabel *label_Rx;
    QLabel *label_Ry;
    QLabel *label_Rz;
    QLabel *label_Tx;
    QLabel *label_Ty;
    QLabel *label_Tz;
    QLabel *label_Info;
    QPushButton *pushButton_GetNDIPoint;
    QPushButton *pushButton_GetModelPoint;
    QPushButton *pushButton_StartRegister;
    QLineEdit *lineEdit_Rx;
    QLineEdit *lineEdit_Ry;
    QLineEdit *lineEdit_Rz;
    QLineEdit *lineEdit_Tx;
    QLineEdit *lineEdit_Ty;
    QLineEdit *lineEdit_TZ;
    QLineEdit *lineEdit_Info;
    QLineEdit *lineEdit_NDIpointX;
    QLineEdit *lineEdit_NDIpointY;
    QLineEdit *lineEdit_NDIpointZ;
    QLineEdit *lineEdit_ModelPointX;
    QLineEdit *lineEdit_ModelPointY;
    QLineEdit *lineEdit_ModelPointZ;
    QLabel *label_ModelPointX;
    QLabel *label_ModelPointY;
    QLabel *label_ModelPointZ;
    QLabel *label_NDIPointX;
    QLabel *label_NDIPointY;
    QLabel *label_NDIPointZ;

    void setupUi(QDialog *SBMECoordinateRegistrationDlg)
    {
        if (SBMECoordinateRegistrationDlg->objectName().isEmpty())
            SBMECoordinateRegistrationDlg->setObjectName(QStringLiteral("SBMECoordinateRegistrationDlg"));
        SBMECoordinateRegistrationDlg->resize(396, 388);
        label_Rx = new QLabel(SBMECoordinateRegistrationDlg);
        label_Rx->setObjectName(QStringLiteral("label_Rx"));
        label_Rx->setGeometry(QRect(10, 311, 31, 16));
        label_Ry = new QLabel(SBMECoordinateRegistrationDlg);
        label_Ry->setObjectName(QStringLiteral("label_Ry"));
        label_Ry->setGeometry(QRect(136, 311, 21, 16));
        label_Rz = new QLabel(SBMECoordinateRegistrationDlg);
        label_Rz->setObjectName(QStringLiteral("label_Rz"));
        label_Rz->setGeometry(QRect(260, 311, 21, 16));
        label_Tx = new QLabel(SBMECoordinateRegistrationDlg);
        label_Tx->setObjectName(QStringLiteral("label_Tx"));
        label_Tx->setGeometry(QRect(10, 354, 21, 16));
        label_Ty = new QLabel(SBMECoordinateRegistrationDlg);
        label_Ty->setObjectName(QStringLiteral("label_Ty"));
        label_Ty->setGeometry(QRect(136, 354, 21, 16));
        label_Tz = new QLabel(SBMECoordinateRegistrationDlg);
        label_Tz->setObjectName(QStringLiteral("label_Tz"));
        label_Tz->setGeometry(QRect(260, 354, 21, 16));
        label_Info = new QLabel(SBMECoordinateRegistrationDlg);
        label_Info->setObjectName(QStringLiteral("label_Info"));
        label_Info->setGeometry(QRect(20, 210, 41, 16));
        pushButton_GetNDIPoint = new QPushButton(SBMECoordinateRegistrationDlg);
        pushButton_GetNDIPoint->setObjectName(QStringLiteral("pushButton_GetNDIPoint"));
        pushButton_GetNDIPoint->setGeometry(QRect(240, 10, 131, 31));
        pushButton_GetModelPoint = new QPushButton(SBMECoordinateRegistrationDlg);
        pushButton_GetModelPoint->setObjectName(QStringLiteral("pushButton_GetModelPoint"));
        pushButton_GetModelPoint->setGeometry(QRect(240, 110, 131, 31));
        pushButton_StartRegister = new QPushButton(SBMECoordinateRegistrationDlg);
        pushButton_StartRegister->setObjectName(QStringLiteral("pushButton_StartRegister"));
        pushButton_StartRegister->setGeometry(QRect(290, 260, 81, 31));
        lineEdit_Rx = new QLineEdit(SBMECoordinateRegistrationDlg);
        lineEdit_Rx->setObjectName(QStringLiteral("lineEdit_Rx"));
        lineEdit_Rx->setGeometry(QRect(40, 310, 81, 20));
        lineEdit_Rx->setReadOnly(true);
        lineEdit_Ry = new QLineEdit(SBMECoordinateRegistrationDlg);
        lineEdit_Ry->setObjectName(QStringLiteral("lineEdit_Ry"));
        lineEdit_Ry->setGeometry(QRect(170, 310, 81, 20));
        lineEdit_Ry->setReadOnly(true);
        lineEdit_Rz = new QLineEdit(SBMECoordinateRegistrationDlg);
        lineEdit_Rz->setObjectName(QStringLiteral("lineEdit_Rz"));
        lineEdit_Rz->setGeometry(QRect(290, 310, 81, 20));
        lineEdit_Rz->setReadOnly(true);
        lineEdit_Tx = new QLineEdit(SBMECoordinateRegistrationDlg);
        lineEdit_Tx->setObjectName(QStringLiteral("lineEdit_Tx"));
        lineEdit_Tx->setGeometry(QRect(40, 350, 81, 20));
        lineEdit_Tx->setReadOnly(true);
        lineEdit_Ty = new QLineEdit(SBMECoordinateRegistrationDlg);
        lineEdit_Ty->setObjectName(QStringLiteral("lineEdit_Ty"));
        lineEdit_Ty->setGeometry(QRect(170, 350, 81, 20));
        lineEdit_Ty->setReadOnly(true);
        lineEdit_TZ = new QLineEdit(SBMECoordinateRegistrationDlg);
        lineEdit_TZ->setObjectName(QStringLiteral("lineEdit_TZ"));
        lineEdit_TZ->setGeometry(QRect(290, 350, 81, 20));
        lineEdit_TZ->setReadOnly(true);
        lineEdit_Info = new QLineEdit(SBMECoordinateRegistrationDlg);
        lineEdit_Info->setObjectName(QStringLiteral("lineEdit_Info"));
        lineEdit_Info->setGeometry(QRect(0, 230, 371, 20));
        lineEdit_NDIpointX = new QLineEdit(SBMECoordinateRegistrationDlg);
        lineEdit_NDIpointX->setObjectName(QStringLiteral("lineEdit_NDIpointX"));
        lineEdit_NDIpointX->setGeometry(QRect(20, 80, 71, 21));
        lineEdit_NDIpointY = new QLineEdit(SBMECoordinateRegistrationDlg);
        lineEdit_NDIpointY->setObjectName(QStringLiteral("lineEdit_NDIpointY"));
        lineEdit_NDIpointY->setGeometry(QRect(110, 80, 71, 21));
        lineEdit_NDIpointZ = new QLineEdit(SBMECoordinateRegistrationDlg);
        lineEdit_NDIpointZ->setObjectName(QStringLiteral("lineEdit_NDIpointZ"));
        lineEdit_NDIpointZ->setGeometry(QRect(200, 80, 71, 21));
        lineEdit_ModelPointX = new QLineEdit(SBMECoordinateRegistrationDlg);
        lineEdit_ModelPointX->setObjectName(QStringLiteral("lineEdit_ModelPointX"));
        lineEdit_ModelPointX->setGeometry(QRect(20, 180, 71, 21));
        lineEdit_ModelPointY = new QLineEdit(SBMECoordinateRegistrationDlg);
        lineEdit_ModelPointY->setObjectName(QStringLiteral("lineEdit_ModelPointY"));
        lineEdit_ModelPointY->setGeometry(QRect(110, 180, 71, 21));
        lineEdit_ModelPointZ = new QLineEdit(SBMECoordinateRegistrationDlg);
        lineEdit_ModelPointZ->setObjectName(QStringLiteral("lineEdit_ModelPointZ"));
        lineEdit_ModelPointZ->setGeometry(QRect(200, 180, 71, 21));
        label_ModelPointX = new QLabel(SBMECoordinateRegistrationDlg);
        label_ModelPointX->setObjectName(QStringLiteral("label_ModelPointX"));
        label_ModelPointX->setGeometry(QRect(24, 151, 96, 16));
        label_ModelPointY = new QLabel(SBMECoordinateRegistrationDlg);
        label_ModelPointY->setObjectName(QStringLiteral("label_ModelPointY"));
        label_ModelPointY->setGeometry(QRect(127, 151, 96, 16));
        label_ModelPointZ = new QLabel(SBMECoordinateRegistrationDlg);
        label_ModelPointZ->setObjectName(QStringLiteral("label_ModelPointZ"));
        label_ModelPointZ->setGeometry(QRect(230, 151, 96, 16));
        label_NDIPointX = new QLabel(SBMECoordinateRegistrationDlg);
        label_NDIPointX->setObjectName(QStringLiteral("label_NDIPointX"));
        label_NDIPointX->setGeometry(QRect(26, 51, 80, 16));
        label_NDIPointY = new QLabel(SBMECoordinateRegistrationDlg);
        label_NDIPointY->setObjectName(QStringLiteral("label_NDIPointY"));
        label_NDIPointY->setGeometry(QRect(113, 51, 80, 16));
        label_NDIPointZ = new QLabel(SBMECoordinateRegistrationDlg);
        label_NDIPointZ->setObjectName(QStringLiteral("label_NDIPointZ"));
        label_NDIPointZ->setGeometry(QRect(200, 51, 80, 16));

        retranslateUi(SBMECoordinateRegistrationDlg);

        QMetaObject::connectSlotsByName(SBMECoordinateRegistrationDlg);
    } // setupUi

    void retranslateUi(QDialog *SBMECoordinateRegistrationDlg)
    {
        SBMECoordinateRegistrationDlg->setWindowTitle(QApplication::translate("SBMECoordinateRegistrationDlg", "Dialog", 0));
        label_Rx->setText(QApplication::translate("SBMECoordinateRegistrationDlg", "Rx:", 0));
        label_Ry->setText(QApplication::translate("SBMECoordinateRegistrationDlg", "Ry:", 0));
        label_Rz->setText(QApplication::translate("SBMECoordinateRegistrationDlg", "Rz:", 0));
        label_Tx->setText(QApplication::translate("SBMECoordinateRegistrationDlg", "Tx:", 0));
        label_Ty->setText(QApplication::translate("SBMECoordinateRegistrationDlg", "Ty:", 0));
        label_Tz->setText(QApplication::translate("SBMECoordinateRegistrationDlg", "Tz:", 0));
        label_Info->setText(QApplication::translate("SBMECoordinateRegistrationDlg", "Info:", 0));
        pushButton_GetNDIPoint->setText(QApplication::translate("SBMECoordinateRegistrationDlg", "Get NDI Point", 0));
        pushButton_GetModelPoint->setText(QApplication::translate("SBMECoordinateRegistrationDlg", "Get Model Point", 0));
        pushButton_StartRegister->setText(QApplication::translate("SBMECoordinateRegistrationDlg", "Register", 0));
        label_ModelPointX->setText(QApplication::translate("SBMECoordinateRegistrationDlg", "ModelPointX:", 0));
        label_ModelPointY->setText(QApplication::translate("SBMECoordinateRegistrationDlg", "ModelPointY:", 0));
        label_ModelPointZ->setText(QApplication::translate("SBMECoordinateRegistrationDlg", "ModelPointZ:", 0));
        label_NDIPointX->setText(QApplication::translate("SBMECoordinateRegistrationDlg", "NDIPointX:", 0));
        label_NDIPointY->setText(QApplication::translate("SBMECoordinateRegistrationDlg", "NDIPointY:", 0));
        label_NDIPointZ->setText(QApplication::translate("SBMECoordinateRegistrationDlg", "NDIPointZ:", 0));
    } // retranslateUi

};

namespace Ui {
    class SBMECoordinateRegistrationDlg: public Ui_SBMECoordinateRegistrationDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SBMECOORDINATEREGISTRATIONDLG_H
