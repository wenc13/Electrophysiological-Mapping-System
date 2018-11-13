#include "SBMEDeformModel.h"

SBMEDeformModel::SBMEDeformModel(void)
{

}

SBMEDeformModel::~SBMEDeformModel(void)
{

}

// 该函数用来设置该类中包含的SBMEGridPoints类的需要的分层数
void SBMEDeformModel::SetLayers(int layers)
{
    modelSurface.ReSetLayers(layers);
}

// 该函数用来设置该类中包含的SBMEGridPoints类的需要的半径
void SBMEDeformModel::SetRadius(double radius)
{
    modelSurface.ReSetRadius(radius);
}

// 读取指定的文件并将参数传递给对象
bool SBMEDeformModel::LoadFile(const char *filename)
{
    // 重新更新网格模型
    SetRadius(50);
    return inputPoints.LoadFile(filename);
}

// 该函数将SBMEGridPoints对象 校准到SBMEPoints3D对象的中心处，SBMEPoints3D对象的中心用一个数组表示
void SBMEDeformModel::AlignSurfaceModelToInputPoints(double *pointsCenter)
{
    int modelSurfaceNum = modelSurface.GetVerticesNum();
    double tmp[3];
    for (int i = 0; i != modelSurfaceNum; i++)
    {
        modelSurface.GetPoint(i, tmp);
        for (int j = 0; j != 3; j++)
        {
            *(tmp + j) += *(pointsCenter + j);
        }
        modelSurface.SetPoint(i, tmp);
    }
}

