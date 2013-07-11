#include <iostream> 
#include "tvector.h"
#include "gobject.h"

TVector::TVector()
{

	size = 100;
	
	arr = (GObject**)malloc(sizeof(GObject*)*size);

	for(int i=0; i<size; i++)
	{
		arr[i] = NULL;
	}

}

TVector::~TVector()
{
	deleteall();
	//if(arr!=NULL) {
	
	free(arr);
	//	arr = NULL;

	//}
	//printf("Object destroyed\n");
}

void TVector::setat(GObject * p, int pos)
{
	arr[pos] = p;
}
GObject * TVector::get(int pos)
{
	return arr[pos];
}
void TVector::showall()
{
	for(int i=0; i<size; i++)
		if(arr[i]!=NULL) arr[i]->show();
		else printf("[%d] empty\n", i);
}
void TVector::deleteall()
{
	for(int i=0; i<size; i++)
		if(arr[i]!=NULL) {
			delete arr[i];
			arr[i] = NULL;
		}
	size = 0;
}
void TVector::show(int pos)
{

}
