#ifndef gobj_h
#define gobj_h

class GObject
{
protected: 
	int x;
	int y;
public:
	GObject();
	GObject(int ix, int iy);
	virtual ~GObject();
	virtual void show();
	void setx(int ix);
	void sety(int iy);
	int getx();
	int gety();
	virtual void rotate(int x, int y, float angle);
	virtual void shift(int dx, int dy);
};

#endif