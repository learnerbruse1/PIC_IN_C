// #include <stdlib.h>
// #include <time.h>

// /**
//  * 生成一个 [1, n] 的随机排列
//  * @*param n  排列的长度（n >= 1）
//  * @*return   指向动态分配的整型数组的指针，包含 n 个整数的随机排列
//  *           调用者必须使用 free() 释放内存
//  */
// int* randperm(int n) {
//     if (n <= 0) return NULL;

//     // 1. 分配数组并填充 1..n
//     int* arr = (int*)malloc(n * sizeof(int));
//     if (arr == NULL) return NULL;  // 分配失败

//     for (int i = 0; i < n; i++) {
//         arr[i] = i + 1;   // 注意：MATLAB 索引从 1 开始，C 从 0 开始，但返回值仍是 1..n
//     }

//     // 2. Fisher-Yates 洗牌
//     // 使用当前时间初始化随机数种子（保证每次运行结果不同）
//     srand((unsigned int)time(NULL));

//     for (int i = n - 1; i > 0; i--) {
//         // 生成 [0, i] 内的随机整数
//         int j = rand() % (i + 1);
//         // 交换 arr[i] 和 arr[j]
//         int temp = arr[i];
//         arr[i] = arr[j];
//         arr[j] = temp;
//     }

//     return arr;
// }