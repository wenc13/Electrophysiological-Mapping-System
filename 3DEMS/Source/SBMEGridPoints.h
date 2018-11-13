#ifndef SBMEGRIDPOINTS_H
#define SBMEGRIDPOINTS_H

#include <iostream>
#include <cstdio>
#include <cmath>

#define PI 3.1415926
#define INVALIDATE_INT -999999

using namespace std;

typedef struct GridPointInfoStruct
{
    int numOfPointNeighbor;
    int positionIdOfPointNeighbor[6];
    int positionIdOfLineNeighbor[6][2];
    double positionOfPoint[3];
    double translateVector[3];
    double positionOfPointOriginal[3];
    double pointNeighborMeanDistance; //该参数暂时未使用，应该与pointMeadDistance的意思相同，以后如有必要替换名字
    double pointMeanDistance;  
} GridPointInfo;

typedef struct GridLineInfoStruct
{
    //int firstPointIndex;
    //int secondPointIndex;
    int pointsIndex[2];
}GridLineInfo;

typedef struct GridTriangleInfoStruct
{
    int pointsIndex[3];
}GridTriangleInfo;

class __declspec(dllexport) SBMEGridPoints
{
public:
    SBMEGridPoints(void);
    ~SBMEGridPoints(void);

    // 带半径和分层数的构造函数
    SBMEGridPoints(int layers, double radius);
    // 该函数对象进行更新，调用 加上 translateVector 的方式
    void UpdateByAddTranslateVector(void);
    // 该函数对象进行更新，调用 直接设置成 translateVector 的方式
    void UpdateBySetToTranslateVector(void);
    // 返回网格表面顶点的总数
    int GetVerticesNum(void);
    // 返回网格表面连线的总数
    int GetLinesNum(void);
    // 返回网格表面三角形的总数
    int GetTrianglesNum(void);
    // 重新设置半径
    void ReSetRadius(double para);
    // 重新设置分层数
    void ReSetLayers(int para);
    // 重新设置参数，包括半径和分层数
    void ReSetParameters(int layers, double radius);
    // 建立网格表面顶点的关系，比如邻域点数
    void CreatePointsRelation(void);
    // 返回一个指定 pointnum 的点的坐标，存储在数组指针 pointvalue 所指的数组对象中
    void GetPoint(const int pointnum, double *pointvalue);
    // 查找指定参数 pointnum 的三维坐标点，并返回坐标点的地址引用
    double *GetPoint(const int pointnum);
    // 设定一个指定 pointnum 的点的坐标，数组指针 pointvalue 作为输入
    void SetPoint(const int pointnum, const double *pointvalue);
    // 设定一个指定 pointnum 的点的位移向量，数组指针 pointvalue 作为输入
    void SetPointTransVector(const int pointnum, const double *pointvalue);
    // 获取点周围邻域点的平均距离
    double GetPointMeanDistance(const int pointnum);
    // 获取指定索引的三角形的三个坐标点的索引
    void GetTrianglePoints(const int pointnum, int *pointvalue);

private:
    // 定义网格模型所具有的顶点总数
    int numGridPoints3D;
    // 定义网格模型所具有的边的总数
    int numGridLines2D;
    // 定义网格模型所具有的三角形的总数
    int numGridTriangles3D;
    // 网格模型的分层数
    int m_iLayer;
    // 网格模型的初始半径
    double m_dRadius;
    // 定义存储每个网格顶点相关信息的结构体指针
    GridPointInfo *infoGridPoints;
    // 该函数在确定输入半径和分层数并对数据分配内存后计算点的坐标并存储
    void ComputePointsCoordinate(void);
    // 定义存储每条网格线的结构体指针
    GridLineInfo *infoGridLines;
    // 该函数在确定点的坐标后确定所有的点连线
    void ComputeLinesRelation(void);
    // 定义存储每个三角形结构体指针
    GridTriangleInfo *infoGridTriangles;
    // 该函数在确定点的坐标后确定所有三角形
    void ComputeTrianglesRelation(void);
    // 该函数在每次设置了新的 translateVector 后更新点的坐标并存储 以加上 translateVector 的方式
    void UpdatePointsCoordinateByAddTranslateVector(void);
    // 该函数在每次设置了新的 translateVector 后更新点的坐标并存储 以直接设置成 translateVector 的方式
    void UpdatePointsCoordinateBySetToTranslateVector(void);
    // 工具函数
    // 根据输入的两个角度和半径计算坐标 输入经度角：theta，纬度角：fai，返回给输入的数组引用
    void ComputeCoordinateByAngle(double theta, double fai, double radius, double *arrAddress);
    // 工具函数
    // 数组赋值，直接将一个数组的 n 个值赋给另一个数组
    template<class T>
    void ArrayValueAssignment(T *arrOne, const T *arrTwo, const int arrDimension);
    // 设置网格表面顶点的总数
    void SetVerticesNum(int para);
    // 设置网格表面连线的总数
    void SetLinesNum(int para);
    // 设置网格表面三角形的总数
    void SetTrianglesNum(int para);
    // 设置半径
    void SetRadius(double para);
    // 设置分层数
    void SetLayers(int para);
    // 利用传入的参数构建网格模型，包括表面点，点之间的拓扑关系，以及线和三角形的数据维护
    void ConstructGridModel(void);
    // 当更新点后可以调用，设置点周围邻域点的平均距离
    void SetPointMeanDistance(void);
    // 工具函数
    // 求两个点之间的距离
    double funDistance(double *pointOne, double *pointTwo, int dimension = 3);
};

#endif // SBMEGRIDPOINTS_H
