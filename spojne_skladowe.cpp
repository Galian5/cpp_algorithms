#include <iostream>
#include <iomanip>

using namespace std;

// Typy dla dynamicznej tablicy list s�siedztwa i stosu

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

//---------------------
// Metody obiektu stack
//---------------------

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
void AP(slistEl **A, int n)
{
   int cn = 0,v,u;
   stack S;
   slistEl *p;
   int C[n];
   for(int i=0;i<n;i++)
            C[i]=0;

  for(int i = 0; i < n; i++)
    if(!C[i])                // Szukamy nieodwiedzonego jeszcze wierzcho�ka
    {
      cn++;                  // Zwi�kszamy licznik sk�adowych
      S.push(i);             // Na stosie umieszczamy numer bie��cego wierzcho�ka
      C[i] = cn;             // i oznaczamy go jako odwiedzonego i ponumerowanego
      while(!S.empty())      // Przechodzimy graf algorytmem DFS
      {
        v = S.top();         // Pobieramy wierzcho�ek
        S.pop();             // Usuwamy go ze stosu

        // Przegl�damy s�siad�w wierzcho�ka v

        for(p = A[v]; p; p = p->next)
        {
          u = p->v;          // Numer s�siada do u
          if(!C[u])
          {
            S.push(u);       // Na stos id� s�siedzi nieodwiedzeni
            C[u] = cn;       // i ponumerowani
          }
        }
      }
    }
  for(int i = 1; i <= cn; i++)
  {
    cout << "SCC : " << i << " : "; // Numer sp�jnej sk�adowej
    for(int j = 0; j < n; j++)
      if(C[j] == i) cout << setw(2) << j << " "; // Wierzcho�ki tej sk�adowej
    cout << endl;
  }
}

int main()
{
  int n,m;                   // Liczba wierzcho�k�w i kraw�dzi
  slistEl ** A;              // Tablica list s�siedztwa
  int cn,i,j,v,u;
  slistEl *p,*r;

  cin >> n >> m;             // Odczytujemy liczb� wierzcho�k�w i kraw�dzi

  A = new slistEl * [n];     // Tworzymy tablice dynamiczne
  for(i = 0; i < n; i++)
  {
    A[i] = NULL;
  }

  // Odczytujemy kolejne definicje kraw�dzi.

  for(i = 0; i < m; i++)
  {
    cin >> v >> u;           // Wierzcho�ki tworz�ce kraw�d�
    p = new slistEl;         // Tworzymy nowy element
    p->v = u;                // Numerujemy go jako w
    p->next = A[v];          // Dodajemy go na pocz�tek listy A[v]
    A[v] = p;
    p = new slistEl;         // To samo dla kraw�dzi w drug� stron�
    p->v = v;
    p->next = A[u];
    A[u] = p;
  }

   AP(A,n);

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
