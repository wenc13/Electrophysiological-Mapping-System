#include "SBMEGridPoints.h"

SBMEGridPoints::SBMEGridPoints(void)
    : numGridPoints3D(0)
    , numGridLines2D(0)
    , numGridTriangles3D(0)
    , m_iLayer(60)
    , m_dRadius(50)
{
    ConstructGridModel();
}

// 带半径和分层数的构造函数
SBMEGridPoints::SBMEGridPoints(int layers, double radius)
{
    SetLayers(layers);
    SetRadius(radius);
    ConstructGridModel();
}

SBMEGridPoints::~SBMEGridPoints(void)
{
    delete [] infoGridTriangles;
    infoGridTriangles = NULL;

    delete [] infoGridLines;
    infoGridLines = NULL;

    delete [] infoGridPoints;
    infoGridPoints = NULL;
}

// 该函数在确定输入半径和分层数并对数据分配内存后计算点的坐标并存储
void SBMEGridPoints::ComputePointsCoordinate(void)
{
    int m_iPointNum = 0; //球面具有的点数初始化
    int m_iPointNumPerLayer; //每层具有的点数
    double theta; //纬度角
    double fai; //经度角
    double arr[3]; //临时变量，用于存储临时三维坐标点

    for (int i = 0; i != m_iLayer / 2 + 1; ++i)
    {
        m_iPointNumPerLayer = (i == 0) ? 1 : 6 * i;
        for (int j = 0; j < m_iPointNumPerLayer; j++)
        {
            theta = (i == 0) ? 0 : 0 + (2 * PI / (6 * i)) * j;
            fai = (PI / m_iLayer) * i;
            ComputeCoordinateByAngle(theta, fai, m_dRadius, arr);
            ArrayValueAssignment((infoGridPoints + m_iPointNum + j)->positionOfPoint, arr, 3);
            ArrayValueAssignment((infoGridPoints + m_iPointNum + j)->positionOfPointOriginal, arr, 3);
        }
        m_iPointNum += m_iPointNumPerLayer;
    }

    for (int i = m_iLayer / 2 +1; i != m_iLayer + 1; i++)
    {
        m_iPointNumPerLayer = (i == m_iLayer) ? 1 : 6 * (m_iLayer - i);
        for (int j = 0; j < m_iPointNumPerLayer; j++)
        {
            theta = (i == m_iLayer) ? 0 :0 + (2 * PI / (6 * (m_iLayer - i))) * j;
            fai = (PI / m_iLayer) * i;
            ComputeCoordinateByAngle(theta, fai, m_dRadius, arr);
            ArrayValueAssignment((infoGridPoints + m_iPointNum + j)->positionOfPoint, arr, 3);
            ArrayValueAssignment((infoGridPoints + m_iPointNum + j)->positionOfPointOriginal, arr, 3);
        }
        m_iPointNum += m_iPointNumPerLayer;
    }
}

