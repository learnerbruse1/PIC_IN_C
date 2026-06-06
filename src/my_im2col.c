#include "head.h"
my_im2col(struct picture_info *image, int blkSize, int slidingDis, float *blocks, int *idx){
    if (slidingDis == 1){
        blocks = im2col(image, blkSize, slidingDis);
        //idx = (int*)malloc(image -> height * image -> width * sizeof(int));
        int height_col = (image -> height - blkSize) / slidingDis + 1;
        int width_col = (image -> width - blkSize) / slidingDis + 1;
        int N = height_col * width_col;  // 滑动窗口的个数
        idx = (int *)malloc(N * sizeof(int));
        for (int i = 0; i < N; i++)
            idx[i] = i;
    }
}