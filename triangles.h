#ifndef  _triangles_h
#define _triangles_h
#include "gobject.h"
#include "tvector.h"

//Точка
class TPoint: public GObject
{
public:
    TPoint();
    TPoint(int ix, int iy);
    friend bool operator==(const TPoint& left, const TPoint& right);
};

bool operator==(const TPoint& left, const TPoint& right);

//Отрезок
class TLine: public GObject
{
public:
    TPoint p1;
    TPoint p2;
    TLine();
    virtual void show();
    virtual void rotate(GObject *center,double angle);
    virtual void shift(int dx, int dy);
};

//Треугольник
class TTriangle: public GObject
{
public:
    TLine l1;
    TLine l2;
    TLine l3;

    TTriangle();
    virtual ~TTriangle();
    virtual void show();
    virtual void rotate(GObject *center,double angle);
    virtual void shift(int dx, int dy);

};

void getLinesFromTriangles(TSafeVector *triangles,TSafeVector *lines, int *lcnt);

//Инициализировать отрезки
void initLines(TSafeVector *lines, //массив отрезков
               int *cnt);    //количество инициализированных отрезков

//Показать отрезки
void showLines(TSafeVector *lines, //массив отрезков
               int lcnt);    //количество отрезков

//Показать треулгольники
void showTriangles(TSafeVector *triangles, //массив треугольников
                   int tricnt);    	     //количество треугольников

//Найти треугольники
void calcTriangles(TSafeVector *lines,         //массив отрезков
                   int lcnt,             //количество отрезков
                   TSafeVector *triangles, //массив для записи найденных треугольников
                   int *tricnt);         //количество найденных треугольников

void findConLine(TSafeVector *all, int lcnt, TPoint p1, TLine *line, TSafeVector res, int *cnt);

#endif /* _triangles_h */