// 建立网格表面顶点的关系，比如邻域点数
void SBMEGridPoints::CreatePointsRelation(void)
{
    int m_iPointNumPerLayer;
    /***************************** 上半球体 ******************************/
    for (int i = 0; i < m_iLayer / 2; i++)
    {
        m_iPointNumPerLayer = (i == 0) ? 1 : 6 * i;
        for (int j = 0; j < m_iPointNumPerLayer; j++)
        {
            if (0 == i)
            {
                infoGridPoints->numOfPointNeighbor = 6;
                for (int k = 1; k <= 6; k++)
                {
                    infoGridPoints->positionIdOfPointNeighbor[k-1] = k;
                    infoGridPoints->positionIdOfLineNeighbor[k-1][0] = (k == 6) ? 1 : k+1;
                    infoGridPoints->positionIdOfLineNeighbor[k-1][0] = (k == 1) ? 6 : k-1;
                }
            }
            else
            {
                int k = j / i;
                (infoGridPoints + j + 3 * i * (i - 1) + 1)->numOfPointNeighbor = 6;
                if (0 == j % i)
                {
                    (infoGridPoints + j + 3 * i * (i - 1) + 1)->positionIdOfPointNeighbor[0] =
                        ((1 == i) && (j == 6 * i - 1)) ? j + 3 * i * (i - 1) + 1 + 1 - 6 * i : j + 3 * i * (i - 1) + 1 + 1;
                    (infoGridPoints + j + 3 * i * (i - 1) + 1)->positionIdOfPointNeighbor[1] =
                        ((1 == i) && (j == 6 * i - 1)) ? j + 3 * i * (i - 1) + 1 + 1 - 6 * i : j + 3 * i * (i - 1) + 1 + 1;
                    (infoGridPoints + j + 3 * i * (i - 1) + 1)->positionIdOfPointNeighbor[2] =
                        3 * i * (i + 1) + 1 + 1 + (i + 1) * k;
                    (infoGridPoints + j + 3 * i * (i - 1) + 1)->positionIdOfPointNeighbor[3] =
                        3 * i * (i + 1) + 1 + (i + 1) * k;
                    (infoGridPoints + j + 3 * i * (i - 1) + 1)->positionIdOfPointNeighbor[4] =
                        (0 == k) ? 3 * (i + 1) * (i + 2) + 1 - 1 : 3 * (i + 1) * (i + 2) + 1 - 1 + (k - 6) * (i + 1);
                    (infoGridPoints + j + 3*i*(i-1) + 1)->positionIdOfPointNeighbor[5] =
                        (k == 0) ? j + 3 * i * (i - 1) + 1 - 1 + 6 * i : j + 3 * i * (i - 1) + 1 - 1;

                    for (int k = 0; k < 6; k++)
                    {
                        (infoGridPoints + j + 3 * i * (i - 1) + 1)->positionIdOfLineNeighbor[k][0] =
                            (k == 0) ? (infoGridPoints + j + 3 * i * (i - 1) + 1)->positionIdOfPointNeighbor[5] :
                                       (infoGridPoints + j + 3 * i * (i - 1) + 1)->positionIdOfPointNeighbor[k - 1];
                        (infoGridPoints + j + 3*i*(i-1) + 1)->positionIdOfLineNeighbor[k][1] =
                            (k == 5) ? (infoGridPoints + j + 3 * i * (i - 1) + 1)->positionIdOfPointNeighbor[0] :
                                       (infoGridPoints + j + 3 * i * (i - 1) + 1)->positionIdOfPointNeighbor[k + 1];
                    }
                }
                else
                {
                    //左上点
                    (infoGridPoints + j + 3 * i * (i - 1) + 1)->positionIdOfPointNeighbor[0] =
                        (j % i == 1) ? 3 * (i - 2) * (i - 1) + 1 + (i - 1) * k : j + 3 * i * (i - 1) + 1 - 6 * (i - 1) - k - 1;
                    //右上点
                    (infoGridPoints + j + 3 * i * (i - 1) + 1)->positionIdOfPointNeighbor[1] =
                        (j == 6 * i - 1) ? 3 * i * (i - 1) + 1 - 6 * (i - 1) : j + 3 * i * (i - 1) + 1 - 6 * (i - 1) - k;
                    //右点
                    (infoGridPoints + j + 3 * i * (i - 1) + 1)->positionIdOfPointNeighbor[2] =
                        (j == 6 * i -1) ? 3 * i * (i - 1) + 1 : j + 3 * i * (i - 1) + 1 + 1;
                    //右下点
                    (infoGridPoints + j + 3 * i * (i - 1) + 1)->positionIdOfPointNeighbor[3] =
                        j+ 3 * i * (i - 1) + 1 + 6 * i + k + 1;
                    //左下点
                    (infoGridPoints + j + 3 * i * (i - 1) + 1)->positionIdOfPointNeighbor[4] =
                        j+ 3 * i * (i - 1) + 1 + 6 * i + k;
                    //左点
                    (infoGridPoints + j + 3 * i * (i - 1) + 1)->positionIdOfPointNeighbor[5] =
                        j + 3 * i * (i - 1);

                    for (int k = 0; k < 6; k++)
                    {
                        (infoGridPoints + j + 3 * i * (i - 1) + 1)->positionIdOfLineNeighbor[k][0] =
                                (k == 0) ? (infoGridPoints + j + 3 * i * (i - 1) + 1)->positionIdOfPointNeighbor[5] :
                                           (infoGridPoints + j + 3 * i * (i - 1) + 1)->positionIdOfPointNeighbor[k - 1];
                        (infoGridPoints + j + 3*i*(i-1) + 1)->positionIdOfLineNeighbor[k][1] =
                                (k == 5) ? (infoGridPoints + j + 3 * i * (i - 1) + 1)->positionIdOfPointNeighbor[0] :
                                           (infoGridPoints + j + 3 * i * (i - 1) + 1)->positionIdOfPointNeighbor[k + 1];
                    }
                }
            }
        }
    }
    /***************************** 上半球体 ******************************/

    /***************************** 中间线 ******************************/
    m_iPointNumPerLayer = 6 * m_iLayer / 2;
    for (int j = 0; j < m_iPointNumPerLayer; j++)
    {
        int k = j / (m_iLayer / 2);

        if (j % (m_iLayer / 2) == 0)
        {
            (infoGridPoints + j + 3 * (m_iLayer / 2) * ((m_iLayer / 2) - 1) + 1)->numOfPointNeighbor = 4;
            //上边点
            (infoGridPoints + j + 3 * (m_iLayer / 2) * ((m_iLayer / 2) - 1) + 1)->positionIdOfPointNeighbor[0] =
                                  3 * ((m_iLayer / 2) - 2) * ((m_iLayer / 2) - 1) + 1 + ((m_iLayer / 2) - 1) * k;
            //右边点
            (infoGridPoints + j + 3 * (m_iLayer / 2) * ((m_iLayer / 2) - 1) + 1)->positionIdOfPointNeighbor[1] =
                              j + 3 * (m_iLayer / 2) * ((m_iLayer / 2) - 1) + 1 + 1;
            //下边点
            (infoGridPoints + j + 3 * (m_iLayer / 2) * ((m_iLayer / 2) - 1) + 1)->positionIdOfPointNeighbor[2] = ((GetVerticesNum() - 1) +
                              j - 3 * (m_iLayer / 2) * ((m_iLayer / 2) + 1)) + 6 * (m_iLayer / 2) - k;
            //左边点
            (infoGridPoints + j + 3 * (m_iLayer / 2) * ((m_iLayer / 2) - 1) + 1)->positionIdOfPointNeighbor[3] = (k == 0) ?
                              j + 3 * (m_iLayer / 2) * ((m_iLayer / 2) - 1) + 1 - 1 + 6 * (m_iLayer / 2) :
                              j + 3 * (m_iLayer / 2) * ((m_iLayer / 2) - 1) + 1 - 1;
            //无效点
            (infoGridPoints + j + 3 * (m_iLayer / 2) * ((m_iLayer / 2) - 1) + 1)->positionIdOfPointNeighbor[4] = INVALIDATE_INT;
            (infoGridPoints + j + 3 * (m_iLayer / 2) * ((m_iLayer / 2) - 1) + 1)->positionIdOfPointNeighbor[5] = INVALIDATE_INT;

            for (int k = 0; k < 4; k++)
            {
                (infoGridPoints + j + 3 * (m_iLayer / 2) * ((m_iLayer / 2) - 1) + 1)->positionIdOfLineNeighbor[k][0] = (k == 0) ?
                (infoGridPoints + j + 3 * (m_iLayer / 2) * ((m_iLayer / 2) - 1) + 1)->positionIdOfPointNeighbor[3] :
                (infoGridPoints + j + 3 * (m_iLayer / 2) * ((m_iLayer / 2) - 1) + 1)->positionIdOfPointNeighbor[k - 1];
                (infoGridPoints + j + 3 * (m_iLayer / 2) * ((m_iLayer / 2) - 1) + 1)->positionIdOfLineNeighbor[k][1] = (k == 3) ?
                (infoGridPoints + j + 3 * (m_iLayer / 2) * ((m_iLayer / 2) - 1) + 1)->positionIdOfPointNeighbor[0] :
                (infoGridPoints + j + 3 * (m_iLayer / 2) * ((m_iLayer / 2) - 1) + 1)->positionIdOfPointNeighbor[k + 1];
            }
        }
        else
        {
            (infoGridPoints + j + 3 * (m_iLayer / 2) * ((m_iLayer / 2) - 1) + 1)->numOfPointNeighbor = 6;

            //左上点
            (infoGridPoints + j + 3 * (m_iLayer / 2) * ((m_iLayer / 2) - 1) + 1)->positionIdOfPointNeighbor[0] = (j % (m_iLayer / 2) == 1) ?
                                  3 * ((m_iLayer / 2) - 2) * ((m_iLayer / 2) - 1) + 1 + ((m_iLayer / 2) - 1) * k :
                              j + 3 * (m_iLayer / 2) * ((m_iLayer / 2) - 1) + 1 - 6 * ((m_iLayer / 2) - 1) - k - 1;
            //右上点
            (infoGridPoints + j + 3 * (m_iLayer / 2) * ((m_iLayer / 2) - 1) + 1)->positionIdOfPointNeighbor[1] = (j == 6 * (m_iLayer / 2) - 1) ?
                                  3 * (m_iLayer / 2) * ((m_iLayer / 2) - 1) + 1 - 6 * ((m_iLayer / 2) - 1) :
                              j + 3 * (m_iLayer / 2) * ((m_iLayer / 2) - 1) + 1 - 6 * ((m_iLayer / 2) - 1) - k;
            //右点
            (infoGridPoints + j + 3 * (m_iLayer / 2) * ((m_iLayer / 2) - 1) + 1)->positionIdOfPointNeighbor[2] = (j == 6 * (m_iLayer / 2) - 1) ?
                                  3 * (m_iLayer / 2) * ((m_iLayer / 2) - 1) + 1 :
                              j + 3 * (m_iLayer / 2) * ((m_iLayer / 2) - 1) + 1 + 1;
            //右下点
            (infoGridPoints + j + 3 * (m_iLayer / 2) * ((m_iLayer / 2) - 1) + 1)->positionIdOfPointNeighbor[3] = (j == 6 * (m_iLayer / 2) - 1) ?
                                   (GetVerticesNum() - 1) - 3 * (m_iLayer / 2) * ((m_iLayer / 2) + 1) + 6 * (m_iLayer / 2) :
                              j + ((GetVerticesNum() - 1) - 3 * (m_iLayer / 2) * ((m_iLayer / 2) + 1)) + 6 * (m_iLayer / 2) - k - 1 + 1;
            //左下点
            (infoGridPoints + j + 3 * (m_iLayer / 2) * ((m_iLayer / 2) - 1) + 1)->positionIdOfPointNeighbor[4] = ((GetVerticesNum() - 1) +
                              j - 3 * (m_iLayer / 2) * ((m_iLayer / 2) + 1)) + 6 * (m_iLayer / 2) - k - 1;
            //左点
            (infoGridPoints + j + 3 * (m_iLayer / 2) * ((m_iLayer / 2) - 1) + 1)->positionIdOfPointNeighbor[5] =
                              j + 3 * (m_iLayer / 2) * ((m_iLayer / 2) - 1);

            for (int k = 0; k < 6; k++)
            {
                (infoGridPoints + j + 3 * (m_iLayer / 2) * ((m_iLayer / 2) - 1) + 1)->positionIdOfLineNeighbor[k][0] = (k == 0) ?
                (infoGridPoints + j + 3 * (m_iLayer / 2) * ((m_iLayer / 2) - 1) + 1)->positionIdOfPointNeighbor[5] :
                (infoGridPoints + j + 3 * (m_iLayer / 2) * ((m_iLayer / 2) - 1) + 1)->positionIdOfPointNeighbor[k - 1];
                (infoGridPoints + j + 3 * (m_iLayer / 2) * ((m_iLayer / 2) - 1) + 1)->positionIdOfLineNeighbor[k][1] = (k == 5) ?
                (infoGridPoints + j + 3 * (m_iLayer / 2) * ((m_iLayer / 2) - 1) + 1)->positionIdOfPointNeighbor[0] :
                (infoGridPoints + j + 3 * (m_iLayer / 2) * ((m_iLayer / 2) - 1) + 1)->positionIdOfPointNeighbor[k + 1];
            }
        }
    }
    /***************************** 中间线 ******************************/

    /***************************** 下半球体 ******************************/
    for (int i = m_iLayer; i >= m_iLayer / 2 + 1; i--)
    {
        m_iPointNumPerLayer = (i == m_iLayer) ? 1 : 6 * (m_iLayer - i);
        int m_iLayerT = m_iLayer - i;

        for (int j = 0; j < m_iPointNumPerLayer; j++)
        {
            if (m_iLayer == i)
            {
                (infoGridPoints + GetVerticesNum() - 1)->numOfPointNeighbor = 6;

                for (int k = 0; k < 6; k++)
                {
                    (infoGridPoints + GetVerticesNum() - 1)->positionIdOfPointNeighbor[k] = GetVerticesNum() - 1 + (k - 6);
                    (infoGridPoints + GetVerticesNum() - 1)->positionIdOfLineNeighbor[k][0] = ( k == 0 ) ?
                    (infoGridPoints + GetVerticesNum() - 1)->positionIdOfPointNeighbor[5] :
                    (infoGridPoints + GetVerticesNum() - 1)->positionIdOfPointNeighbor[k - 1];
                    (infoGridPoints + GetVerticesNum() - 1)->positionIdOfLineNeighbor[k][1] = ( k == 5 ) ?
                    (infoGridPoints + GetVerticesNum() - 1)->positionIdOfPointNeighbor[0] :
                    (infoGridPoints + GetVerticesNum() - 1)->positionIdOfPointNeighbor[k + 1];
                }
            }
            else
            {
                int k = j / m_iLayerT;
                (infoGridPoints + j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)))->numOfPointNeighbor = 6;

                if (0 == j % m_iLayerT)
                {
                    //从外面看下 从里面看上边点
                    (infoGridPoints + j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)))->positionIdOfPointNeighbor[3] = (m_iLayerT >= 2) ?
                                      j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) + 6 * m_iLayerT - k : GetVerticesNum() - 1;
                    //从外看右 从里面看右边点
                    (infoGridPoints + j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)))->positionIdOfPointNeighbor[2] = ((1 == m_iLayerT) && (j == 6 * m_iLayerT - 1)) ?
                                      j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) + 1 - 6 * m_iLayerT :
                                      j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) + 1;
                    //从外看右上 从里面看右下
                    (infoGridPoints + j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)))->positionIdOfPointNeighbor[1] =
                                      j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) - 6 * (m_iLayerT + 1) + (k + 1);
                    //从外看上 从里面看下边点
                    (infoGridPoints + j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)))->positionIdOfPointNeighbor[0] =
                                      j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) - 6 * (m_iLayerT+1) + k;
                    //从外看左上 从里面看左下点
                    (infoGridPoints + j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)))->positionIdOfPointNeighbor[5] = (0 == k) ?
                                      j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) - 1 :
                                      j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) - 6 * (m_iLayerT + 1) + (k - 1);
                    //从外面看左 从里面看左边点
                    (infoGridPoints + j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)))->positionIdOfPointNeighbor[4] = (k == 0) ?
                                      j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) - 1 + 6 * m_iLayerT :
                                      j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) - 1;

                    for (int k = 0; k < 6; k++)
                    {
                        (infoGridPoints + j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)))->positionIdOfLineNeighbor[k][0] = ( k == 0 ) ?
                        (infoGridPoints + j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)))->positionIdOfPointNeighbor[5] :
                        (infoGridPoints + j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)))->positionIdOfPointNeighbor[k - 1];

                        (infoGridPoints + j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)))->positionIdOfLineNeighbor[k][1] = ( k == 5 ) ?
                        (infoGridPoints + j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)))->positionIdOfPointNeighbor[0] :
                        (infoGridPoints + j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)))->positionIdOfPointNeighbor[k + 1];
                    }
                }
                else
                {
                    //从外面看左下 从里面看左上点
                    (infoGridPoints + j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)))->positionIdOfPointNeighbor[4] =
                                      j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) + 6 * m_iLayerT - k - 1;
                    //从外面看右下 从里面看右上点
                    (infoGridPoints + j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)))->positionIdOfPointNeighbor[3] = (j == 6 * m_iLayerT - 1) ?
                                           (GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1) + 6 * m_iLayerT :
                                      j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) + 6 * m_iLayerT - k - 1 + 1;
                    //从外面看右 从里面看右点
                    (infoGridPoints + j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)))->positionIdOfPointNeighbor[2] = (j == 6 * m_iLayerT - 1) ?
                                           (GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1) :
                                      j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) + 1;
                    //从外面看右上 从里面看右下点
                    (infoGridPoints + j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)))->positionIdOfPointNeighbor[1] =
                                      j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) - 6 * (m_iLayerT + 1) + k + 1;
                    //从外面看左上 从里面看左下点
                    (infoGridPoints + j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)))->positionIdOfPointNeighbor[0] =
                                      j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) - 6 * (m_iLayerT + 1) + k;
                    //从外面看左点 从里面看左点
                    (infoGridPoints + j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)))->positionIdOfPointNeighbor[5] =
                                      j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) - 1;

                    for (int k = 0; k < 6; k++)
                    {
                        (infoGridPoints + j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)))->positionIdOfLineNeighbor[k][0] = ( k == 0 ) ?
                        (infoGridPoints + j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)))->positionIdOfPointNeighbor[5] :
                        (infoGridPoints + j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)))->positionIdOfPointNeighbor[k - 1];

                        (infoGridPoints + j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)))->positionIdOfLineNeighbor[k][1] = ( k == 5 ) ?
                        (infoGridPoints + j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)))->positionIdOfPointNeighbor[0] :
                        (infoGridPoints + j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)))->positionIdOfPointNeighbor[k + 1];
                    }
                }
            }
        }
    }
    /***************************** 下半球体 ******************************/
}

