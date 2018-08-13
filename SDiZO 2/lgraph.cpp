#include "stdafx.h"
#include "lgraph.h"


bool lgraph::BF(int v, long long *cost, int *pred, int n, int m)
{
	bool test;

	cost[v] = 0;
	for (int i = 1; i < n; i++) {
		test = true;
		for (int x = 0; x < n; x++) {
			for (listelem = listarr[x]; listelem; listelem = listelem->next) {
				if (cost[listelem->v] > cost[x] + listelem->weight) {
					test = false;
					cost[listelem->v] = cost[x] + listelem->weight;
					pred[listelem->v] = x;
				}
				if(test) return true;
			}
		}
	}

	for (int x = 0; x < n; x++) {
		for (listelem = listarr[x]; listelem; listelem->next) {
			if (cost[listelem->v] > cost[x] + listelem->weight) return false;
		}
	}
	
}

lgraph::lgraph(int n)
{

	listarr = new(std::nothrow)slist *[n]; // Tworzymy tablicê list s¹siedztwa

	for (int i = 0; i < n; i++) listarr[i] = NULL;
}


lgraph::~lgraph()
{
	for (int i = 0; i < sizeof(listarr); i++) delete listarr[i];
	delete[] listarr;
}

void lgraph::createFfile(int n, int m) {
	std::fstream file;
	file.open("graf.txt");
	std::string line;
	int v1, v2, weight;

	std::getline(file, line);


	for (int i = 0; i < m; i++)
	{
		std::getline(file, line);
		v1 = stoi(line.substr(0, line.find(" ")));

		std::string s = line.substr(line.find(" ") + 1);
		v2 = stoi(s.substr(0, s.find(" ")));

		s = s.substr(s.find(" ") + 1);
		weight = stoi(s.substr(0, s.find(" ")));

		listelem = new(std::nothrow)slist;    // Tworzymy nowy element
		listelem->v = v2;          // Numerujemy go jako v2
		listelem->weight = weight; // Dodajemy wagê krawêdzi
		listelem->next = listarr[v1];    // Dodajemy go na pocz¹tek listy A[v1]
		listarr[v1] = listelem;
	}
	file.close();
}

void lgraph::display(int n){
	for (int i = 0; i < n; i++)
	{
		std::cout << "A[" << i << "] =";
		listelem = listarr[i];
		while (listelem)
		{
			std::cout << std::setw(3) << listelem->v << ":" << listelem->weight;
			listelem = listelem->next;
		}
		std::cout << std::endl;
	}

}

void lgraph::remove(int n){
	for (int i = 0; i < n; i++)
	{
		listelem = listarr[i];
		while (listelem)
		{
			buff = listelem;
			listelem = listelem->next;
			delete buff;
		}
	}
	delete[] listarr;
}

void lgraph::krusk(int n, int m){
	edge e;

	dsstruct z(n);
	queue q(m);
	mstree t(n);

	for (int i = 0; i < n; i++) z.makeSet(i);

	for (int i = 0; i < n; i++) {
		listelem = listarr[i];
		while (listelem) {
			e.v1 = i;
			e.v2 = listelem->v;
			e.weight = listelem->weight;
			q.push(e);
			listelem = listelem->next;
		}
	}

	for (int i = 1; i < n; i++) {
		do {
			e = q.front();
			q.pop();
		} while (z.findSet(e.v1) == z.findSet(e.v2));
		t.addEdge(e);
		z.unionSets(e);
	}

	t.print();
	
}

void lgraph::prim(int n, int m){
	edge e;
	tnode * elem;
	int i, v;


	queue q(m);                     // Kolejka priorytetowa oparta na kopcu
	mstree t(n);                    // Minimalne drzewo rozpinaj¹ce
	mstree g(n);                    // Graf
	bool * visited = new bool[n];

	for (i = 0; i < n; i++)
		visited[i] = false;           // Inicjujemy tablicê odwiedzin

	for (int i = 0; i < n; i++) {
		listelem = listarr[i];
		while (listelem) {
			e.v1 = i;
			e.v2 = listelem->v;
			e.weight = listelem->weight;
			g.addEdge(e);
			listelem = listelem->next;
		}
	}

	// Tworzymy minimalne drzewo rozpinaj¹ce

	v = 0;                          // Wierzcho³ek startowy
	visited[v] = true;              // Oznaczamy go jako odwiedzonego

	for (i = 1; i < n; i++)          // Do drzewa dodamy n - 1 krawêdzi grafu
	{
		for (elem = g.getListarr(v); elem; elem = elem->next) // Przegl¹damy listê s¹siadów
			if (!visited[elem->v])          // Jeœli s¹siad jest nieodwiedzony,
			{
				e.v1 = v;                 // to tworzymy krawêdŸ
				e.v2 = elem->v;
				e.weight = elem->weight;
				q.push(e);                // Dodajemy j¹ do kolejki priorytetowej
			}

		do
		{
			e = q.front();              // Pobieramy krawêdŸ z kolejki
			q.pop();
		} while (visited[e.v2]);       // KrawêdŸ prowadzi poza drzewo?

		t.addEdge(e);                 // Dodajemy krawêdŸ do drzewa rozpinaj¹cego
		visited[e.v2] = true;         // Oznaczamy drugi wierzcho³ek jako odwiedzony
		v = e.v2;
	}

	// Wyœwietlamy wyniki

	t.print();
}

