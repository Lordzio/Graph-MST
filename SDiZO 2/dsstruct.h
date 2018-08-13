#pragma once
struct dsnode
{
	int up, rank;
};
class dsstruct
{
private:
	dsnode *Z;
public:
	dsstruct(int n);
	~dsstruct();
	void makeSet(int v);
	int findSet(int v);
	void unionSets(edge e);
};