// 该函数在确定点的坐标后确定所有的点连线
void SBMEGridPoints::ComputeLinesRelation(void)
{
    int m_iPointNumPerLayer; //每层具有的点数
    int m_iLineNum = 0; //球面具有的边数初始化
    int indexTmp[2]; //临时变量，用于存储线临时二维点索引
    /************************************************************
    上半球体连接线
    ************************************************************/
    for (int i = 0; i < m_iLayer / 2; i++)
    {
        m_iPointNumPerLayer = (i == 0) ? 1 : 6 * i;
        for (int j = 0; j < m_iPointNumPerLayer; j++)
        {
            if (0 == i)
            {
                indexTmp[0] = 0;
                for (int k = 0; k != 6; k++)
                {
                    indexTmp[1] = k + 1;
                    ArrayValueAssignment((infoGridLines + m_iLineNum)->pointsIndex, indexTmp, 2);
                    ++m_iLineNum;
                }
            }
            else
            {
                int k = j / i;
                indexTmp[0] = j + 3 * i * (i - 1) + 1;
                if (0 == j % i)
                {
                    if (0 == k)
                    {
                        //左下
                        indexTmp[1] = 3 * (i + 1) * (i + 2) + 1 - 1;
                        ArrayValueAssignment((infoGridLines + m_iLineNum)->pointsIndex, indexTmp, 2);
                        ++m_iLineNum;
                        //下
                        indexTmp[1] = 3 * i * (i + 1) + 1;
                        ArrayValueAssignment((infoGridLines + m_iLineNum)->pointsIndex, indexTmp, 2);
                        ++m_iLineNum;
                        //右下
                        indexTmp[1] = 3 * i * (i + 1) + 1 + 1;
                        ArrayValueAssignment((infoGridLines + m_iLineNum)->pointsIndex, indexTmp, 2);
                        ++m_iLineNum;
                        //右
                        indexTmp[1] = j + 3 * i * (i - 1) + 1 + 1;
                        ArrayValueAssignment((infoGridLines + m_iLineNum)->pointsIndex, indexTmp, 2);
                        ++m_iLineNum;
                    }
                    else
                    {
                        //左下
                        indexTmp[1] = 3 * (i + 1) * (i + 2) + 1 - 1 + (k - 6) * (i + 1);
                        ArrayValueAssignment((infoGridLines + m_iLineNum)->pointsIndex, indexTmp, 2);
                        ++m_iLineNum;
                        //下
                        indexTmp[1] = 3 * i * (i + 1) + 1 + k * (i + 1);
                        ArrayValueAssignment((infoGridLines + m_iLineNum)->pointsIndex, indexTmp, 2);
                        ++m_iLineNum;
                        //右下
                        indexTmp[1] = 3 * i * (i + 1) + 1 + 1 + k * (i + 1);
                        ArrayValueAssignment((infoGridLines + m_iLineNum)->pointsIndex, indexTmp, 2);
                        ++m_iLineNum;
                        //右
                        if ((1 == i) && (j == 6 * i - 1))
                        {
                            indexTmp[1] = j + 3 * i * (i - 1) + 1 + 1 - 6 * i;
                            ArrayValueAssignment((infoGridLines + m_iLineNum)->pointsIndex, indexTmp, 2);
                            ++m_iLineNum;
                        }
                        else
                        {
                            indexTmp[1] = j + 3 * i * (i - 1) + 1 + 1;
                            ArrayValueAssignment((infoGridLines + m_iLineNum)->pointsIndex, indexTmp, 2);
                            ++m_iLineNum;
                        }
                    }
                }
                else
                {
                    //左下
                    indexTmp[1] = j + 3 * i * (i - 1) + 1 + 6 * i + k;
                    ArrayValueAssignment((infoGridLines + m_iLineNum)->pointsIndex, indexTmp, 2);
                    ++m_iLineNum;
                    //右下
                    indexTmp[1] = j + 3 * i * (i - 1) + 1 + 6 * i + k + 1;
                    ArrayValueAssignment((infoGridLines + m_iLineNum)->pointsIndex, indexTmp, 2);
                    ++m_iLineNum;
                    //右
                    if (j == 6 * i -1)
                    {
                        indexTmp[1] = 3 * i * (i - 1) + 1;
                        ArrayValueAssignment((infoGridLines + m_iLineNum)->pointsIndex, indexTmp, 2);
                        ++m_iLineNum;
                    }
                    else
                    {
                        indexTmp[1] = j + 3 * i * (i - 1) + 1 + 1;
                        ArrayValueAssignment((infoGridLines + m_iLineNum)->pointsIndex, indexTmp, 2);
                        ++m_iLineNum;
                    }
                }
            }
        }
    }
    /************************************************************
    上半球体连接线
    ************************************************************/


    /************************************************************
    中间连接线
    ************************************************************/
    m_iPointNumPerLayer = 6 * m_iLayer / 2;
    for (int j = 0; j != m_iPointNumPerLayer; j++)
    {
        indexTmp[0] = j + 3 * (m_iLayer / 2) * ((m_iLayer / 2) - 1) + 1;
        if (j == m_iPointNumPerLayer - 1)
        {
            indexTmp[1] = 0 + 3 * (m_iLayer / 2) * ((m_iLayer / 2) - 1) + 1;
            ArrayValueAssignment((infoGridLines + m_iLineNum)->pointsIndex, indexTmp, 2);
            ++m_iLineNum;
        }
        else
        {
            indexTmp[1] = j + 1 + 3 * (m_iLayer / 2) * ((m_iLayer / 2) - 1) + 1;
            ArrayValueAssignment((infoGridLines + m_iLineNum)->pointsIndex, indexTmp, 2);
            ++m_iLineNum;
        }
    }
    /************************************************************
    中间连接线
    ************************************************************/


    /************************************************************
    下半球体连接线
    ************************************************************/
    for (int i = m_iLayer; i >= m_iLayer / 2 + 1; i--)
    {
        m_iPointNumPerLayer = (i == m_iLayer) ? 1 : 6 * (m_iLayer - i);
        int m_iLayerT = m_iLayer - i;

        for (int j = 0; j < m_iPointNumPerLayer; j++)
        {
            if (i == m_iLayer)
            {
                indexTmp[0] = GetVerticesNum() - 1;
                for (int k = 0; k < 6; k++)
                {
                    indexTmp[1] = GetVerticesNum() - 1 + (k - 6);
                    ArrayValueAssignment((infoGridLines + m_iLineNum)->pointsIndex, indexTmp, 2);
                    ++m_iLineNum;
                }
            }
            else
            {
                int k = j / m_iLayerT;
                indexTmp[0] = j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1));
                if (0 == j % m_iLayerT)
                {
                    if (0 == k)
                    {
                        //从外看左上 从里面看左下
                        indexTmp[1] = j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) - 1;
                        ArrayValueAssignment((infoGridLines + m_iLineNum)->pointsIndex, indexTmp, 2);
                        ++m_iLineNum;
                        //从外看上 从里面看下
                        indexTmp[1] = j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) - 6 * (m_iLayerT + 1);
                        ArrayValueAssignment((infoGridLines + m_iLineNum)->pointsIndex, indexTmp, 2);
                        ++m_iLineNum;
                        //从外看右上 从里面看右下
                        indexTmp[1] = j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) - 6 * (m_iLayerT + 1) + 1;
                        ArrayValueAssignment((infoGridLines + m_iLineNum)->pointsIndex, indexTmp, 2);
                        ++m_iLineNum;
                        //从外看右 从里面看右
                        indexTmp[1] = j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) + 1;
                        ArrayValueAssignment((infoGridLines + m_iLineNum)->pointsIndex, indexTmp, 2);
                        ++m_iLineNum;
                    }
                    else
                    {
                        //从外看左上 从里面看左下
                        indexTmp[1] = j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) - 6 * (m_iLayerT + 1) + (k - 1);
                        ArrayValueAssignment((infoGridLines + m_iLineNum)->pointsIndex, indexTmp, 2);
                        ++m_iLineNum;
                        //从外看上 从里面看下
                        indexTmp[1] = j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) - 6 * (m_iLayerT + 1) + k;
                        ArrayValueAssignment((infoGridLines + m_iLineNum)->pointsIndex, indexTmp, 2);
                        ++m_iLineNum;
                        //从外看右上 从里面看右下
                        indexTmp[1] = j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) - 6 * (m_iLayerT + 1) + (k + 1);
                        ArrayValueAssignment((infoGridLines + m_iLineNum)->pointsIndex, indexTmp, 2);
                        ++m_iLineNum;
                        //从外看右 从里面看右
                        if ((1 == m_iLayerT) && (j == 6 * m_iLayerT -  1))
                        {
                            indexTmp[1] = j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) + 1 - 6 * m_iLayerT;
                            ArrayValueAssignment((infoGridLines + m_iLineNum)->pointsIndex, indexTmp, 2);
                            ++m_iLineNum;
                        }
                        else
                        {
                            indexTmp[1] = j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) + 1;
                            ArrayValueAssignment((infoGridLines + m_iLineNum)->pointsIndex, indexTmp, 2);
                            ++m_iLineNum;
                        }
                    }
                }
                else
                {
                    //从外看左上 从里面看左下
                    indexTmp[1] = j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) - 6 * (m_iLayerT + 1) + k;
                    ArrayValueAssignment((infoGridLines + m_iLineNum)->pointsIndex, indexTmp, 2);
                    ++m_iLineNum;
                    //从外看右上 从里面看右下
                    indexTmp[1] = j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) - 6 * (m_iLayerT + 1) + k + 1;
                    ArrayValueAssignment((infoGridLines + m_iLineNum)->pointsIndex, indexTmp, 2);
                    ++m_iLineNum;
                    //从外看右 从里面看右
                    if (j == 6 * m_iLayerT - 1)
                    {
                        indexTmp[1] = j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) + 1 - 6 * m_iLayerT;
                        ArrayValueAssignment((infoGridLines + m_iLineNum)->pointsIndex, indexTmp, 2);
                        ++m_iLineNum;
                    }
                    else
                    {
                        indexTmp[1] = j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) + 1;
                        ArrayValueAssignment((infoGridLines + m_iLineNum)->pointsIndex, indexTmp, 2);
                        ++m_iLineNum;
                    }
                }
            }
        }
    }
    /************************************************************
    下半球体连接线
    ************************************************************/
}