// 该函数对校准后的SBMEGridPoints对象 进行初始变形，围绕SBMEPoints3D对象
void SBMEDeformModel::FirstApproximateSurfaceModelToInputPoints(void)
{
    int inputPointsNum = inputPoints.GetPointsNum();
    int surfaceModelPointsNum = modelSurface.GetVerticesNum();

    // 1.对每个模型网格点计算出其与每个真实点的之间的向量，临时向量
    //double SurfaceToPointsVectorTmp[3] = {0};
    double pointVectorCoarse[3] = {0};
    // 2.定义每个模型网格点在粗调整阶段需要改变的向量值，临时向量
    double vectorTmp[3] = {0};
    double vectorSumTmp[3] = {0};
    // 3.定义一个能量系数k，k的取值范围为4-10，更小的范围可以取为6-8
    int energyFactor = 7;
    // 4.定义一个很小的量epsilon，其主要作用是使分母不为0，可以取为采样点（真实点）的采样精度
    double epsilon = 0.001;
    //定义一个总的控制系数scalarFactor，用于控制粗调整中网格点与采样点（真实点）的逼近程度
    //该系数越大，则在粗调整中网格点与采样点（真实点）越靠近，一般可以取为0.1-1，更小的范围可以取为0.5-0.9
    //此处直接取为0.79
    double scalarFactor = /*0.79*/0.79;

    double sumTmp = 0;
    double *deltaTmp = new double[inputPointsNum];
    double deltaVectorTmp[3] = {0};

    double test1[3], test2[3];

    /*********************************************************************************************

    此段代码为改进代码，来源于Progressive surface reconstruction for heart mapping procedure
    引入了λ——lambda，用来表示每个采样点附近的真实点密度
    需要定义的量：	lambdaVector[3] = {};用来表示每次求得的真实点与网格点之间的临时向量
                    lambdaTmp = 0;
                    lambda[5402] = {0};用来存放每次求得的lambda
                    lambdaMid = 0;用来存放计算的lambda中间值
                    lambdaRef = 0;用来存放计算的lambda参考值
                    lambdaFlag = 0;用来存放有多少个lambda大于lambdaRef
                    lambdaNorm = 1;用于存放归一化的lambda

    ***********************************************************************************************/
    double lambdaVector[3] = {};//用来表示每次求得的真实点与网格点之间的临时向量
    double lambdaTmp = 0;
    double *lambda = new double[surfaceModelPointsNum];//用来存放每次求得的lambda
    double lambdaMid = 0;//用来存放计算的lambda中间值
    double lambdaRef = 0;//用来存放计算的lambda参考值
    int lambdaFlag = 0;//用来存放有多少个lambda大于lambdaRef

    double lambdaNorm = 1;//用于存放归一化的lambda

    for (int i = 0; i < surfaceModelPointsNum; i++)
    {
        modelSurface.GetPoint(i, test1);
        lambdaTmp = 0;
        for (int j = 0;j < inputPointsNum; j++)
        {
            inputPoints.GetPoint(j,test2);

            lambdaVector[0] = test1[0] - test2[0];
            lambdaVector[1] = test1[1] - test2[1];
            lambdaVector[2] = test1[2] - test2[2];

            lambdaTmp += 1 / (pow(normOfVector(lambdaVector, 3), 2) + 1);
        }
        lambda[i] = 1 / lambdaTmp;
    }
    lambdaMid = (findMax(lambda, surfaceModelPointsNum) + findMin(lambda ,surfaceModelPointsNum)) / 2;
    for (int i = 0; i < surfaceModelPointsNum; i++)
    {
        if (lambda[i] - lambdaMid >= 0)
        {
            lambdaFlag++;
            lambdaRef += lambda[i];
        }
    }
    lambdaRef = lambdaRef / lambdaFlag;

    //改进代码 Progressive

    //double gridPointTmp[3]; //用于存放临时取出的网格点坐标
    //double gridPointNeighborTmp[3]; //用于存放临时取出的网格点邻域网格点坐标

    //double gridToGridDistanceTmp = 0; //用于存放网格点到网格点之间的临时距离

    //int numOfPointIn = 0; //用于记录包围在由指定半径组成的圆球内的真实点的个数
    //bool *numOfPointInFlag = new bool[inputPointsNum]; // 临时变量 用于记录对于每一个网格点来说哪些真实点包括在了上述指定半径组成的圆球内

    for (int j = 0; j != inputPointsNum; j++)
    {
        deltaTmp[j] = 0;
        for (int k = 0; k != inputPointsNum; k++)
        {
            inputPoints.GetPoint(j,test1);
            inputPoints.GetPoint(k,test2);

            for (int l = 0; l != 3; l++)
            {
                deltaVectorTmp[l] = test1[l] - test2[l];
            }

            deltaTmp[j] += 1 / (pow(normOfVector(deltaVectorTmp, 3), 2) + 1);
        }
        deltaTmp[j] = 1 / deltaTmp[j];
    }

    for (int i = 0; i != surfaceModelPointsNum; i++)
    {
        sumTmp = 0;

        for (int l = 0; l != 3; l++)
        {
            vectorTmp[l] = 0;
        }

        modelSurface.GetPoint(i, test2);
        for (int j = 0; j != inputPointsNum; j++)
        {
            inputPoints.GetPoint(j, test1);

            for (int l = 0; l != 3; l++)
            {
                pointVectorCoarse[l] = test1[l] - test2[l];
            }

            sumTmp += deltaTmp[j] * 1 / (pow(normOfVector(pointVectorCoarse), energyFactor) + epsilon);

            for (int l = 0; l != 3; l++)
            {
                vectorTmp[l] += deltaTmp[j] * pointVectorCoarse[l] / (pow(normOfVector(pointVectorCoarse), energyFactor) + epsilon);
            }
        }

        lambdaNorm = ((lambdaRef + 2 * lambda[i]) / (2 * lambdaRef + lambda[i]));

        for (int l = 0; l != 3; l++)
        {
            vectorSumTmp[l] = lambdaNorm * scalarFactor * vectorTmp[l] / sumTmp;
        }
        modelSurface.SetPointTransVector(i, vectorSumTmp);
    }
    modelSurface.UpdateByAddTranslateVector();

    delete [] deltaTmp;
    deltaTmp = NULL;
    delete [] lambda;
    lambda = NULL;
    //delete [] numOfPointInFlag;
    //numOfPointInFlag = NULL;
}

