/********************************************************************************
** Form generated from reading UI file 'SBMEColorDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SBMECOLORDLG_H
#define UI_SBMECOLORDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SBMEColorDlg
{
public:
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_2;
    QSlider *horizontalSlider_ColoringRadius;
    QLabel *label_ColoringRadius;
    QLabel *label;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout;
    QSlider *horizontalSlider_ColoringDistance;
    QLabel *label_ColoringDistance;
    QLabel *label_5;
    QPushButton *pushButton_EnableColoring;

    void setupUi(QDialog *SBMEColorDlg)
    {
        if (SBMEColorDlg->objectName().isEmpty())
            SBMEColorDlg->setObjectName(QStringLiteral("SBMEColorDlg"));
        SBMEColorDlg->resize(200, 170);
        horizontalLayout_3 = new QHBoxLayout(SBMEColorDlg);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(36, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_2 = new QLabel(SBMEColorDlg);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout->addWidget(label_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSlider_ColoringRadius = new QSlider(SBMEColorDlg);
        horizontalSlider_ColoringRadius->setObjectName(QStringLiteral("horizontalSlider_ColoringRadius"));
        horizontalSlider_ColoringRadius->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(horizontalSlider_ColoringRadius);

        label_ColoringRadius = new QLabel(SBMEColorDlg);
        label_ColoringRadius->setObjectName(QStringLiteral("label_ColoringRadius"));

        horizontalLayout_2->addWidget(label_ColoringRadius);

        label = new QLabel(SBMEColorDlg);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);


        verticalLayout->addLayout(horizontalLayout_2);

        label_3 = new QLabel(SBMEColorDlg);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout->addWidget(label_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSlider_ColoringDistance = new QSlider(SBMEColorDlg);
        horizontalSlider_ColoringDistance->setObjectName(QStringLiteral("horizontalSlider_ColoringDistance"));
        horizontalSlider_ColoringDistance->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(horizontalSlider_ColoringDistance);

        label_ColoringDistance = new QLabel(SBMEColorDlg);
        label_ColoringDistance->setObjectName(QStringLiteral("label_ColoringDistance"));

        horizontalLayout->addWidget(label_ColoringDistance);

        label_5 = new QLabel(SBMEColorDlg);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout->addWidget(label_5);


        verticalLayout->addLayout(horizontalLayout);


        verticalLayout_2->addLayout(verticalLayout);

        pushButton_EnableColoring = new QPushButton(SBMEColorDlg);
        pushButton_EnableColoring->setObjectName(QStringLiteral("pushButton_EnableColoring"));

        verticalLayout_2->addWidget(pushButton_EnableColoring);


        horizontalLayout_3->addLayout(verticalLayout_2);


        retranslateUi(SBMEColorDlg);

        QMetaObject::connectSlotsByName(SBMEColorDlg);
    } // setupUi

    void retranslateUi(QDialog *SBMEColorDlg)
    {
        SBMEColorDlg->setWindowTitle(QApplication::translate("SBMEColorDlg", "Color Control Dialog", 0));
        label_2->setText(QApplication::translate("SBMEColorDlg", "3D Coloring Radius:", 0));
        label_ColoringRadius->setText(QString());
        label->setText(QApplication::translate("SBMEColorDlg", "mm", 0));
        label_3->setText(QApplication::translate("SBMEColorDlg", "EAG Coloring Distance:", 0));
        label_ColoringDistance->setText(QString());
        label_5->setText(QApplication::translate("SBMEColorDlg", "pixel", 0));
        pushButton_EnableColoring->setText(QApplication::translate("SBMEColorDlg", "Disable Coloring", 0));
    } // retranslateUi

};

namespace Ui {
    class SBMEColorDlg: public Ui_SBMEColorDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SBMECOLORDLG_H