// 该函数在确定点的坐标后确定所有的点连线
void SBMEGridPoints::ComputeTrianglesRelation(void)
{
    int m_iPointNumPerLayer; //每层具有的点数
    int m_iTriangleNum = 0; //球面具有的三角形数初始化
    int indexTmp[3]; //临时变量，用于存储线临时三维点索引

    /************************************************************
    构建上半球三角面片
    ************************************************************/
    for (int i = 0; i < m_iLayer / 2; i++)
    {
        m_iPointNumPerLayer = (i == 0) ? 1 : 6 * i;

        for (int j = 0; j < m_iPointNumPerLayer; j++)
        {
            if (0 == i)
            {
                indexTmp[0] = 0;
                for (int k = 1; k <= 6; k++)
                {
                    indexTmp[1] = k;
                    indexTmp[2] = 6 == k ? 1 : k + 1;
                    ArrayValueAssignment((infoGridTriangles + m_iTriangleNum)->pointsIndex, indexTmp, 3);
                    ++m_iTriangleNum;
                }
            }
            else
            {
                int k = j / i;

                indexTmp[0] = j + 3 * i * (i - 1) + 1;
                if (0 == j % i)
                {
                    if (0 == k)
                    {
                        indexTmp[1] = 3 * (i + 1) * (i + 2) + 1 - 1;
                        indexTmp[2] = 3 * i * (i + 1) + 1;
                        ArrayValueAssignment((infoGridTriangles + m_iTriangleNum)->pointsIndex, indexTmp, 3);
                        ++m_iTriangleNum;

                        indexTmp[1] = 3 * i * (i + 1) + 1;
                        indexTmp[2] = 3 * i * (i + 1) + 1 + 1;
                        ArrayValueAssignment((infoGridTriangles + m_iTriangleNum)->pointsIndex, indexTmp, 3);
                        ++m_iTriangleNum;

                        indexTmp[1] = 3 * i * (i + 1) + 1 + 1;
                        indexTmp[2] = j + 3 * i * (i - 1) + 1 + 1;
                        ArrayValueAssignment((infoGridTriangles + m_iTriangleNum)->pointsIndex, indexTmp, 3);
                        ++m_iTriangleNum;
                    }
                    else
                    {
                        indexTmp[1] = 3 * (i + 1) * (i + 2) + 1 - 1 + (k - 6) * (i + 1);
                        indexTmp[2] = 3 * i *(i + 1) + 1 + k * (i + 1);
                        ArrayValueAssignment((infoGridTriangles + m_iTriangleNum)->pointsIndex, indexTmp, 3);
                        ++m_iTriangleNum;

                        indexTmp[1] = 3 * i * (i + 1) + 1 + k * (i + 1);
                        indexTmp[2] = 3 * i * (i + 1) + 1 + 1 + k * (i + 1);
                        ArrayValueAssignment((infoGridTriangles + m_iTriangleNum)->pointsIndex, indexTmp, 3);
                        ++m_iTriangleNum;

                        indexTmp[1] = 3 * i * (i + 1) + 1 + 1 + k * (i + 1);
                        indexTmp[2] = ((1 == i) && (j == 6 * i - 1)) ? j + 3 * i * (i - 1) + 1 + 1 - 6 * i : j + 3 * i * (i - 1) + 1 + 1;
                        ArrayValueAssignment((infoGridTriangles + m_iTriangleNum)->pointsIndex, indexTmp, 3);
                        ++m_iTriangleNum;
                    }
                }
                else
                {
                    indexTmp[1] = (j == 6 * i -1) ? 3 * i * (i - 1) + 1 : j + 3 * i * (i - 1) + 1 + 1;
                    indexTmp[2] = j + 3 * i * (i - 1) + 1 + 6 * i + k + 1;
                    ArrayValueAssignment((infoGridTriangles + m_iTriangleNum)->pointsIndex, indexTmp, 3);
                    ++m_iTriangleNum;

                    indexTmp[1] = j + 3 * i * (i - 1) + 1 + 6 * i + k;
                    indexTmp[2] = j + 3 * i * (i - 1) + 1 + 6 * i + k + 1;
                    ArrayValueAssignment((infoGridTriangles + m_iTriangleNum)->pointsIndex, indexTmp, 3);
                    ++m_iTriangleNum;
                }
            }
        }
    }
    /************************************************************
    构建上半球三角面片
    ************************************************************/


    /************************************************************
    构建下半球三角面片
    ************************************************************/
    for (int i = m_iLayer; i >= m_iLayer / 2 + 1; i--)
    {
        m_iPointNumPerLayer = (i == m_iLayer) ? 1 : 6 * (m_iLayer - i);
        int m_iLayerT = m_iLayer - i;

        for (int j = 0; j < m_iPointNumPerLayer; j++)
        {
            if (m_iLayer == i)
            {
                indexTmp[0] = GetVerticesNum() - 1;
                for (int k = 0; k < 6; k++)
                {
                    indexTmp[1] = GetVerticesNum() - 1 + (k - 6);
                    indexTmp[2] = (5 == k ? GetVerticesNum() - 1 - 6 : GetVerticesNum() - 1 + (k - 6) + 1);
                    ArrayValueAssignment((infoGridTriangles + m_iTriangleNum)->pointsIndex, indexTmp, 3);
                    ++m_iTriangleNum;
                }
            }
            else
            {
                int k = j / m_iLayerT;
                indexTmp[0] = j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1));
                if (0 == j % m_iLayerT)
                {
                    if (0 == k)
                    {
                        indexTmp[1] = j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) - 1;
                        indexTmp[2] = j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) - 6 * (m_iLayerT + 1);
                        ArrayValueAssignment((infoGridTriangles + m_iTriangleNum)->pointsIndex, indexTmp, 3);
                        ++m_iTriangleNum;

                        indexTmp[1] = j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) - 6 * (m_iLayerT + 1);
                        indexTmp[2] = j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) - 6 * (m_iLayerT + 1) + 1;
                        ArrayValueAssignment((infoGridTriangles + m_iTriangleNum)->pointsIndex, indexTmp, 3);
                        ++m_iTriangleNum;

                        indexTmp[1] = j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) - 6 * (m_iLayerT + 1) + 1;
                        indexTmp[2] = j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) + 1;
                        ArrayValueAssignment((infoGridTriangles + m_iTriangleNum)->pointsIndex, indexTmp, 3);
                        ++m_iTriangleNum;
                    }
                    else
                    {
                        indexTmp[1] = j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) - 6 * (m_iLayerT + 1) + (k - 1);
                        indexTmp[2] = j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) - 6 * (m_iLayerT + 1) + k;
                        ArrayValueAssignment((infoGridTriangles + m_iTriangleNum)->pointsIndex, indexTmp, 3);
                        ++m_iTriangleNum;

                        indexTmp[1] = j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) - 6 * (m_iLayerT + 1) + k;
                        indexTmp[2] = j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) - 6 * (m_iLayerT + 1) + (k + 1);
                        ArrayValueAssignment((infoGridTriangles + m_iTriangleNum)->pointsIndex, indexTmp, 3);
                        ++m_iTriangleNum;

                        indexTmp[1] = j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) - 6 * (m_iLayerT + 1) + (k + 1);
                        indexTmp[2] = ((1 == m_iLayerT) && (j == 6 * m_iLayerT - 1))
                                ? j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) + 1 - 6 * m_iLayerT
                                : j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) + 1;
                        ArrayValueAssignment((infoGridTriangles + m_iTriangleNum)->pointsIndex, indexTmp, 3);
                        ++m_iTriangleNum;
                    }
                }
                else
                {
                    indexTmp[1] = j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) - 6 * (m_iLayerT + 1) + k;
                    indexTmp[2] = j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) - 6 * (m_iLayerT + 1) + k + 1;
                    ArrayValueAssignment((infoGridTriangles + m_iTriangleNum)->pointsIndex, indexTmp, 3);
                    ++m_iTriangleNum;

                    indexTmp[1] = (j == 6 * m_iLayerT - 1)
                            ? j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) + 1 - 6 * m_iLayerT
                            : j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) + 1;
                    indexTmp[2] = j + ((GetVerticesNum() - 1) - 3 * m_iLayerT * (m_iLayerT + 1)) - 6 * (m_iLayerT + 1) + k + 1;
                    ArrayValueAssignment((infoGridTriangles + m_iTriangleNum)->pointsIndex, indexTmp, 3);
                    ++m_iTriangleNum;
                }
            }
        }
    }
    /************************************************************
    构建下半球三角面片
    ************************************************************/
}

