#include <iostream> 
#include <string>
#include "toglimage.h"
#include "timage.h"
#include <GL/glut.h>
#include <GL/gl.h> 
#include <GL/glu.h>

TOGLImage::TOGLImage(void)
{
}

TOGLImage::~TOGLImage(void)
{
}

void TOGLImage::show()
{
	GLubyte *data;
	data = (GLubyte*)malloc(sizeof(GLubyte)*(w*h));

	int i = 0;
	for(int y=1;y<=h;y++)
		for(int x=1;x<=w;x++,i++)
			data[i]=(int)(getpoint(x,h-y+1)*255/max);

	glRasterPos2f(-w/4,-h/4);
	glDrawPixels(w, h, GL_LUMINANCE, GL_UNSIGNED_BYTE, data);
}