// 该函数对校准后并己完成初始变形的SBMEGridPoints对象 进行连续更新，在每次读取到一个有效点后更新
void SBMEDeformModel::ProgressiveApproximateSurfaceModelToInputPoint(void)
{
    int inputPointsNum = inputPoints.GetPointsNum();
    int surfaceModelPointsNum = modelSurface.GetVerticesNum();


    // 找到每个输入点在网格点上的最近点 === BEGIN ===
    double *pointDistance = new double[inputPointsNum];
    double *pointDistanceMin = new double[inputPointsNum];

    int *flag = new int[inputPointsNum];
    bool isExist;

    double test1[3];
    double test2[3];

    for (int i = 0; i != inputPointsNum; i++)
    {
        inputPoints.GetPoint(i,test1);
        pointDistanceMin[i] = 100;
        for (int j = 0; j != surfaceModelPointsNum; j++)
        {
            modelSurface.GetPoint(j,test2);
            pointDistance[i] = funDistance(test1, test2);
            isExist = false;

            if (pointDistance[i] <= pointDistanceMin[i])
            {
                for (int k = 0; k < i; k++)
                {
                    if (j == flag[k])
                    {
                        isExist = true;
                    }
                }
                if (!isExist)
                {
                    pointDistanceMin[i] = pointDistance[i];
                    flag[i] = j;
                }
            }
        }
    }
    // 找到每个输入点在网格点上的最近点 === END ===

    double pointOne[3], pointTwo[3];
    //矩阵的形式为 AX=b 现在需要求解X
    //首先需要构造 矩阵 A
    double **transMatrix;
    transMatrix = new double *[inputPointsNum + 4];
    for (int i = 0; i != inputPointsNum + 4; i++)
    {
        transMatrix[i] = new double[inputPointsNum + 4];
    }

    for (int i = 0; i != inputPointsNum; i++)
    {
        modelSurface.GetPoint(flag[i], pointOne);
        for (int j = 0; j != inputPointsNum; j++)
        {
            modelSurface.GetPoint(flag[j], pointTwo);
            transMatrix[i][j] = funDistance(pointOne, pointTwo);
        }
    }
    for (int j = 0; j != inputPointsNum; j++)
    {
        modelSurface.GetPoint(flag[j], pointTwo);
        transMatrix[j][inputPointsNum]     = 1;
        transMatrix[inputPointsNum][j]     = 1;
        transMatrix[j][inputPointsNum + 1] = pointTwo[0];
        transMatrix[inputPointsNum + 1][j] = pointTwo[0];
        transMatrix[j][inputPointsNum + 2] = pointTwo[1];
        transMatrix[inputPointsNum + 2][j] = pointTwo[1];
        transMatrix[j][inputPointsNum + 3] = pointTwo[2];
        transMatrix[inputPointsNum + 3][j] = pointTwo[2];
    }

    //然后构造 矩阵 b
    double **realPointsMatrix;
    realPointsMatrix = new double *[inputPointsNum + 4];
    for (int i = 0; i != inputPointsNum + 4; i++)
    {
        realPointsMatrix[i] = new double[3];
        for (int l = 0; l != 3; l++)
        {
            realPointsMatrix[i][l] = 0;
        }
    }
    for (int i = 0; i != inputPointsNum; i++)
    {
        inputPoints.GetPoint(i, pointOne);
        for (int j = 0; j < 3; j++)
        {
            realPointsMatrix[i][j] = pointOne[j];
        }
    }

    //接下来构造需要求解的 系数矩阵 X
    double **realCoffientMatrix;
    realCoffientMatrix = new double *[inputPointsNum + 4];
    for (int i = 0; i != inputPointsNum + 4; i++)
    {
        realCoffientMatrix[i] = new double[3];
        for (int l = 0; l != 3; l++)
        {
            realCoffientMatrix[i][l] = 0;
        }
    }

    //将矩阵A求逆
    inverseMatrix(transMatrix, inputPointsNum + 4);
    //inverseMatrix(&transMatrix[0][0],inputPointsNum + 4);

    //将求逆后的结果与真实点矩阵相乘  X=A^-1*b
    multiplyMatrix(transMatrix, realPointsMatrix, inputPointsNum + 4, inputPointsNum + 4, 3, realCoffientMatrix);
    //multiplyMatrix(&transMatrix[0][0],&realPointsMatrix[0][0],inputPointsNum + 4,inputPointsNum + 4,3,&realCoffientMatrix[0][0]);

    double pointTmp[3] = {0};
    for (int i = 0; i != surfaceModelPointsNum; i++)
    {
        modelSurface.GetPoint(i, pointOne);
        for (int j = 0; j != 3; j++)
        {
            pointTmp[j] = realCoffientMatrix[inputPointsNum][j]
                        + realCoffientMatrix[inputPointsNum+1][j] * pointOne[0]
                        + realCoffientMatrix[inputPointsNum+2][j] * pointOne[1]
                        + realCoffientMatrix[inputPointsNum+3][j] * pointOne[2];
            for (int k = 0; k != inputPointsNum; k++)
            {
                modelSurface.GetPoint(flag[k], pointTwo);
                pointTmp[j] += realCoffientMatrix[k][j] * sqrt(pow(pointOne[0] - pointTwo[0], 2)
                             + pow(pointOne[1] - pointTwo[1], 2)
                             + pow(pointOne[2] - pointTwo[2], 2));
            }
        }
        modelSurface.SetPointTransVector(i, pointTmp);
    }
    modelSurface.UpdateBySetToTranslateVector();

    delete [] pointDistance;
    pointDistance = NULL;
    delete [] pointDistanceMin;
    pointDistanceMin = NULL;
    delete [] flag;
    flag = NULL;

    for (int i = 0; i != inputPointsNum + 4; i++)
    {
        delete [] transMatrix[i];
        transMatrix[i] = NULL;
    }
    delete [] transMatrix;
    transMatrix = NULL;

    for (int i = 0; i != inputPointsNum + 4; i++)
    {
        delete [] realPointsMatrix[i];
        realPointsMatrix[i] = NULL;
    }
    delete [] realPointsMatrix;
    realPointsMatrix = NULL;

    for (int i = 0; i != inputPointsNum + 4; i++)
    {
        delete [] realCoffientMatrix[i];
        realCoffientMatrix[i] = NULL;
    }
    delete [] realCoffientMatrix;
    realCoffientMatrix = NULL;
}

