#ifndef line_h
#define line_h

#include "gobject.h"
#include "tpoint.h"

class TLine: public GObject
{
	TPoint p1;
	TPoint p2;
public:
	void setp1(int ix, int iy);
	void setp2(int ix, int iy);
	TPoint * getp1();
	TPoint * getp2();
	TLine(void);
	TLine::TLine(int ix1, int iy1, int ix2, int iy2);
	virtual ~TLine(void);
	void show();

	friend bool operator==(const TLine& left, const TLine& right);
};

#endif
