//将线性索引idx位置转化为相应二维函数位置
//仿照matlab设置为列优先，但数组下标依然是以0开始(c标准)
#include "head.h"
void ind2sub(int rows, int cols, int idx, int *row, int *col) {
    // idx is 1-based column-major linear index
    int total = rows * cols;
    if (idx < 0 || idx >= total) {
        fprintf(stderr,"索引无效");   // 索引无效
        exit(1);
    }
    int zero_based = idx;
    *row = zero_based % rows;
    *col = zero_based / rows;
}