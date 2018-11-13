#ifndef SBMEPOINTS3D_H
#define SBMEPOINTS3D_H

#include <vector>
#include <iostream>
#include <cstdio>

using namespace std;

//定义可以存储点的坐标，编号以及（类型）的结构体
//struct pointInfo
//{
//	double pointCoordinate[3];
//	int pointNum;
//};

//template class __declspec(dllexport) std::vector<int>;
//template class __declspec(dllexport) std::vector<double>;
//template class __declspec(dllexport) std::vector<string>;

class __declspec(dllexport) SBMEPoints3D
{
public:
    SBMEPoints3D(void);
    ~SBMEPoints3D(void);

    // 读取指定的文件并存储数据
    bool LoadFile(const char *filename);
    // 查找指定参数 pointnum 的三维坐标点，并将坐标点数值存储在 pointvalue 指定的数组内
    // 返回输入的参数 pointnum
    int GetPoint(const int pointnum, double *pointvalue);
    // 查找指定参数 pointnum 的三维坐标点，并返回坐标点的地址引用
    double *GetPoint(const int pointnum);
    // 向数据结构中插入一个坐标点，插入在尾端
    // 返回当前点的编号
    int InsertPoint(const double *pointvalue);
    // 返回当前数据内点的数目
    int GetPointsNum(void);
    // 删除数据中尾端的数据，包括坐标点以及编号
    int DeletePoint(void);
    // 删除指定序号的数据，其它数据依次填补，当指定序号 = 有效数据点的数目时，删除最后一个数
    int DeletePoint(int pointnum);
    // 计算所有坐标点的中心坐标，并存储在 pointvalue 指定的数组内
    void GetCenter(double *pointvalue);
    // 计算所有坐标点的中心坐标，并存储在 pointvalue 指定的数组内
    //double *GetCenter(void);

private:
    // 存储总的有效点的数目
    int numPoints3DValidate;
    // 存储总的输入点的编号的最大值,也即总共输入了多少次，包括最开始从文件
    // 读取的次数以及之后插入点的次数
    int numPoints3DIndex;
    // 存储每一个输入点的坐标
    vector<double> pointsDataCoordinateVec;
    //存储每一个输入点的编号
    vector<int> pointsDataIndexVec;
    //存储每一个输入点的类型
    vector<string> pointsDataTypeVec;
    // 工具函数
    // 数组赋值，直接将一个数组的 n 个值赋给另一个数组
    template<class T>
    void ArrayValueAssignment(T *arrOne, const T *arrTwo, const int arrDimension);
};

#endif // SBMEPOINTS3D_H
