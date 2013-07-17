#pragma once

#include "gobject.h"
#include "tline.h"

class Triangle: public GObject
{
	TLine l1;
	TLine l2;
	TLine l3;
public:
	void sett(int num);
	void setLines(TLine il1,TLine il2,TLine il3);
	Triangle(void);
	Triangle(TLine il1,TLine il2,TLine il3);
	virtual ~Triangle(void);
	void show();
	virtual void rotate(int x, int y, float angle);
	TLine * getLine(int li);
	virtual void shift(int dx, int dy);
};

