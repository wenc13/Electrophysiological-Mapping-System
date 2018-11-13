#include "SBMEPoints3D.h"

SBMEPoints3D::SBMEPoints3D(void)
    : numPoints3DValidate(0)
    , numPoints3DIndex(0)
{
}

SBMEPoints3D::~SBMEPoints3D(void)
{
}

// 读取指写的文件并存储数据
bool SBMEPoints3D::LoadFile(const char *filename)
// REMIND 提醒
// 处理文件的方法
// http://wenku.it168.com/d_000586304.shtml
{
    // 清空vector
    pointsDataCoordinateVec.clear();
    numPoints3DValidate = 0;
    numPoints3DIndex = 0;

    FILE *fp = NULL;
    fopen_s(&fp, filename, "r");
    if (NULL == fp)
        return false;
    else
    {
        double pointInputTmp[3] = {0, 0, 0};
        //pointInfo pointInfoTmp;
        while (!feof(fp))
        {
            int ret = fscanf_s(fp, "%lf,%lf,%lf\n", &pointInputTmp[0], &pointInputTmp[1], &pointInputTmp[2]);
            //int ret=fscanf(fp,"%lf,%lf,%lf\n",&pointInfoTmp.pointCoordinate[0],&pointInfoTmp.pointCoordinate[1],&pointInfoTmp.pointCoordinate[2]);
            //pointInputTmp[4] = static_cast<double>(numPoints3DValidate + 1);
            if (ret != 3)
                break;
            pointsDataIndexVec.push_back(numPoints3DValidate + 1);
            pointsDataCoordinateVec.push_back(pointInputTmp[0]);
            pointsDataCoordinateVec.push_back(pointInputTmp[1]);
            pointsDataCoordinateVec.push_back(pointInputTmp[2]);
            ++numPoints3DValidate;
            ++numPoints3DIndex;
        }
        fclose(fp);
        return true;
    }

}

// 查找指定参数 pointnum 的三维坐标点，并将坐标点数值存储在 pointvalue 指定的数组内
// 返回输入的参数 pointnum
int SBMEPoints3D::GetPoint(const int pointnum, double *pointvalue)
{
    vector<double>::size_type pointnumFind = pointnum/*(pointnum - 1)*/ * 3;
    *pointvalue = pointsDataCoordinateVec[pointnumFind];
    *(pointvalue + 1) = pointsDataCoordinateVec[pointnumFind + 1];
    *(pointvalue + 2) = pointsDataCoordinateVec[pointnumFind + 2];
    return pointnum;
}

// 查找指定参数 pointnum 的三维坐标点，并返回坐标点的地址引用
double *SBMEPoints3D::GetPoint(const int pointnum)
{
    vector<double>::size_type pointnumFind = pointnum/*(pointnum - 1)*/ * 3;
    return &pointsDataCoordinateVec[pointnumFind];
}

// 向数据结构中插入一个坐标点，插入在尾端
// 返回当前点的编号
int SBMEPoints3D::InsertPoint(const double *pointvalue)
{
    pointsDataIndexVec.push_back(numPoints3DIndex + 1);
    pointsDataCoordinateVec.push_back(*(pointvalue + 0));
    pointsDataCoordinateVec.push_back(*(pointvalue + 1));
    pointsDataCoordinateVec.push_back(*(pointvalue + 2));
    ++numPoints3DValidate;
    ++numPoints3DIndex;
    return GetPointsNum();
}

// 返回当前数据内点的数目
int SBMEPoints3D::GetPointsNum(void)
{
    return numPoints3DValidate;
}


// 删除数据中尾端的数据，包括坐标点以及编号
int SBMEPoints3D::DeletePoint(void)
{
    pointsDataIndexVec.pop_back();
    pointsDataCoordinateVec.pop_back();
    pointsDataCoordinateVec.pop_back();
    pointsDataCoordinateVec.pop_back();
    --numPoints3DValidate;
    return GetPointsNum();
}

// 删除指定序号的数据，其它数据依次填补，当指定序号 = 有效数据点的数目时，删除最后一个数
int SBMEPoints3D::DeletePoint(int pointnum)
{
    vector<int>::size_type pointnumFindInt = pointnum - 1;
    for ( ; pointnumFindInt != pointsDataIndexVec.size(); ++pointnumFindInt)
    {
        pointsDataIndexVec[pointnumFindInt] = pointsDataIndexVec[pointnumFindInt + 1];
    }
    vector<double>::size_type pointnumFindDouble = (pointnum - 1) * 3;
    for ( ; pointnumFindDouble != pointsDataCoordinateVec.size() - 3; ++pointnumFindDouble)
    {
        pointsDataIndexVec[pointnumFindDouble] = pointsDataIndexVec[pointnumFindDouble + 3];
    }
    return DeletePoint();
}

// 计算所有坐标点的中心坐标，并存储在 pointvalue 指定的数组内
void SBMEPoints3D::GetCenter(double *pointvalue)
{
    double sum[3] = {0, 0 ,0};
    for (vector<double>::iterator iter = pointsDataCoordinateVec.begin();
         iter != pointsDataCoordinateVec.end(); iter += 3)
    {
        for (int i = 0; i != 3; ++i)
        {
            sum[i] += *(iter + i);
        }
    }
    for (int i = 0; i != 3; ++i)
    {
        sum[i] /= (pointsDataCoordinateVec.size() / 3);
    }
    ArrayValueAssignment(pointvalue, sum, 3);
}

// 计算所有坐标点的中心坐标，并存储在 pointvalue 指定的数组内
//double *SBMEPoints3D::GetCenter(void)
//{
//	double sum[3] = {0,0,0};
//	for(vector<double>::iterator iter = pointsDataCoordinateVec.begin();
//		iter != pointsDataCoordinateVec.end(); iter += 3)
//	{
//		for(int i = 0; i != 3; ++i)
//		{
//			sum[i] += *(iter + i);
//		}
//	}
//	for(int i = 0; i != 3; ++i)
//	{
//		sum[i] /= (pointsDataCoordinateVec.size() / 3);
//	}
//
//	return sum;
//}

// 工具函数
// 数组赋值，直接将一个数组的 arrDimension 个值赋给另一个数组
template<class T>
void SBMEPoints3D::ArrayValueAssignment(T *arrOne, const T *arrTwo, const int arrDimension)
{
    for (int i = 0; i != arrDimension; i++)
    {
        *(arrOne + i) = *(arrTwo + i);
    }
}
