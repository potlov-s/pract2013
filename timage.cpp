#include "timage.h"
#include <iostream> 
#include <string>

TImage::TImage(void)
{
	w = 0;
	h = 0;
}


TImage::~TImage(void)
{

}

void TImage::setpoint(int px, int py, int color)
{
	image[(py-1)*w+px] = color;
}

int TImage::getpoint(int px, int py)
{
	return image[(py-1)*w+px-1];
}

void TImage::load(char* file)
{

	FILE *fp;
	fp = fopen(file,"r");
	char c[100];

	fgets(c,sizeof(c),fp);
	fgets(c,sizeof(c),fp);
	if(c[0]!='#')
		sscanf(c,"%d%d",&w,&h);
	else
		fscanf(fp, "%d%d", &w, &h);
	fscanf(fp, "%d", &max);
	image = (int*)malloc(sizeof(int)*(w*h));

	int i = 0;
	while(fscanf(fp, "%d", &image[i]) != EOF) i++;
	
	fclose(fp);
}

void TImage::save(char* file)
{
	FILE *fp;
	fp = fopen(file,"w");

	fprintf(fp, "P2\n%d %d\n%d\n", w, h, max);
	for(int i=0;i<h;i++)
	{
		for(int j=0;j<w;j++)
		{
			fprintf(fp,"%d",image[w*i+j]);
			if(j!=(w-1))fprintf(fp," ");
		}
		if(i!=(h-1)) fprintf(fp,"\n");
	}
	fclose(fp);
}
