#include "stdafx.h"
#include "mgraph.h"


bool mgraph::BF(int v, long long * cost, int * pred, int n, int m, slist ** listarr)
{
	slist *listelem;
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
				if (test) return true;
			}
		}
	}

	for (int x = 0; x < n; x++) {
		for (listelem = listarr[x]; listelem; listelem->next) {
			if (cost[listelem->v] > cost[x] + listelem->weight) return false;
		}
	}

}

mgraph::mgraph(int n, int m)
{
	matrix = new(std::nothrow)int *[n];    // Tworzymy tablic� wska�nik�w

	for (int i = 0; i < n; i++)
		matrix[i] = new(std::nothrow)int[m]; // Tworzymy wiersze
				

	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) matrix[i][j] = 0;
}


mgraph::~mgraph()
{
	for (int i = 0; i < sizeof(matrix); i++) delete matrix[i];
	delete[] matrix;
}

void mgraph::createFfile(int m){
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

			matrix[v1][i] = weight;       // Wierzcho�ek startowy
			matrix[v2][i] = -weight;      // Wierzcho�ek ko�cowy

		}
	file.close();
}

void mgraph::display(int m, int n){
	std::cout << "   ";
	for (int i = 0; i < m; i++) std::cout << std::setw(3) << i;
	std::cout << std::endl;
	for (int i = 0; i < n; i++)
	{
		std::cout << std::setw(3) << i;
		for (int j = 0; j < m; j++) std::cout << std::setw(3) << (int)matrix[i][j];
		std::cout << std::endl;
	}
}

void mgraph::remove(int n){
	for (int i = 0; i < n; i++) delete[] matrix[i];
	delete[] matrix;
}

