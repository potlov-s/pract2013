#include <stdlib.h>
#include <stdio.h>
#include "triangles.h"

TPoint::TPoint()
{
    setx(0);
    sety(0);
}

TPoint::TPoint(int ix, int iy)
{
    setx(ix);
    sety(iy);
}

//Оператор равенства для двух точек
const int minDelta = 3;
bool operator==(const TPoint& left, const TPoint& right)
{
    if((abs(left.getx()-right.getx())<minDelta) && (abs(left.gety()-right.gety())<minDelta))
        return true;
    else
        return false;
}

TLine::TLine()
{
    p1.setx(0);
    p1.sety(0);
    p2.setx(0);
    p2.sety(0);
}

void TLine::rotate(GObject *center,double angle)
{
    p1.rotate(center,angle);
    p2.rotate(center,angle);
}

void TLine::shift(int dx, int dy)
{
    p1.shift(dx,dy);
    p2.shift(dx,dy);
}

TTriangle::TTriangle()
{

}

TTriangle::~TTriangle()
{
    //printf("Triangle deleted!\n");
}

void TTriangle::rotate(GObject *center,double angle)
{
    l1.rotate(center,angle);
    l2.rotate(center,angle);
    l3.rotate(center,angle);
}

void TTriangle::shift(int dx, int dy)
{
    l1.shift(dx,dy);
    l2.shift(dx,dy);
    l3.shift(dx,dy);
}

void TTriangle::show()
{
    printf("Line 1 ");
    l1.show();
    printf("Line 2 ");
    l2.show();
    printf("Line 3 ");
    l3.show();
}

void TLine::show()
{
    printf("p1(%d,%d) p2(%d,%d)\n",p1.getx(),p1.gety(),p2.getx(),p2.gety());
}

void getLinesFromTriangles(TSafeVector *triangles,TSafeVector *lines, int *lcnt)
{
    int j=0;
    for(int i=0;i<triangles->getsize();i++)
    {
        if(triangles->get(i)!=NULL)
        {
            lines->setat(&(((TTriangle*)triangles->get(i))->l1),j++);
            lines->setat(&(((TTriangle*)triangles->get(i))->l2),j++);
            lines->setat(&(((TTriangle*)triangles->get(i))->l3),j++);
        }
    }
    *lcnt=j;
}

TLine *l1,*l2,*l3,*l4,*l5,*l6,*l7,*l8,*l9,*l10,*l11,*l12,*l13,*l14;

//Инициализировать отрезки
void initLines(TSafeVector *lines, //массив отрезков
               int *cnt)     //количество инициализированных отрезков
{

    l1=new TLine();
    l6=new TLine();
    l11=new TLine();
    l2=new TLine();
    l7=new TLine();
    l12=new TLine();
    l3=new TLine();
    l8=new TLine();
    l13=new TLine();
    l4=new TLine();
    l9=new TLine();
    l14=new TLine();
    l5=new TLine();
    l10=new TLine();

    l1->p1.setx(3);
    l1->p1.sety(10);
    l1->p2.setx(10);
    l1->p2.sety(14);

    lines->setat(l1,0);

    l2->p1.setx(40);
    l2->p1.sety(2);
    l2->p2.setx(46);
    l2->p2.sety(6);

    lines->setat(l2,1);

    l3->p1.setx(11);
    l3->p1.sety(15);
    l3->p2.setx(14);
    l3->p2.sety(7);

    lines->setat(l3,2);

    l4->p1.setx(14);
    l4->p1.sety(7);
    l4->p2.setx(3);
    l4->p2.sety(9);

    lines->setat(l4,3);

    l5->p1.setx(9);
    l5->p1.sety(4);
    l5->p2.setx(10);
    l5->p2.sety(11);

    lines->setat(l5,4);

    l6->p1.setx(9);
    l6->p1.sety(4);
    l6->p2.setx(16);
    l6->p2.sety(12);

    lines->setat(l6,5);

    l7->p1.setx(10);
    l7->p1.sety(11);
    l7->p2.setx(17);
    l7->p2.sety(13);

    lines->setat(l7,6);

    l8->p1.setx(11);
    l8->p1.sety(15);
    l8->p2.setx(20);
    l8->p2.sety(14);

    lines->setat(l8,7);

    l9->p1.setx(14);
    l9->p1.sety(7);
    l9->p2.setx(20);
    l9->p2.sety(14);

    lines->setat(l9,8);

    l10->p1.setx(11);
    l10->p1.sety(15);
    l10->p2.setx(5);
    l10->p2.sety(16);

    lines->setat(l10,9);

    l11->p1.setx(2);
    l11->p1.sety(14);
    l11->p2.setx(7);
    l11->p2.sety(11);

    lines->setat(l11,10);

    l12->p1.setx(13);
    l12->p1.sety(11);
    l12->p2.setx(15);
    l12->p2.sety(16);

    lines->setat(l12,11);

    l13->p1.setx(7);
    l13->p1.sety(11);
    l13->p2.setx(19);
    l13->p2.sety(6);

    lines->setat(l13,12);

    l14->p1.setx(2);
    l14->p1.sety(14);
    l14->p2.setx(13);
    l14->p2.sety(2);

    lines->setat(l14,13);

    *cnt=14;

};