// 工具函数
// 根据输入的两个角度和半径计算坐标 输入经度角：theta，纬度角：fai，返回给输入的数组引用
void SBMEGridPoints::ComputeCoordinateByAngle(double theta, double fai, double radius, double *arrAddress)
{
    *arrAddress       = radius * cos(theta) * sin(fai);
    *(arrAddress + 1) = radius * sin(theta) * sin(fai);
    *(arrAddress + 2) = radius * cos(fai);
}

// 工具函数
// 数组赋值，直接将一个数组的 arrDimension 个值赋给另一个数组
template<class T>
void SBMEGridPoints::ArrayValueAssignment(T *arrOne, const T *arrTwo, const int arrDimension)
{
    for (int i = 0; i != arrDimension; i++)
    {
        *(arrOne + i) = *(arrTwo + i);
    }
}

// 返回网格表面顶点的总数
int SBMEGridPoints::GetVerticesNum(void)
{
    return numGridPoints3D;
}

// 返回网格表面连线的总数
int SBMEGridPoints::GetLinesNum(void)
{
    return numGridLines2D;
}

// 返回网格表面三角形的总数
int SBMEGridPoints::GetTrianglesNum(void)
{
    return numGridTriangles3D;
}

// 设置网格表面顶点的总数
void SBMEGridPoints::SetVerticesNum(int para)
{
    numGridPoints3D = para;
}

