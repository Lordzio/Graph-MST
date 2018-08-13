#pragma once
struct edge
{
	int v1, v2, weight;
};
class queue
{
private:
	edge *Heap;
	int hpos;
public:
	queue(int n);
	~queue();
	edge front();
	void push(edge e);
	void pop();
};

