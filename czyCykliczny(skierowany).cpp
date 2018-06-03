#include <iostream>

using namespace std;

struct slistEl
{
  slistEl * next;
  int v;
};

// Funkcje badaj¹ce cyklicznoœæ grafu
//-----------------------------------
bool isGraphCyclic(slistEl ** G, int v, char * visited)
{
  int u;

  visited[v] = 'G';             // Kolorujemy wierzcho³ek na szaro
  slistEl *p = G[v];            // Sprawdzamy kolejnych s¹siadów
  while(p)
  {
    u = p->v;                   // u <-- numer s¹siada
    if(visited[u] == 'G') return true; // S¹siad szary - mamy cykl. przerywamy
    if((visited[u] == 'W') && isGraphCyclic(G,u,visited)) return true; // Wywo³anie rekurencyjne
    p = p->next;
  }
  visited[v] = 'B';             // Kolorujemy wierzcho³ek na czarno
  return false;
}

bool isCyclic(int n, slistEl ** G)
{
  int i;
  char * visited;

  visited = new char[n];        // Tworzymy tablicê odwiedzin
  for(i = 0; i < n; i++)
    visited[i] = 'W';           // Tablicê zerujemy
  for(i = 0; i < n; i++)
    if((visited[i] = 'W') && isGraphCyclic(G,i,visited)) return true;
  return false;
}

int main()
{
  int n,m,i,v1,v2;
  slistEl * p,* r,** A;

  cin >> n >> m;         // Czytamy liczbê wierzcho³ków i krawêdzi

  A = new slistEl * [n]; // Tworzymy tablicê list s¹siedztwa

  // Tablice wype³niamy pustymi listami

  for(i = 0; i < n; i++) A[i] = NULL;

  // Odczytujemy kolejne definicje krawêdzi

  for(i = 0; i < m; i++)
  {
    cin >> v1 >> v2;    // Wierzcho³ek startowy i koñcowy krawêdzi
    p = new slistEl;    // Tworzymy nowy element
    p->v = v2;          // Numerujemy go jako v2
    p->next = A[v1];    // Dodajemy go na pocz¹tek listy A[v1]
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
