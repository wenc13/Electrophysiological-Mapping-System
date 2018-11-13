#ifndef SBMENDIROMFILEDLG_H
#define SBMENDIROMFILEDLG_H

#include <QDialog>
#include <QSettings>
#include "SBMENDIDef.h"

namespace Ui
{
    class SBMENDIRomFileDlg;
}

class SBMENDIRomFileDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SBMENDIRomFileDlg(QWidget *parent = 0);
    ~SBMENDIRomFileDlg();
    void SetSysteminfo(int nTypeofSystem, int nNoActivePorts, int nNoPassivePorts, int nNoMagneticPorts);

private:
    Ui::SBMENDIRomFileDlg *ui;

    int m_nTypeofSystem;
    int m_nNoActivePorts;
    int m_nNoPassivePorts;
    int m_nNoMagneticPorts;
    int m_nCurrentRow;
    bool m_bFillTablebFinished;
    bool m_bChangesSaved;
    QString	m_sPortID;
    QString	m_sROMFile;
    QSettings *m_pSettings;

    void FillRomFileTable();
    void AddItemToList(QString PortID, QString RomFileName);

signals:
    void m_signalRomFileChanged();

private slots:
    void m_slotOnClickTable(int row, int column);
    void m_slotOnBrowse();
    void m_slotOnSave();
    void m_slotOnClose();

};

#endif // SBMENDIROMFILEDLG_H
