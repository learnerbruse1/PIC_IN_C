#include "head.h"
char * s_gets(char * st, int n){
    char * ret_val;
    char * find;

    ret_val = fgets(st, n, stdin);
    if (ret_val){
        find = strchr(st, '\n');        //查找换行符
        if (find)                       //如果地址不是NULL
            *find = '\0';               //在此处放置一个空字符
        else
            while (getchar() != '\n')
                continue;
    }
    return ret_val;
}

//该函数实现丢弃输入的换行符，并在读取数据后清空缓冲区