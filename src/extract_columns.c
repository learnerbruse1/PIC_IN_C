//对应matlab代码的blocks(:,jj:jumpSize)


#include <stdlib.h>
#include <string.h>

/**
 * 提取矩阵 blocks 的指定列范围（所有行）
 * 
 * @param blocks       原矩阵（行主序）
 * @param rows         总行数
 * @param original_cols 原矩阵的总列数
 * @param start_col    起始列（0‑based，包含）
 * @param end_col      结束列（0‑based，包含）
 * @return             新分配的矩阵（行主序），调用者负责 free
 */
float* extract_columns(const float* blocks, int rows, int original_cols,
                       int start_col, int end_col) {
    if (start_col < 0 || end_col >= original_cols || start_col > end_col)
        return NULL;  // 参数无效

    int new_cols = end_col - start_col + 1;
    float* sub = (float*)malloc(rows * new_cols * sizeof(float));
    if (!sub) return NULL;

    // 逐行拷贝需要的列
    for (int i = 0; i < rows; ++i) {
        const float* src_row = blocks + i * original_cols;  // 源行起始地址
        float* dst_row = sub + i * new_cols;               // 目标行起始地址
        // 拷贝从 start_col 到 end_col 的连续数据
        memcpy(dst_row, src_row + start_col, new_cols * sizeof(float));
    }
    return sub;
}