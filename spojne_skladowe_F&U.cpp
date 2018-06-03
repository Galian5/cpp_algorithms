#include <iostream>
#include <iomanip>

using namespace std;

// Typy danych dla drzew struktury zbiorów roz³¹cznych

struct TNode
{
  TNode *up;                      // Rodzic wêz³a
  int rank;                       // Ranga
  int data;                       // Zawartoœæ wêz³a
};

// Tworzy drzewo jednowêz³owe
//---------------------------
void MakeSet(TNode * x)
{
  x->up = x;                      // x staje siê korzeniem drzewa
  x->rank = 0;                    // Rangê zerujemy
}

// Zwraca korzeñ drzewa i ustawia pola up
// wszystkich wêz³ów nadrzêdnych a¿ do korzenia
//---------------------------------------------
TNode * FindSet(TNode * x)
{
  if(x->up != x) x->up = FindSet(x->up);
  return x->up;
}

// £¹czy ze sob¹ drzewa z x i z y
//-------------------------------
void UnionSets(TNode *x, TNode *y)
{
  TNode *rx,*ry;

  rx = FindSet(x);                // Wyznaczamy korzeñ drzewa z wêz³em x
  ry = FindSet(y);                // Wyznaczamy korzeñ drzewa z wêz³em y
  if(rx != ry)                    // Korzenie musz¹ byæ ró¿ne
  {
    if(rx->rank > ry->rank)       // Porównujemy rangi drzew
       ry->up = rx;               // rx wiêksze, do³¹czamy ry
    else
    {
      rx->up = ry;                // równe lub ry wiêksze, do³¹czamy rx
      if(rx->rank == ry->rank) ry->rank++;
    }
  }
}
int main()
{
  int n,m;                        // Liczba wierzcho³ków i krawêdzi
  TNode * T;
  int i,j,v,u;

  cin >> n >> m;                  // Odczytujemy liczbê wierzcho³ków i krawêdzi
  T = new TNode [n];              // Tworzymy tablicê zbiorów roz³¹cznych

  // Tablicê T inicjujemy

  for(i = 0; i < n; i++)
  {
    T[i].data = i;                // Numer wêz³a
    MakeSet(&T[i]);               // Tworzymy zbiór jednoelementowy
  }

  // Odczytujemy kolejne definicje krawêdzi.

  for(i = 0; i < m; i++)
  {
    cin >> v >> u;                // Wierzcho³ki tworz¹ce krawêdŸ
    UnionSets(&T[v],&T[u]);       // £¹czymy zbiory z u i v
  }

  // Wypisujemy wyniki

  cout << endl;

  for(i = 0; i < n; i++)
    if(i == FindSet(&T[i])->data)
    {
      cout << "SCC id =" << setw(3) << i << " :";
      for(j = 0; j < n; j++)
        if(i == FindSet(&T[j])->data) cout << setw(3) << j;
      cout << endl;
    }

  delete [] T;

  return 0;
}
