该项目为半成品，仅实现了对图片提取进行黑白的转换，添加噪声
入口文件为demo2Main.c

最终生效的文件仅为 src的 demo2Main, s_gets, char_and_double, to_randn，和include的head
deps文件中只有std生效

该程序只能处理jpeg图像
要处理的图片请放在exe程序相同文件下
输入图片名称时请注意英文大小写


用到的第三方库：
**std_image.h**:           `https://github.com/nothings/stb`
**std_image_write.h**:    `https://github.com/nothings/stb`




编译方法    (windows环境  需要c语言编译器和cmake)
在cmake所在目录 使用 cmake build (生成构建系统，结果保存在build文件下)
然后在cmake所在目录使用 cmake --build build (利用build文件的构建系统进行文件编译，结果保存在配置的test文件下)



