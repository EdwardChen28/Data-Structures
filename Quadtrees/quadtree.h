// **************************************************************
// *		   
// *  quadtree.h
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"

class Quadtree
{
	public:
		Quadtree();
		Quadtree(const PNG & source, int resolution);
		Quadtree(Quadtree const & other);
		~Quadtree();
		Quadtree operator=(Quadtree const & other);
		void buildTree(PNG const & source, int resolution);
		RGBAPixel getPixel(int x, int y ) const;
		PNG decompress()const;
		void clockwiseRotate();
		void prune(int tolerance);
		int pruneSize(int tolerance) const;
		int idealPrune(int numLeaves) const;
	private:

	// A simple class representing a single node of a Quadtree.
	// You may want to add to this class; in particular, it could probably
	// use a constructor or two...
	class QuadtreeNode
	{
		public:
		QuadtreeNode* nwChild;  // pointer to northwest child
		QuadtreeNode* neChild;  // pointer to northeast child
		QuadtreeNode* swChild;  // pointer to southwest child
		QuadtreeNode* seChild;  // pointer to southeast child

		RGBAPixel element;  // the pixel stored as this node's "data"
		QuadtreeNode(){
			nwChild = NULL;
			neChild = NULL;
			swChild = NULL;
			seChild = NULL;
			}
	};
	
	QuadtreeNode* root;    // pointer to root of quadtree
	//helper function
	int resoln;
	void copy(Quadtree const & other);
	void copy(QuadtreeNode * &root, QuadtreeNode * const &otherRoot);
	void clear();
	void clear(QuadtreeNode* &subroot);
	void buildTreeRe(QuadtreeNode * &root,int x, int y,  PNG const & source , int resolution);
	RGBAPixel getPixelRe(int x, int y, QuadtreeNode * root, int resolution) const;
	void clockwiseRotate(QuadtreeNode * subroot);
	void prune(QuadtreeNode* &subroot, int tolerance);
	bool pruneCheck(QuadtreeNode* &node, QuadtreeNode * &subroot, int tolerance);
	int pruneSize(QuadtreeNode * subroot, int tolerance)const;
	bool pruneSizeCheck(QuadtreeNode* node, QuadtreeNode * subroot, int tolerance) const;
	int idealPrune(int numLeaves, int min, int max)const;
	void  decompress(PNG & img, QuadtreeNode * subroot, int res, int x, int y)const;
	/**** Functions added for testing/grading                ****/
	/**** Do not remove this line or copy its contents here! ****/
	#include "quadtree_given.h"
};

#endif