// 向数据结构中插入一个坐标点，插入在尾端
// 返回当前点的编号
int SBMEDeformModel::InsertPoint(const double *pointvalue)
{
    int pointNum = inputPoints.InsertPoint(pointvalue);
    if (pointNum > 3 )
    {
        if (pointNum == 4)
        {
            StartApproximation();
        }
        else
        {
            ProgressiveApproximation();
        }
    }
    //ProgressiveApproximation();
    return pointNum;

}

// 向数据结构中插入一个坐标点，插入在尾端，以三个double型数据的方式插入
// 返回当前点的编号
int SBMEDeformModel::InsertPoint(const double valueA, const double valueB, const double valueC)
{
    double tmp[3] = {valueA, valueB, valueC};
    int pointNum = inputPoints.InsertPoint(tmp);
    if (pointNum > 3)
    {
        if (pointNum == 4)
        {
            StartApproximation();
        }
        else
        {
            ProgressiveApproximation();
        }
    }
    return pointNum;
}

// 该函数在读取指定文件（如果需要），或者读入多个点
// 并且己经指定网格的参数（半径和分层数）后
// 对网格进行变形
void SBMEDeformModel::StartApproximation(void)
{
    // 重要 IMPORTANT
    // 关于输入点集的中心，应该将所有的网格点移至其包围盒的中心
    // 而不是所有的输入点的几何中心

    // 考虑一种极端情况：假设采集的点分为两部分，这两部分分别比较集中，但距离差较远
    // 其中一部分只拥有极少的点，而另一冲分的点较多，且集中在一定的范围，但此范围比两部分点之间的距离小很多
    // 此时如果将网格点移至几何中心，则可能偏向于点较多的部分，而未覆盖到点较少的部分
    // 这样会造成结果不正确
    double inputPointsCenter[3];
    inputPoints.GetCenter(inputPointsCenter);
    // 错误 ERROR
    // 直接引用 AlignSurfaceModelToInputPoints(inputPoints.GetCenter);
    // 而没有一个间接的数组来存储返回的地址会导致错误
    AlignSurfaceModelToInputPoints(inputPointsCenter);
    FirstApproximateSurfaceModelToInputPoints();
    ProgressiveApproximateSurfaceModelToInputPoint();
}

