/********************************************************************************
** Form generated from reading UI file 'SBMENDISerialPortSettingsDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SBMENDISERIALPORTSETTINGSDLG_H
#define UI_SBMENDISERIALPORTSETTINGSDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SBMENDISerialPortSettingsDlg
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QGroupBox *selectBox;
    QGridLayout *gridLayout;
    QComboBox *serialPortInfoListBox;
    QLabel *descriptionLabel;
    QLabel *manufacturerLabel;
    QLabel *locationLabel;
    QLabel *vidLabel;
    QLabel *pidLabel;
    QGroupBox *parametersBox;
    QGridLayout *gridLayout_2;
    QComboBox *dataBitsBox;
    QComboBox *stopBitsBox;
    QLabel *parityLabel;
    QComboBox *baudRateBox;
    QLabel *stopBitsLabel;
    QLabel *baudRateLabel;
    QLabel *dataBitsLabel;
    QComboBox *parityBox;
    QLabel *flowControlLabel;
    QComboBox *flowControlBox;
    QCheckBox *checkBox_Wireless;
    QCheckBox *checkBox_Reset;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SBMENDISerialPortSettingsDlg)
    {
        if (SBMENDISerialPortSettingsDlg->objectName().isEmpty())
            SBMENDISerialPortSettingsDlg->setObjectName(QStringLiteral("SBMENDISerialPortSettingsDlg"));
        SBMENDISerialPortSettingsDlg->resize(560, 458);
        layoutWidget = new QWidget(SBMENDISerialPortSettingsDlg);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 10, 531, 441));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        selectBox = new QGroupBox(layoutWidget);
        selectBox->setObjectName(QStringLiteral("selectBox"));
        gridLayout = new QGridLayout(selectBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        serialPortInfoListBox = new QComboBox(selectBox);
        serialPortInfoListBox->setObjectName(QStringLiteral("serialPortInfoListBox"));

        gridLayout->addWidget(serialPortInfoListBox, 0, 0, 1, 1);

        descriptionLabel = new QLabel(selectBox);
        descriptionLabel->setObjectName(QStringLiteral("descriptionLabel"));

        gridLayout->addWidget(descriptionLabel, 1, 0, 1, 1);

        manufacturerLabel = new QLabel(selectBox);
        manufacturerLabel->setObjectName(QStringLiteral("manufacturerLabel"));

        gridLayout->addWidget(manufacturerLabel, 2, 0, 1, 1);

        locationLabel = new QLabel(selectBox);
        locationLabel->setObjectName(QStringLiteral("locationLabel"));

        gridLayout->addWidget(locationLabel, 3, 0, 1, 1);

        vidLabel = new QLabel(selectBox);
        vidLabel->setObjectName(QStringLiteral("vidLabel"));

        gridLayout->addWidget(vidLabel, 4, 0, 1, 1);

        pidLabel = new QLabel(selectBox);
        pidLabel->setObjectName(QStringLiteral("pidLabel"));

        gridLayout->addWidget(pidLabel, 5, 0, 1, 1);


        horizontalLayout->addWidget(selectBox);

        parametersBox = new QGroupBox(layoutWidget);
        parametersBox->setObjectName(QStringLiteral("parametersBox"));
        gridLayout_2 = new QGridLayout(parametersBox);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        dataBitsBox = new QComboBox(parametersBox);
        dataBitsBox->setObjectName(QStringLiteral("dataBitsBox"));

        gridLayout_2->addWidget(dataBitsBox, 1, 1, 1, 1);

        stopBitsBox = new QComboBox(parametersBox);
        stopBitsBox->setObjectName(QStringLiteral("stopBitsBox"));

        gridLayout_2->addWidget(stopBitsBox, 3, 1, 1, 1);

        parityLabel = new QLabel(parametersBox);
        parityLabel->setObjectName(QStringLiteral("parityLabel"));

        gridLayout_2->addWidget(parityLabel, 2, 0, 1, 1);

        baudRateBox = new QComboBox(parametersBox);
        baudRateBox->setObjectName(QStringLiteral("baudRateBox"));

        gridLayout_2->addWidget(baudRateBox, 0, 1, 1, 1);

        stopBitsLabel = new QLabel(parametersBox);
        stopBitsLabel->setObjectName(QStringLiteral("stopBitsLabel"));

        gridLayout_2->addWidget(stopBitsLabel, 3, 0, 1, 1);

        baudRateLabel = new QLabel(parametersBox);
        baudRateLabel->setObjectName(QStringLiteral("baudRateLabel"));

        gridLayout_2->addWidget(baudRateLabel, 0, 0, 1, 1);

        dataBitsLabel = new QLabel(parametersBox);
        dataBitsLabel->setObjectName(QStringLiteral("dataBitsLabel"));

        gridLayout_2->addWidget(dataBitsLabel, 1, 0, 1, 1);

        parityBox = new QComboBox(parametersBox);
        parityBox->setObjectName(QStringLiteral("parityBox"));

        gridLayout_2->addWidget(parityBox, 2, 1, 1, 1);

        flowControlLabel = new QLabel(parametersBox);
        flowControlLabel->setObjectName(QStringLiteral("flowControlLabel"));

        gridLayout_2->addWidget(flowControlLabel, 5, 0, 1, 1);

        flowControlBox = new QComboBox(parametersBox);
        flowControlBox->setObjectName(QStringLiteral("flowControlBox"));

        gridLayout_2->addWidget(flowControlBox, 5, 1, 1, 1);


        horizontalLayout->addWidget(parametersBox);


        verticalLayout->addLayout(horizontalLayout);

        checkBox_Wireless = new QCheckBox(layoutWidget);
        checkBox_Wireless->setObjectName(QStringLiteral("checkBox_Wireless"));

        verticalLayout->addWidget(checkBox_Wireless);

        checkBox_Reset = new QCheckBox(layoutWidget);
        checkBox_Reset->setObjectName(QStringLiteral("checkBox_Reset"));

        verticalLayout->addWidget(checkBox_Reset);

        buttonBox = new QDialogButtonBox(layoutWidget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(SBMENDISerialPortSettingsDlg);
        QObject::connect(buttonBox, SIGNAL(accepted()), SBMENDISerialPortSettingsDlg, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SBMENDISerialPortSettingsDlg, SLOT(reject()));

        QMetaObject::connectSlotsByName(SBMENDISerialPortSettingsDlg);
    } // setupUi

    void retranslateUi(QDialog *SBMENDISerialPortSettingsDlg)
    {
        SBMENDISerialPortSettingsDlg->setWindowTitle(QApplication::translate("SBMENDISerialPortSettingsDlg", "NDI SerialPort Settings", 0));
        selectBox->setTitle(QApplication::translate("SBMENDISerialPortSettingsDlg", "Select Serial Port", 0));
        descriptionLabel->setText(QApplication::translate("SBMENDISerialPortSettingsDlg", "Description:", 0));
        manufacturerLabel->setText(QApplication::translate("SBMENDISerialPortSettingsDlg", "Manufacturer:", 0));
        locationLabel->setText(QApplication::translate("SBMENDISerialPortSettingsDlg", "Location:", 0));
        vidLabel->setText(QApplication::translate("SBMENDISerialPortSettingsDlg", "Vendor ID:", 0));
        pidLabel->setText(QApplication::translate("SBMENDISerialPortSettingsDlg", "Product ID:", 0));
        parametersBox->setTitle(QApplication::translate("SBMENDISerialPortSettingsDlg", "Select Parameters", 0));
        parityLabel->setText(QApplication::translate("SBMENDISerialPortSettingsDlg", "Parity:", 0));
        stopBitsLabel->setText(QApplication::translate("SBMENDISerialPortSettingsDlg", "Stop bits:", 0));
        baudRateLabel->setText(QApplication::translate("SBMENDISerialPortSettingsDlg", "BaudRate:", 0));
        dataBitsLabel->setText(QApplication::translate("SBMENDISerialPortSettingsDlg", "Data bits:", 0));
        flowControlLabel->setText(QApplication::translate("SBMENDISerialPortSettingsDlg", "Flow control:", 0));
        checkBox_Wireless->setText(QApplication::translate("SBMENDISerialPortSettingsDlg", "Wireless Communication Port", 0));
        checkBox_Reset->setText(QApplication::translate("SBMENDISerialPortSettingsDlg", "Reset Hardware upon initialization", 0));
    } // retranslateUi

};

namespace Ui {
    class SBMENDISerialPortSettingsDlg: public Ui_SBMENDISerialPortSettingsDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SBMENDISERIALPORTSETTINGSDLG_H
