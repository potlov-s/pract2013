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

const int delta = 5;

bool operator==(const TPoint& left, const TPoint& right) {
	if((abs(left.x-right.x)<=delta) && (abs(left.y-right.y)<=delta))
		return 1;
	else
		return 0;
}

int isequals(TPoint &p1, TPoint &p2, int delta)
{
	if((abs(p2.getx()-p1.getx())<=delta) && (abs(p2.gety()-p1.gety())<=delta))
		return 1;
	else
		return 0;
}