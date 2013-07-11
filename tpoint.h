#ifndef point_h
#define point_h
#include "gobject.h"

class TPoint: public GObject
{
public:
	void setxy(int ix, int iy);
	TPoint(void);
	TPoint(int ix, int iy);
	virtual ~TPoint(void);

	friend bool operator==(const TPoint& left, const TPoint& right);
};

#endif