#ifndef MATHUTIL_H

#include "Windows.h"
#include "stdio.h"
#include "string.h"
#include "malloc.h"

#define MATHUTIL_H
class MathUtil{
public:
	static void idct(long *p, int k);
	static void IDCTint(long *metrix);
};

#endif // MATHUTIL_H
