/********************************************************************************
** Form generated from reading UI file 'SBMEStereoProjectorControlPanelDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SBMESTEREOPROJECTORCONTROLPANELDLG_H
#define UI_SBMESTEREOPROJECTORCONTROLPANELDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SBMEStereoProjectorControlPanelDlg
{
public:
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QSlider *horizontalSlider_FocalDistance;
    QLabel *label_FD;
    QLabel *label_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_3;
    QSlider *horizontalSlider_PupilDistance;
    QLabel *label_PD;
    QLabel *label_4;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_5;
    QHBoxLayout *horizontalLayout;
    QSlider *horizontalSlider_Fovy;
    QLabel *label_Fovy;
    QLabel *label_6;

    void setupUi(QDialog *SBMEStereoProjectorControlPanelDlg)
    {
        if (SBMEStereoProjectorControlPanelDlg->objectName().isEmpty())
            SBMEStereoProjectorControlPanelDlg->setObjectName(QStringLiteral("SBMEStereoProjectorControlPanelDlg"));
        SBMEStereoProjectorControlPanelDlg->resize(222, 162);
        verticalLayout_5 = new QVBoxLayout(SBMEStereoProjectorControlPanelDlg);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(SBMEStereoProjectorControlPanelDlg);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSlider_FocalDistance = new QSlider(SBMEStereoProjectorControlPanelDlg);
        horizontalSlider_FocalDistance->setObjectName(QStringLiteral("horizontalSlider_FocalDistance"));
        horizontalSlider_FocalDistance->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(horizontalSlider_FocalDistance);

        label_FD = new QLabel(SBMEStereoProjectorControlPanelDlg);
        label_FD->setObjectName(QStringLiteral("label_FD"));

        horizontalLayout_2->addWidget(label_FD);

        label_3 = new QLabel(SBMEStereoProjectorControlPanelDlg);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_2->addWidget(label_3);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_4->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_2 = new QLabel(SBMEStereoProjectorControlPanelDlg);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_2->addWidget(label_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSlider_PupilDistance = new QSlider(SBMEStereoProjectorControlPanelDlg);
        horizontalSlider_PupilDistance->setObjectName(QStringLiteral("horizontalSlider_PupilDistance"));
        horizontalSlider_PupilDistance->setAcceptDrops(false);
        horizontalSlider_PupilDistance->setInputMethodHints(Qt::ImhNone);
        horizontalSlider_PupilDistance->setPageStep(10);
        horizontalSlider_PupilDistance->setOrientation(Qt::Horizontal);
        horizontalSlider_PupilDistance->setInvertedAppearance(false);
        horizontalSlider_PupilDistance->setInvertedControls(false);

        horizontalLayout_3->addWidget(horizontalSlider_PupilDistance);

        label_PD = new QLabel(SBMEStereoProjectorControlPanelDlg);
        label_PD->setObjectName(QStringLiteral("label_PD"));

        horizontalLayout_3->addWidget(label_PD);

        label_4 = new QLabel(SBMEStereoProjectorControlPanelDlg);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_3->addWidget(label_4);


        verticalLayout_2->addLayout(horizontalLayout_3);


        verticalLayout_4->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_5 = new QLabel(SBMEStereoProjectorControlPanelDlg);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout_3->addWidget(label_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSlider_Fovy = new QSlider(SBMEStereoProjectorControlPanelDlg);
        horizontalSlider_Fovy->setObjectName(QStringLiteral("horizontalSlider_Fovy"));
        horizontalSlider_Fovy->setMaximum(179);
        horizontalSlider_Fovy->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(horizontalSlider_Fovy);

        label_Fovy = new QLabel(SBMEStereoProjectorControlPanelDlg);
        label_Fovy->setObjectName(QStringLiteral("label_Fovy"));

        horizontalLayout->addWidget(label_Fovy);

        label_6 = new QLabel(SBMEStereoProjectorControlPanelDlg);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout->addWidget(label_6);


        verticalLayout_3->addLayout(horizontalLayout);


        verticalLayout_4->addLayout(verticalLayout_3);


        verticalLayout_5->addLayout(verticalLayout_4);


        retranslateUi(SBMEStereoProjectorControlPanelDlg);

        QMetaObject::connectSlotsByName(SBMEStereoProjectorControlPanelDlg);
    } // setupUi

    void retranslateUi(QDialog *SBMEStereoProjectorControlPanelDlg)
    {
        SBMEStereoProjectorControlPanelDlg->setWindowTitle(QApplication::translate("SBMEStereoProjectorControlPanelDlg", "Stereo Projector Control Panel", 0));
        label->setText(QApplication::translate("SBMEStereoProjectorControlPanelDlg", "Focal Distance:", 0));
        label_FD->setText(QApplication::translate("SBMEStereoProjectorControlPanelDlg", "00", 0));
        label_3->setText(QApplication::translate("SBMEStereoProjectorControlPanelDlg", "mm", 0));
        label_2->setText(QApplication::translate("SBMEStereoProjectorControlPanelDlg", "Pupil Distance:", 0));
        label_PD->setText(QApplication::translate("SBMEStereoProjectorControlPanelDlg", "00", 0));
        label_4->setText(QApplication::translate("SBMEStereoProjectorControlPanelDlg", "mm", 0));
        label_5->setText(QApplication::translate("SBMEStereoProjectorControlPanelDlg", "Fovy\357\274\232", 0));
        label_Fovy->setText(QString());
        label_6->setText(QApplication::translate("SBMEStereoProjectorControlPanelDlg", "\302\260", 0));
    } // retranslateUi

};

namespace Ui {
    class SBMEStereoProjectorControlPanelDlg: public Ui_SBMEStereoProjectorControlPanelDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SBMESTEREOPROJECTORCONTROLPANELDLG_H
