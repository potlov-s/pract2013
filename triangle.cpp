#include "Triangle.h"
#include <iostream> 

Triangle::Triangle(void)
{
}

Triangle::Triangle(TLine il1,TLine il2,TLine il3)
{
	l1 = il1;
	l2 = il2;
	l3 = il3;
}

Triangle::~Triangle(void)
{
}


void Triangle::setLines(TLine il1,TLine il2,TLine il3)
{
	l1 = il1;
	l2 = il2;
	l3 = il3;
}

void Triangle::show(void)
{
	l1.show(); printf(" ");
	l2.show(); printf(" ");
	l3.show();
}

void Triangle::rotate(int x, int y, float angle)
{
	l1.getp1()->rotate(x, y, angle);
	l1.getp2()->rotate(x, y, angle);
	l2.getp1()->rotate(x, y, angle);
	l2.getp2()->rotate(x, y, angle);
	l3.getp1()->rotate(x, y, angle);
	l3.getp2()->rotate(x, y, angle);
}

TLine * Triangle::getLine(int li)
{
	switch(li) {
		case 1: return &l1;
		case 2: return &l2;
		case 3: return &l3;
		default: return &l1;
	}
}

void Triangle::shift(int dx, int dy)
{
	l1.getp1()->shift(dx,dy);
	l1.getp2()->shift(dx,dy);
	l2.getp1()->shift(dx,dy);
	l2.getp2()->shift(dx,dy);
	l3.getp1()->shift(dx,dy);
	l3.getp2()->shift(dx,dy);
}