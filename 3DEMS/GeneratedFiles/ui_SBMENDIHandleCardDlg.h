/********************************************************************************
** Form generated from reading UI file 'SBMENDIHandleCardDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SBMENDIHANDLECARDDLG_H
#define UI_SBMENDIHANDLECARDDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SBMENDIHandleCardDlg
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_11;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QLineEdit *lineEdit_PortIndex;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QLineEdit *lineEdit_PartNum;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label;
    QLineEdit *lineEdit_Status;
    QLineEdit *lineEdit_OV;
    QHBoxLayout *horizontalLayout_10;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout;
    QLabel *label_Tx;
    QLineEdit *lineEdit_Tx;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_Ty;
    QLineEdit *lineEdit_Ty;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_Tz;
    QLineEdit *lineEdit_Tz;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_Error;
    QLineEdit *lineEdit_Error;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_Q0;
    QLineEdit *lineEdit_Q0;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_Qx;
    QLineEdit *lineEdit_Qx;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_Qy;
    QLineEdit *lineEdit_Qy;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_Qz;
    QLineEdit *lineEdit_Qz;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_4;
    QComboBox *comboBox_HandleModel;
    QVBoxLayout *verticalLayout_4;
    QPushButton *pushButton_Color;
    QPushButton *pushButton_Enable;
    QPushButton *pushButton_SetAsReferenceHandle;
    QPushButton *pushButton_SetAsActiveHandle;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *SBMENDIHandleCardDlg)
    {
        if (SBMENDIHandleCardDlg->objectName().isEmpty())
            SBMENDIHandleCardDlg->setObjectName(QStringLiteral("SBMENDIHandleCardDlg"));
        SBMENDIHandleCardDlg->resize(412, 344);
        gridLayout = new QGridLayout(SBMENDIHandleCardDlg);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_2 = new QLabel(SBMENDIHandleCardDlg);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        lineEdit_PortIndex = new QLineEdit(SBMENDIHandleCardDlg);
        lineEdit_PortIndex->setObjectName(QStringLiteral("lineEdit_PortIndex"));

        verticalLayout->addWidget(lineEdit_PortIndex);


        horizontalLayout_11->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_3 = new QLabel(SBMENDIHandleCardDlg);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_2->addWidget(label_3);

        lineEdit_PartNum = new QLineEdit(SBMENDIHandleCardDlg);
        lineEdit_PartNum->setObjectName(QStringLiteral("lineEdit_PartNum"));

        verticalLayout_2->addWidget(lineEdit_PartNum);


        horizontalLayout_11->addLayout(verticalLayout_2);


        gridLayout->addLayout(horizontalLayout_11, 0, 0, 1, 2);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label = new QLabel(SBMENDIHandleCardDlg);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        horizontalLayout_9->addWidget(label);

        lineEdit_Status = new QLineEdit(SBMENDIHandleCardDlg);
        lineEdit_Status->setObjectName(QStringLiteral("lineEdit_Status"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit_Status->sizePolicy().hasHeightForWidth());
        lineEdit_Status->setSizePolicy(sizePolicy1);
        lineEdit_Status->setReadOnly(false);

        horizontalLayout_9->addWidget(lineEdit_Status);

        lineEdit_OV = new QLineEdit(SBMENDIHandleCardDlg);
        lineEdit_OV->setObjectName(QStringLiteral("lineEdit_OV"));
        sizePolicy1.setHeightForWidth(lineEdit_OV->sizePolicy().hasHeightForWidth());
        lineEdit_OV->setSizePolicy(sizePolicy1);

        horizontalLayout_9->addWidget(lineEdit_OV);


        gridLayout->addLayout(horizontalLayout_9, 1, 0, 1, 2);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_Tx = new QLabel(SBMENDIHandleCardDlg);
        label_Tx->setObjectName(QStringLiteral("label_Tx"));

        horizontalLayout->addWidget(label_Tx);

        lineEdit_Tx = new QLineEdit(SBMENDIHandleCardDlg);
        lineEdit_Tx->setObjectName(QStringLiteral("lineEdit_Tx"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(lineEdit_Tx->sizePolicy().hasHeightForWidth());
        lineEdit_Tx->setSizePolicy(sizePolicy2);
        lineEdit_Tx->setReadOnly(true);

        horizontalLayout->addWidget(lineEdit_Tx);


        verticalLayout_5->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_Ty = new QLabel(SBMENDIHandleCardDlg);
        label_Ty->setObjectName(QStringLiteral("label_Ty"));

        horizontalLayout_2->addWidget(label_Ty);

        lineEdit_Ty = new QLineEdit(SBMENDIHandleCardDlg);
        lineEdit_Ty->setObjectName(QStringLiteral("lineEdit_Ty"));
        sizePolicy2.setHeightForWidth(lineEdit_Ty->sizePolicy().hasHeightForWidth());
        lineEdit_Ty->setSizePolicy(sizePolicy2);
        lineEdit_Ty->setReadOnly(true);

        horizontalLayout_2->addWidget(lineEdit_Ty);


        verticalLayout_5->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_Tz = new QLabel(SBMENDIHandleCardDlg);
        label_Tz->setObjectName(QStringLiteral("label_Tz"));

        horizontalLayout_3->addWidget(label_Tz);

        lineEdit_Tz = new QLineEdit(SBMENDIHandleCardDlg);
        lineEdit_Tz->setObjectName(QStringLiteral("lineEdit_Tz"));
        sizePolicy2.setHeightForWidth(lineEdit_Tz->sizePolicy().hasHeightForWidth());
        lineEdit_Tz->setSizePolicy(sizePolicy2);
        lineEdit_Tz->setReadOnly(true);

        horizontalLayout_3->addWidget(lineEdit_Tz);


        verticalLayout_5->addLayout(horizontalLayout_3);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_Error = new QLabel(SBMENDIHandleCardDlg);
        label_Error->setObjectName(QStringLiteral("label_Error"));

        horizontalLayout_7->addWidget(label_Error);

        lineEdit_Error = new QLineEdit(SBMENDIHandleCardDlg);
        lineEdit_Error->setObjectName(QStringLiteral("lineEdit_Error"));
        sizePolicy2.setHeightForWidth(lineEdit_Error->sizePolicy().hasHeightForWidth());
        lineEdit_Error->setSizePolicy(sizePolicy2);
        lineEdit_Error->setReadOnly(true);

        horizontalLayout_7->addWidget(lineEdit_Error);


        verticalLayout_5->addLayout(horizontalLayout_7);


        horizontalLayout_10->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_Q0 = new QLabel(SBMENDIHandleCardDlg);
        label_Q0->setObjectName(QStringLiteral("label_Q0"));

        horizontalLayout_4->addWidget(label_Q0);

        lineEdit_Q0 = new QLineEdit(SBMENDIHandleCardDlg);
        lineEdit_Q0->setObjectName(QStringLiteral("lineEdit_Q0"));
        sizePolicy2.setHeightForWidth(lineEdit_Q0->sizePolicy().hasHeightForWidth());
        lineEdit_Q0->setSizePolicy(sizePolicy2);
        lineEdit_Q0->setReadOnly(true);

        horizontalLayout_4->addWidget(lineEdit_Q0);


        verticalLayout_6->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_Qx = new QLabel(SBMENDIHandleCardDlg);
        label_Qx->setObjectName(QStringLiteral("label_Qx"));

        horizontalLayout_5->addWidget(label_Qx);

        lineEdit_Qx = new QLineEdit(SBMENDIHandleCardDlg);
        lineEdit_Qx->setObjectName(QStringLiteral("lineEdit_Qx"));
        sizePolicy2.setHeightForWidth(lineEdit_Qx->sizePolicy().hasHeightForWidth());
        lineEdit_Qx->setSizePolicy(sizePolicy2);
        lineEdit_Qx->setReadOnly(true);

        horizontalLayout_5->addWidget(lineEdit_Qx);


        verticalLayout_6->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_Qy = new QLabel(SBMENDIHandleCardDlg);
        label_Qy->setObjectName(QStringLiteral("label_Qy"));

        horizontalLayout_6->addWidget(label_Qy);

        lineEdit_Qy = new QLineEdit(SBMENDIHandleCardDlg);
        lineEdit_Qy->setObjectName(QStringLiteral("lineEdit_Qy"));
        sizePolicy2.setHeightForWidth(lineEdit_Qy->sizePolicy().hasHeightForWidth());
        lineEdit_Qy->setSizePolicy(sizePolicy2);
        lineEdit_Qy->setReadOnly(true);

        horizontalLayout_6->addWidget(lineEdit_Qy);


        verticalLayout_6->addLayout(horizontalLayout_6);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_Qz = new QLabel(SBMENDIHandleCardDlg);
        label_Qz->setObjectName(QStringLiteral("label_Qz"));

        horizontalLayout_8->addWidget(label_Qz);

        lineEdit_Qz = new QLineEdit(SBMENDIHandleCardDlg);
        lineEdit_Qz->setObjectName(QStringLiteral("lineEdit_Qz"));
        sizePolicy2.setHeightForWidth(lineEdit_Qz->sizePolicy().hasHeightForWidth());
        lineEdit_Qz->setSizePolicy(sizePolicy2);
        lineEdit_Qz->setReadOnly(true);

        horizontalLayout_8->addWidget(lineEdit_Qz);


        verticalLayout_6->addLayout(horizontalLayout_8);


        horizontalLayout_10->addLayout(verticalLayout_6);


        gridLayout->addLayout(horizontalLayout_10, 2, 0, 1, 2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_4 = new QLabel(SBMENDIHandleCardDlg);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout_3->addWidget(label_4);

        comboBox_HandleModel = new QComboBox(SBMENDIHandleCardDlg);
        comboBox_HandleModel->setObjectName(QStringLiteral("comboBox_HandleModel"));

        verticalLayout_3->addWidget(comboBox_HandleModel);


        gridLayout->addLayout(verticalLayout_3, 3, 0, 1, 1);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        pushButton_Color = new QPushButton(SBMENDIHandleCardDlg);
        pushButton_Color->setObjectName(QStringLiteral("pushButton_Color"));

        verticalLayout_4->addWidget(pushButton_Color);

        pushButton_Enable = new QPushButton(SBMENDIHandleCardDlg);
        pushButton_Enable->setObjectName(QStringLiteral("pushButton_Enable"));

        verticalLayout_4->addWidget(pushButton_Enable);

        pushButton_SetAsReferenceHandle = new QPushButton(SBMENDIHandleCardDlg);
        pushButton_SetAsReferenceHandle->setObjectName(QStringLiteral("pushButton_SetAsReferenceHandle"));

        verticalLayout_4->addWidget(pushButton_SetAsReferenceHandle);

        pushButton_SetAsActiveHandle = new QPushButton(SBMENDIHandleCardDlg);
        pushButton_SetAsActiveHandle->setObjectName(QStringLiteral("pushButton_SetAsActiveHandle"));

        verticalLayout_4->addWidget(pushButton_SetAsActiveHandle);


        gridLayout->addLayout(verticalLayout_4, 3, 1, 2, 1);

        verticalSpacer = new QSpacerItem(20, 85, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 4, 0, 1, 1);


        retranslateUi(SBMENDIHandleCardDlg);

        QMetaObject::connectSlotsByName(SBMENDIHandleCardDlg);
    } // setupUi

    void retranslateUi(QDialog *SBMENDIHandleCardDlg)
    {
        SBMENDIHandleCardDlg->setWindowTitle(QApplication::translate("SBMENDIHandleCardDlg", "NDI Handle Card", 0));
        label_2->setText(QApplication::translate("SBMENDIHandleCardDlg", "Port Index:", 0));
        label_3->setText(QApplication::translate("SBMENDIHandleCardDlg", "PartNum:", 0));
        label->setText(QApplication::translate("SBMENDIHandleCardDlg", "Status:", 0));
        label_Tx->setText(QApplication::translate("SBMENDIHandleCardDlg", "Tx:", 0));
        label_Ty->setText(QApplication::translate("SBMENDIHandleCardDlg", "Ty:", 0));
        label_Tz->setText(QApplication::translate("SBMENDIHandleCardDlg", "Tz:", 0));
        label_Error->setText(QApplication::translate("SBMENDIHandleCardDlg", "Error:", 0));
        label_Q0->setText(QApplication::translate("SBMENDIHandleCardDlg", "Q0:", 0));
        label_Qx->setText(QApplication::translate("SBMENDIHandleCardDlg", "Qx:", 0));
        label_Qy->setText(QApplication::translate("SBMENDIHandleCardDlg", "Qy:", 0));
        label_Qz->setText(QApplication::translate("SBMENDIHandleCardDlg", "Qz:", 0));
        label_4->setText(QApplication::translate("SBMENDIHandleCardDlg", "Load Handle Model:", 0));
        pushButton_Color->setText(QApplication::translate("SBMENDIHandleCardDlg", "Color", 0));
        pushButton_Enable->setText(QApplication::translate("SBMENDIHandleCardDlg", "Enable", 0));
        pushButton_SetAsReferenceHandle->setText(QApplication::translate("SBMENDIHandleCardDlg", "Set As Reference Handle", 0));
        pushButton_SetAsActiveHandle->setText(QApplication::translate("SBMENDIHandleCardDlg", "Set As Active Handle", 0));
    } // retranslateUi

};

namespace Ui {
    class SBMENDIHandleCardDlg: public Ui_SBMENDIHandleCardDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SBMENDIHANDLECARDDLG_H
