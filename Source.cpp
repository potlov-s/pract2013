#include <iostream> 
#include <conio.h>
#include <math.h>

#include "tpoint.h"
#include "tline.h"
#include "trectangle.h"
#include "Triangle.h"
#include "tsafevector.h"
#include "timage.h"
#include "toglimage.h"
#include "graphics.h"

#include <GL/glut.h>
#include <GL/gl.h> 
#include <GL/glu.h>
#include <Windows.h>

#include "lsd.h"

const float PI = 3.141592653589;

TSafeVector linesq;
TSafeVector recsq;
TSafeVector triangles;
TSafeVector figures;
TSafeVector figures2;
TOGLImage img;

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

void findConLine(TSafeVector *all, int li, TPoint *p1, int *resl, int cnt, TSafeVector *res,int n, int cur_i, int maxl)
{
	if(n<maxl+1){
		for(int i=cur_i; i<(all->length()); i++)
		{
			if((i!=li) && ( (*(((TLine*)(all->get(i)))->getp1()) == *p1 ) || (*(((TLine*)(all->get(i)))->getp2()) == *p1)))
			{
				resl[cnt] = i;
				if(*(((TLine*)(all->get(i)))->getp1())==*p1)
					findConLine(all, i, ((TLine*)(all->get(i)))->getp2(), resl, cnt+1, res, n+1,cur_i,maxl);
				else
					findConLine(all, i, ((TLine*)(all->get(i)))->getp1(), resl, cnt+1, res, n+1,cur_i,maxl);
			}
		}
	}
	else{
		if((li==resl[0]) && (*(((TLine*)(all->get(resl[0])))->getp2())==*p1))
		{
			if(maxl==4)
			{
				if(	   !(	isCrossed(*(TLine*)(all->get(resl[0])), *(TLine*)(all->get(resl[2]))) || isCrossed(*(TLine*)(all->get(resl[1])), *(TLine*)(all->get(resl[3])))) 
					&& !(	isParallel(*(TLine*)(all->get(resl[0])), *(TLine*)(all->get(resl[1]))) || 
							isParallel(*(TLine*)(all->get(resl[1])), *(TLine*)(all->get(resl[2]))) || 
							isParallel(*(TLine*)(all->get(resl[2])), *(TLine*)(all->get(resl[3]))) || 
							isParallel(*(TLine*)(all->get(resl[3])), *(TLine*)(all->get(resl[0]))) ))
				{
					// найден четырехугольник
					res->setat(new TRectangle(*(TLine*)(all->get(resl[0])),*(TLine*)(all->get(resl[1])),*(TLine*)(all->get(resl[2])),*(TLine*)(all->get(resl[3]))),res->length());
				}
			}
			else
			{
				if(	   !(isParallel(*(TLine*)(all->get(resl[0])), *(TLine*)(all->get(resl[1]))) || 
						isParallel(*(TLine*)(all->get(resl[1])), *(TLine*)(all->get(resl[2]))) || 
						isParallel(*(TLine*)(all->get(resl[2])), *(TLine*)(all->get(resl[0]))) ))
				{
					// найден трехугольник
					res->setat(new Triangle(*(TLine*)(all->get(resl[0])),*(TLine*)(all->get(resl[1])),*(TLine*)(all->get(resl[2]))),res->length());
				}
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
		findConLine(linesq, i, ((TLine*)(linesq->get(i)))->getp2(), resl, rescnt, recsq, 1, i,4);
	}
	
}

void calcTriangles(TSafeVector *linesq, TSafeVector *trngls)
{
	for(int i=0; i<(linesq->length()); i++)
	{
		int resl[4];
		resl[0] = i;
		int rescnt = 1;
		findConLine(linesq, i, ((TLine*)(linesq->get(i)))->getp2(), resl, rescnt, trngls, 1, i,3);
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

void showTriangles(TSafeVector *t)
{
	for(int i=0; i<(t->length()); i++)
	{
		printf("Triangle %d: ",i+1);
		((Triangle*)(t->get(i)))->show();
		printf("\n");
	}
}

int hasLine(TSafeVector * lines, TLine * l){
	for(int i=0; i<(lines->length()); i++)
		if(*((TLine*)(lines->get(i))) == *l) return 1;
	return 0;
}

void getLinesFromFigures(TSafeVector * lines, TSafeVector * v,int n)
{
	int j = lines->length();
	for(int i=0; i<(v->length()); i++)
	{
		for(int k=1; k<=n; k++)
		{
			if(n==4)
			{//4х-угольник
				if(!hasLine(lines, ((TRectangle*)(v->get(i)))->getLine(k))) 
				{
					lines->setat(((TRectangle*)(v->get(i)))->getLine(k),j);
					j++;
				}
			}
			else
			{//3х-угольник
				if(!hasLine(lines, ((Triangle*)(v->get(i)))->getLine(k))) 
				{
					lines->setat(((Triangle*)(v->get(i)))->getLine(k),j);
					j++;
				}
			}
		}
	}
}

void recalc()
{
	for(int i = 0; i < recsq.length(); i++)
		((TRectangle*)(recsq.get(i)))->rotate(0,0,PI/30);
	
	for(int i = 0; i < triangles.length(); i++)
		((Triangle*)(triangles.get(i)))->rotate(0,0,PI/30);

	linesq.deleteall();
	getLinesFromFigures(&linesq, &recsq,4);
	getLinesFromFigures(&linesq, &triangles,3);

	linesq.mix();
	figures.deleteall();
	figures2.deleteall();
	calcRectangles(&linesq, &figures);
	calcTriangles(&linesq, &figures2);
	
	for(int i = 0; i < figures.length(); i++)
		((TLine*)figures.get(i))->shift(2,2);
	
	for(int i = 0; i < figures2.length(); i++)
		((TLine*)figures2.get(i))->shift(2,2);
	
}



void display( void )
{

	
	glClear( GL_COLOR_BUFFER_BIT ); // Очистка экрана

	float col1[3] = {0, 0.7, 1}; // голубой
	float col2[3] = {1, 1, 1}; // белый
	float col3[3] = {1, 0.8, 0.2}; // оранжевый
	float col4[3] = {1, 0.1, 0.3};

	/*
	for(int i = 0; i < recsq.length(); i++)
		drawQuad((TRectangle*)(recsq.get(i)), col1);
	
	for(int i = 0; i < triangles.length(); i++)
		drawTriangle((Triangle*)(triangles.get(i)), col3);
	

	for(int i = 0; i < figures.length(); i++)
		drawQuad((TRectangle*)(figures.get(i)), col2);
	
	for(int i = 0; i < figures2.length(); i++)
		drawTriangle((Triangle*)(figures2.get(i)), col2);
	*/

	double * image;
	double * out;
	int x,y,i,j,n;
	int X = img.getw();  /* x image size */
	int Y = img.geth();  /* y image size */

	image = (double *) malloc( X * Y * sizeof(double) );
	 if( image == NULL )
    {
      fprintf(stderr,"error: not enough memory\n");
      exit(EXIT_FAILURE);
    }
	for(x=0;x<X;x++)
		for(y=0;y<Y;y++)
			image[x+y*X] = img.getpoint(x+1,y+1); /* image(x,y) */
	
	/* LSD call */
	out = lsd(&n,image,X,Y);

	TSafeVector lns;
	//linesq.deleteall();
	int k = 0;
	for(i=0;i<n;i++)
	{
		//for(j=0;j<7;j++)
			//printf("%4.0f ",out[7*i+j]);
		lns.setat(new TLine(out[7*i+0],img.geth()-out[7*i+1],out[7*i+2],img.geth()-out[7*i+3]),k);
		((TLine*)(lns.get(k)))->shift(-img.getw()/2,-img.geth()/2);
		k++;
    }

	img.show();

	for(int i = 0; i < lns.length(); i++)
		drawLine((TLine*)(lns.get(i)), col1);

	calcRectangles(&lns, &figures);
	calcTriangles(&lns, &figures2);

	for(int i = 0; i < figures.length(); i++)
		drawQuad((TRectangle*)(figures.get(i)), col3);
	
	for(int i = 0; i < figures2.length(); i++)
		drawTriangle((Triangle*)(figures2.get(i)), col4);

	glutSwapBuffers();
	
	free( (void *) image );
	free( (void *) out );

	/*
	Sleep(40);
	recalc();
	glutPostRedisplay();
	*/	
}



int main(int argc, char** argv)
{
	img.load("img/4.pgm");
	//img.filterSobel();
	
    initLines(&linesq);
	showLines(&linesq);
	calcRectangles(&linesq, &recsq);
	calcTriangles(&linesq, &triangles);
	showRectangles(&recsq);
	showTriangles(&triangles);
	
	 
	glutInit( &argc, argv );
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(1000, 700);
	glutInitWindowPosition(100, 100);
	glutCreateWindow( "Cam" );
	glutDisplayFunc(display);
	//glutMouseFunc(mouseButton); 
	glutKeyboardFunc(keyboard);
	//glutReshapeFunc(resize); 
	initialize(); //init OpenGL state
	glutMainLoop();

    return 0;
}

