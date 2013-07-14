#include <iostream> 
#include <conio.h>
#include <math.h>

#include "tpoint.h"
#include "tline.h"
#include "trectangle.h"
#include "tsafevector.h"
#include "timage.h"
#include "toglimage.h"

#include <GL/glut.h>
#include <GL/gl.h> 
#include <GL/glu.h>
#include <Windows.h>

const float PI = 3.141592653589;

TSafeVector linesq;
TSafeVector recsq;
TSafeVector figures;
TOGLImage img;

int isequals(TPoint &p1, TPoint &p2, int delta)
{
	if((abs(p2.getx()-p1.getx())<=delta) && (abs(p2.gety()-p1.gety())<=delta))
		return 1;
	else
		return 0;
}

void getDXY(TLine *l, float *dx, float *dy, int *x1, int *x2, int *y1, int *y2)
{
	if(l->getp2()->getx() > l->getp1()->getx()) 
	{ 
		*x1 = l->getp1()->getx(); 
		*x2 = l->getp2()->getx(); 
		*y1 = l->getp1()->gety(); 
		*y2 = l->getp2()->gety(); 
	}
	else 
	{ 
		*x1 = l->getp2()->getx(); 
		*x2 = l->getp1()->getx(); 
		*y1 = l->getp2()->gety(); 
		*y2 = l->getp1()->gety(); 
	}
	*dx = x2-x1;
	*dy = y2-y1; 
}

int isCrossed(TLine &l1, TLine &l2)
{
	float k1,k2,b1,b2,xx1,yy1,dx1,dx2,dy1,dy2;
	int x11,x12,x21,x22,y11,y12,y21,y22;
	getDXY(&l1, &dx1, &dy1, &x11, &x12, &y11, &y12);
	getDXY(&l2, &dx2, &dy2, &x21, &x22, &y21, &y22);

	if((dx1==0) && (dx2==0))
		return 0; // две вертикальные линии
	else{
		if(dx1==0) // первая линия - вертикальная
		{
			xx1 = x11;
			k2 = dy2/dx2;
			b2 = y21-k2*x21;
			yy1 = xx1*k2+b2;
		}
		else if(dx2==0) // вторая линия - вертикальная
		{
			xx1 = x21;
			k1 = dy1/dx1;
			b1 = y11-k1*x11;
			yy1 = xx1*k1+b1;
		}
		else
		{
			k1 = dy1/dx1;
			k2 = dy2/dx2;
			if(k1!=k2)
			{
				b1 = y11-k1*x11;
				b2 = y21-k2*x21;
				xx1 = (b2-b1)/(k1-k2);
				yy1 = xx1*k1+b1;
			}
			else 
				return 0; // параллельные линии
		}
	}

	if( ((xx1 == x11) && (yy1 == y11)) || ((xx1 == x12) && (yy1 == y12)) || ((xx1 == x21) && (yy1 == y21)) || ((xx1 == x22) && (yy1 == y22)))
		return 0; // пересечение на месте соедниения
	else
		if((xx1>=x11) && (xx1<=x12) && (xx1>=x21) && (xx1<=x22)) 
			return 1; 
		else 
			return 0;
}

int isParallel(TLine &l1, TLine &l2)
{
	float dx1 = (*l1.getp2()).getx()-(*l1.getp1()).getx();
	float dy1 = (*l1.getp2()).gety()-(*l1.getp1()).gety();
	float dx2 = (*l2.getp2()).getx()-(*l2.getp1()).getx();
	float dy2 = (*l2.getp2()).gety()-(*l2.getp1()).gety();
	
	if((dx1==0) || (dx2==0))
		if(dx1==dx2) 
			return 1; 
		else	
			return 0;
	else
	{
		float k1 = dy1/dx1;
		float k2 = dy2/dx2;
		if(k1==k2)
			return 1; 
		else 
			return 0;
	}
	
}

void loadLines(TSafeVector *lns, char *fname)
{
	FILE *fp;
	fp = fopen(fname,"r");

	int i = 0;
	int k = 0;
	int n[4];
	int cnt = 0;

	while(fscanf(fp, "%d", &n[i]) != EOF){
		i++;
		if(i==4)
		{
			i = 0;
			(*lns).setat(new TLine(n[0],n[1],n[2],n[3]),cnt);
			cnt++;
		}
	}

	fclose(fp);
}


void initLines(TSafeVector *p)
{
	loadLines(p,"input3.txt");
}

void showLines(TSafeVector *p)
{
	for(int i=0; i<p->length(); i++)
	{
		printf("Line %d: ", i+1);
		(*p).show(i);
		printf("\n");
	}	
	
}