void lgraph::dijk(int n, int m){
	bool *qs;
	int *cost, *pred, *stack, stackptr;
	int v;

	cost = new(std::nothrow)int[n];
	pred = new(std::nothrow)int[n];
	qs = new(std::nothrow)bool[n];
	stack = new(std::nothrow)int[n];
	stackptr = 0;

	for (int i = 0; i < n; i++) {
		cost[i] = INT32_MAX;
		pred[i] = -1;
		qs[i] = false;
	}

	std::cout << "Podaj wierzcholek startowy: " << std::endl;
	std::cin >> v;

	std::chrono::time_point<std::chrono::system_clock>start, end;
	start = std::chrono::system_clock::now();
	cost[v] = 0;

	for (int i = 0; i < n; i++)
	{
		// Szukamy wierzcho³ka w Q o najmniejszym koszcie d
		int j, u;
		for (j = 0; qs[j]; j++);
		for (u = j++; j < n; j++)
			if (!qs[j] && (cost[j] < cost[u])) u = j;

		// Znaleziony wierzcho³ek przenosimy do S

		qs[u] = true;

		// Modyfikujemy odpowiednio wszystkich s¹siadów u, którzy s¹ w Q

		for (listelem = listarr[u]; listelem; listelem = listelem->next)
			if (!qs[listelem->v] && (cost[listelem->v] > cost[u] + listelem->weight))
			{
				cost[listelem->v] = cost[u] + listelem->weight;
				pred[listelem->v] = u;
			}
	}

	for (int i = 0; i < n; i++)
	{
		std::cout << i << ": ";

		// Œcie¿kê przechodzimy od koñca ku pocz¹tkowi,
		// Zapisuj¹c na stosie kolejne wierzcho³ki

		for (int j = i; j > -1; j = pred[j]) stack[stackptr++] = j;

		// Wyœwietlamy œcie¿kê, pobieraj¹c wierzcho³ki ze stosu

		while (stackptr) std::cout << stack[--stackptr] << " ";

		// Na koñcu œcie¿ki wypisujemy jej koszt
		if (cost[i] == INT32_MAX || cost[i] == -(INT32_MAX)) {
			std::cout << "Nie ma drogi" << std::endl;
		}
		else { std::cout << "$" << cost[i] << std::endl; }
	}

	// Usuwamy tablice dynamiczne

	delete[] cost;
	delete[] pred;
	delete[] qs;
	delete[] stack;

	end = std::chrono::system_clock::now();
	std::chrono::duration<double> seconds = end - start;
	std::cout << "\nLista sasiedztw - czas: " << seconds.count() << "s\n";

}

void lgraph::bell(int n, int m){

	long long *cost;
	int *pred, v, *stack, stackptr;

	std::cout << "Podaj wierzcholek startowy" << std::endl;
	std::cin >> v;
	std::chrono::time_point<std::chrono::system_clock>start, end;
	start = std::chrono::system_clock::now();

	cost = new(std::nothrow)long long[n];
	pred = new(std::nothrow)int[n];
	for (int i = 0; i < n; i++) {
		cost[i] = INT32_MAX;
		pred[i] = -1;
	}

	if (BF(v, cost, pred, n, m)) {
		stack = new(std::nothrow)int[n];
		stackptr = 0;

		for (int i = 0; i < n; i++)
		{
			std::cout << i << ": ";
			for (int x = i; x != -1; x = pred[x]) // Wierzcho³ki œcie¿ki umieszczamy na stosie
				stack[stackptr++] = x;            // w kolejnoœci od ostatniego do pierwszego

			while (stackptr)                 // Wierzcho³ki ze stosu drukujemy
				std::cout << stack[--stackptr] << " "; // w kolejnoœci od pierwszego do ostatniego

			std::cout << "$" << cost[i] << std::endl; // Na koñcu wyœwietlamy koszt
		}
		delete[] stack;                  // Usuwamy stos
	}
	else std::cout << "Negative Cycle found!" << std::endl;

	delete[] cost;
	delete[] pred;

	end = std::chrono::system_clock::now();
	std::chrono::duration<double> seconds = end - start;
	std::cout << "\nLista sasiedztw - czas: " << seconds.count() << "s\n";
}

