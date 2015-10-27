// **************************************************************
// *		   
// *  quadtree.cpp
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************
#include <iostream>
using namespace std;
#include "quadtree.h"

//default contructor which produce a NULL root
Quadtree::Quadtree()	
{
	root=NULL;
	resoln = 0;
}

Quadtree::Quadtree(const PNG & source, int resolution)
{
	resoln = resolution;
	buildTree (source, resolution);
}

//copy contructor
Quadtree::Quadtree(Quadtree const & other)
{
	
	copy(other);
	resoln = other.resoln;
}
void Quadtree::copy(Quadtree const & other)
{
	resoln = other.resoln;
	copy(root, other.root);
}

//helpe function using preorder traversal 
void Quadtree::copy(QuadtreeNode * &subroot, QuadtreeNode * const &otherRoot)
{
	
	if(otherRoot != NULL){							//check condition before recusive
		subroot = new QuadtreeNode();					// create a new QuadtreeNode
		subroot->element = otherRoot->element;			// copy the pixel value over to a new node
		copy(subroot->nwChild, otherRoot->nwChild);	//recusive calls for the four children
		copy(subroot->neChild, otherRoot->neChild);
		copy(subroot->swChild, otherRoot->swChild);
		copy(subroot->seChild, otherRoot->seChild);
	}
}

//destructor
Quadtree::~Quadtree()
{
	clear();
}
void Quadtree::clear()
{
	clear(root);
}

//helper function,using postOrder to clear all the dynamic memory in the Quadtree.
void Quadtree:: clear(QuadtreeNode* &subroot)
{
	if(subroot!=NULL){
		clear(subroot->nwChild);		//recusive calls
		clear(subroot->neChild);
		clear(subroot->swChild);
		clear(subroot->seChild);
		delete subroot;				//free the dynamic memory
		subroot=NULL;
		}
}
//operator =
Quadtree Quadtree:: operator=(Quadtree const & other)
{
	clear();
	copy(other);
	return *(this);
}



void Quadtree::buildTree(PNG const & source, int resolution)
{
	
	buildTreeRe(root, 0, 0, source, resolution);
	 resoln = resolution;
}
//helper
void Quadtree:: buildTreeRe(QuadtreeNode * & subroot,int x, int y,  PNG const & source , int resolution)
{
	subroot = new QuadtreeNode();
	if( resolution == 1){
		subroot->element= *source(x,y);
		return;
	}
	
	buildTreeRe(subroot->nwChild, x, y, source, resolution/2);
	buildTreeRe(subroot->neChild, x+(resolution/2), y, source, resolution/2);
	buildTreeRe(subroot->swChild, x, y +(resolution/2),source, resolution/2); 
	buildTreeRe(subroot->seChild, x+(resolution/2), y+(resolution/2), source, resolution/2);
	int nwRed = (subroot->nwChild->element).red;
	int nwGreen = (subroot->nwChild->element).green;
	int nwBlue = (subroot->nwChild->element).blue;
	int neRed = (subroot->neChild->element).red;
	int neGreen = (subroot->neChild->element).green;
	int neBlue = (subroot->neChild->element).blue;
	int swRed = (subroot->swChild->element).red;
	int swGreen = (subroot->swChild->element).green;
	int swBlue = (subroot->swChild->element).blue;
	int seRed = (subroot->seChild->element).red;
	int seGreen =(subroot->seChild->element).green;
	int seBlue = (subroot->seChild->element).blue;
	(subroot->element).red = (nwRed+neRed+swRed+seRed)/4;
	(subroot->element).green = (nwGreen+neGreen+swGreen+seGreen)/4;
	(subroot->element).blue = (nwBlue+neBlue+swBlue+seBlue)/4;
}

RGBAPixel Quadtree:: getPixel(int x, int y) const
{
	return getPixelRe( x, y, root, resoln);
}

RGBAPixel Quadtree:: getPixelRe(int x, int y, QuadtreeNode * subroot, int resolution) const
{
	RGBAPixel result = RGBAPixel() ;
	if( x >= resolution || y >= resolution || x < 0 || y < 0|| subroot==NULL || resolution ==0) return result;
	
	else if( resolution == 1 || (subroot->nwChild==NULL&& subroot->neChild==NULL && subroot->swChild==NULL && subroot->seChild == NULL))
	 	return subroot->element;
		
	else{
		if(x < resolution/2 && y < resolution /2)
			return getPixelRe( x, y, subroot->nwChild, resolution/2);
		
		else if(x < resolution/2 && y >=resolution/2)
			return getPixelRe( x, y-(resolution/2), subroot->swChild, resolution/2);
				
		else if( x >= resolution/2 && y < resolution/2)
			return getPixelRe( x-(resolution/2), y, subroot->neChild, resolution/2);
			
		else	return getPixelRe( x-(resolution/2), y-(resolution/2), subroot->seChild, resolution/2);
	}
	
	return result;
}

PNG Quadtree:: decompress() const
{

	PNG result(resoln, resoln);
	decompress(result, root, resoln, 0,0);
	return result;
	/*if( root == NULL) return result;
	for( int i = 0; i < resoln; i++){
		for( int j = 0; j<resoln; j++){
			*(result(i,j)) = getPixel(i,j);
		}
	}
	return result;	*/ 

}