// 设置网格表面连线的总数
void SBMEGridPoints::SetLinesNum(int para)
{
    numGridLines2D = para;
}

// 设置网格表面三角形的总数
void SBMEGridPoints::SetTrianglesNum(int para)
{
    numGridTriangles3D = para;
}

// 设置半径
void SBMEGridPoints::SetRadius(double para)
{
    m_dRadius = para;
}

// 设置分层数
void SBMEGridPoints::SetLayers(int para)
{
    m_iLayer = para;
}

// 设置半径
void SBMEGridPoints::ReSetRadius(double para)
{
    SetRadius(para);

    delete [] infoGridPoints;
    delete [] infoGridLines;
    delete [] infoGridTriangles;

    ConstructGridModel();
}

// 设置分层数
void SBMEGridPoints::ReSetLayers(int para)
{
    SetLayers(para);

    delete [] infoGridTriangles;
    delete [] infoGridLines;
    delete [] infoGridPoints;

    ConstructGridModel();
}

// 重新设置参数，包括半径和分层数
void SBMEGridPoints::ReSetParameters(int layers, double radius)
{
    SetRadius(radius);
    SetLayers(layers);

    delete [] infoGridTriangles;
    delete [] infoGridLines;
    delete [] infoGridPoints;

    ConstructGridModel();
}

