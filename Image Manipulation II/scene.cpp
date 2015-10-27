#include "scene.h"
#include <iostream>
#include "image.h"
#include "png.h"
using namespace std;

Scene::Scene(int max)
{
	imgptr = new Image*[max];
	for(int i =0; i < max; i++){
		imgptr[i]=NULL;
	}
	xc=new int[max];
	yc=new int[max];
	maxnum = max;
	
	
}

void Scene:: copy(const Scene & source )
{
	maxnum = source.maxnum;
	imgptr = new Image*[maxnum];
	for(int i=0; i< maxnum; i++) imgptr[i] = NULL;
	xc = new int[maxnum];
	yc = new int[maxnum];
	for( int i =0; i< maxnum; i++)
	{	
		if( source.imgptr[i]!=NULL){
		imgptr[i] = new Image;
		*imgptr[i]=*(source.imgptr[i]);
		xc[i] = source.xc[i];
		yc[i] = source.yc[i];}
	}
}	

void Scene:: clear(){
	for(int i =0; i < maxnum; i++){
		if(imgptr[i] != NULL){
			delete imgptr[i];
			imgptr[i]=NULL;
		}
	}
	delete [] imgptr;
	imgptr=NULL;
	delete [] xc;
	xc=NULL;
	delete [] yc;
	yc=NULL;
}

Scene::Scene(const Scene & source)
{
	copy(source);	
}

Scene :: ~Scene(){
	clear();
}



const Scene & Scene::operator = (const Scene & source)
{
	if(this != &source)
	{
		clear();
		copy(source);
	}
	return *this;
}

void Scene::changemaxlayers(int newmax)
{
	
	
	if(newmax > maxnum) cout<<"incalid newmax"<<endl;

	else {
		Image **newimgptr;
		newimgptr = imgptr;
		imgptr = new Image*[newmax];
		for(int i =0 ; i < newmax; i++)
		{
			imgptr[i] = new Image;
			imgptr[i]=newimgptr[i];
		}
		delete [] newimgptr;
	}

	

}

void Scene::addpicture(const char* FileName, int index , int x, int y)
{
	if(index <0 || index >= maxnum) cout << "index out of bounds" << endl;
	else{
		xc[index] = x;
		yc[index] = y;
		imgptr[index]=new Image;
		(*imgptr[index]).readFromFile(FileName);
	
	}
	
}

void Scene:: changelayer(int index, int newindex)
{
	if(index<0 || index>=maxnum || newindex < 0 || newindex>=maxnum)
		cout << "invaild index" << endl;
	
	else if( index == newindex) return;
	
	else {
		if(imgptr[newindex] !=NULL){
		delete imgptr[newindex];}
		imgptr[newindex] =imgptr[index];
		imgptr[index]=NULL;
		xc[newindex]=xc[index];
		yc[newindex]=yc[index];
		
	}
	
}

void Scene:: translate(int index, int xcoord , int ycoord)
{
	if(index>maxnum-1 || index <0 || imgptr[index]==NULL) cout << "invalid index" << endl;
	else {
		xc[index]=xcoord;
		yc[index]=ycoord;
	}

}

void Scene::deletepicture(int index)
{
	if(index>maxnum-1 || index < 0 || imgptr[index]==NULL) cout << "invalid index" << endl;
	else{
		delete imgptr[index];
		imgptr[index]=NULL;
		
	}
}


Image * Scene::getpicture(int index)const
{
	if(index>maxnum-1 || index <0 || imgptr[index]==NULL) 
	{
	cout << "invalid index" << endl;
	return NULL;
	}
	return imgptr[index];

}

Image Scene::drawscene()const
{
	int width = 0;
	int height = 0;
	for(int i = 0; i < maxnum; i++)
	{
		if(imgptr[i] != NULL){
		int a = xc[i]+ imgptr[i]->width();
		int b = yc[i]+ imgptr[i]->height();
		if(a > width) width = a;
		if(b > height) height = b;}
	}

	Image newimage;
	newimage.resize(width,height);
	for(int i=0; i<maxnum; i++){
		if(imgptr[i]!=NULL){
			int w = imgptr[i]->width();
			int h = imgptr[i]->height();
			for(int j =0; j < w;j++){
				for(int k = 0 ; k < h; k++){
					*(newimage(j+xc[i],k+yc[i])) = *((*imgptr[i])(j,k));
				}	
			}
		}
	}
	return newimage;
}


