#include <iostream>
#include<ctime>
#include<cstdlib>
using namespace std;
#define M 6
#define N 8

struct node{
	node* parent;
	int rank;
	bool val;
};

node *MAKE_SET(bool x) {
	node *s = new node;
	s->val = x;
	s->parent = s;
	s->rank = 0;
	return s;
}

node *FIND(node *x) {

	if (x->parent != x) {
		node *y = FIND(x->parent);
		x->parent = y;
		return y;
	}
	else
		return x;
}
void UNION(node *x, node *y) {
	node *Px = FIND(x);
	node *Py = FIND(y);
	if (Py->rank < Px->rank)
		Py->parent = Px;
	else {
		Px->parent = Py;
		if (Px->rank == Py->rank)
			Px->rank++;
	}
}

int gracz(bool T[][N], int x, int y) {
	node *S[M][N];
	int count = 0;
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			S[i][j] = MAKE_SET(T[i][j]);

	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++) {
			if (S[i][j]->val == true) {
				if (j + 1 < N && S[i][j + 1]->val == true)
					UNION(S[i][j], S[i][j + 1]);
				if (i + 1 < M && S[i + 1][j]->val == true)
					UNION(S[i][j], S[i + 1][j]);
			}
		}

	node* Px = FIND(S[y][x]);
	for (int i = 0; i < M; i++)
		for (int j = 0; j < N; j++)
			if (FIND(S[i][j]) == Px)
				count++;
	count--;
	return count;


}







	int main() {
		srand(time(NULL));
		bool T[M][N];
		int x = 3;
		int y = 3;
		for (int z = 0; z < 15; z++) {
			for (int i = 0; i < M; i++) {
				for (int j = 0; j < N; j++) {
					T[i][j] = rand() % 2;
					if (i == y && j == x)
						cout << "_ ";
					else
					cout << T[i][j] << " ";
				}
				cout << endl;
			}
			cout << endl;
			T[3][3] = true;
			cout << gracz(T,x,y);
			cout << endl;
			cout << "---------------------------";
			cout << endl;
		}


	}
