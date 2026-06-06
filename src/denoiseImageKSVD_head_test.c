// #include "head.h"

// //为保持图像计算时的高精度，所有图像数据在计算时均使用double类型
// void denoiseImageKSVD(unsigned char *image_read,double sigma,int k,struct Iout *Iout, struct output *output,struct picture_info *image){
//     int NN1 = image -> height;
//     int NN2 = image -> width;
//     int reduceDC = 1;   //是否去除块均值（DC分量）

//     int numIterOfKsvd;
//     if (sigma > 50)
//         numIterOfKsvd = 20;
//     else
//         numIterOfKsvd = 5;
//     double C = 1.15;    //容错因子，用于计算允许的重建误差
//     int maxBlocksToConsider = 260000;   //最大处理的块数（受内存限制）
//     int slidDis = 1;        //滑动步长，用于提取重叠块。若块数超过限制，会自动增大步长
//     int bb = 8;              //块大小（8×8）
//     int maxNumBlocksToTrainOn = 65000;   //训练字典时最多使用的样本块数
//     int displayFlag = 1;    //显示进度信息

//     //计算全图采用滑动步长为1时，能提取出的总块数（即 (高度-bb+1)*(宽度-bb+1)
//     //如果这个总块数 > maxNumBlocksToTrainOn，则说明全图所有块太多，内存放不下，需要随机采样部分块进行训练；否则（被注释掉的 else 分支）直接取全部块。
//     if( ((NN1 - bb + 1) * (NN2 - bb + 1)) > maxNumBlocksToTrainOn){
//         //返回一个由 1 到 N 的整数组成的随机排列（无重复）
//         int *randPermutation = randperm((NN1 - bb + 1) * (NN2 - bb + 1));

//         //取随机排列的前 maxNumBlocksToTrainOn 个索引，作为要选中的块的线性索引
//         int *selectedBlocks = (int *)malloc(maxNumBlocksToTrainOn * sizeof(int));
//         if (!selectedBlocks){
//             fprintf(stderr,"error in denoisemageKSVD: selectedBlocks create default");
//             return -1;
//         }
//         memcpy(selectedBlocks, randPermutation,maxNumBlocksToTrainOn  * sizeof(int));
//         double **blkMatrix = zeros(bb * bb, maxNumBlocksToTrainOn);
//         for(int i = 0; i < maxNumBlocksToTrainOn; i++){
//             //这里的矩阵仿照matlab按列优先来
//             int row, col;
//             ind2sub(, int cols, &selectedBlocks(i-1), &row, &col)
//         }
//     }

// }
