#ifndef SBMENDISERIALPORTSETTINGSDLG_H
#define SBMENDISERIALPORTSETTINGSDLG_H

#include <QDialog>
#include <QSettings>
#include <QSerialPort>

namespace Ui
{
    class SBMENDISerialPortSettingsDlg;
}

class SBMENDISerialPortSettingsDlg : public QDialog
{
    Q_OBJECT
public:
    explicit SBMENDISerialPortSettingsDlg(QWidget *parent = 0);
    ~SBMENDISerialPortSettingsDlg();

	//int     NDIComIndex;
	//int     portNumber; 
    //QString portName;

	/*struct SerialPortSettings
    {
        int     NDIComIndex;    //串口索引
        int     portNumber;     //串口号
        QString portName;
		int     baudRate;
        int     dataBits;
        int     parity;
        int     stopBits;
        int     flowControl;
		
		//qint32                   baudRate;
		//QSerialPort::BaudRate    baudRate;
        //QSerialPort::DataBits    dataBits;
        //QSerialPort::Parity      parity;
        //QSerialPort::StopBits    stopBits;
        //QSerialPort::FlowControl flowControl;
    };*/
    //SerialPortSettings Settings() const;

private:
    Ui::SBMENDISerialPortSettingsDlg *ui;
    //SerialPortSettings currentSettings;
	QSettings *m_pSettings;

	//int  m_nBaudRate;
	//int  m_nDataBits;
	//int  m_nParity;
	//int  m_nStopBits;
	//int  m_nFlowControl;
	//bool m_bResetChecked;
	//bool m_bWirelessChecked;
    
	void FillPortsInfo();
    void FillPortsParameters();
    void UpdateSettings();

signals:
	void m_signalCOMPortParametersChange();

private slots:
    void m_slotShowPortInfo(int idx);
    //void m_slotSetHandshaking(bool ishandshaking);
    void m_slotAccept();

};

#endif // SBMENDISERIALPORTSETTINGSDLG_H
