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
    slistEl * S;   // lista przechowuj�ca stos

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

// Destruktor - zwalnia tablic� dynamiczn�
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

// Funkcja rekurencyjna wyszukuj�ca cykl
//--------------------------------------
bool DFSfindCycle(slistEl ** graf, int v, int w, stack & S, bool * visited)
{
  int u;

  visited[w] = true;             // Oznaczamy wierzcho�ek jako odwiedzony
  slistEl *p = graf[w];                   // Rozpoczynamy przegl�danie s�siad�w
  while(p)
  {
    u = p->v;                    // u - numer wierzcho�ka b�d�cego s�siadem
    if(u != S.top())             // Pomijamy wierzcho�ek, z kt�rego przyszli�my
    {
      S.push(w);                 // Na stos wierzcho�ek bie��cy
      if(u == v) return true;    // Cykl znaleziony, ko�czymy
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

  cin >> n >> m;         // Czytamy liczb� wierzcho�k�w i kraw�dzi

  A = new slistEl * [n]; // Tworzymy tablic� list s�siedztwa

  // Tablice wype�niamy pustymi listami

  for(i = 0; i < n; i++) A[i] = NULL;

  for(i = 0; i < m; i++)
  {
    cin >> v1 >> v2;    // Wierzcho�ek startowy i ko�cowy kraw�dzi
    p = new slistEl;    // Tworzymy nowy element
    p->v = v2;          // Numerujemy go jako v2
    p->next = A[v1];    // Dodajemy go na pocz�tek listy A[v1]
    A[v1] = p;
    p = new slistEl;    // Kraw�d� w drug� stron�, bo graf jest nieskierowany
    p->v = v1;
    p->next = A[v2];
    A[v2] = p;
  }

  cout << endl;

  visited = new bool [n];          // Tworzymy tablic� odwiedzin

  for(i = 0; i < n; i++)           // Przechodzimy przez kolejne wierzcho�ki grafu
  {
    for(j = 0; j < n; j++)         // Zerujemy tablic� odwiedzin
      visited[j] = false;

    S.push(-1);                    // Na stos znacznik pocz�tku �cie�ki

    cout << i <<": ";                     // Wypisujemy wierzcho�ek startowy cyklu

    if(!DFSfindCycle(A,i,i,S,visited)) // Szukamy cyklu
    {
      S.pop();                     // Usuwamy ze stosu pocz�tek �cie�ki
      cout << " - no cycle\n";   // Komunikat
    }
    else
      while(!S.empty())            // Wypisujemy cykl, jesli istnieje
      {
        u = S.top(); S.pop();      // Pobieramy ze stosu numer wierzcjo�ka
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
