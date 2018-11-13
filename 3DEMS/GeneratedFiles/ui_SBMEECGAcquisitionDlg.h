/********************************************************************************
** Form generated from reading UI file 'SBMEECGAcquisitionDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SBMEECGACQUISITIONDLG_H
#define UI_SBMEECGACQUISITIONDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SBMEECGAcquisitionDlg
{
public:
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_4;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_StartDAQ;
    QPushButton *pushButton_StopDAQ;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_InputRange;
    QComboBox *comboBox_InputRange;
    QPushButton *pushButton_PlayBack;
    QSpacerItem *verticalSpacer_4;

    void setupUi(QDialog *SBMEECGAcquisitionDlg)
    {
        if (SBMEECGAcquisitionDlg->objectName().isEmpty())
            SBMEECGAcquisitionDlg->setObjectName(QStringLiteral("SBMEECGAcquisitionDlg"));
        SBMEECGAcquisitionDlg->resize(803, 374);
        horizontalLayout_2 = new QHBoxLayout(SBMEECGAcquisitionDlg);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(638, 209, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalSpacer = new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pushButton_StartDAQ = new QPushButton(SBMEECGAcquisitionDlg);
        pushButton_StartDAQ->setObjectName(QStringLiteral("pushButton_StartDAQ"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_StartDAQ->sizePolicy().hasHeightForWidth());
        pushButton_StartDAQ->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(pushButton_StartDAQ);

        pushButton_StopDAQ = new QPushButton(SBMEECGAcquisitionDlg);
        pushButton_StopDAQ->setObjectName(QStringLiteral("pushButton_StopDAQ"));
        sizePolicy.setHeightForWidth(pushButton_StopDAQ->sizePolicy().hasHeightForWidth());
        pushButton_StopDAQ->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(pushButton_StopDAQ);


        verticalLayout_2->addLayout(verticalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_InputRange = new QLabel(SBMEECGAcquisitionDlg);
        label_InputRange->setObjectName(QStringLiteral("label_InputRange"));
        sizePolicy.setHeightForWidth(label_InputRange->sizePolicy().hasHeightForWidth());
        label_InputRange->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(label_InputRange);

        comboBox_InputRange = new QComboBox(SBMEECGAcquisitionDlg);
        comboBox_InputRange->setObjectName(QStringLiteral("comboBox_InputRange"));
        sizePolicy.setHeightForWidth(comboBox_InputRange->sizePolicy().hasHeightForWidth());
        comboBox_InputRange->setSizePolicy(sizePolicy);
        comboBox_InputRange->setEditable(false);

        verticalLayout_3->addWidget(comboBox_InputRange);


        verticalLayout_2->addLayout(verticalLayout_3);

        pushButton_PlayBack = new QPushButton(SBMEECGAcquisitionDlg);
        pushButton_PlayBack->setObjectName(QStringLiteral("pushButton_PlayBack"));

        verticalLayout_2->addWidget(pushButton_PlayBack);


        verticalLayout_4->addLayout(verticalLayout_2);

        verticalSpacer_4 = new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_4);


        horizontalLayout->addLayout(verticalLayout_4);


        horizontalLayout_2->addLayout(horizontalLayout);


        retranslateUi(SBMEECGAcquisitionDlg);

        QMetaObject::connectSlotsByName(SBMEECGAcquisitionDlg);
    } // setupUi

    void retranslateUi(QDialog *SBMEECGAcquisitionDlg)
    {
        SBMEECGAcquisitionDlg->setWindowTitle(QApplication::translate("SBMEECGAcquisitionDlg", "Dialog", 0));
        pushButton_StartDAQ->setText(QApplication::translate("SBMEECGAcquisitionDlg", "Start", 0));
        pushButton_StopDAQ->setText(QApplication::translate("SBMEECGAcquisitionDlg", "Stop", 0));
        label_InputRange->setText(QApplication::translate("SBMEECGAcquisitionDlg", "Input Range", 0));
        pushButton_PlayBack->setText(QApplication::translate("SBMEECGAcquisitionDlg", "Play Back", 0));
    } // retranslateUi

};

namespace Ui {
    class SBMEECGAcquisitionDlg: public Ui_SBMEECGAcquisitionDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SBMEECGACQUISITIONDLG_H
