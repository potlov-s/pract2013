#include "tpoint.h"
#include <iostream> 
#include <math.h>



void TPoint::setxy(int ix, int iy)
{
	x = ix;
	y = iy;
}


TPoint::TPoint(void)
{
	x = 0;
	y = 0;
}

TPoint::TPoint(int ix, int iy)
{
	x = ix;
	y = iy;
}




TPoint::~TPoint(void)
{

}

const int delta = 1;

bool operator==(const TPoint& left, const TPoint& right) {
	if((abs(left.x-right.x)<=delta) && (abs(left.y-right.y)<=delta))
		return 1;
	else
		return 0;
}