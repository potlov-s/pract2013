#include <iostream> 
#include "tsafevector.h"
#include "gobject.h"

TSafeVector::TSafeVector()
{
	size = 0;
}
TSafeVector::~TSafeVector()
{
	deleteall();
}

void TSafeVector::setat(GObject * p, int pos)
{
	if(pos<size)
	{
		arr[pos] = p;
	}
	else
	{
		
		GObject **old = arr;

		arr = (GObject**)malloc(sizeof(GObject*)*(pos+1));
		
		arr[pos] = p;

		for(int i=0; i<size; i++) arr[i] = old[i];
		for(int i=size; i<pos; i++) arr[i] = NULL;

		size = pos+1;

	}
}
void TSafeVector::showall()
{
	for(int i=0; i<size; i++)
		if(arr[i]!=NULL) arr[i]->show();
		else printf("[%d] empty\n", i);
}

void TSafeVector::deleteall()
{
	//printf("[%d]\n",size);
	for(int i=0; i<size; i++)
	{
		//printf("%d-",i);
		if(arr[i]!=NULL) {
			//delete arr[i];
			arr[i] = NULL;
		}
	}
	size = 0;
}

void TSafeVector::show(int pos)
{
	arr[pos] -> show();
}

int TSafeVector::length()
{
	return size;
}

void TSafeVector::mix()
{
	for (size_t i = 0; i < size; i ++) {
		std::swap(arr[i], arr[rand() % size]);
	}
}