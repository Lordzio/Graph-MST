#include "stdafx.h"
#include "mstree.h"


mstree::mstree(int n)
{
	int i;

	listarr = new tnode *[n];            // Tworzymy tablic� dynamiczn�
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
			buff = element;                      // Zapami�tujemy wskazanie
			element = element->next;                // Przesuwamy si� do nast�pnego elementu listy
			delete buff;                   // Usuwamy element
		}
	}

	delete[] listarr;
}

void mstree::addEdge(edge e) {
	tnode *elem;

	weight += e.weight;             // Do wagi drzewa dodajemy wag� kraw�dzi
	elem = new tnode;                  // Tworzymy nowy w�ze�
	elem->v = e.v2;                    // Wierzcho�ek ko�cowy
	elem->weight = e.weight;           // Waga kraw�dzi
	elem->next = listarr[e.v1];              // Dodajemy p do listy wierzcho�ka v1
	listarr[e.v1] = elem;

	elem = new tnode;                  // To samo dla kraw�dzi odwrotnej
	elem->v = e.v1;                    // Wierzcho�ek ko�cowy
	elem->weight = e.weight;           // Waga kraw�dzi
	elem->next = listarr[e.v2];              // Dodajemy p do listy wierzcho�ka v2
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

