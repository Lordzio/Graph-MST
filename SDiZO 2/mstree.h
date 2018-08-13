#pragma once
struct tnode
{
	tnode * next;
	int v, weight;
};
class mstree
{
private:
	tnode ** listarr;                   
	int arrlen;                     
	int weight;
public:
	mstree(int n);
	~mstree();
	void addEdge(edge e);
	void print();
	tnode *mstree::getListarr(int n);
};

