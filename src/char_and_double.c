#include "head.h"
//将image图像在unsigned char* 和 double**类型之间转换
//使用的std_image项目只能处理unsigned char*类型

//将使用std_image读取的image图像从 unsigned char* 转换为 double** 类型
void pic_char_to_double(unsigned char *imageA, double **imageB, struct picture_info *image){
    double** imageB = (double**)malloc(image -> height * sizeof(double*));
    for (int i = 0; i < image -> channels; i++) {
        imageB[i] = (double*)malloc(image -> width * sizeof(double));
        for (int j = 0; j < image -> width; j++) {
            // unsigned char 值直接转换为 double，范围保持 0~255
            imageB[i][j] = (double)imageA[i * image -> width + j];
        }
    }
}

//将使用std_image读取的image图像从 double** 转换为 unsigned char* 类型
void pic_double_to_char(double **imageA, unsigned char *imageB, struct picture_info *image){
    imageB = (unsigned char*)malloc(image -> width * image -> height);
    for (int i = 0; i < image -> height; i++) {
        for (int j = 0; j < image -> width; j++) {
            // 限制在 0~255 并取整（处理可能超出范围的值）
            double val = imageA[i][j];
            if (val < 0) val = 0;
            if (val > 255) val = 255;
            imageB[i * image -> width + j] = (unsigned char)(val + 0.5); // 四舍五入
        }
    }
}