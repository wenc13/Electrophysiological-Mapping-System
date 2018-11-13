#ifndef SBMEDEFORMMODEL_H
#define SBMEDEFORMMODEL_H

#include "SBMEPoints3D.h"
#include "SBMEGridPoints.h"
#include "SBMEMatrixComputation.h"

//class SBMEGridPoints;
//class SBMEPoints3D;
//#pragma comment(lib, "DeformModel.lib")

class __declspec(dllexport) SBMEDeformModel
{
public:
    SBMEDeformModel(void);
    ~SBMEDeformModel(void);

    // 该函数用来设置该类中包含的SBMEGridPoints类的需要的分层数
    void SetLayers(int layers);
    // 该函数用来设置该类中包含的SBMEGridPoints类的需要的半径
    void SetRadius(double radius);
    // 读取指定的文件并将参数传递给对象
    bool LoadFile(const char *filename);
    // 向数据结构中插入一个坐标点，插入在尾端
    // 返回当前点的编号
    int InsertPoint(const double *pointvalue);
    // 向数据结构中插入一个坐标点，插入在尾端，以三个double型数据的方式插入
    // 返回当前点的编号
    int InsertPoint(const double valueA, const double valueB, const double valueC);
    // 该函数在读取指定文件（如果需要），或者读入多个点
    // 并且己经指定网格的参数（半径和分层数）后
    // 对网格进行变形
    void StartApproximation(void);
    // 该函数在读取指定文件（如果需要），或者读入多个点
    // 并且己经指定网格的参数（半径和分层数）后
    // 但对当前的形变结果不是很满意，则调用些函数
    // 对网格进行变形
    void ReStartApproximation(void);
    // 该函数获取SBMEGridPoints的点数
    int GetGridPointsNum(void);
    // 该函数获取SBMEPoints3D的点数
    int GetPoints3DNum(void);
    // 该函数获取SBMEGridPoints的某个特定点 pointnum
    double *GetGridPointsPoint(const int pointnum);
    // 该函数获取SBMEPoints3D的某个特定点 pointnum
    double *GetPoints3DPoint(const int pointnum);
    // 获取当前中心点
    void GetCenter(double *pointCenter);
    // 获取三角形总数
    int GetTriangleNum(void);
    // 获取指定索引的三角形的三个坐标点的索引
    void GetTrianglePointIndex(const int triangleIndex, int *pointsIndex);

private:
    SBMEGridPoints modelSurface;
    SBMEPoints3D inputPoints;

    // 该函数将SBMEGridPoints对象 校准到SBMEPoints3D对象的中心处，SBMEPoints3D对象的中心用一个数组表示
    void AlignSurfaceModelToInputPoints(double *pointsCenter);
    // 该函数对校准后的SBMEGridPoints对象 进行初始变形，围绕SBMEPoints3D对象
    void FirstApproximateSurfaceModelToInputPoints(void);
    // 该函数对校准后并己完成初始变形的SBMEGridPoints对象 进行连续更新，在每次读取到一个有效点后更新
    void ProgressiveApproximateSurfaceModelToInputPoint(void);
    // 工具函数
    // 返回一个指针所指数组对象的模
    double normOfVector(const double *vector, int dimension = 3);
    // 工具函数
    // 求一个数组中的最大值
    double findMax(const double *a, int size);
    // 工具函数
    // 求一个数组中的最小值
    double findMin(const double *a, int size);
    // 工具函数
    // 求两个点之间的距离
    double funDistance(double *pointOne, double *pointTwo, int dimension = 3);
    // 该函数在每次加入新的采集点后
    // 对网格进行变形
    void ProgressiveApproximation(void);
};

#endif // SBMEDEFORMMODEL_H
