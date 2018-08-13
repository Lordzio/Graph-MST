#pragma once
class mgraph
{private:
	int **matrix;
	bool BF(int v, long long *cost, int *pred, int n, int m, slist **listarr);
public:
	mgraph(int n, int m);
	~mgraph();
	void createFfile(int m);
	void display(int m, int n);
	void remove(int n);
	void krusk(int n, int m);
	void prim(int n, int m);
	void dijk(int n, int m);
	void bell(int n, int m);
};

