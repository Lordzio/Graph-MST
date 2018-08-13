#pragma once
struct slist
{
	slist * next;
	int v, weight;
};
class lgraph
{private:
	slist **listarr;
	slist *listelem, *buff;

	bool BF(int v, long long *cost, int *pred, int n, int m);
public:
	lgraph(int n);
	~lgraph();
	void createFfile(int n, int m);
	void display(int n);
	void remove(int n);
	void krusk(int n, int m);
	void prim(int n, int m);
	void dijk(int n, int m);
	void bell(int n, int m);
};

