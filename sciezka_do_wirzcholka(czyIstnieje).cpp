#include <iostream>
#include <iomanip>

using namespace std;

// Typy dla dynamicznej tablicy list s¹siedztwa i stosu
//-----------------------------------------------------
struct slistEl
{
  slistEl * next;
  int v;
};

// Definicja typu obiektowego stack
//---------------------------------
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

// Zmienne globalne
//-----------------

int n;                   // Liczba wierzcho³ków
slistEl ** A;            // Macierz s¹siedztwa
stack S;                 // Stos
bool * visited;          // Tablica odwiedzin
int vs,vk;               // Wierzcho³ki startowy i koñcowy œcie¿ki

// Rekurencyjna funkcja DFS
//-------------------------
bool DFS(int v)
{
  visited[v] = true;     // Oznaczamy wierzcho³ek jako odwiedzony

  S.push(v);             // Zapamiêtujemy wierzcho³ek na stosie

  if(v == vk) return true; // Jeœli koniec, koñczymy

  // Przetwarzamy nieodwiedzonych s¹siadów

  for(slistEl * p = A[v]; p; p = p->next)
    if(!visited[p->v] && DFS(p->v)) return true;

  S.pop();               // Brak œcie¿ki, usuwamy wierzcho³ek ze stosu
  return false;          // Koñczymy z wynikiem false
}

// Procedura szukania œcie¿ki
//---------------------------
void DFS_Path()
{
  visited = new bool [n];// Tworzymy tablice odwiedzin
  for(int i = 0; i < n; i++) // Tablicê visited zerujemy
    visited[i] = false;

  if(!DFS(vs)) cout << "BRAK";
  else
    while(!S.empty())   // Wypisujemy œcie¿kê
    {
      cout << setw(3) << S.top();
      S.pop();
    }

  cout << endl;

  delete [] visited;
}

int main()
{
  int m,i;
  slistEl *p,*r;

  cin >> n >> m;               // Czytamy liczbê wierzcho³ków i krawêdzi

  A = new slistEl * [n];       // Tworzymy tablicê list s¹siedztwa

  // Tablicê wype³niamy pustymi listami

  for(i = 0; i < n; i++) A[i] = NULL;

  // Odczytujemy kolejne definicje krawêdzi

  for(i = 0; i < m; i++)
  {
    cin >> vs >> vk;    // Wierzcho³ek startowy i koñcowy krawêdzi
    p = new slistEl;    // Tworzymy nowy element
    p->v = vk;          // Numerujemy go jako vk
    p->next = A[vs];    // Dodajemy go na pocz¹tek listy A[vs]
    A[vs] = p;
  }

  // Odczytujemy wierzcho³ek startowy i koñcowy œcie¿ki

  cin >> vs >> vk;

  cout << endl;

  // Szukamy œcie¿ki

  DFS_Path();


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

  cout << endl;

  return 0;
}
