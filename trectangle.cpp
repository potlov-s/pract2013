#include "trectangle.h"
#include <iostream> 

TRectangle::TRectangle(void)
{
}

TRectangle::TRectangle(TLine il1,TLine il2,TLine il3,TLine il4)
{
	l1 = il1;
	l2 = il2;
	l3 = il3;
	l4 = il4;
}

TRectangle::~TRectangle(void)
{
}


void TRectangle::setLines(TLine il1,TLine il2,TLine il3,TLine il4)
{
	l1 = il1;
	l2 = il2;
	l3 = il3;
	l4 = il4;
}

void TRectangle::show(void)
{
	l1.show(); printf(" ");
	l2.show(); printf(" ");
	l3.show(); printf(" ");
	l4.show();
}

void TRectangle::rotate(int x, int y, float angle/*, int center*/)
{
	/*
	if(center)
	{
		x = (l1.getp1()->getx()+l1.getp2()->getx()+l3.getp1()->getx()+l3.getp2()->getx())/4;
		y = (l1.getp1()->gety()+l1.getp2()->gety()+l3.getp1()->gety()+l3.getp2()->gety())/4;
	}
	*/
	l1.getp1()->rotate(x, y, angle);
	l1.getp2()->rotate(x, y, angle);
	l2.getp1()->rotate(x, y, angle);
	l2.getp2()->rotate(x, y, angle);
	l3.getp1()->rotate(x, y, angle);
	l3.getp2()->rotate(x, y, angle);
	l4.getp1()->rotate(x, y, angle);
	l4.getp2()->rotate(x, y, angle);
}

TLine * TRectangle::getLine(int li)
{
	switch(li) {
		case 1: return &l1;
		case 2: return &l2;
		case 3: return &l3;
		case 4: return &l4;
		default: return &l1;
	}
}

void TRectangle::shift(int dx, int dy)
{
	l1.getp1()->shift(dx,dy);
	l1.getp2()->shift(dx,dy);
	l2.getp1()->shift(dx,dy);
	l2.getp2()->shift(dx,dy);
	l3.getp1()->shift(dx,dy);
	l3.getp2()->shift(dx,dy);
	l4.getp1()->shift(dx,dy);
	l4.getp2()->shift(dx,dy);
}