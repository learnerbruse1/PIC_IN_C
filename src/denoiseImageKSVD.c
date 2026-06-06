#include "head.h"
denoiseImageKSVD(unsigned char *image_read,double sigma,int k,struct Iout *Iout, struct picture_info *image){
    int NN1 = image -> height;
    int NN2 = image -> width;
    bool reduceDC = 1;      //布尔标志,用于指示是否需要减去每列的均值,即直流分量
    int bb = 8;              //块大小（8×8）
    int slidingDis = 1;      //滑动步长，用于提取重叠块。若块数超过限制，会自动增大步长
    int maxBlocksToConsider = 260000;   //最大处理的块数（受内存限制)

    double **Weight = zeros(NN1, NN2);
    double **IMout = zeros(NN1, NN2);

    //将线性索引idx位置转化为相应二维函数位置
    //仿照matlab设置为列优先，但数组下标依然是以0开始
    while ( (floor(((double)(NN1-bb))/(double)slidingDis) + (double)1)*(floor(((double)(NN2-bb))/slidingDis) + (double)1) > maxBlocksToConsider)
        slidingDis = slidingDis + 1;
    float *blocks;
    int *idx;
    my_im2col(image, 8, slidingDis, blocks, idx);
    int height_col = (image -> height  - bb) / slidingDis + 1;
    int width_col  = (image -> width   - bb) / slidingDis + 1;
    int col_count = height_col * width_col;   // 这就是输出矩阵的列数
    for (int jj = 0; jj < col_count; jj = jj + 30000){
        int jumpSize = min(jj + 30000 - 1, col_count-1);
    
        int rows = 1 * bb * bb;
        int cols = jumpSize - jj + 1;   //要处理的列数
        if(reduceDC){
            float *sub_data = extract_columns(blocks, rows, col_count, jj, jumpSize);
            /**
            * 计算子矩阵（行主序）的列均值
            * param sub_data  子矩阵，大小为 rows x cols
            * param rows      行数
            * param cols      列数
            * return          动态分配的 vecOfMeans 数组（长度 cols），调用者 free
            */
            // float* vecOfMeans = (float*)malloc(cols * sizeof(float));
            // for (int i = 0; i < rows; ++i) {
            //     const float* row = sub_data + i * cols;
            //     for (int j = 0; j < cols; ++j) {
            //         vecOfMeans[j] += row[j];
            //         vecOfMeans[j] /= rows;
            //     }
            // }


            //计算每列的均值（直接使用列优先数组）
            float *vecOfMeans = (float*)calloc(cols, sizeof(float));
            for (int c = 0; c < cols; ++c) {
                int col = jj + c;
                float sum = 0.0f;
                for (int r = 0; r < rows; ++r) {
                    sum += blocks[r + col * rows];
                }
                vecOfMeans[c] = sum / rows;
            }
            for (int c = 0; c < cols; ++c) {
                int col = jj + c;              // 列索引（0-index）
                float mean = vecOfMeans[c];    // 该列的均值
                for (int r = 0; r < rows; ++r) {
                    // 列优先：行索引 r + 列索引 col × 行数 N
                    blocks[r + col * rows] -= mean;
                }
            }
            free(vecOfMeans);
        }

    }
}