void mgraph::krusk(int n, int m) {
	edge e;

	dsstruct z(n);
	queue q(m);
	mstree t(n);

	for (int i = 0; i < n; i++) z.makeSet(i);

	for (int j = 0; j < m; j++){
		for (int i = 0; i < n; i++){
			if (matrix[i][j] > 0) {e.v1 = i; e.weight = matrix[i][j];}
			if (matrix[i][j] < 0) e.v2 = i;
		}
		q.push(e);
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

void mgraph::prim(int n, int m) {
	edge e;
	tnode * elem;
	int i, v;


	queue q(m);                     // Kolejka priorytetowa oparta na kopcu
	mstree t(n);                    // Minimalne drzewo rozpinaj�ce
	mstree g(n);                    // Graf
	bool * visited = new bool[n];

	for (i = 0; i < n; i++)
		visited[i] = false;           // Inicjujemy tablic� odwiedzin

	for (int j = 0; j < m; j++) {
		for (int i = 0; i < n; i++) {
			if (matrix[i][j] > 0) { e.v1 = i; e.weight = matrix[i][j]; }
			if (matrix[i][j] < 0) e.v2 = i;
		}
		g.addEdge(e);
	}

	// Tworzymy minimalne drzewo rozpinaj�ce

	v = 0;                          // Wierzcho�ek startowy
	visited[v] = true;              // Oznaczamy go jako odwiedzonego

	for (i = 1; i < n; i++)          // Do drzewa dodamy n - 1 kraw�dzi grafu
	{
		for (elem = g.getListarr(v); elem; elem = elem->next) // Przegl�damy list� s�siad�w
			if (!visited[elem->v])          // Je�li s�siad jest nieodwiedzony,
			{
				e.v1 = v;                 // to tworzymy kraw�d�
				e.v2 = elem->v;
				e.weight = elem->weight;
				q.push(e);                // Dodajemy j� do kolejki priorytetowej
			}

		do
		{
			e = q.front();              // Pobieramy kraw�d� z kolejki
			q.pop();
		} while (visited[e.v2]);       // Kraw�d� prowadzi poza drzewo?

		t.addEdge(e);                 // Dodajemy kraw�d� do drzewa rozpinaj�cego
		visited[e.v2] = true;         // Oznaczamy drugi wierzcho�ek jako odwiedzony
		v = e.v2;
	}

	// Wy�wietlamy wyniki

	t.print();
}

void mgraph::dijk(int n, int m) {
	slist *listelem, *buff, **listarr;
	int v1, v2, weight, v;

	std::cout << "Podaj wierzcholek startowy: " << std::endl;
	std::cin >> v;
	std::chrono::time_point<std::chrono::system_clock>start, end;
	start = std::chrono::system_clock::now();

	listarr = new(std::nothrow)slist*[n];

	for (int i = 0; i < n; i++) {
		listarr[i] = NULL;
	}

	for (int j = 0; j < m; j++) {
		listelem = new(std::nothrow)slist;
		for (int i = 0; i < n; i++) {
			if (matrix[i][j] > 0) { v1 = i; weight = matrix[i][j]; }
			if (matrix[i][j] < 0) v2 = i;
		}
		listelem->v = v2;          // Numerujemy go jako v2
		listelem->weight = weight; // Dodajemy wag� kraw�dzi
		listelem->next = listarr[v1];    // Dodajemy go na pocz�tek listy A[v1]
		listarr[v1] = listelem;
	}

	bool *qs;
	int *cost, *pred, *stack, stackptr;

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


	cost[v] = 0;

	for (int i = 0; i < n; i++)
	{
		// Szukamy wierzcho�ka w Q o najmniejszym koszcie d
		int j, u;
		for (j = 0; qs[j]; j++);
		for (u = j++; j < n; j++)
			if (!qs[j] && (cost[j] < cost[u])) u = j;

		// Znaleziony wierzcho�ek przenosimy do S

		qs[u] = true;

		// Modyfikujemy odpowiednio wszystkich s�siad�w u, kt�rzy s� w Q

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

		// �cie�k� przechodzimy od ko�ca ku pocz�tkowi,
		// Zapisuj�c na stosie kolejne wierzcho�ki

		for (int j = i; j > -1; j = pred[j]) stack[stackptr++] = j;

		// Wy�wietlamy �cie�k�, pobieraj�c wierzcho�ki ze stosu

		while (stackptr) std::cout << stack[--stackptr] << " ";

		// Na ko�cu �cie�ki wypisujemy jej koszt
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

	end = std::chrono::system_clock::now();
	std::chrono::duration<double> seconds = end - start;
	std::cout << "\nMacierz incydencji - czas: " << seconds.count() << "s\n";

}

void mgraph::bell(int n, int m){
	long long *cost;
	int *pred, v, *stack, stackptr, v1, v2, weight;
	slist **listarr, *buff, *listelem;

	std::cout << "Podaj wierzcholek startowy" << std::endl;
	std::cin >> v;
	std::chrono::time_point<std::chrono::system_clock>start, end;
	start = std::chrono::system_clock::now();

	listarr = new(std::nothrow)slist*[n];

	for (int i = 0; i < n; i++) {
		listarr[i] = NULL;
	}

	for (int j = 0; j < m; j++) {
		listelem = new(std::nothrow)slist;
		for (int i = 0; i < n; i++) {
			if (matrix[i][j] > 0) { v1 = i; weight = matrix[i][j]; }
			if (matrix[i][j] < 0) v2 = i;
		}
		listelem->v = v2;          // Numerujemy go jako v2
		listelem->weight = weight; // Dodajemy wag� kraw�dzi
		listelem->next = listarr[v1];    // Dodajemy go na pocz�tek listy A[v1]
		listarr[v1] = listelem;
	}



	cost = new(std::nothrow)long long[n];
	pred = new(std::nothrow)int[n];
	for (int i = 0; i < n; i++) {
		cost[i] = INT32_MAX;
		pred[i] = -1;
	}

	if (BF(v, cost, pred, n, m, listarr)) {
		stack = new(std::nothrow)int[n];
		stackptr = 0;

		for (int i = 0; i < n; i++)
		{
			std::cout << i << ": ";
			for (int x = i; x != -1; x = pred[x]) // Wierzcho�ki �cie�ki umieszczamy na stosie
				stack[stackptr++] = x;            // w kolejno�ci od ostatniego do pierwszego

			while (stackptr)                 // Wierzcho�ki ze stosu drukujemy
				std::cout << stack[--stackptr] << " "; // w kolejno�ci od pierwszego do ostatniego

			std::cout << "$" << cost[i] << std::endl; // Na ko�cu wy�wietlamy koszt
		}
		delete[] stack;                  // Usuwamy stos
	}
	else std::cout << "Negative Cycle found!" << std::endl;

	delete[] cost;
	delete[] pred;

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

	end = std::chrono::system_clock::now();
	std::chrono::duration<double> seconds = end - start;
	std::cout << "\nMacierz incydencji - czas: " << seconds.count() << "s\n";
}