// 该函数在读取指定文件（如果需要），或者读入多个点
// 并且己经指定网格的参数（半径和分层数）后
// 但对当前的形变结果不是很满意，则调用些函数
// 对网格进行变形
void SBMEDeformModel::ReStartApproximation(void)
{
    SetRadius(50);
    double inputPointsCenter[3];
    inputPoints.GetCenter(inputPointsCenter);
    AlignSurfaceModelToInputPoints(inputPointsCenter);
    FirstApproximateSurfaceModelToInputPoints();
    ProgressiveApproximateSurfaceModelToInputPoint();
}

// 该函数在每次加入新的采集点后
// 对网格进行变形
void SBMEDeformModel::ProgressiveApproximation(void)
{
    ProgressiveApproximateSurfaceModelToInputPoint();
}

// 该函数获取SBMEGridPoints的点数
int SBMEDeformModel::GetGridPointsNum(void)
{
    return modelSurface.GetVerticesNum();
}

// 该函数获取SBMEPoints3D的点数
int SBMEDeformModel::GetPoints3DNum(void)
{
    return inputPoints.GetPointsNum();
}

// 该函数获取SBMEGridPoints的某个特定点 pointnum
double *SBMEDeformModel::GetGridPointsPoint(const int pointnum)
{
    return modelSurface.GetPoint(pointnum);
}

// 该函数获取SBMEPoints3D的某个特定点 pointnum
double *SBMEDeformModel::GetPoints3DPoint(const int pointnum)
{
    return inputPoints.GetPoint(pointnum);
}

// 返回一个指针所指数组对象的模
double SBMEDeformModel::normOfVector(const double *vector, int dimension/* = 3*/)
{
    double sum = 0;
    for (int i = 0; i != dimension; i++)
    {
        sum += pow(*(vector + i), 2);
    }
    return sqrt(sum);
}

//求一个数组中的最大值
double SBMEDeformModel::findMax(const double *a, int size)
{
    double maxVal = *a;
    for (int i = 1; i < size; i++)
    {
        if (*(a + i) > maxVal)
        {
            maxVal = *(a + i);
        }
    }
    return maxVal;
}

//求一个数组中的最小值
double SBMEDeformModel::findMin(const double *a, int size)
{
    double minVal = *a;
    for (int i = 1; i < size; i++)
    {
        if (*(a + i) < minVal)
        {
            minVal = *(a + i);
        }
    }
    return minVal;
}

// 工具函数
// 求两个点之间的距离
double SBMEDeformModel::funDistance(double *pointOne, double *pointTwo, int dimension)
{
    return sqrt((pointOne[0] - pointTwo[0]) * (pointOne[0] - pointTwo[0])
              + (pointOne[1] - pointTwo[1]) * (pointOne[1] - pointTwo[1])
              + (pointOne[2] - pointTwo[2]) * (pointOne[2] - pointTwo[2]));
}

// 获取当前中心点
void SBMEDeformModel::GetCenter(double *pointCenter)
{
    inputPoints.GetCenter(pointCenter);
}

// 获取三角形总数
int SBMEDeformModel::GetTriangleNum(void)
{
    return modelSurface.GetTrianglesNum();
}

// 获取指定索引的三角形的三个坐标点的索引
void SBMEDeformModel::GetTrianglePointIndex(const int triangleIndex, int *pointsIndex)
{
    modelSurface.GetTrianglePoints(triangleIndex, pointsIndex);
}
