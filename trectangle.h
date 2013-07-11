#ifndef rect_h
#define rect_h

#include "gobject.h"
#include "tline.h"

class TRectangle: public GObject
{
	TLine l1;
	TLine l2;
	TLine l3;
	TLine l4;
public:
	void sett(int num);
	void setLines(TLine il1,TLine il2,TLine il3,TLine il4);
	TRectangle(void);
	TRectangle(TLine il1,TLine il2,TLine il3,TLine il4);
	virtual ~TRectangle(void);
	void show();
	virtual void rotate(int x, int y, float angle/*, int center*/);
	TLine * getLine(int li);
	virtual void shift(int dx, int dy);
};

#endif