//Показать отрезки
void showLines(TSafeVector *lines, //массив отрезков
               int lcnt)     //количество отрезков
{

    if(lcnt>0)
    {
        for(int i=0; i<lcnt; i++)
        {
            printf("Line %d ",i);
            lines->get(i)->show();
        }
    }

};

//Показать треулгольники
void showTriangles(TSafeVector *triangles, //массив треугольников
                   int tricnt)           //количество треугольников
{
    if(tricnt>0)
    {
        for(int i=0; i<tricnt; i++)
        {
            printf("Triangle %d\n",i);
            triangles->get(i)->show();
        }
    }
};

void findConLine(TSafeVector *all, int lcnt, TPoint p1, TLine *line, TSafeVector *res, int *cnt)
{
    int i=0;
    int count=0;
    while(i<lcnt)
    {
        if(line!=((TLine*)all->get(i)))
        {

            if(p1==((TLine*)all->get(i))->p1)
            {
                res->setat(all->get(i),count);
                count++;
            }
            else
            {
                if(p1==((TLine*)all->get(i))->p2)
                {
                    res->setat(all->get(i),count);
                    count++;
                }
            }
        }
        i++;
    }

    *cnt=count;

};

TTriangle *temptriangle;
//Найти треугольники
void calcTriangles(TSafeVector *lines,         //массив отрезков
                   int lcnt,             //количество отрезков
                   TSafeVector *triangles, //массив для записи найденных треугольников
                   int *tricnt)          //количество найденных треугольников
{

    int cnt=0;
    *tricnt=0;
    int count=0;
    int m=0;

    TSafeVector *res;
    res=new TSafeVector();

    for(int i=0; i<lcnt; i++)
    {
        for(int j=i+1; j<lcnt; j++)
        {

            if(((TLine*)lines->get(i))->p1==((TLine*)lines->get(j))->p1)
            {
                findConLine(lines, lcnt, ((TLine*)lines->get(j))->p2, ((TLine*)lines->get(j)), res, &cnt);
                for(int k=0; k<cnt; k++)
                {
                    if((((TLine*)lines->get(i))->p2==((TLine*)res->get(k))->p1)||
                            (((TLine*)lines->get(i))->p2==((TLine*)res->get(k))->p2))
                    {
                        temptriangle = new TTriangle();
                        temptriangle->l1=*(TLine*)lines->get(i);
                        temptriangle->l2=*(TLine*)lines->get(j);
                        temptriangle->l3=*(TLine*)res->get(k);
                        triangles->setat(temptriangle,count);
                        count++;
                        *tricnt=count;

                    }
                }
            }
            else
            {
                if((((TLine*)lines->get(i))->p1==((TLine*)lines->get(j))->p2))
                {
                    findConLine(lines, lcnt, ((TLine*)lines->get(j))->p1, ((TLine*)lines->get(j)), res, &cnt);
                    for(int k=0; k<cnt; k++)
                    {
                        if((((TLine*)lines->get(i))->p2==((TLine*)res->get(k))->p1)||
                                (((TLine*)lines->get(i))->p2==((TLine*)res->get(k))->p2))
                        {
                            temptriangle = new TTriangle();
                            temptriangle->l1=*(TLine*)lines->get(i);
                            temptriangle->l2=*(TLine*)lines->get(j);
                            temptriangle->l3=*(TLine*)res->get(k);
                            triangles->setat(temptriangle,count);
                            count++;
                            *tricnt=count;
                        }
                    }
                }
            }
        }
    }

};






