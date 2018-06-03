#include <iostream>

using namespace std;

struct slistEl
{
  slistEl * next;
  int v;
};

class stack
{
  private:
    slistEl * S;   // lista przechowuj¹ca stos

  public:
    stack();       // konstruktor
    ~stack();      // destruktor
    bool empty(void);
    int  top(void);
    void push(int v);
    void pop(void);
};

// Konstruktor
//------------
stack::stack()
{
  S = NULL;
}

// Destruktor - zwalnia tablicê dynamiczn¹
//----------------------------------------
stack::~stack()
{
  while(S) pop();
}

// Sprawdza, czy stos jest pusty
//------------------------------
bool stack::empty(void)
{
  return !S;
}

// Zwraca szczyt stosu
//--------------------
int stack::top(void)
{
  return S->v;
}

// Zapisuje na stos
//-----------------
void stack::push(int v)
{
  slistEl * e = new slistEl;
  e->v    = v;
  e->next = S;
  S = e;
}

// Usuwa ze stosu
//---------------
void stack::pop(void)
{
  if(S)
  {
    slistEl * e = S;
    S = S->next;
    delete e;
  }
}

// Funkcja rekurencyjna wyszukuj¹ca cykl
//--------------------------------------
bool DFSfindCycle(slistEl ** graf, int v, int w, stack & S, bool * visited)
{
  int u;

  visited[w] = true;             // Oznaczamy wierzcho³ek jako odwiedzony
  slistEl *p = graf[w];                   // Rozpoczynamy przegl¹danie s¹siadów
  while(p)
  {
    u = p->v;                    // u - numer wierzcho³ka bêd¹cego s¹siadem
    if(u != S.top())             // Pomijamy wierzcho³ek, z którego przyszliœmy
    {
      S.push(w);                 // Na stos wierzcho³ek bie¿¹cy
      if(u == v) return true;    // Cykl znaleziony, koñczymy
      if(!visited[u] && DFSfindCycle(graf,v,u,S,visited)) return true;
      S.pop();
    }
    p = p->next;
  }
  return false;
}

int main()
{
  int n,m,i,j,u,v1,v2;
  slistEl * p,* r,** A;
  bool * visited;
  stack S;

  cin >> n >> m;         // Czytamy liczbê wierzcho³ków i krawêdzi

  A = new slistEl * [n]; // Tworzymy tablicê list s¹siedztwa

  // Tablice wype³niamy pustymi listami

  for(i = 0; i < n; i++) A[i] = NULL;

  for(i = 0; i < m; i++)
  {
    cin >> v1 >> v2;    // Wierzcho³ek startowy i koñcowy krawêdzi
    p = new slistEl;    // Tworzymy nowy element
    p->v = v2;          // Numerujemy go jako v2
    p->next = A[v1];    // Dodajemy go na pocz¹tek listy A[v1]
    A[v1] = p;
    p = new slistEl;    // KrawêdŸ w drug¹ stronê, bo graf jest nieskierowany
    p->v = v1;
    p->next = A[v2];
    A[v2] = p;
  }

  cout << endl;

  visited = new bool [n];          // Tworzymy tablicê odwiedzin

  for(i = 0; i < n; i++)           // Przechodzimy przez kolejne wierzcho³ki grafu
  {
    for(j = 0; j < n; j++)         // Zerujemy tablicê odwiedzin
      visited[j] = false;

    S.push(-1);                    // Na stos znacznik pocz¹tku œcie¿ki

    cout << i <<": ";                     // Wypisujemy wierzcho³ek startowy cyklu

    if(!DFSfindCycle(A,i,i,S,visited)) // Szukamy cyklu
    {
      S.pop();                     // Usuwamy ze stosu pocz¹tek œcie¿ki
      cout << " - no cycle\n";   // Komunikat
    }
    else
      while(!S.empty())            // Wypisujemy cykl, jesli istnieje
      {
        u = S.top(); S.pop();      // Pobieramy ze stosu numer wierzcjo³ka
        if(u > -1) cout << " " << u; // i wypisujemy go
        else       cout << endl;
      }
  }

  // Usuwamy dynamiczne struktury danych

  delete [] visited;

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
