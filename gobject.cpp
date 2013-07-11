#include <iostream> 
#include "gobject.h"

const float PI = 3.141592653589;

GObject::GObject()
{
	x = 0;
	y = 0;
}
GObject::GObject(int ix, int iy)
{
	x = ix;
	y = iy;
}
GObject::~GObject()
{
	//printf("GObject destroyed\n");
}
void GObject::show()
{
	printf("(%d, %d)\n", x, y);
}

void GObject::setx(int ix)
{
	x = ix;
}
void GObject::sety(int iy)
{
	y = iy;
}
int GObject::getx()
{
	return x;
}
int GObject::gety()
{
	return y;
}


void GObject::rotate(int ix, int iy, float angle)
{
	float old_angle, new_angle, r;


	r = sqrt(pow(y-iy,2)+pow(x-ix,2));
	if(x!=ix)
	{
		old_angle = atan((float)(y-iy)/(float)(x-ix)); 
		if(old_angle<0) old_angle+=PI;
		if(y<iy) old_angle+=PI;
		if(y==iy && x<ix) old_angle+=PI;
	}
	else
	{
		if(y>iy) old_angle = PI/2;
		else old_angle = 1.5*PI;
	}
	new_angle = old_angle + angle;

	//printf("-----------------------------\n");
	//printf("( x = %d, y = %d )\n",x,y);
	//printf("old_a = %f, new_a = %f \n",old_angle*57.295779513, new_angle*57.295779513);
	

	x = ix+(int)(floor(r*cos(new_angle)));
	y = iy+(int)(floor(r*sin(new_angle)));

	
	
	
}

void GObject::shift(int dx, int dy)
{
	x += dx;
	y += dy;
}