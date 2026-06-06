#include <stdbool.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "stb_image.h"
#include "stb_image_write.h"


//存储图像信息
struct picture_info{            
    unsigned char* data;        // 像素数据指针
    int width;                  // 图像宽度
    int height;                 // 图像高度
    int channels;               // 颜色通道数 (3: RGB, 4: RGBA, 1: 灰度)
};

 struct Iout{

};
// struct output{

// };


char * s_gets(char * st, int n);    //处理字符串的输入，st为字符串指针，n为字符串长度
double gaussian_rand();

//KSVD 图像的去噪算法
//struct picture_info *image 传入含有图像信息的结构体指针
void denoiseImageKSVD(unsigned char *image_read,double sigma,int k,struct Iout *Iout, struct picture_info *image);
  
//将使用std_image读取的image图像从 unsigned char* 转换为 double** 类型
//imageA传入图像数据指针，imageB只需传入空指针，结果存入imageB
//struct picture_info *image 传入含有图像信息的结构体指针
void pic_char_to_double(unsigned char *imageA, double **imageB, struct picture_info *image);

//将使用std_image读取的image图像从 double** 转换为 unsigned char* 类型
//imageA传入图像数据指针，imageB只需传入空指针，结果存入imageB
//struct picture_info *image 传入含有图像信息的指针
void pic_double_to_char(double **imageA, unsigned char *imageB, struct picture_info *image);

//返回一个由 1 到 N 的整数组成的随机排列(无重复)
//int* randperm(int n);

//创建二维矩阵(全零)
double ** zeros(int row, int col);    

//将线性索引idx位置转化为相应二维函数位置
//仿照matlab设置为列优先，但数组下标依然是以0开始(c标准)
void ind2sub(int rows, int cols, int idx, int *row, int *col);

void my_im2col(struct picture_info *image, int blkSize, int slidingDis, float *blocks, int *idx);

float *im2col(struct picture_info *image, int bb, int slidingDis);

float* extract_columns(const float* blocks, int rows, int original_cols,
                       int start_col, int end_col);