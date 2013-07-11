#ifndef vect_h
#define vect_h

#include "gobject.h"

class TVector
{
protected: 
	GObject **arr;
	int size;
public:
	TVector();
	virtual ~TVector();
	virtual void setat(GObject * p, int pos);
	GObject * get(int pos);
	virtual void showall();
	virtual void show(int pos);
	virtual void deleteall();
};

#endif