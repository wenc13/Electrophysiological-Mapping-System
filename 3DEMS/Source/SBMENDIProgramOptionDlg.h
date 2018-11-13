#ifndef SBMENDIPROGRAMOPTIONDLG_H
#define SBMENDIPROGRAMOPTIONDLG_H

#include <QDialog>
#include <QSettings>

namespace Ui
{
    class SBMENDIProgramOptionDlg;
}

class SBMENDIProgramOptionDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SBMENDIProgramOptionDlg(QWidget *parent = 0);
    ~SBMENDIProgramOptionDlg();

private:
    Ui::SBMENDIProgramOptionDlg *ui;
    QSettings *m_pSettings;

    void InitiallizeDlg();

private slots:
    void m_slotOnLogToFile();
    void m_slotOnBrowse();
    void m_slotOnBeepOnError();
    void m_slotOnBeepOnWarning();
    void m_slotAccept();
};

#endif // SBMENDIPROGRAMOPTIONDLG_H
