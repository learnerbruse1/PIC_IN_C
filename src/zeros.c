#include "head.h"
double ** zeros(int row, int col){                                  //创建存储数据全为0的数组
    double ** arr = (double**) calloc(row , sizeof(double*)); //进行内存分配
    for(int i = 0; i < row; i++){
        arr[i] = (double*) calloc(col , sizeof(double));
    }
    return arr;
}