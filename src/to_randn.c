#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define M_PI 3.14159265358979323846

/* 生成一个均值为0，方差为1的随机数（Box-Muller） */
double randn_box_muller() {
    static int have_next = 0;
    static double next_gaussian;
    double u1, u2, r, z0, z1;

    if (have_next) {
        have_next = 0;
        return next_gaussian;
    }

    /* 生成两个 (0,1) 内的均匀随机数（避免 u1 为 0） */
    do {
        u1 = (double)rand() / (RAND_MAX + 1.0);
    } while (u1 == 0.0);
    u2 = (double)rand() / (RAND_MAX + 1.0);

    r = sqrt(-2.0 * log(u1));
    z0 = r * cos(2.0 * M_PI * u2);
    z1 = r * sin(2.0 * M_PI * u2);

    next_gaussian = z1;
    have_next = 1;
    return z0;
}

// /*
//  * 为整个图像矩阵添加高斯噪声
//  * img_clean : 原始图像，大小为 rows x cols，double 类型（假设值域 0-255）
//  * sigma     : 噪声标准差
//  * img_noisy : 输出带噪图像，大小同 img_clean
//  */
// void add_gaussian_noise(const double* img_clean, int rows, int cols,
//                         double sigma, double* img_noisy) {
//     int total = rows * cols;
//     for (int i = 0; i < total; i++) {
//         double noise = randn_box_muller();   // 标准正态 N(0,1)
//         img_noisy[i] = img_clean[i] + sigma * noise;
//     }
// }