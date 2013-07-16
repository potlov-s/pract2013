#include "timage.h"
#include <iostream> 
#include <string>

TImage::TImage(void)
{
	w = 0;
	h = 0;
	image = NULL;
}


TImage::~TImage(void)
{

}

void TImage::setpoint(int px, int py, int color)
{
	image[(py-1)*w+px-1] = color;
}

int TImage::getpoint(int px, int py)
{
	if(px<1) px=1;
	if(py<1) py=1;
	if(px>w) px=w;
	if(py>h) py=h;
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

void TImage::copy(TImage *p)
{
	if(image!=NULL) free(image);
	w = p->w;
	h = p->h;
	image = (int*)malloc(sizeof(int)*(w*h));
	for(int i=0;i<w*h;i++)
		image[i] = p->image[i];
	max = p->max;
}

void TImage::filterSobel()
{
	int z[3][3];
	int Gx,Gy,G;
	int Wx[3][3] = {{-1,-2,-1},{0,0,0},{1,2,1}};
	int Wy[3][3] = {{-1,0,1},{-2,0,2},{-1,0,1}};

	int *buf;
	buf = (int*)malloc(sizeof(int)*(w*h));

	for(int y=1;y<=h;y++)
	{
		for(int x=1;x<=w;x++)
		{
			z[0][0] = getpoint(x-1,y-1);
			z[0][1] = getpoint(x,y-1);
			z[0][2] = getpoint(x+1,y-1);
			z[1][0] = getpoint(x-1,y);
			z[1][1] = getpoint(x,y);
			z[1][2] = getpoint(x+1,y);
			z[2][0] = getpoint(x-1,y+1);
			z[2][1] = getpoint(x,y+1);
			z[2][2] = getpoint(x+1,y+1);
			Gx = 0;
			Gy = 0;
			for(int i=0;i<3;i++)
				for(int j=0;j<3;j++)
				{
					Gx += Wx[i][j] * z[i][j];
					Gy += Wy[i][j] * z[i][j];
				}

			G=sqrt(abs(Gx*Gx+Gy*Gy));
			if(G>max) G=max;
			//if(G<max*0.2) G=0;

			buf[(y-1)*w+x-1] = G;
		}
	}
	for(int y=1;y<=h;y++)
		for(int x=1;x<=w;x++)
			image[(y-1)*w+x-1] = buf[(y-1)*w+x-1];
}