// 利用传入的参数构建网格模型，包括表面点，点之间的拓扑关系，以及线和三角形的数据维护
void SBMEGridPoints::ConstructGridModel(void)
{
    SetVerticesNum(3 * m_iLayer * m_iLayer / 2 + 2);
    infoGridPoints = new GridPointInfo[GetVerticesNum()];
    //SetLinesNum(20000);	// 需要计算出有多少条边
    SetLinesNum(9 * m_iLayer * m_iLayer / 2);	// 需要计算出有多少条边
    infoGridLines = new GridLineInfo[GetLinesNum()];
    //SetTrianglesNum(20000);	// 需要计算出有多少个三角形
    SetTrianglesNum(3 * m_iLayer * m_iLayer);	// 需要计算出有多少个三角形
    infoGridTriangles = new GridTriangleInfo[GetTrianglesNum()];

    ComputePointsCoordinate();
    CreatePointsRelation();
    SetPointMeanDistance();
    ComputeLinesRelation();
    ComputeTrianglesRelation();
}

// 返回一个指定 pointnum 的点的坐标，存储在数组指针 pointvalue 所指的数组对象中
void SBMEGridPoints::GetPoint(const int pointnum, double *pointvalue)
{
    //for(int i = 0; i != 3; i++)
    //{
    //	pointvalue[i] = (infoGridPoints + pointnum)->positionOfPoint[i];
    //}

    // 错误 ERROR NO ERROR
    // 此时结构体里的地址排列不一定是规则的，所以用地址直接赋值有可能会出错
    // 这种调用方式是没有错误的
    ArrayValueAssignment(pointvalue, (infoGridPoints + pointnum)->positionOfPoint, 3);
}

