#include "stdafx.h"
#include "dsstruct.h"


dsstruct::dsstruct(int n)
{
	Z = new dsnode[n];
}


dsstruct::~dsstruct()
{
	delete[] Z;
}

void dsstruct::makeSet(int v) {
	Z[v].up = v;
	Z[v].rank = 0;
}

int dsstruct::findSet(int v) {
	if (Z[v].up != v) Z[v].up = findSet(Z[v].up);
	return Z[v].up;
}

void dsstruct::unionSets(edge e) {
	int ru, rv;

	ru = findSet(e.v1);             // Wyznaczamy korzeñ drzewa z wêz³em u
	rv = findSet(e.v2);             // Wyznaczamy korzeñ drzewa z wêz³em v
	if (ru != rv)                    
	{
		if (Z[ru].rank > Z[rv].rank)   // Porównujemy rangi drzew
			Z[rv].up = ru;              // ru wiêksze, do³¹czamy rv
		else
		{
			Z[ru].up = rv;              // równe lub rv wiêksze, do³¹czamy ru
			if (Z[ru].rank == Z[rv].rank) Z[rv].rank++;
		}
	}

}