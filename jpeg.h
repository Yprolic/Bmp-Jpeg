#ifndef JPEG_H

#include <stdio.h>
#include <malloc.h>
#include <math.h>
#include <stdlib.h>
#include <string>
#include "mathUtil.h" 

#define JPEG_H
#define PI 3.1415927
#define widthbytes(i) ((i+31)/32*4)//��ʾBMPͼ��ÿһ�е��ֽ������������ĸ��ֽڵ�Ҫ����
const int Z[8][8] = { { 0, 1, 5, 6, 14, 15, 27, 28 }, { 2, 4, 7, 13, 16, 26, 29, 42 },
{ 3, 8, 12, 17, 25, 30, 41, 43 }, { 9, 11, 18, 24, 31, 40, 44, 53 },
{ 10, 19, 23, 32, 39, 45, 52, 54 }, { 20, 22, 33, 38, 46, 51, 55, 60 },
{ 21, 34, 37, 47, 50, 56, 59, 61 }, { 35, 36, 48, 49, 57, 58, 62, 63 } };
const unsigned char And[9] = { 0, 1, 3, 7, 0xf, 0x1f, 0x3f, 0x7f, 0xff };



class Jpeg{

	int sampleYH, sampleYV, sampleUH, sampleUV, sampleVH, sampleVV;
	int HYtoU, VYtoU, HYtoV, VYtoV, YinMCU, UinMCU, VinMCU;
	int compressnum = 0;//ͼ������ĸ���
	int Qt[3][64];//����DCT������һ�������ֻ��������
	int *YQt, *UQt, *VQt;//ָ���ͼ��������õ�������
	int codepos[4][16];//����Ϊj�ĵ�һ�������ڵ���(����Ӧ��codevalue��ֵ����ֵ��0��ʼ)
	int codelen[4][16];//codelen��ʾÿ�����ȵ����Ӧ�ĸ���
	unsigned char YDCindex, YACindex, UVDCindex, UVACindex;
	unsigned char compressindex[3];//��ʾ�ڼ���ͼ������ı��
	unsigned char HufTabindex;//��ʾ�ڼ���huf��
	unsigned int codevalue[4][256];//codevalue[4][j]=(Z,R)���������к�
	unsigned int hufmin[4][16];//hufmin[4][j]��ʾj+1���ȵ���Ŀ�ʼ�루������intֵ��ʾ�ģ�
	unsigned int hufmax[4][16];//��ʾj���ȵ���Ľ����루������intֵ��ʾ�ģ�                                       
	int bitpos = 0, curbyte = 0, run = 0, value = 0, MCUbuffer[10 * 64], blockbuffer[64];
	//blockbuffer[64]����һ����
	//value��ʾÿ����������ֵ������ǵ�һ�������ʾֱ��������ֺ��ֵ��
	//value��DecodeMCUBlock������Ҫ��Ӳ��ܵõ�������ֱ��ϵ��
	//run��ʾÿ������ϵ��֮ǰ��0�ĸ���
	int tempp = 0; //��ʾ��ȡhuf��ʱ�����ĳ��ȣ������жϱ��Ƿ����
	//
	int intervalflag = 0, interval = 0, restart = 0;
	//restart=Ri��DRI���е���������ֽ�Ri�������ֽڱ�ʾһ��SCAN��ÿ��
	//MCU-Segment���������MCU�ĸ���������segment֮����RST��־�֣�RST=0����0��7ѭ����
	//interval��ʾÿ��segment��ѭ�����˵ڼ���MCU��interval=0-Ri��
	//intervalflag=0��ʾһ��segment��MCUѭ�������������ڶ���segment������ʼ
	int ycoef = 0, ucoef = 0, vcoef = 0;//coef��ÿ����ĵ�һ��ϵ������ʾÿ�����ֱ������
	long Y[4 * 64], U[4 * 64], V[4 * 64], QtZMCUbuffer[10 * 64];//QtZMCUbuffer��ʾ�����������MCU������
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
