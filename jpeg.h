#ifndef JPEG_H

#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <stdlib.h>
#include <string>
#include "mathUtil.h" 

#define JPEG_H
#define PI 3.1415927
#define widthbytes(i) ((i+31)/32*4)//表示BMP图像每一行的字节数，不够的四个字节的要补齐
const int Z[8][8] = { { 0, 1, 5, 6, 14, 15, 27, 28 }, { 2, 4, 7, 13, 16, 26, 29, 42 },
{ 3, 8, 12, 17, 25, 30, 41, 43 }, { 9, 11, 18, 24, 31, 40, 44, 53 },
{ 10, 19, 23, 32, 39, 45, 52, 54 }, { 20, 22, 33, 38, 46, 51, 55, 60 },
{ 21, 34, 37, 47, 50, 56, 59, 61 }, { 35, 36, 48, 49, 57, 58, 62, 63 } };
const unsigned char And[9] = { 0, 1, 3, 7, 0xf, 0x1f, 0x3f, 0x7f, 0xff };



class Jpeg{

	int sampleYH, sampleYV, sampleUH, sampleUV, sampleVH, sampleVV;
	int HYtoU, VYtoU, HYtoV, VYtoV, YinMCU, UinMCU, VinMCU;
	int compressnum = 0;//图像分量的个数
	int Qt[3][64];//存贮DCT量化表，一般情况下只有两个表
	int *YQt, *UQt, *VQt;//指向各图像分量所用的量化表
	int codepos[4][16];//长度为j的第一个码所在的行(即对应的codevalue的值，行值从0开始)
	int codelen[4][16];//codelen表示每个长度的码对应的个数
	unsigned char YDCindex, YACindex, UVDCindex, UVACindex;
	unsigned char compressindex[3];//表示第几个图像分量的标号
	unsigned char HufTabindex;//表示第几个huf表
	unsigned int codevalue[4][256];//codevalue[4][j]=(Z,R)连零数加行号
	unsigned int hufmin[4][16];//hufmin[4][j]表示j+1长度的码的开始码（码是用int值表示的）
	unsigned int hufmax[4][16];//表示j长度的码的结束码（码是用int值表示的）                                       
	int bitpos = 0, curbyte = 0, run = 0, value = 0, MCUbuffer[10 * 64], blockbuffer[64];
	//blockbuffer[64]存贮一个块
	//value表示每个码解出来的值，如果是第一个码则表示直流分量差分后的值，
	//value在DecodeMCUBlock（）还要相加才能得到真正的直流系数
	//run表示每个交流系数之前连0的个数
	int tempp = 0; //表示读取huf表时所读的长度，用来判断表是否结束
	//
	int intervalflag = 0, interval = 0, restart = 0;
	//restart=Ri（DRI段中的最后两个字节Ri）两个字节表示一个SCAN中每个
	//MCU-Segment里面包含的MCU的个数，两个segment之间是RST标志字，RST=0（从0—7循环）
	//interval表示每个segment中循环到了第几个MCU（interval=0-Ri）
	//intervalflag=0表示一个segment中MCU循环到最后结束，第二个segment即将开始
	int ycoef = 0, ucoef = 0, vcoef = 0;//coef是每个块的第一个系数，表示每个块的直流分量
	long Y[4 * 64], U[4 * 64], V[4 * 64], QtZMCUbuffer[10 * 64];//QtZMCUbuffer表示反量化后存贮MCU的数组
	unsigned long  width = 0, height = 0, linebytes;
	
	

	
	void error(std::string s);
	void makeRGB888();
	void initialize(FILE *fp);
	void savebmp();
	unsigned char readbyte(FILE *fp);
	int DecodeElement(FILE *fp);
	int HufBlock(FILE *fp, unsigned char dchufindex, unsigned char achufindex);
	int DecodeMCUBlock(FILE *fp);
	void IQtZBlock(int *s, long*d, int *pQt, int correct);
	void IQtZMCU(int xx, int yy, int offset, int *pQt, int correct);
	void getYUV(int xx, int yy, long *buf, int offset);
	void decode(FILE *fp1);

public:
	Jpeg(char* filename);
	unsigned char *buffer;
	unsigned long imgwidth = 0, imgheight = 0;

};

#endif // JPEG_H
