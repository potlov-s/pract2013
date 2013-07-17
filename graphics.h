#pragma once
#include <GL/glut.h>
#include <GL/gl.h> 
#include <GL/glu.h>

void display( void );
void keyboard(unsigned char key, int x, int y );
void drawQuad(TRectangle *r, GLfloat color[]);
void drawTriangle(Triangle *r, GLfloat color[]);
void drawLine(TLine *l, GLfloat color[]);
void initialize();
