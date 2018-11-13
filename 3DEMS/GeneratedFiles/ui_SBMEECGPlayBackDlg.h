/********************************************************************************
** Form generated from reading UI file 'SBMEECGPlayBackDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SBMEECGPLAYBACKDLG_H
#define UI_SBMEECGPLAYBACKDLG_H

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
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SBMEECGPlayBackDlg
{
public:
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_PlayBackTitle;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_PlayBackBegin;
    QLineEdit *lineEdit_PlayBackBegin;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_PlayBackEnd;
    QLineEdit *lineEdit_PlayBackEnd;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_PlayBackOK;
    QPushButton *pushButton_PlayBackCancel;

    void setupUi(QDialog *SBMEECGPlayBackDlg)
    {
        if (SBMEECGPlayBackDlg->objectName().isEmpty())
            SBMEECGPlayBackDlg->setObjectName(QStringLiteral("SBMEECGPlayBackDlg"));
        SBMEECGPlayBackDlg->resize(359, 92);
        horizontalLayout_5 = new QHBoxLayout(SBMEECGPlayBackDlg);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_PlayBackTitle = new QLabel(SBMEECGPlayBackDlg);
        label_PlayBackTitle->setObjectName(QStringLiteral("label_PlayBackTitle"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_PlayBackTitle->sizePolicy().hasHeightForWidth());
        label_PlayBackTitle->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(label_PlayBackTitle);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_PlayBackBegin = new QLabel(SBMEECGPlayBackDlg);
        label_PlayBackBegin->setObjectName(QStringLiteral("label_PlayBackBegin"));
        sizePolicy.setHeightForWidth(label_PlayBackBegin->sizePolicy().hasHeightForWidth());
        label_PlayBackBegin->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(label_PlayBackBegin);

        lineEdit_PlayBackBegin = new QLineEdit(SBMEECGPlayBackDlg);
        lineEdit_PlayBackBegin->setObjectName(QStringLiteral("lineEdit_PlayBackBegin"));
        sizePolicy.setHeightForWidth(lineEdit_PlayBackBegin->sizePolicy().hasHeightForWidth());
        lineEdit_PlayBackBegin->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(lineEdit_PlayBackBegin);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_PlayBackEnd = new QLabel(SBMEECGPlayBackDlg);
        label_PlayBackEnd->setObjectName(QStringLiteral("label_PlayBackEnd"));
        sizePolicy.setHeightForWidth(label_PlayBackEnd->sizePolicy().hasHeightForWidth());
        label_PlayBackEnd->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(label_PlayBackEnd);

        lineEdit_PlayBackEnd = new QLineEdit(SBMEECGPlayBackDlg);
        lineEdit_PlayBackEnd->setObjectName(QStringLiteral("lineEdit_PlayBackEnd"));
        sizePolicy.setHeightForWidth(lineEdit_PlayBackEnd->sizePolicy().hasHeightForWidth());
        lineEdit_PlayBackEnd->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(lineEdit_PlayBackEnd);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout_4->addLayout(verticalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        pushButton_PlayBackOK = new QPushButton(SBMEECGPlayBackDlg);
        pushButton_PlayBackOK->setObjectName(QStringLiteral("pushButton_PlayBackOK"));
        sizePolicy.setHeightForWidth(pushButton_PlayBackOK->sizePolicy().hasHeightForWidth());
        pushButton_PlayBackOK->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(pushButton_PlayBackOK);

        pushButton_PlayBackCancel = new QPushButton(SBMEECGPlayBackDlg);
        pushButton_PlayBackCancel->setObjectName(QStringLiteral("pushButton_PlayBackCancel"));
        sizePolicy.setHeightForWidth(pushButton_PlayBackCancel->sizePolicy().hasHeightForWidth());
        pushButton_PlayBackCancel->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(pushButton_PlayBackCancel);


        horizontalLayout_4->addLayout(horizontalLayout_3);


        verticalLayout_2->addLayout(horizontalLayout_4);


        horizontalLayout_5->addLayout(verticalLayout_2);


        retranslateUi(SBMEECGPlayBackDlg);

        QMetaObject::connectSlotsByName(SBMEECGPlayBackDlg);
    } // setupUi

    void retranslateUi(QDialog *SBMEECGPlayBackDlg)
    {
        SBMEECGPlayBackDlg->setWindowTitle(QApplication::translate("SBMEECGPlayBackDlg", "Dialog", 0));
        label_PlayBackTitle->setText(QApplication::translate("SBMEECGPlayBackDlg", "Please Input the Time Range", 0));
        label_PlayBackBegin->setText(QApplication::translate("SBMEECGPlayBackDlg", "Begin", 0));
        lineEdit_PlayBackBegin->setText(QString());
        label_PlayBackEnd->setText(QApplication::translate("SBMEECGPlayBackDlg", "End  ", 0));
        pushButton_PlayBackOK->setText(QApplication::translate("SBMEECGPlayBackDlg", "OK", 0));
        pushButton_PlayBackCancel->setText(QApplication::translate("SBMEECGPlayBackDlg", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class SBMEECGPlayBackDlg: public Ui_SBMEECGPlayBackDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SBMEECGPLAYBACKDLG_H
