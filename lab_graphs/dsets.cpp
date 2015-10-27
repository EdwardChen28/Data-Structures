#include "dsets.h"



void DisjointSets::addelements(int num){
	for(int i = 0; i <num; i++)
		set.push_back(-1);
}

int DisjointSets::find(int elem){
	if(set[elem] < 0)
		return elem;
	return set[elem] = find(set[elem]);

}

void DisjointSets::setunion(int a, int b){
	int idxA = find(a);
	int idxB = find(b);
	int newSize = set[idxA]+set[idxB];
	if(set[idxA] <= set[idxB]){
		set[idxB] = idxA;
		set[idxA] = newSize;
	}
	else{
		set[idxA] = idxB;
		set[idxB] = newSize;
	}
		
}
