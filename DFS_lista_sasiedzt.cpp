#include <iostream>
#include <iomanip>

using namespace std;

// Typy dla dynamicznej tablicy list s�siedztwa

struct slistEl
{
  slistEl * next;
  int v;
};

// Zmienne globalne

int n;                   // Liczba wierzcho�k�w
slistEl ** A;            // Macierz s�siedztwa
bool * visited;          // Tablica odwiedzin

// Rekurencyjna procedura przej�cia w g��b
//----------------------------------------
void DFS(int v)
{
  slistEl * p;

  visited[v] = true;     // Zaznaczamy w�ze� jako odwiedzony
  cout << setw(3) << v;  // Przetwarzamy w�ze� (wypisujemy jego numer)

// Rekurencyjnie odwiedzamy nieodwiedzonych s�siad�w

  for(p = A[v]; p!=NULL; p = p->next)
    if(!visited[p->v]) DFS(p->v);
}

int main()
{
  int m,i,v1,v2;
  slistEl *p,*r;

  cin >> n >> m;               // Czytamy liczb� wierzcho�k�w i kraw�dzi

  A = new slistEl * [n];       // Tworzymy tablic� list s�siedztwa
  visited = new bool[n];       // Tworzymy tablic� odwiedzin

  // Tablic� wype�niamy pustymi listami

  for(i = 0; i < n; i++)
  {
    A[i] = NULL;
    visited[i] = false;
  }

  // Odczytujemy kolejne definicje kraw�dzi

  for(i = 0; i < m; i++)
  {
    cin >> v1 >> v2;    // Wierzcho�ek startowy i ko�cowy kraw�dzi
    p = new slistEl;    // Tworzymy nowy element
    p->v = v2;          // Numerujemy go jako v2
    p->next = A[v1];    // Dodajemy go na pocz�tek listy A[v1]
    A[v1] = p;
  }

  cout << endl;

  // Przechodzimy graf w g��b

  DFS(0);


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
