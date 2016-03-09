#include "mathUtil.h"
void MathUtil::idct(long *p, int k)
{
	long x, x0, x1, x2, x3, x4, x5, x6, x7;
	x1 = p[k * 4] << 11;
	x2 = p[k * 6];
	x3 = p[k * 2];
	x4 = p[k * 1];
	x5 = p[k * 7];
	x6 = p[k * 5];
	x7 = p[k * 3];
	x0 = (p[0] << 11) + 1024;
	x = 565 * (x4 + x5); x4 = x + 2276 * x4; x5 = x - 3406 * x5;
	x = 2408 * (x6 + x7); x6 = x - 799 * x6; x7 = x - 4017 * x7;
	x = 1108 * (x3 + x2); x2 = x - 3784 * x2; x3 = x + 1568 * x3;

	x = x6; x6 = x5 + x7; x5 -= x7; x7 = x0 + x1; x0 -= x1; x1 = x + x4; x4 -= x;
	x = x5; x5 = x7 - x3; x7 += x3; x3 = x0 + x2; x0 -= x2; x2 = (181 * (x4 + x) + 128) >> 8; x4 = (181 * (x4 - x) + 128) >> 8;
	p[0] = (x7 + x1) >> 11;
	p[k * 1] = (x3 + x2) >> 11;
	p[k * 2] = (x0 + x4) >> 11;  p[k * 3] = (x5 + x6) >> 11;
	p[k * 4] = (x5 - x6) >> 11;  p[k * 5] = (x0 - x4) >> 11;
	p[k * 6] = (x3 - x2) >> 11; p[k * 7] = (x7 - x1) >> 11;
}
void MathUtil::IDCTint(long *metrix)
{
	int i;
	for (i = 0; i<8; i++)
		idct(metrix + 8 * i, 1);
	for (i = 0; i<8; i++)
		idct(metrix + i, 8);
}