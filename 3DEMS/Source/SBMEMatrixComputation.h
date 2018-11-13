#ifndef SBMEMATRIXCOMPUTATION_H
#define SBMEMATRIXCOMPUTATION_H

#include <cmath>

//计算行列式，参数一为存储行列式的数组，参数二为阶数
double calculateDeterminant(double *p, int n);
// 使用Gauss-Jordan消去法求n阶实矩阵的逆矩阵
// 返回结果存放在a中，n是矩阵的阶数
int inverseMatrix(double **a, int n);
// 矩阵相乘// 矩阵a[m*n]乘以矩阵b[n*k]，得到矩阵c[m*k]
// 矩阵c[m*k]为返回结果
void multiplyMatrix(double **a, double **b, int m, int n, int k, double **c);

#endif // SBMEMATRIXCOMPUTATION_H
