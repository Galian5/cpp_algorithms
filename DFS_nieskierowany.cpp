#include <iostream>
#include <iomanip>

using namespace std;

// Typy dla dynamicznej tablicy list s¹siedztwa

struct slistEl
{
  slistEl * next;
  int v;
};

// Zmienne globalne

int n;                   // Liczba wierzcho³ków
slistEl ** A;            // Macierz s¹siedztwa
bool * visited;          // Tablica odwiedzin

// Rekurencyjna procedura przejœcia w g³¹b
//----------------------------------------
void DFS(int v)
{
  slistEl * p;

  visited[v] = true;     // Zaznaczamy wêze³ jako odwiedzony
  cout << setw(3) << v;  // Przetwarzamy wêze³ (wypisujemy jego numer)

// Rekurencyjnie odwiedzamy nieodwiedzonych s¹siadów

  for(p = A[v]; p!=NULL; p = p->next)
    if(!visited[p->v]) DFS(p->v);
}

// **********************
// *** PROGRAM G£ÓWNY ***
// **********************

int main()
{
  int m,i,v1,v2;
  slistEl *p,*r, *x;

  cin >> n >> m;               // Czytamy liczbê wierzcho³ków i krawêdzi

  A = new slistEl * [n];       // Tworzymy tablicê list s¹siedztwa
  visited = new bool[n];       // Tworzymy tablicê odwiedzin

  // Tablicê wype³niamy pustymi listami

  for(i = 0; i < n; i++)
  {
    A[i] = NULL;
    visited[i] = false;
  }

  // Odczytujemy kolejne definicje krawêdzi

  for(i = 0; i < m; i++)
  {
    cin >> v1 >> v2;    // Wierzcho³ek startowy i koñcowy krawêdzi
    p = new slistEl;    // Tworzymy nowy element
    p->v = v2;          // Numerujemy go jako v2
    p->next = A[v1];    // Dodajemy go na pocz¹tek listy A[v1]
    A[v1] = p;
    x = new slistEl;    // nieskerowany
    x->v=v1;
    x->next=A[v2];
    A[v2]=x;
  }

  cout << endl;

  // Przechodzimy graf w g³¹b

  DFS(0);

  // Usuwamy tablicê list s¹siedztwa

  for(i = 0; i < n; i++)
  {
    p = A[i];
    while(p)
    {
      r = p;
      p = p->next;
      delete r;
    }
  }
  delete [] A;
  delete [] visited;

  cout << endl;

  return 0;
}

