#pragma once
class myList
{
private:
	struct Element {
		std::string data;
		Element *next;
	};
	int length;
public:
	Element *head;
	myList();
	~myList();
	void insert(std::string dat);
};

