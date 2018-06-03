#include <iostream>
#include <iomanip>

using namespace std;

// Typy danych dla drzew struktury zbior�w roz��cznych

struct TNode
{
  TNode *up;                      // Rodzic w�z�a
  int rank;                       // Ranga
  int data;                       // Zawarto�� w�z�a
};

// Tworzy drzewo jednow�z�owe
//---------------------------
void MakeSet(TNode * x)
{
  x->up = x;                      // x staje si� korzeniem drzewa
  x->rank = 0;                    // Rang� zerujemy
}

// Zwraca korze� drzewa i ustawia pola up
// wszystkich w�z��w nadrz�dnych a� do korzenia
//---------------------------------------------
TNode * FindSet(TNode * x)
{
  if(x->up != x) x->up = FindSet(x->up);
  return x->up;
}

// ��czy ze sob� drzewa z x i z y
//-------------------------------
void UnionSets(TNode *x, TNode *y)
{
  TNode *rx,*ry;

  rx = FindSet(x);                // Wyznaczamy korze� drzewa z w�z�em x
  ry = FindSet(y);                // Wyznaczamy korze� drzewa z w�z�em y
  if(rx != ry)                    // Korzenie musz� by� r�ne
  {
    if(rx->rank > ry->rank)       // Por�wnujemy rangi drzew
       ry->up = rx;               // rx wi�ksze, do��czamy ry
    else
    {
      rx->up = ry;                // r�wne lub ry wi�ksze, do��czamy rx
      if(rx->rank == ry->rank) ry->rank++;
    }
  }
}
int main()
{
  int n,m;                        // Liczba wierzcho�k�w i kraw�dzi
  TNode * T;
  int i,j,v,u;

  cin >> n >> m;                  // Odczytujemy liczb� wierzcho�k�w i kraw�dzi
  T = new TNode [n];              // Tworzymy tablic� zbior�w roz��cznych

  // Tablic� T inicjujemy

  for(i = 0; i < n; i++)
  {
    T[i].data = i;                // Numer w�z�a
    MakeSet(&T[i]);               // Tworzymy zbi�r jednoelementowy
  }

  // Odczytujemy kolejne definicje kraw�dzi.

  for(i = 0; i < m; i++)
  {
    cin >> v >> u;                // Wierzcho�ki tworz�ce kraw�d�
    UnionSets(&T[v],&T[u]);       // ��czymy zbiory z u i v
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