// 查找指定参数 pointnum 的三维坐标点，并返回坐标点的地址引用
double *SBMEGridPoints::GetPoint(const int pointnum)
{

    return (infoGridPoints + pointnum)->positionOfPoint;
}

// 设定一个指定 pointnum 的点的坐标，数组指针 pointvalue 作为输入
void SBMEGridPoints::SetPoint(const int pointnum, const double *pointvalue)
{
    ArrayValueAssignment((infoGridPoints + pointnum)->positionOfPoint, pointvalue, 3);
}

// 设定一个指定 pointnum 的点的位移向量，数组指针 pointvalue 作为输入
void SBMEGridPoints::SetPointTransVector(const int pointnum, const double *pointvalue)
{
    ArrayValueAssignment((infoGridPoints + pointnum)->translateVector, pointvalue, 3);
}

// 该函数在每次设置了新的 translateVector 后更新点的坐标并存储 以加上 translateVector 的方式
void SBMEGridPoints::UpdatePointsCoordinateByAddTranslateVector(void)
{
    double tmp[3];
    for (int i = 0; i != GetVerticesNum(); i++)
    {
        GetPoint(i, tmp);
        for (int l = 0; l != 3; l++)
        {
            tmp[l] += (infoGridPoints + i)->translateVector[l];
        }
        SetPoint(i, tmp);
    }
}

// 该函数在每次设置了新的 translateVector 后更新点的坐标并存储 以直接设置成 translateVector 的方式
void SBMEGridPoints::UpdatePointsCoordinateBySetToTranslateVector(void)
{
    double tmp[3];
    for (int i = 0; i != GetVerticesNum(); i++)
    {
        for (int l = 0; l != 3; l++)
        {
            tmp[l] = (infoGridPoints + i)->translateVector[l];
        }
        SetPoint(i,tmp);
    }
}

// 该函数对象进行更新，调用 加上 translateVector 的方式
void SBMEGridPoints::UpdateByAddTranslateVector(void)
{
    UpdatePointsCoordinateByAddTranslateVector();
}

// 该函数对象进行更新，调用 直接设置成 translateVector 的方式
void SBMEGridPoints::UpdateBySetToTranslateVector(void)
{
    UpdatePointsCoordinateBySetToTranslateVector();
}

// 获取点周围邻域点的平均距离
double SBMEGridPoints::GetPointMeanDistance(const int pointnum)
{
    return (infoGridPoints + pointnum)->pointMeanDistance;
}

// 当更新点后可以调用，设置点周围邻域点的平均距离
void SBMEGridPoints::SetPointMeanDistance(void)
{
    double gridPointTmp[3]; //用于存放临时取出的网格点坐标
    double gridPointNeighborTmp[3]; //用于存放临时取出的网格点邻域网格点坐标
    for (int i = 0; i != GetVerticesNum(); i++)
    {
        (infoGridPoints + i)->pointMeanDistance = 0;
        for (int j = 0; j != (infoGridPoints + i)->numOfPointNeighbor; j++)
        {
            GetPoint(i, gridPointTmp);
            GetPoint((infoGridPoints + i)->positionIdOfPointNeighbor[j], gridPointNeighborTmp);
            (infoGridPoints + i)->pointMeanDistance += funDistance(gridPointTmp, gridPointNeighborTmp);
        }
        (infoGridPoints + i)->pointMeanDistance /= (infoGridPoints + i)->numOfPointNeighbor;
    }
}

// 求两个点之间的距离
double SBMEGridPoints::funDistance(double *pointOne, double *pointTwo, int dimension/* = 3*/)
{
    double sum = 0;
    for (int i = 0; i != dimension; i++)
    {
        sum += pow((*(pointOne + i) - *(pointTwo + i)), 2);
    }
    return sqrt(sum);
}

// 获取指定索引的三角形的三个坐标点的索引
void SBMEGridPoints::GetTrianglePoints(const int pointnum, int *pointvalue)
{
    //int tmp[3] = {0,0,0};
    ArrayValueAssignment(pointvalue, (infoGridTriangles + pointnum)->pointsIndex, 3);
}
