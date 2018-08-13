#include "stdafx.h"
#include "mstree.h"


mstree::mstree(int n)
{
	int i;

	listarr = new tnode *[n];            // Tworzymy tablicê dynamiczn¹
	for (i = 0; i < n; i++) listarr[i] = NULL; 
	arrlen = n - 1;                   
	weight = 0;
}


mstree::~mstree()
{
	int i;
	tnode *element, *buff;

	for (i = 0; i <= arrlen; i++)
	{
		element = listarr[i];
		while (element)
		{
			buff = element;                      // Zapamiêtujemy wskazanie
			element = element->next;                // Przesuwamy siê do nastêpnego elementu listy
			delete buff;                   // Usuwamy element
		}
	}

	delete[] listarr;
}

void mstree::addEdge(edge e) {
	tnode *elem;

	weight += e.weight;             // Do wagi drzewa dodajemy wagê krawêdzi
	elem = new tnode;                  // Tworzymy nowy wêze³
	elem->v = e.v2;                    // Wierzcho³ek koñcowy
	elem->weight = e.weight;           // Waga krawêdzi
	elem->next = listarr[e.v1];              // Dodajemy p do listy wierzcho³ka v1
	listarr[e.v1] = elem;

	elem = new tnode;                  // To samo dla krawêdzi odwrotnej
	elem->v = e.v1;                    // Wierzcho³ek koñcowy
	elem->weight = e.weight;           // Waga krawêdzi
	elem->next = listarr[e.v2];              // Dodajemy p do listy wierzcho³ka v2
	listarr[e.v2] = elem;
}

void mstree::print() {
	int i;
	tnode *elem;

	std::cout << std::endl;
	for (i = 0; i <= arrlen; i++)
	{
		std::cout << "Wierzcholek " << i << " - ";
		for (elem = listarr[i]; elem; elem = elem->next) std::cout << elem->v << ":" << elem->weight << " ";
		std::cout << std::endl;
	}
	std::cout << std::endl << std::endl << "Waga MST = " << weight << std::endl << std::endl;
}

tnode *mstree::getListarr(int n){
	return listarr[n];
}

