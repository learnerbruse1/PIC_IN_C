/**
 * 将stb_image加载的交错格式图像转换为Darknet所需的平面格式。
 *
 * @*param img_data      stb_image加载的原始数据 (unsigned char*)
 * @*param channels      图像通道数 (例如: 3)
 * @*param height        图像高度
 * @*param width         图像宽度
 * @*param out_data      预分配的用于存放结果数据的数组 (float*)。
 *                      其大小应为 channels * height * width。结果将按平面格式存储。
 */

#include "head.h"
void stb_to_darknet_format(unsigned char* img_data, int channels, int height, int width, float* out_data) {
    for (int c = 0; c < channels; ++c) {
        for (int h = 0; h < height; ++h) {
            for (int w = 0; w < width; ++w) {
                // 计算在 stb_image 交错存储中的索引: (h * width + w) * channels + c
                int stb_index = (h * width + w) * channels + c;
                // 计算在 Darknet 平面存储中的索引
                int darknet_index = c * height * width + h * width + w;
                // 转换：类型转换为float，并归一化到 [0,1] 范围
                out_data[darknet_index] = (float)img_data[stb_index] / 255.0f;
            }
        }
    }
}

float *im2col(struct picture_info *image, int bb, int slidingDis){
    //准备 Darknet 格式的数据缓冲区
    int input_size = image -> channels * image -> height * image -> width;
    float *darknet_img = (float*)malloc(input_size * sizeof(float));
    if (darknet_img == NULL)
        printf("Memory allocation failed\n");
    //转换格式
    stb_to_darknet_format(image -> data, image -> channels, image -> height, image -> width, darknet_img);
    //设置 im2col_cpu 参数
    int ksize = bb;
    int stride = slidingDis;
    int pad = 0;

    // 计算输出矩阵大小
    int height_col = (image -> height + 2*pad - ksize) / stride + 1;
    int width_col = (image -> width + 2*pad - ksize) / stride + 1;
    int channels_col = image -> channels * ksize * ksize;
    int output_size = channels_col * height_col * width_col;

    // 为 im2col 结果分配内存
    float *data_col = (float*)malloc(output_size * sizeof(float));
    if (data_col == NULL) {
        printf("Memory allocation for data_col failed\n");
        free(darknet_img);
        return -1;
    }
    
    //调用 im2col_cpu
    im2col_cpu(darknet_img, image -> channels, image -> height, image -> width, ksize, stride, pad, data_col);
    return data_col;
}