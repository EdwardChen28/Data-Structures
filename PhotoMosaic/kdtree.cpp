/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */
#include<math.h>

template<int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim> & first, const Point<Dim> & second, int curDim) const
{

	if( first[curDim] == second[curDim])
		return first < second;
	else return first[curDim] < second[curDim];
    /**
     * @todo Implement this function!
     */
    //return false
}


template<int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim> & target, const Point<Dim> & currentBest, const Point<Dim> & potential) const
{
	int squareSumCurr=0;
	int squareSumPot=0;
	/*for(int i = 0; i< Dim; i++){
		squareSumCurr += (target[i] - currentBest[i])*(target[i] - currentBest[i]);
		squareSumPot += (target[i] - potential[i])*(target[i] - potential[i]);
    }*/
    squareSumCurr = squareDistance(target, currentBest);
    squareSumPot = squareDistance(target, potential);
    //if they are tie, based on operator < , in this case is false
    if(squareSumCurr == squareSumPot) 
    	return potential < currentBest;
    return squareSumPot < squareSumCurr;
    /**
     * @todo Implement this function!
     */
    
}

template<int Dim>
KDTree<Dim>::KDTree(const vector< Point<Dim> > & newPoints)
{
	if (newPoints.size() == 0) return ;
	
	for(int i = 0; i<newPoints.size(); i++)
		points.push_back(newPoints[i]);

	KDTreeHelper(0, points.size()-1 ,0);

		
    /**
     * @todo Implement this function!
     */
}
template<int Dim>
void KDTree<Dim>::KDTreeHelper( int  lo, int  hi, int  dim){
	
	if(lo >= hi) return;
	int mid = (lo+hi)/2;
	dim = dim%Dim;
	selection(lo, hi, mid, dim);
	KDTreeHelper(lo, mid-1, dim+1);
	KDTreeHelper(mid+1, hi, dim+1);

}

template<int Dim>
int KDTree<Dim>:: partition( int lo, int hi, int n, int  dim){
	//int pivotVal = (lo+hi)/2;
	swap(n, hi);
	int index = lo;
	for(int i = lo; i < hi; i++){ 
		if(smallerDimVal(points[i], points[hi], dim)){
			swap(index, i);
			index++;
		}
	}
	swap(index, hi);
	return index;
}
template<int Dim>
void KDTree<Dim>::selection( int lo, int hi, int n, int dim){
	if (lo >= hi) return ;
	//int pivot = (lo+hi)/2;
	int pivot = partition( lo, hi, n , dim);
	if(n == pivot) return; 
	else if (n<pivot) return selection( lo, pivot-1, n, dim);
	else return selection( pivot+1, hi, n, dim);
}
template<int Dim>
void KDTree<Dim>::swap( int x, int y){
	Point<Dim> temp =points[x];
	points[x] = points[y];
	points[y] = temp;
}


template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> & query) const
{
	return findNearestNeighbor(query, 0, points.size()-1, 0);
    /**
     * @todo Implement this function!
     */
}
template<int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim> & query, int lo, int  hi, int  dim) const{
	if(lo >= hi ) return points[lo]; //base case
	
	int mid = (hi+lo)/2;	//calculate the minPoint index
	Point<Dim> temp;				
	Point<Dim> curr = points[mid];	
	dim = dim%Dim; 	
	int direction=0;
	if(smallerDimVal(query, points[mid], dim)){		
		direction = 0;
	 	temp = findNearestNeighbor(query, lo, mid-1, dim+1); //left half
	}
	else{
		direction =1;
		temp = findNearestNeighbor(query, mid+1, hi, dim+1);  //recusively call the function on the left half
	}
	Point<Dim> best;
	if(shouldReplace(query, temp, curr) ) best= curr;
	else best = temp;
	
	int dimD = (curr[dim] - query[dim])*(curr[dim] - query[dim]);
	int bestCurr = squareDistance(best, query);
	if(dimD > bestCurr) return best;
	else{	
		Point<Dim> t;
		if(direction == 0)	
			 t = findNearestNeighbor(query, mid+1, hi, dim+1);
		else t = findNearestNeighbor(query, lo, mid-1,dim+1);
	
		if(shouldReplace(query,t, best)) return best;
		else return t;
	}
		
}
template<int Dim>
int KDTree<Dim>::squareDistance(const Point<Dim> & first, const Point<Dim> & second) const{
	int squareSum=0;
	for(int i = 0; i< Dim; i++)
		squareSum += (first[i] - second[i])*(first[i] - second[i]);
	return squareSum;
}
