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

	glPixelStorei(1, 1);
	glRasterPos2i(0, 0);

	GLubyte *data;
	data = (GLubyte*)malloc(sizeof(GLubyte)*(w*h));
	int i = 0;
	for(int y=1;y<=h;y++)
		for(int x=1;x<=w;x++)
		{
			data[i]=getpoint(x,h-y+1);
			i++;
		}

	glRasterPos2f(2.0f, 1.0f);
	glDrawPixels(w, h, GL_LUMINANCE, GL_UNSIGNED_BYTE, data);
	
}