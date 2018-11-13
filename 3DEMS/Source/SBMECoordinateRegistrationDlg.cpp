#include "SBMECoordinateRegistrationDlg.h"
#include "ui_SBMECoordinateRegistrationDlg.h"

SBMECoordinateRegistrationDlg::SBMECoordinateRegistrationDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SBMECoordinateRegistrationDlg)
{
    ui->setupUi(this);
    connect(ui->pushButton_GetNDIPoint,   SIGNAL(clicked()), this, SLOT(m_slotGetNDIPoint()));
    connect(ui->pushButton_GetModelPoint, SIGNAL(clicked()), this, SLOT(m_slotGetModelPoint()));
    connect(ui->pushButton_StartRegister, SIGNAL(clicked()), this, SLOT(m_slotSartRegister()));
    ReadytoGegister();
}

SBMECoordinateRegistrationDlg::~SBMECoordinateRegistrationDlg()
{
    delete ui;
}

void SBMECoordinateRegistrationDlg::ReadytoGegister()
{
    m_bRegistered = false;
    m_nNDIPoint = 0;
    m_nModelPoint = 0;
    ui->lineEdit_Info->setText("please hold the NDI handle and get a landmark");
    ui->pushButton_GetNDIPoint->setEnabled(true);
    ui->pushButton_GetModelPoint->setDisabled(true);
    ui->pushButton_StartRegister->setDisabled(true);
    ui->lineEdit_ModelPointX->setText("");
    ui->lineEdit_ModelPointY->setText("");
    ui->lineEdit_ModelPointZ->setText("");
    ui->lineEdit_NDIpointX->setText("");
    ui->lineEdit_NDIpointY->setText("");
    ui->lineEdit_NDIpointZ->setText("");
    ui->lineEdit_Rx->setText("");
    ui->lineEdit_Ry->setText("");
    ui->lineEdit_Rz->setText("");
    ui->lineEdit_Tx->setText("");
    ui->lineEdit_Ty->setText("");
    ui->lineEdit_TZ->setText("");
}

void SBMECoordinateRegistrationDlg::m_slotGetNDIPoint()
{
    emit m_signalToGetNDIPoint();
}

void SBMECoordinateRegistrationDlg::m_slotGetModelPoint()
{
    emit m_signalToGetModelPoint();
}

void SBMECoordinateRegistrationDlg::m_slotSartRegister()
{
    if (ComputeRegisterMatrix(m_NDIPoint, m_ModelPoint, m_nModelPoint, m_Traslation, m_Rotation, m_fZoom))
    {
        float fRoll, fCosRoll, fSinRoll;
        fRoll = atan2(m_Rotation[1][0], m_Rotation[0][0]);
        fCosRoll = cos(fRoll);
        fSinRoll = sin(fRoll);
        m_EulerRot[0] = fRoll;
        m_EulerRot[1] = atan2(-m_Rotation[2][0], (fCosRoll * m_Rotation[0][0]) + (fSinRoll * m_Rotation[1][0]));
        m_EulerRot[2] = atan2((fSinRoll * m_Rotation[0][2]) - (fCosRoll * m_Rotation[1][2]), (-fSinRoll * m_Rotation[0][1]) + (fCosRoll * m_Rotation[1][1]));

        ui->lineEdit_Tx->setText(QString::number(m_Traslation[0]));
        ui->lineEdit_Ty->setText(QString::number(m_Traslation[1]));
        ui->lineEdit_TZ->setText(QString::number(m_Traslation[2]));
        ui->lineEdit_Rx->setText(QString::number(m_EulerRot[0]));
        ui->lineEdit_Ry->setText(QString::number(m_EulerRot[1]));
        ui->lineEdit_Rz->setText(QString::number(m_EulerRot[2]));
        m_bRegistered = true;
        ui->lineEdit_Info->setText(QString("Successfully Registered"));
        ui->pushButton_StartRegister->setDisabled(true);
    }
    else
    {
        ReadytoGegister();
    }
}

void SBMECoordinateRegistrationDlg::NDIPointGot(float NdiPointX, float NdiPointY, float NdiPointZ)
{
    m_NDIPoint[m_nNDIPoint][0] = NdiPointX;
    m_NDIPoint[m_nNDIPoint][1] = NdiPointY;
    m_NDIPoint[m_nNDIPoint][2] = NdiPointZ;
    m_nNDIPoint++;
    ui->lineEdit_NDIpointX->setText(QString::number(NdiPointX));
    ui->lineEdit_NDIpointY->setText(QString::number(NdiPointY));
    ui->lineEdit_NDIpointZ->setText(QString::number(NdiPointZ));
    ui->pushButton_GetNDIPoint->setDisabled(true);
    ui->pushButton_GetModelPoint->setEnabled(true);
    ui->lineEdit_Info->setText(QString("%1 NDI Points Got").arg(m_nNDIPoint));
}

