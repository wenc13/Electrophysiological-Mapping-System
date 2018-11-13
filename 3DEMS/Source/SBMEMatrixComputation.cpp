#include "SBMEMatrixComputation.h"
// 修改了一下，使之适用于不连续的矩阵

//计算行列式，参数一为存储行列式的数组，参数二为阶数
double calculateDeterminant(double *p, int n)
{
    if (n < 1)
    {
        return -1;
    }
    //若行列式阶数为1，则返回其内的唯一元素值
    if (n == 1)
    {
        return *p;
    }

    //定义临时指针变量指向当前行列式余子式数组
    double *curr = new double[(n - 1) * (n - 1)];
    double result = 0;
    int i, r, c, cc;

    for (i = 1; i <= n; ++i)
    {
        for (r = 2; r <= n; ++r)
        {
            cc = -1;
            for (c = 1; c <= n; ++c)
            {
                if (c != i)
                {
                    *(curr + (r - 2) * (n - 1) + (++cc)) = *(p + (r - 1) * n + (c - 1));
                }
            }
        }
        //计算求代数余子式之和，使用递归调用计算其余子式的值
        result += *(p + i - 1) * pow(double(-1), 1 + i) * calculateDeterminant(curr, n - 1);
    }
    //释放存储临时变量所占空间
    delete [] curr;
    return result;
}

// 使用Gauss-Jordan消去法求n阶实矩阵的逆矩阵
// 返回结果存放在a中，n是矩阵的阶数
int inverseMatrix(double **a, int n)
{
    int *is, *js;
    int i, j, k;
    double d, p;

    is = new int[n];
    js = new int[n];

    // 判断矩阵的的行列式是否为0，
    // 如果为0，则说明没有逆矩阵
    // 否则有逆矩阵
    double *q = new double[n * n];
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            q[i * n + j] = a[i][j];
        }
    }
    //if(calculateDeterminant(q, n) == 0)
    //{
    //	// printf("This matrix does not have inverse matrix...");
    //	return 0;
    //}
    delete [] q;

    //开始计算逆矩阵
    for (k = 0; k <= n - 1; k++)
    {
        d = 0.0;
        for (i = k; i <= n - 1; i++)
        {
            for (j = k; j <= n - 1; j++)
            {
                //l = i * n + j;
                p = fabs(a[i][j]);
                if (p > d)
                {
                    d = p;
                    is[k] = i;
                    js[k] = j;
                }
            }
        }
        if (is[k] != k)
        {
            for (j = 0; j <= n - 1; j++)
            {
                //u = k * n + j;
                //v = is[k] * n + j;
                p = a[k][j];
                a[k][j] = a[is[k]][j];
                a[is[k]][j] = p;
            }
        }
        if (js[k] != k)
        {
            for (i = 0; i <= n - 1; i++)
            {
                //u = i * n + k;
                //v = i * n + js[k];
                p = a[i][k];
                a[i][k] = a[i][js[k]];
                a[i][js[k]] = p;
            }
        }
        //l = k * n + k;
        a[k][k] = 1.0 / a[k][k];
        for (j = 0; j <= n - 1; j++)
        {
            if (j != k)
            {
                //u = k * n + j;
                a[k][j] = a[k][j] * a[k][k];
            }
        }
        for (i = 0; i <= n - 1; i++)
        {
            if (i != k)
            {
                for (j = 0; j <= n - 1; j++)
                {
                    if (j != k)
                    {
                        //u = i * n + j;
                        a[i][j] = a[i][j] - a[i][k] * a[k][j];
                    }
                }
            }
        }
        for (i = 0; i <= n - 1; i++)
        {
            if (i != k)
            {
                //u = i * n + k;
                a[i][k] = -a[i][k] * a[k][k];
            }
        }
    }
    for (k = n - 1; k >= 0; k--)
    {
        if (js[k] != k)
        {
            for (j = 0; j <= n - 1; j++)
            {
                //u = k * n + j;
                //v = js[k] * n + j;
                p = a[k][j];
                a[k][j] = a[js[k]][j];
                a[js[k]][j] = p;
            }
        }
        if (is[k] != k)
        {
            for (i = 0; i <= n - 1; i++)
            {
                //u = i * n + k;
                //v = i * n + is[k];
                p = a[i][k];
                a[i][k] = a[i][is[k]];
                a[i][is[k]] = p;
            }
        }
    }
    delete [] is;
    delete [] js;
    return 1;
}

// 矩阵相乘
// 矩阵a[m*n]乘以矩阵b[n*k]，得到矩阵c[m*k]
// 矩阵c[m*k]为返回结果
void multiplyMatrix(double **a, double **b, int m, int n, int k, double **c)
{
    int i, j, l;
    for (i = 0; i <= m - 1; i++)
    {
        for (j = 0; j <= k - 1; j++)
        {
            //u = i * k + j;
            c[i][j] = 0.0;
            for (l = 0; l <= n - 1; l++)
            {
                c[i][j] = c[i][j] + a[i][l] * b[l][j];
            }
        }
    }
    return;
}