void Quadtree:: decompress(PNG & img, QuadtreeNode * subroot, int res, int x, int y)const{
	if(subroot == NULL) return;
	if(subroot->nwChild==NULL &&subroot->neChild==NULL && subroot->swChild==NULL && subroot->seChild==NULL){
		for(int i = 0; i<res; i++){
			for(int j =0; j<res; j++){
				*(img(x+i,y+j)) = subroot->element;
				}
			}
			return;
	}
		decompress(img,subroot->nwChild, res/2, x, y);
		decompress(img,subroot->neChild, res/2, x+res/2, y);
		decompress(img,subroot->swChild, res/2, x , y+res/2);
		decompress(img,subroot->seChild, res/2, x+res/2, y+res/2);
		
}		


void Quadtree::clockwiseRotate()
{
	clockwiseRotate(root);
	//code here
}
void Quadtree::clockwiseRotate(QuadtreeNode * subroot)
{
	if(subroot != NULL ){
		QuadtreeNode* temp = subroot->nwChild;
		subroot->nwChild = subroot->swChild;
		subroot->swChild = subroot->seChild;
		subroot->seChild = subroot->neChild;
		subroot->neChild = temp;
		clockwiseRotate(subroot->nwChild);
		clockwiseRotate(subroot->neChild);
		clockwiseRotate(subroot->swChild);
		clockwiseRotate(subroot->seChild);
	}	
}

void Quadtree::prune(int tolerance)
{
	prune(root, tolerance);
	//code here
}
//prune helper function
void Quadtree::prune(QuadtreeNode* &subroot, int tolerance)
{
	if( subroot != NULL){
		if(pruneCheck(subroot, subroot, tolerance)){
			clear(subroot->nwChild);
			clear(subroot->neChild);
			clear(subroot->swChild);
			clear(subroot->seChild);
		}
		prune(subroot->nwChild, tolerance);
		prune(subroot->neChild, tolerance);
		prune(subroot->swChild, tolerance);
		prune(subroot->seChild, tolerance);
	}	

}
bool Quadtree::pruneCheck(QuadtreeNode* &node, QuadtreeNode * &subroot, int tolerance)
{
	if(node == NULL) return false;
	if(subroot->nwChild==NULL && subroot->neChild==NULL&& subroot->swChild==NULL&& subroot->seChild==NULL){
		int difR = node->element.red - subroot->element.red;
		int difG = node->element.green - subroot->element.green;
		int difB = node->element.blue - subroot->element.blue;
		return ( (difR*difR + difG*difG + difB*difB)<=tolerance);
	}
	return pruneCheck(node, subroot->nwChild, tolerance)&&
		   pruneCheck(node, subroot->neChild, tolerance)&&
		   pruneCheck(node, subroot->swChild, tolerance)&&
		   pruneCheck(node, subroot->seChild, tolerance);

}

int Quadtree::pruneSize(int tolerance) const
{
	
	return pruneSize(root,tolerance);
}
int Quadtree::pruneSize(QuadtreeNode * subroot, int tolerance)const
{
	if(subroot == NULL) return 0;
	if(pruneSizeCheck(subroot,subroot,tolerance))
		return 1;
	return pruneSize(subroot->nwChild, tolerance)+
			pruneSize(subroot->neChild, tolerance)+
			pruneSize(subroot->swChild, tolerance)+
			pruneSize(subroot->seChild, tolerance);
			
}
		

bool Quadtree::pruneSizeCheck(QuadtreeNode* node, QuadtreeNode * subroot, int tolerance) const
{
	if(node == NULL) return false;
	if(subroot->nwChild==NULL && subroot->neChild==NULL&& subroot->swChild==NULL&& subroot->seChild==NULL){
		int difR = node->element.red - subroot->element.red;
		int difG = node->element.green - subroot->element.green;
		int difB = node->element.blue - subroot->element.blue;
		return ( (difR*difR + difG*difG + difB*difB)<=tolerance);
	}
	return pruneSizeCheck(node, subroot->nwChild, tolerance)&&
		   pruneSizeCheck(node, subroot->neChild, tolerance)&&
		   pruneSizeCheck(node, subroot->swChild, tolerance)&&
		   pruneSizeCheck(node, subroot->seChild, tolerance);

}

int Quadtree::idealPrune(int numLeaves) const
{

	if(root == NULL || numLeaves>(resoln*resoln)) return 0;
	
	int num = idealPrune(numLeaves, 0 , 195075);
	while(pruneSize(num) == numLeaves){
		num --;
	}
	return num+1;
//	return idealPrune(numLeaves, 0, 3*225*225);
}

int Quadtree::idealPrune(int numLeaves, int min, int max)const
{	if(min>=max)
		return min;
	
	int mid = (min+max)/2;
	int num = pruneSize(mid);
	if(num == numLeaves)
		return mid;
	if(num <= numLeaves)
		 return idealPrune(numLeaves, min, mid);
	else return idealPrune(numLeaves, mid+1,max);
}
