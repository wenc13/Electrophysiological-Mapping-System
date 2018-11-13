#ifndef SBMEECGPLAYBACKDLG_H
#define SBMEECGPLAYBACKDLG_H

#include <QDialog>

namespace Ui
{
    class SBMEECGPlayBackDlg;
}
class SBMEECGPlayBackDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SBMEECGPlayBackDlg(QWidget *parent = 0);
    ~SBMEECGPlayBackDlg();

private:
    Ui::SBMEECGPlayBackDlg *ui;
    QStringList m_BeginTimeList;
    QStringList m_EndTimeList;
    int m_PlayBackTime[6];

signals:
    void m_signalPlayBackTime(int *);

private slots:
    void m_slotPlayBackTimeBegin(const QString &);
    void m_slotPlayBackTimeEnd(const QString &);
    void m_slotPlayBackOK();
    void m_slotPlayBackCancel();
};

#endif // SBMEECGPLAYBACKDLG_H
