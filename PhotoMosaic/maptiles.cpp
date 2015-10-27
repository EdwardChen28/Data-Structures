/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */
	 			
#include <iostream>
#include <map>
#include "maptiles.h"

using namespace std;

MosaicCanvas * mapTiles(SourceImage const & theSource, vector<TileImage> const & theTiles)
{
	int row = theSource.getRows();
	int column = theSource.getColumns();
	//create a vector of point in 3D(red,green,blue)
	vector< Point<3> > pts;
	//create a map which with point as key and tileImage as value
	map< Point<3>, TileImage> m;
	//loop the tileimage to add points and key&value into vector and map
	for(int i =0 ; i< theTiles.size(); i++){
		RGBAPixel pixel = theTiles[i].getAverageColor();
		Point<3> p(pixel.red,pixel.green, pixel.blue);
		pts.push_back(p);
		m[p] = theTiles[i];
	}
		
	//create a KDTree in 3 dimension
	KDTree<3> tree(pts);
	// initialize a pointer of mosaicCanvas
	MosaicCanvas *result = new MosaicCanvas(row, column);
	//loop every coordinate in the thesource
	
	for( int i = 0; i < row; i++){
		for( int j =0; j < column; j++){
			RGBAPixel tempPixel = theSource.getRegionColor(i,j);
			Point<3> tempPoint(tempPixel.red,tempPixel.green,tempPixel.blue);
			//get the best match tileimage
			result->setTile(i,j,m[tree.findNearestNeighbor(tempPoint)]);
		
		}
   	}
    /**
     * @todo Implement this function!
     */
	return result;
}