void findConLine(TSafeVector *all, int li, TPoint *p1, int *resl, int cnt, TSafeVector *recsq,int n, int cur_i)
{
	if(n<5){
		for(int i=cur_i; i<(all->length()); i++)
		{
			if((i!=li) && ( (*(((TLine*)(all->get(i)))->getp1()) == *p1 ) || (*(((TLine*)(all->get(i)))->getp2()) == *p1)))
			{
				resl[cnt] = i;
				if(*(((TLine*)(all->get(i)))->getp1())==*p1)
					findConLine(all, i, ((TLine*)(all->get(i)))->getp2(), resl, cnt+1, recsq, n+1,cur_i);
				else
					findConLine(all, i, ((TLine*)(all->get(i)))->getp1(), resl, cnt+1, recsq, n+1,cur_i);
			}
		}
	}
	else{
		if((li==resl[0]) && (*(((TLine*)(all->get(resl[0])))->getp2())==*p1))
		{
			if(	   !(	isCrossed(*(TLine*)(all->get(resl[0])), *(TLine*)(all->get(resl[2]))) || isCrossed(*(TLine*)(all->get(resl[1])), *(TLine*)(all->get(resl[3])))) 
				&& !(	isParallel(*(TLine*)(all->get(resl[0])), *(TLine*)(all->get(resl[1]))) || 
						isParallel(*(TLine*)(all->get(resl[1])), *(TLine*)(all->get(resl[2]))) || 
						isParallel(*(TLine*)(all->get(resl[2])), *(TLine*)(all->get(resl[3]))) || 
						isParallel(*(TLine*)(all->get(resl[3])), *(TLine*)(all->get(resl[0]))) ))
			{
				// найден четырехугольник
				recsq->setat(new TRectangle(*(TLine*)(all->get(resl[0])),*(TLine*)(all->get(resl[1])),*(TLine*)(all->get(resl[2])),*(TLine*)(all->get(resl[3]))),recsq->length());
				//printf("[%d-%d-%d-%d]\n",resl[0]+1,resl[1]+1,resl[2]+1,resl[3]+1);
			}
		}
	}
}

void calcRectangles(TSafeVector *linesq, TSafeVector *recsq)
{
	for(int i=0; i<(linesq->length()); i++)
	{
		int resl[5];
		resl[0] = i;
		int rescnt = 1;
		findConLine(linesq, i, ((TLine*)(linesq->get(i)))->getp2(), resl, rescnt, recsq, 1, i);
	}
	
}

void showRectangles(TSafeVector *recsq)
{
	for(int i=0; i<(recsq->length()); i++)
	{
		printf("Rectangle %d: ",i+1);
		((TRectangle*)(recsq->get(i)))->show();
		printf("\n");
	}
}

int hasLine(TSafeVector * lines, TLine * l){
	for(int i=0; i<(lines->length()); i++)
		if(*((TLine*)(lines->get(i))) == *l) return 1;
	return 0;
}

void getLinesFromRecs(TSafeVector * lines, TSafeVector * recs)
{
	int j = 0;
	for(int i=0; i<(recs->length()); i++)
	{
		for(int k=1; k<=4; k++)
		{
			if(!hasLine(lines, ((TRectangle*)(recs->get(i)))->getLine(k))) 
			{
				lines->setat(((TRectangle*)(recs->get(i)))->getLine(k),j);
				j++;
			}
		}
	}
}

void drawQuad(TRectangle *r, GLfloat color[]) {
	glBegin( GL_LINE_LOOP );
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

GLint viewport[4];

void initialize()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-200,200,-200,200);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glGetIntegerv(GL_VIEWPORT,viewport);
}

void recalc()
{
	for(int i = 0; i < recsq.length(); i++)
		((TRectangle*)(recsq.get(i)))->rotate(0,0,PI/30);
	linesq.deleteall();
	getLinesFromRecs(&linesq, &recsq);
	linesq.mix();
	figures.deleteall();
	calcRectangles(&linesq, &figures);
	
	for(int i = 0; i < figures.length(); i++)
		((TLine*)figures.get(i))->shift(2,2);
	
}

void display( void )
{
	glClear( GL_COLOR_BUFFER_BIT ); // Очистка экрана

	float col[3] = {0, 0.7, 1};
	float col2[3] = {1, 1, 1};

	/*
	for(int i = 0; i < recsq.length(); i++)
		drawQuad((TRectangle*)(recsq.get(i)), col);
	
	for(int i = 0; i < figures.length(); i++)
		drawQuad((TRectangle*)(figures.get(i)), col2);
		*/

	img.show();

	glutSwapBuffers();
	
	/*
	Sleep(40);
	recalc();
	glutPostRedisplay();
	*/
		
}

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


int main(int argc, char** argv)
{
	img.load("img/2.pgm");

	img.save("img/test.pgm");
	
    initLines(&linesq);
	showLines(&linesq);
	calcRectangles(&linesq, &recsq);
	showRectangles(&recsq);

	glutInit( &argc, argv ); 
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(800, 100);
	glutCreateWindow( "My First Window" );
	glutDisplayFunc(display);
	//glutMouseFunc(mouseButton); 
	glutKeyboardFunc(keyboard);
	//glutReshapeFunc(resize); 
	initialize(); //init OpenGL state
	
	glutMainLoop();


	//getchar();

    return 0;
}