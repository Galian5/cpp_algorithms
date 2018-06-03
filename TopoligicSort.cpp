#include <iostream>

using namespace std;

struct slistEl
{
  slistEl *next;
  int v;
};

int sptr,*S;
char *visited;

const char WHITE = 0;           //nieprzetworzony
const char GRAY  = 1;           //w trakcie
const char GREEN = 2;           //przetworzony

// Rekurencyjna funkcja dokonuj¹ca sortowania topologicznego
// v - wierzcho³ek startowy
//----------------------------------------------------------
bool DFStsort(int v,slistEl **G)
{
  slistEl *p;

  if(visited[v] == GRAY)        // Sprawdzamy, czy nie ma cyklu
  {
    cout << "\nNOT A DAG\n\n";  // Jest cykl - sortowanie topologiczne
    return false;               // nie mo¿e zostaæ wykonane
  }
  if(visited[v] == WHITE)       // Jeœli wierzcho³ek jest bia³y,
  {
    visited[v] = GRAY;          // to kolorujemy go na szaro
    for(p = G[v];p;p = p->next) // i przegl¹damy wszystkich s¹siadów
      if(!DFStsort(p->v,G)) return false; // Wywo³anie rekurencyjne
    visited[v] = GREEN;         // Wierzcho³ek kolorujemy na zielono
    S[sptr++] = v;              // i umieszczamy go na stosie
  }
  return true;                  // Koñczymy z wynikiem true
}

int main()
{
  int n,m,i,v1,v2;
  slistEl *p,*r;
  slistEl **graf;
  cin >> n >> m;                // Czytamy liczbê wierzcho³ków i krawêdzi

  // Tworzymy tablice dynamiczne

  graf = new slistEl * [n];
  S    = new int [n]; sptr = 0; // Pusty stos
  visited = new char [n];
  for(i = 0; i < n; i++)
  {
    graf[i] = NULL;
    visited[i] = WHITE;         // Wierzcho³ki kolorujemy na bia³o
  }

  for(i = 0; i < m; i++)
  {
    cin >> v1 >> v2;
    p = new slistEl;
    p->v = v2;
    p->next = graf[v1];
    graf[v1] = p;
  }

  cout << endl;

  // Wykonujemy sortowanie topologiczne grafu

  for(i = 0; i < n; i++)
    if(visited[i] == WHITE)
    {
      if(!DFStsort(i,graf)) break;
    }

  // Wypisujemy wyniki

  if(sptr == n)
    for(i = n - 1; i >= 0; i--) cout << S[i] << " ";

  cout << endl;

  // Usuwamy zmienne dynamiczne

  for(i = 0; i < n; i++)
  {
    p = graf[i];
    while(p)
    {
      r = p;
      p = p->next;
      delete r;
    }
  }
  delete [] graf;
  delete [] visited;
  delete [] S;

  return 0;
}
