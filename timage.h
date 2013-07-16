#pragma once

class TImage
{
protected:
	int *image;
	int w;
	int h;
	int max;
public:
	TImage(void);
	~TImage(void);
	void setpoint(int px, int py, int color);
	int getpoint(int px, int py);
	void load(char* file);
	void save(char* file);
	void copy(TImage *p);
	void filterSobel();
	 
	friend bool operator==(const TImage& left, const TImage& right);
	TImage& operator=(TImage& i);
};

