#ifndef svect_h
#define svect_h

#include "tvector.h"

class TSafeVector: public TVector
{
public:
	TSafeVector();
	virtual ~TSafeVector();
	void setat(GObject * p, int pos);
	void showall();
	void show(int pos);
	virtual void deleteall();
	int length();
	void mix();
};

#endif