void SBMECoordinateRegistrationDlg::ModelPointGot(float ModelPointX, float ModelPointY, float ModelPointZ)
{
    m_ModelPoint[m_nModelPoint][0] = ModelPointX;
    m_ModelPoint[m_nModelPoint][1] = ModelPointY;
    m_ModelPoint[m_nModelPoint][2] = ModelPointZ;
    m_nModelPoint++;
    ui->lineEdit_ModelPointX->setText(QString::number(ModelPointX));
    ui->lineEdit_ModelPointY->setText(QString::number(ModelPointY));
    ui->lineEdit_ModelPointZ->setText(QString::number(ModelPointZ));
    if (m_nModelPoint < SBME_MAX_LANDMARK_NUM)
        ui->pushButton_GetNDIPoint->setEnabled(true);
    ui->pushButton_GetModelPoint->setDisabled(true);
    ui->lineEdit_Info->setText(QString("%1 Model Points Got").arg(m_nModelPoint));
    if ((m_nModelPoint >= 4) && (m_nModelPoint < SBME_MAX_LANDMARK_NUM))
        ui->pushButton_StartRegister->setEnabled(true);
}

bool SBMECoordinateRegistrationDlg::ComputeRegisterMatrix(float worldCoords[][3], float modelCoords[][3], int points, float T[], float R[][3], float S)
{
    int i, j, n;
    double temp[3], temp1[3];
    double max_lambda;
    int max_i;
    double mean_W_Coord[20][3], mean_M_Coord[20][3];  //
    double mean_W[3], mean_M[3];  // 世界坐标和模型坐标的质心
    double Sxwxm, Sxwym, Sxwzm, Sywxm, Sywym, Sywzm, Szwxm, Szwym, Szwzm; // 定义计算过程中的9个算子
    double N_matrix[4][4]; // 对称矩阵 4*4
    double v[4][4]; // 用于存放特征向量的矩阵
    int p, q, l;
    double eps;
    int jt;
    //int u,w,t,s;
    double fm, cn, sn, omega, x, y, d; // 矩阵分解的时候用的变量
    double unit_q[4]; // 单位四元数

    if ((points < 4) || (points > 20))
        return false;					// 标志点个数大于20个或者小于4个都不能进行计算

    for (i = 0; i < 3; i++)
    {
        temp[i] = 0.0;
        temp1[i] = 0.0;
    }

    // 计算 世界坐标的质心和模型坐标的质心
    for (i = 0; i < points; i++)
    {
        for (j = 0; j < 3; j++)
        {
            temp[j] = temp[j] + worldCoords[i][j];
            temp1[j] = temp1[j] + modelCoords[i][j];
        }
    }
    for (i = 0; i < 3; i++)
    {
        mean_W[i] = temp[i] / points;
        mean_M[i] = temp1[i] / points;
    }
    // 计算 将点集的绝对坐标值转化为与质心坐标相对应的坐标值
    for (i = 0; i < points; i++)
    {
        for (j = 0; j < 3; j++)
        {
            mean_W_Coord[i][j] = worldCoords[i][j] - mean_W[j];
            mean_M_Coord[i][j] = modelCoords[i][j] - mean_M[j];
        }
    }
    // 计算 点集中points个点的乘子之和
    Sxwxm = 0.0; Sxwym = 0.0; Sxwzm = 0.0;
    Sywxm = 0.0; Sywym = 0.0; Sywzm = 0.0;
    Szwxm = 0.0; Szwym = 0.0; Szwzm = 0.0;
    for (i = 0; i < points; i++)
    {
        Sxwxm = Sxwxm+mean_W_Coord[i][0] * mean_M_Coord[i][0];
        Sxwym = Sxwym+mean_W_Coord[i][0] * mean_M_Coord[i][1];
        Sxwzm = Sxwzm+mean_W_Coord[i][0] * mean_M_Coord[i][2];
        Sywxm = Sywxm+mean_W_Coord[i][1] * mean_M_Coord[i][0];
        Sywym = Sywym+mean_W_Coord[i][1] * mean_M_Coord[i][1];
        Sywzm = Sywzm+mean_W_Coord[i][1] * mean_M_Coord[i][2];
        Szwxm = Szwxm+mean_W_Coord[i][2] * mean_M_Coord[i][0];
        Szwym = Szwym+mean_W_Coord[i][2] * mean_M_Coord[i][1];
        Szwzm = Szwzm+mean_W_Coord[i][2] * mean_M_Coord[i][2];
    }
    // 由乘子组成的对称矩阵N_matrix
    N_matrix[0][0] = Sxwxm + Sywym + Szwzm;
    N_matrix[0][1] = Sywzm - Szwym;
    N_matrix[0][2] = Szwxm - Sxwzm;
    N_matrix[0][3] = Sxwym - Sywxm;

    N_matrix[1][0] = Sywzm - Szwym;
    N_matrix[1][1] = Sxwxm - Sywym - Szwzm;
    N_matrix[1][2] = Sxwym + Sywxm;
    N_matrix[1][3] = Szwxm + Sxwzm;

    N_matrix[2][0] = Szwxm - Sxwzm;
    N_matrix[2][1] = Sxwym + Sywxm;
    N_matrix[2][2] = -Sxwxm + Sywym - Szwzm;
    N_matrix[2][3] = Sywzm + Szwym;

    N_matrix[3][0] = Sxwym - Sywxm;
    N_matrix[3][1] = Szwxm + Sxwzm;
    N_matrix[3][2] = Sywzm + Szwym;
    N_matrix[3][3] = -Sxwxm - Sywym + Szwzm;
    // 根据Berthold方法求解对称矩阵N_matrix的最大特征值所对应的特征向量
    n = 4;  // 在本方法中采用的是4阶矩阵
    l = 1;
    eps = 0.000001;
    jt = 100;
    for (i = 0; i <= n - 1; i++)
    {
        v[i][i] = 1.0;
        for (j = 0; j <= n - 1; j++)
        {
            if (i != j)
                v[i][j] = 0.0;
        }
    }  // 定义了一个单位矩阵

    do //修改过2008-12-31
    {
        fm = 0.0;
        for (i = 0; i <= n - 1; i++)   //修改过2008-12-31
        {
            for (j = 0; j <= i; j++)  //  修改过2008-12-31
            {
                d = fabs(N_matrix[i][j]);
                if ((i != j) && (d > fm))
                {
                    fm = d;
                    p = i;
                    q = j;
                }
            }
        }
        if (fm < eps)
            //	return(1);
            break;//修改过2008-12-31
        if (l > jt)
            //	return(-1);////
            break;//修改过2008-12-31
        l = l + 1;
        //u=p*n+q; w=p*n+p; t=q*n+p; s=q*n+q;
        //x=-a[u]; y=(a[s]-a[w])/2.0;
        x = -N_matrix[p][q];
        y = (N_matrix[q][q] - N_matrix[p][p]) / 2.0;

        omega = x / sqrt(x * x + y * y);  // omega = sin(2*theta)
        if (y < 0.0)
            omega = -omega;
        sn = 1.0 + sqrt(1.0 - omega * omega);
        sn = omega / sqrt(2.0 * sn);  // sin(theta)=omega/sqrt(2*(1+sqrt(1-omega^2)))
        cn = sqrt(1.0 - sn * sn);
        //fm=a[w];
        fm = N_matrix[p][p];
        //a[w]=fm*cn*cn+a[s]*sn*sn+a[u]*omega;
        N_matrix[p][p] = fm * cn * cn + N_matrix[q][q] * sn * sn + N_matrix[p][q] * omega;
        //a[s]=fm*sn*sn+a[s]*cn*cn-a[u]*omega;
        N_matrix[q][q] = fm * sn * sn + N_matrix[q][q] * cn * cn - N_matrix[p][q] * omega;
        //a[u]=0.0; a[t]=0.0;
        N_matrix[p][q] = 0.0;
        N_matrix[q][p] = 0.0;
        for (j = 0; j <= n - 1; j++)
        {
            if ((j != p) && (j != q))
            {
                //u=p*n+j; w=q*n+j;
                //fm=a[u];
                fm = N_matrix[p][j];
                //a[u]=fm*cn+a[w]*sn;
                N_matrix[p][j] = fm * cn + N_matrix[q][j] * sn;
                //a[w]=-fm*sn+a[w]*cn;
                N_matrix[q][j] = -fm * sn + N_matrix[q][j] * cn;
            }
        }
        for (i = 0; i <= n - 1; i++)
        {
            if ((i != p) && (i != q))
            {
                //u=i*n+p; w=i*n+q;
                //fm=a[u];
                fm = N_matrix[i][p];
                //a[u]=fm*cn+a[w]*sn;
                N_matrix[i][p] = fm * cn + N_matrix[i][q] * sn;
                //a[w]=-fm*sn+a[w]*cn;
                N_matrix[i][q] = -fm * sn + N_matrix[i][q] * cn;
            }
        }
        for (i = 0; i <= n-1; i++)
        {
            //u=i*n+p; w=i*n+q;
            //fm=v[u];
            fm = v[i][p];
            //v[u]=fm*cn+v[w]*sn;
            v[i][p] = fm * cn + v[i][q] * sn;
            //v[w]=-fm*sn+v[w]*cn;
            v[i][q] = -fm * sn + v[i][q] * cn;
        }
    }while (1 == 1);// 修改过2008-12-31

    // 计算最大的特征值所对应的特征向量
    max_lambda = 0.0;
    max_i = 0;
    for (i = 0; i < n; i++)
    {
        if (i == 0)
        {
            max_lambda = N_matrix[i][i];
            max_i = i;
        }
        else
        {
            if (N_matrix[i][i] > max_lambda)
            {
                max_lambda = N_matrix[i][i];
                max_i = i;
            }
        }
    }
    // 得到特征向量
    for (i = 0; i < n; i++)
        unit_q[i] = v[i][max_i];
    // 归一化特征向量
    temp[0] = 0.0;
    for (i = 0; i < n; i++)
        temp[0] = temp[0] + unit_q[i] * unit_q[i];
    temp[0] = sqrt(temp[0]);
    for (i = 0; i < n; i++)
        unit_q[i] = unit_q[i] / temp[0];
    //
    // 计算旋转矩阵R
    R[0][0] = unit_q[0] * unit_q[0] + unit_q[1] * unit_q[1] - unit_q[2] * unit_q[2] - unit_q[3] * unit_q[3];
    R[0][1] = 2 * (unit_q[1] * unit_q[2] - unit_q[0] * unit_q[3]);
    R[0][2] = 2 * (unit_q[3] * unit_q[1] + unit_q[0] * unit_q[2]);
    R[1][0] = 2 * (unit_q[1] * unit_q[2] + unit_q[0] * unit_q[3]);
    R[1][1] = unit_q[0] * unit_q[0] - unit_q[1] * unit_q[1] + unit_q[2] * unit_q[2] - unit_q[3] * unit_q[3];
    R[1][2] = 2 * (unit_q[2] * unit_q[3] - unit_q[0] * unit_q[1]);
    R[2][0] = 2 * (unit_q[1] * unit_q[3] - unit_q[0] * unit_q[2]);
    R[2][1] = 2 * (unit_q[2] * unit_q[3] + unit_q[0] * unit_q[1]);
    R[2][2] = unit_q[0] * unit_q[0] - unit_q[1] * unit_q[1] - unit_q[2] * unit_q[2] + unit_q[3] * unit_q[3];
    //
    // 计算缩放量s
    temp[0] = 0.0;
    temp[1] = 0.0;
    for (i = 0; i < points; i++)
    {
        for (j = 0; j < 3; j++)
        {
            temp1[j] = R[j][0] * mean_W_Coord[i][0] + R[j][1] * mean_W_Coord[i][1] + R[j][2] * mean_W_Coord[i][2];
        }
        temp[0] = temp[0] + mean_M_Coord[i][0] * temp1[0] + mean_M_Coord[i][1] * temp1[1] + mean_M_Coord[i][2] * temp1[2];
        temp[1] = temp[1] + mean_W_Coord[i][0] * mean_W_Coord[i][0] + mean_W_Coord[i][1] * mean_W_Coord[i][1] + mean_W_Coord[i][2] * mean_W_Coord[i][2];
    }
    S = temp[0] / temp[1]; // 得到了缩放量
    // 计算平移矩阵
    for (j = 0; j < 3; j++)
    {
        temp1[j] = R[j][0] * mean_W[0] + R[j][1] * mean_W[1] + R[j][2] * mean_W[2];
    }
    for (i = 0; i < 3; i++)
    {

        T[i] = mean_M[i] - S * temp1[i];
    }

    return true;
}
