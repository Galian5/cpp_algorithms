#include <iostream>
using namespace std;

struct node {
	node *parent;
	int rank;
	int val
		;
};

node *MAKE_SET(int v) {
	node *s = new node;
	s->parent = s;
	s->rank = 0;
	s->val = v;
	return s;
}
node *FIND_SET(node *x) {
	if (x->parent != x) {
		node *y = FIND_SET(x->parent);
		x->parent = y;
		return y;
	}
	else
		return x;
}
void UNION(node *x, node *y) {
	node *Rx = FIND_SET(x);
	node *Ry = FIND_SET(y);
	if (Rx->rank > Ry->rank)
		Ry->parent = Rx;
	else {
		Rx->parent = Ry;
		if (Ry->rank == Rx->rank)
			Ry->rank++;
	}

}
void zlicz(int T[], int Score[],int w ,int k)
{
	node **W = new node*[w*k];
	int wiersz, kolumna;
	int counter = 0;
	for (int i = 0; i < w*k; i++)
		W[i] = MAKE_SET(T[i]);
	int j = 0;
	for (int i = 1; i <= w*k; i++)											// g³ówna petla od czasu wstawienia
	{
		for (j = 0; W[j]->val != i; j++);								// szukanie wstawionej plytki

		wiersz = j / k;
		kolumna = j%k;
		counter++; // dodalismy nowa wyspe

		if (wiersz - 1 >= 0 && W[k*wiersz + kolumna]->val > W[k*(wiersz - 1) + kolumna]->val) {
			if (FIND_SET(W[k*wiersz + kolumna]) != FIND_SET(W[k*(wiersz - 1) + kolumna])) {
				UNION(W[k*wiersz + kolumna], W[k*(wiersz - 1) + kolumna]);
				counter--;
			}
		}
	// sprawdzamy czy laczymy jakies wyspy i ewentualnie zmniejszamy licznik wysp
		if (wiersz + 1 < w && W[k*wiersz + kolumna]->val > W[k*(wiersz + 1) + kolumna]->val) {
			if (FIND_SET(W[k*wiersz + kolumna]) != FIND_SET(W[k*(wiersz + 1) + kolumna])) {
				UNION(W[k*wiersz + kolumna], W[k*(wiersz + 1) + kolumna]);
				counter--;
			}
		}

		if (kolumna - 1 >= 0 && W[k*wiersz + kolumna]->val > W[k*wiersz + kolumna-1]->val) {
			if (FIND_SET(W[k*wiersz + kolumna]) != FIND_SET(W[k*wiersz + kolumna-1])) {
				UNION(W[k*wiersz + kolumna], W[k*wiersz + kolumna-1]);
				counter--;
			}
		}

		if (kolumna + 1 < k && W[k*wiersz + kolumna]->val > W[k*wiersz + kolumna + 1]->val) {
			if (FIND_SET(W[k*wiersz + kolumna]) != FIND_SET(W[k*wiersz + kolumna + 1])) {
				UNION(W[k*wiersz + kolumna], W[k*wiersz + kolumna + 1]);
				counter--;
			}
		}

		Score[i - 1] = counter; // zapisujemy wynik

	}

}



int main()
{
	int w, k;
	cin >> w;
	cin >> k;
	int *T = new int[w*k];
	int *Score = new int[w*k];
	for (int i = 0; i < w*k; i++) {
		cin >> T[i];
	}

	zlicz(T, Score, w, k);
	for (int i = 0; i < w*k; i++)
		cout << Score[i] << " ";
}
