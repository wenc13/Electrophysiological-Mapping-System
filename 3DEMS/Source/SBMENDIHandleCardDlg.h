#ifndef SBMENDIHANDLECARDDLG_H
#define SBMENDIHANDLECARDDLG_H

#include <QDialog>

namespace Ui
{
    class SBMENDIHandleCardDlg;
}

class SBMENDIHandleCardDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SBMENDIHandleCardDlg(QWidget *parent = 0);
    ~SBMENDIHandleCardDlg();
    void SetCardIndex(int idx);
    void SetPortIndex(int index);
    void SetPartNum(QString str);
    void SetHandleEnabled(bool bEnabled);
    void EnableorDisableButton(bool bEnable);
	void SetReferenceHandleEnabled(bool bEnable);
    void SetStatus(QString str);
    void SetOutOfVolume(QString str);
	void SetError(QString str);
    void SetTx(QString str);
    void SetTy(QString str);
    void SetTz(QString str);
    void SetQ0(QString str);
    void SetQx(QString str);
    void SetQy(QString str);
    void SetQz(QString str);
    void SetQ0Text(QString str);
    void SetQxText(QString str);
    void SetQyText(QString str);
    void SetQzText(QString str);

private:
    Ui::SBMENDIHandleCardDlg *ui;

    int m_nCardIndex;
    int m_nPortIndex;
    bool m_bIsEnbaled;

signals:
    void m_signalToEnableorDisableHandle(int cardIndex, int portIndex, bool isEnable);
    void m_signalToSetHandleModel(int cardIndex, int model);
    void m_signalToSetHandleColor(int cardIndex, QColor color);
	void m_signalToSetReferenceHandle(int cardIndex, int portIndex);
    void m_signalToSetActiveHandle(int cardIndex);

private slots:
    void m_slotOnEnableorDisableHandle();
    void m_slotOnSetHandleModel(int model);
    void m_slotOnSetHandleColor();
	void m_slotOnSetReferenceHandle();
    void m_slotOnSetActiveHandle();

};

#endif // SBMENDIHANDLECARDDLG_H
