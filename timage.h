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
};

