#include <iostream>
#include <iomanip>

using namespace std;

// Typy dla dynamicznej tablicy list s¹siedztwa i kolejki

struct slistEl
{
  slistEl * next;
  int v;
};

// Zmienne globalne

int n;                   // Liczba wierzcho³ków
slistEl ** A;            // Macierz s¹siedztwa
bool * visited;          // Tablica odwiedzin

// Procedura przejœcia wszerz
//---------------------------
void BFS( int v)
{
  slistEl *p,*q,*head,*tail; // Kolejka

  q = new slistEl;        // W kolejce umieszczamy v
  q->next = NULL;
  q->v = v;
  head = tail = q;

  visited[v] = true;      // Wierzcho³ek v oznaczamy jako odwiedzony

  while(head)
  {
    v = head->v;          // Odczytujemy v z kolejki

    q = head;             // Usuwamy z kolejki odczytane v
    head = head->next;
    if(!head) tail = NULL;
    delete q;

    cout << setw(3) << v;

    for(p = A[v]; p; p = p->next)
    if(!visited[p->v])
    {
      q = new slistEl; // W kolejce umieszczamy nieodwiedzonych s¹siadów
      q->next = NULL;
      q->v = p->v;
      if(!tail) head = q;
      else      tail->next = q;
      tail = q;
      visited[p->v] = true; // i oznaczamy ich jako odwiedzonych
    }
  }
}

// **********************
// *** PROGRAM G£ÓWNY ***
// **********************

int main()
{
  int m,i,v1,v2;
  slistEl *p,*r;

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
  }

  cout << endl;

  // Przechodzimy graf wszerz

  BFS(0);

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
