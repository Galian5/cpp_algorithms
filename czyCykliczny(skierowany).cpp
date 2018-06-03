#include <iostream>

using namespace std;

struct slistEl
{
  slistEl * next;
  int v;
};

// Funkcje badaj�ce cykliczno�� grafu
//-----------------------------------
bool isGraphCyclic(slistEl ** G, int v, char * visited)
{
  int u;

  visited[v] = 'G';             // Kolorujemy wierzcho�ek na szaro
  slistEl *p = G[v];            // Sprawdzamy kolejnych s�siad�w
  while(p)
  {
    u = p->v;                   // u <-- numer s�siada
    if(visited[u] == 'G') return true; // S�siad szary - mamy cykl. przerywamy
    if((visited[u] == 'W') && isGraphCyclic(G,u,visited)) return true; // Wywo�anie rekurencyjne
    p = p->next;
  }
  visited[v] = 'B';             // Kolorujemy wierzcho�ek na czarno
  return false;
}

bool isCyclic(int n, slistEl ** G)
{
  int i;
  char * visited;

  visited = new char[n];        // Tworzymy tablic� odwiedzin
  for(i = 0; i < n; i++)
    visited[i] = 'W';           // Tablic� zerujemy
  for(i = 0; i < n; i++)
    if((visited[i] = 'W') && isGraphCyclic(G,i,visited)) return true;
  return false;
}

int main()
{
  int n,m,i,v1,v2;
  slistEl * p,* r,** A;

  cin >> n >> m;         // Czytamy liczb� wierzcho�k�w i kraw�dzi

  A = new slistEl * [n]; // Tworzymy tablic� list s�siedztwa

  // Tablice wype�niamy pustymi listami

  for(i = 0; i < n; i++) A[i] = NULL;

  // Odczytujemy kolejne definicje kraw�dzi

  for(i = 0; i < m; i++)
  {
    cin >> v1 >> v2;    // Wierzcho�ek startowy i ko�cowy kraw�dzi
    p = new slistEl;    // Tworzymy nowy element
    p->v = v2;          // Numerujemy go jako v2
    p->next = A[v1];    // Dodajemy go na pocz�tek listy A[v1]
    A[v1] = p;
  }

  if(isCyclic(n,A)) cout << "CYCLIC GRAPH";
  else              cout << "ACYCLIC GRAPH";

  cout << endl;

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

  return 0;
}
