#include <iostream>

using namespace std;

// Typy dla dynamicznej tablicy list s¹siedztwa i stosu

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

//---------------------
// Metody obiektu stack
//---------------------

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
bool spojnosc(slistEl **A, bool visited[],int n)
{
  int vc = 0,v,u;
  slistEl *p;                  // Zerujemy licznik wierzcho³ków
  stack S;
  S.push(0);                 // Wierzcho³ek startowy na stos
  visited[0] = true;         // Oznaczamy go jako odwiedzony

  while(!S.empty())          // Wykonujemy przejœcie BFS
  {
    v = S.top();             // Pobieramy wierzcho³ek ze stosu
    S.pop();                 // Pobrany wierzcho³ek usuwamy ze stosu
    vc++;                    // Zwiêkszamy licznik wierzcho³ków
    for(p = A[v]; p; p = p->next) // Przegl¹damy s¹siadów
    {
      u = p->v;
      if(!visited[u])        // Szukamy wierzcho³ków nieodwiedzonych
      {
        visited[u] = true;   // Oznaczamy wierzcho³ek jako odwiedzony
        S.push(u);           // i umieszczamy go na stosie
      }
    }
  }
  if(vc == n)
  {
      cout << "CONNECTED GRAPH";
      return true;
  }
  else
  {
      cout << "DISCONNECTED GRAPH";
      return false;
  }
}
int main()
{
  int n,m;        // Liczba wierzcho³ków i krawêdzi
  slistEl ** A;   // Tablica list s¹siedztwa grafu
  bool * visited; // Tablica odwiedzin
  int i,v,u;
  slistEl *p,*r;

  cin >> n >> m;             // Odczytujemy liczbê wierzcho³ków i krawêdzi

  A = new slistEl * [n];     // Tworzymy tablice dynamiczne
  visited = new bool [n];

  // Inicjujemy tablice

  for(i = 0; i < n; i++)
  {
    A[i] = NULL;
    visited[i] = false;
  }

  // Odczytujemy kolejne definicje krawêdzi.

  for(i = 0; i < m; i++)
  {
    cin >> v >> u;           // Wierzcho³ki tworz¹ce krawêdŸ
    p = new slistEl;         // Tworzymy nowy element
    p->v = u;                // Numerujemy go jako w
    p->next = A[v];          // Dodajemy go na pocz¹tek listy A[v]
    A[v] = p;
    p = new slistEl;         // To samo dla krawêdzi w drug¹ stronê
    p->v = v;
    p->next = A[u];
    A[u] = p;
  }

  // Badamy spójnoœæ grafu
  spojnosc(A,visited,n);


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

  return 0;
}
