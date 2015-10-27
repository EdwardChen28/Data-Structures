#ifndef DSETS_H
#define DSETS_H

#include <vector>

class DisjointSets{
	public:
		void addelements(int num);
		int find(int elem);
		void setunion(int a, int b);

	private:
		std:: vector< int > set;
};

#endif
