#include <string>
using namespace std;
#include <iostream>
int counter = 0;
struct HT {
	string *key;
	int *data;
	bool *free;
	int size;
};
struct node {
	node * parent;
	int rank;
	int val;
	int len;
};
node *FIND(node * x)
{
	if (x->parent != x) {
		node* y = FIND(x->parent);
		x->parent = y;
		return y;
	}
	else return x;
}
void UNION(node *x, node *y) {
	node *Ry = FIND(y);
	node *Rx = FIND(x);
	if (Rx->rank > Ry->rank) {
		Ry->parent = Rx;
		Rx->len += Ry->len;
	}
	else {
		Rx->parent = Ry;
		Ry->len +=Rx->len;
	}
	if (Rx->rank == Ry->rank)
		Ry->rank++;
}
node* MAKESET(int x) {
	node * tmp = new node;
	tmp->parent = tmp;
	tmp->len = 1;
	tmp->rank = 0;
	tmp->val = x;
	return tmp;
}
int hashK(string key,int size)
{
	int seed = 131;
	unsigned long hash = 0;
	for (int i = 0; i < key.length(); i++)
	{
		hash = (hash * seed) + key[i];
	}
	return hash % size;
}


bool Hinsert(HT *ht,int data,string key) {
	int x = hashK(key, ht->size);
	for (int i = 0; i < ht->size; i++) {
		if (ht->free[(x + i) % ht->size]) {
			ht->data[(x + i) % ht->size] = data;
			ht->free[(x + i) % ht->size] = false;
			ht->key[counter] = key;
			counter++;
			return true;
		}
	}
	return false;
}
bool checkHT(HT *ht) {
	node ** SETS = new node *[ht->size];
	for (int i = 0; i < ht->size; i++)
		if (!ht->free[i])
			SETS[i] = MAKESET(ht->data[i]);
	for (int i = 0; i < ht->size-1; i++)
		if (!ht->free[i] && !ht->free[i + 1])
			UNION(SETS[i], SETS[i + 1]);
	if (FIND(SETS[0])->len != ht->size)
		UNION(SETS[ht->size-1], SETS[0]);
	int x;
	for (int i = 0; i < ht->size; i++) {
		x = hashK(ht->key[i],ht->size);
		if (ht->free[x]) return false;
		FIND(SETS[x])->len--;
	}
	for (int i = 0; i < ht->size; i++)
		if (!ht->free[i])
		if (FIND(SETS[i])->len != 0) return false;
	return true;
}

int main() {
	int n;
	cout << "give table size" << endl;
	cin >> n;
	HT *TAB;
	TAB = new HT;
	TAB->key = new string[n];
	TAB->data = new int[n];
	TAB->free = new bool[n];
	TAB->size = n;
	for (int i = 0; i < n; i++)
		TAB->free[i] = true;
	string z;
	int c;
	for (int i = 0; i < n; i++)
	{
		cout << "podaj klucz: ";
		cin >> z;
		cout << "podaj dane: ";
		cin >> c;
		if (Hinsert(TAB, c, z)) cout << "udalo sie oddac element" << endl;
		else cout << "error";
	}

	if (checkHT(TAB)) cout << "WSZYSTKO GRA KAPITANIE";
	else cout << " ERORR EOORROR";


}
