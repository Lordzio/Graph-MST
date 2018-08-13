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

	ru = findSet(e.v1);             // Wyznaczamy korze� drzewa z w�z�em u
	rv = findSet(e.v2);             // Wyznaczamy korze� drzewa z w�z�em v
	if (ru != rv)                    
	{
		if (Z[ru].rank > Z[rv].rank)   // Por�wnujemy rangi drzew
			Z[rv].up = ru;              // ru wi�ksze, do��czamy rv
		else
		{
			Z[ru].up = rv;              // r�wne lub rv wi�ksze, do��czamy ru
			if (Z[ru].rank == Z[rv].rank) Z[rv].rank++;
		}
	}

}