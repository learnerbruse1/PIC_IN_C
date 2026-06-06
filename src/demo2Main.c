#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <head.h>


int main(void){
    SetConsoleOutputCP(CP_UTF8);
    srand((unsigned)time(NULL));        //初始化随机种子

    int bb = 8;         //设置图像块大小
    int RR = 4;         //冗余因子，用于确定字典原子数量、
    int K = RR * bb * bb;   //计算字典中的原子数量
    //FILE * pathFormages = NULL;

    double sigma = 25;     //噪声标准差(范围为0-255)
    char pathFormagesn[60] = "";     //存储图像路径变量，空表示为从当前路径读取
    char imageName[34];             //要处理的图像名称
    puts("Enter the name of picture file[length < 30]:");
    s_gets(imageName,30);
    strcat(pathFormagesn, imageName);//拼接字符串为图像路径
    //strcat(pathFormagesn, ".jpg");
    // if((pathFormages = fopen(pathFormagesn, "rb")) == NULL){
    //     fprintf(stderr, "Can't open %s\n", pathFormagesn);
    //     return -1;
    // }
    //TODO           对图片进行提取
    int width,height,channels;
    unsigned char *image_read = stbi_load(pathFormagesn, &width, &height, &channels, 1);
    if (image_read == NULL){
        strcat(pathFormagesn, ".jpg");
        unsigned char *image_read = stbi_load(pathFormagesn, &width, &height, &channels, 1);
    }
    if (image_read == NULL){
        fprintf(stderr, "error in loading image %s", pathFormagesn);
        getchar();
        return -2;
    }
    const struct picture_info image = {   //存储读取图像的宽度，高度，通道数(const设置该数据为仅可读)
        .data = image_read,
        .width = width,
        .height = height,
        .channels = channels
    };

    printf("宽度: %d ,高度: %d, 原始通道数: %d\n",image.width, image.height, image.channels);


    // double** IMin0 = (double**)malloc(image.height * sizeof(double*));
    // for (int i = 0; i < image.channels; i++) {
    //     IMin0[i] = (double*)malloc(image.width * sizeof(double));
    //     for (int j = 0; j < image.width; j++) {
    //         // unsigned char 值直接转换为 double，范围保持 0~255
    //         IMin0[i][j] = (double)image_read[i * image.width + j];
    //     }
    // }

    double ** IMin0;
    pic_char_to_double(image_read, IMin0, &image);        //记得要释放动态内存

    
    //为图形添加噪声
    double ** IMin = (double **) malloc(image.height * sizeof(double*));
    for (int i = 0; i < image.height; i++){
        IMin[i] = (double *) malloc (image.width * sizeof(double));
        for (int j = 0; j < image.width; j++){
            IMin[i][j] = IMin0[i][j] + sigma * randn_box_muller();
        }
    }
    //denoiseImageKSVD(IMin,sigma,K,out,output);
    
    
    
    //     for (int i = 0; i < height; i++) {
    //     for (int j = 0; j < width; j++) {
    //         printf("%lf  ",IMin0[i][j]);
    //     }
    //     printf("\n");
    // }                正确




    // //将 double** IMin 转回一维 unsigned char 数组
    // unsigned char* out_data = (unsigned char*)malloc(width * height);
    // for (int i = 0; i < image.height; i++) {
    //     for (int j = 0; j < image.width; j++) {
    //         // 限制在 0~255 并取整（处理可能超出范围的值）
    //         double val = IMin[i][j];
    //         if (val < 0) val = 0;
    //         if (val > 255) val = 255;
    //         out_data[i * image.width + j] = (unsigned char)(val + 0.5); // 四舍五入
    //     }
    // }
    
    //将 double** IMin 转回一维 unsigned char 数组
    unsigned char *out_data;
    pic_double_to_char(IMin, out_data, &image);
    
    //保存为 JPG，质量（1~100）
    int quality = 99;
    if (stbi_write_jpg("Original_clean_image.jpg", image.width, image.height, 1, image_read, quality) == 0) {
        printf("Failed to save riginal_clean_image JPG\n");
    } else {
        printf("Saved Original_clean_image.jpg successfully\n");
    }
    if (stbi_write_jpg("Noisy_image.jpg", image.width, image.height, 1, out_data, quality) == 0) {
        printf("Failed to save Noisy_image JPG\n");
    } else {
        printf("Saved Noisy_image.jpg successfully\n");
    }

    getchar();
    stbi_image_free(image_read);
    return 0;
}