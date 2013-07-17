#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h> 
#include <GL/glu.h>
#include "trectangle.h"
#include "triangle.h"
#include "lsd.h"

void keyboard(unsigned char key, int x, int y )
{
	switch( key ) {
		case 'q' : case 'Q' :
			exit( EXIT_SUCCESS );
		break;
		case 'r' : case 'R' :
			//rotate = GL_TRUE;
		break;
	}
}

void drawQuad(TRectangle *r, GLfloat color[]) {
	glBegin( GL_QUADS );
	glColor3fv( color );

	glVertex2f( r->getLine(1)->getp1()->getx(), r->getLine(1)->getp1()->gety());
	glVertex2f( r->getLine(1)->getp2()->getx(), r->getLine(1)->getp2()->gety());

	TPoint * last_point = r->getLine(1)->getp2();
	for(int i = 2; i <= 3; i++)
	{
		if(*(r->getLine(i)->getp1())==(*last_point))
		{
			glVertex2f( r->getLine(i)->getp2()->getx(), r->getLine(i)->getp2()->gety());
			last_point = r->getLine(i)->getp2();
		}
		else
		{
			glVertex2f( r->getLine(i)->getp1()->getx(), r->getLine(i)->getp1()->gety());
			last_point = r->getLine(i)->getp1();
		}
	}
	
	glEnd();

}

void drawTriangle(Triangle *r, GLfloat color[]) {
	glBegin( GL_TRIANGLES );
	glColor3fv( color );

	glVertex2f( r->getLine(1)->getp1()->getx(), r->getLine(1)->getp1()->gety());
	glVertex2f( r->getLine(1)->getp2()->getx(), r->getLine(1)->getp2()->gety());

	TPoint * last_point = r->getLine(1)->getp2();
	for(int i = 2; i <= 2; i++)
	{
		if(*(r->getLine(i)->getp1())==(*last_point))
		{
			glVertex2f( r->getLine(i)->getp2()->getx(), r->getLine(i)->getp2()->gety());
			last_point = r->getLine(i)->getp2();
		}
		else
		{
			glVertex2f( r->getLine(i)->getp1()->getx(), r->getLine(i)->getp1()->gety());
			last_point = r->getLine(i)->getp1();
		}
	}
	
	glEnd();
}

void drawLine(TLine *l, GLfloat color[]) {
	glBegin( GL_LINES );
	glColor3fv( color );

	glVertex2f( l->getp1()->getx(), l->getp1()->gety());
	glVertex2f( l->getp2()->getx(), l->getp2()->gety());
	
	glEnd();
}


GLint viewport[4];

void initialize()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-500,500,-350,350);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glGetIntegerv(GL_VIEWPORT,viewport);
}

