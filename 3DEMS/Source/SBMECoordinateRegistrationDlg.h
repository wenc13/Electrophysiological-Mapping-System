#ifndef SBMECOORDINATEREGISTRATIONDLG_H
#define SBMECOORDINATEREGISTRATIONDLG_H

#include <QDialog>
#include "SBMEMacroDefinition.h"

namespace Ui
{
    class SBMECoordinateRegistrationDlg;
}

class SBMECoordinateRegistrationDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SBMECoordinateRegistrationDlg(QWidget *parent = 0);
    ~SBMECoordinateRegistrationDlg();
    void NDIPointGot(float, float, float);
    void ModelPointGot(float, float, float);
    void ReadytoGegister();

private:
    Ui::SBMECoordinateRegistrationDlg *ui;

    bool  m_bRegistered;
    int   m_nNDIPoint;
    int   m_nModelPoint;
    float m_fZoom;
    float m_NDIPoint[SBME_MAX_LANDMARK_NUM][3];
    float m_ModelPoint[SBME_MAX_LANDMARK_NUM][3];
    float m_Traslation[3];
    float m_Rotation[3][3];
    float m_EulerRot[3];

    bool ComputeRegisterMatrix(float worldCoords[][3], float modelCoords[][3], int points, float T[], float R[][3], float S);

signals:
    void m_signalToGetNDIPoint();
    void m_signalToGetModelPoint();

private slots:
    void m_slotGetNDIPoint();
    void m_slotGetModelPoint();
    void m_slotSartRegister();
};

#endif // SBMECOORDINATEREGISTRATIONDLG_H
