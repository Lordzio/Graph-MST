// SDiZO 2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace std;


void generate(){
	edge *edgearr;
	int edgecnt, n, maxedges, edgethr;
	float dens;
	fstream graph;
	graph.open("graf.txt", ofstream::out | ofstream::trunc);
	graph.close();
	graph.open("graf.txt");
	
	cout << "Podaj ilosc wierzcholkow:" << endl;
	cin >> n;
	cout << "Podaj gestosc:" << endl;
	cin >> dens;

	dens = dens / 100;
	maxedges = n*(n - 1);
	edgethr = maxedges * dens;
	if (edgethr < n - 1) edgethr = n - 1;
	edgearr = new(nothrow)edge[edgethr];

	srand(time(NULL));

	for (edgecnt = 0; edgecnt < n - 1; edgecnt++) {
		edgearr[edgecnt].v1 = edgecnt;
		edgearr[edgecnt].v2 = edgecnt + 1;
		edgearr[edgecnt].weight = (rand() % 100) + 1;
	}
//	edgearr[edgecnt].v1 = edgecnt;
//	edgearr[edgecnt].v2 = 0;
//	edgearr[edgecnt].weight = (rand() % 100) + 1;
//	edgecnt++;

	while (edgecnt < edgethr - 1) {
		edgearr[edgecnt].v1 = rand() % n;

		edgearr[edgecnt].v2 = rand() % n;
		while (edgearr[edgecnt].v1 == edgearr[edgecnt].v2) {
			edgearr[edgecnt].v2 = rand() % n;
		}

		edgearr[edgecnt].weight = (rand() % 100) + 1;
		edgecnt++;
	}
	graph << edgecnt << " " << n << endl;
	for (int i = 0; i < edgecnt; i++) {
		graph << edgearr[i].v1 << " " << edgearr[i].v2 << " " << edgearr[i].weight << endl;
	}

	delete[] edgearr;

}



int main()
{
	int n, m;
	string line;
	fstream file;
	lgraph *listgraph = NULL;
	mgraph *matrixgraph = NULL;
	char choice;
	bool running = true;
	chrono::time_point<chrono::system_clock>start, end;

	do {
		cout << "Wybierz opcje:\n1 - generuj graf losowo\n2 - wczytaj graf z pliku\n3 - wykonaj algorytm Kruskala\n"
			"4 - Wykonaj algorytm Prima\n5 - Wykonaj algorytm Dijkstry\n6 - Wykonaj algorytm Bellmana-Forda\n7 - Zakoncz program\n";
		cin >> choice;
		switch (choice) {
		case '1': {
			generate();
			file.open("graf.txt");
			getline(file, line);
			file.close();

			m = stoi(line.substr(0, line.find(" ")));
			n = stoi(line.substr(line.find(" ")));

			if (listgraph != NULL) delete listgraph;
			if (matrixgraph != NULL) delete matrixgraph;

			listgraph = new(nothrow)lgraph(n);
			matrixgraph = new(nothrow)mgraph(n, m);
			listgraph->createFfile(n, m);
			matrixgraph->createFfile(m);
		//	listgraph->display(n);
		//	matrixgraph->display(m, n);

			break;
		}
		case '2': {
			file.open("graf.txt");
			if (file.is_open()) {
				getline(file, line);

				m = stoi(line.substr(0, line.find(" ")));
				n = stoi(line.substr(line.find(" ")));
				file.close();

				if (listgraph != NULL) delete listgraph;
				if (matrixgraph != NULL) delete matrixgraph;

				listgraph = new(nothrow)lgraph(n);
				matrixgraph = new(nothrow)mgraph(n, m);
				listgraph->createFfile(n, m);
				matrixgraph->createFfile(m);
				listgraph->display(n);
				matrixgraph->display(m, n);
			}
			else cout << "Nie udalo sie otworzyc pliku." << endl;
			break;
		}
		case '3': {
			start = chrono::system_clock::now();
			listgraph->krusk(n, m);
			end = chrono::system_clock::now();
			chrono::duration<double> seconds = end - start;
			cout << "\nLista sasiedztw - czas: " << seconds.count() << "s\n";

			start = chrono::system_clock::now();
			matrixgraph->krusk(n, m);
			end = chrono::system_clock::now();
			seconds = end - start;
			cout << "\nMacierz incydencji - czas: " << seconds.count() << "s\n\n";
			break;
		}
		case '4': {
			start = chrono::system_clock::now();
			listgraph->prim(n, m);
			end = chrono::system_clock::now();
			chrono::duration<double> seconds = end - start;
			cout << "\nLista sasiedztw - czas: " << seconds.count() << "s\n";

			start = chrono::system_clock::now();
			matrixgraph->prim(n, m);
			end = chrono::system_clock::now();
			seconds = end - start;
			cout << "\nMacierz incydencji - czas: " << seconds.count() << "s\n\n";
			break;
		}
		case '5': {
			listgraph->dijk(n, m);
			matrixgraph->dijk(n, m);
			break;
		}
		case '6': {
			listgraph->bell(n, m);
			matrixgraph->bell(n, m);
			break;
		}
		case '7': {
			running = false;
			break;
		}
		default: {
			cout << "Nie ma takiej opcji" << endl;
		}
		}
	} while (running);

	delete listgraph;
	delete matrixgraph;


	system("pause");
	return 0;
}

