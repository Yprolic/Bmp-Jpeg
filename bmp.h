#ifndef BMP_H

#include "Windows.h"
#include "stdio.h"
#include "string.h"
#include "malloc.h"

#define BMP_H
class Bmp{
public:
    unsigned char *pBmpBuf;//读入图像数据的指针
    int bmpWidth;//图像的宽
    int bmpHeight;//图像的高
    RGBQUAD *pColorTable;//颜色表指针
    int biBitCount;//图像类型，每像素位数
    int lineByte;
    bool readBmp(char *bmpName);
	bool setPixels();
	int size;
};

#endif // BMP_H
