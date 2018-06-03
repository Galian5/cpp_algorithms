#include <iostream>
#include <iomanip>

using namespace std;

// Typy dla dynamicznej tablicy list s�siedztwa i stosu
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

// Zmienne globalne
//-----------------

int n;                   // Liczba wierzcho�k�w
slistEl ** A;            // Macierz s�siedztwa
stack S;                 // Stos
bool * visited;          // Tablica odwiedzin
int vs,vk;               // Wierzcho�ki startowy i ko�cowy �cie�ki

// Rekurencyjna funkcja DFS
//-------------------------
bool DFS(int v)
{
  visited[v] = true;     // Oznaczamy wierzcho�ek jako odwiedzony

  S.push(v);             // Zapami�tujemy wierzcho�ek na stosie

  if(v == vk) return true; // Je�li koniec, ko�czymy

  // Przetwarzamy nieodwiedzonych s�siad�w

  for(slistEl * p = A[v]; p; p = p->next)
    if(!visited[p->v] && DFS(p->v)) return true;

  S.pop();               // Brak �cie�ki, usuwamy wierzcho�ek ze stosu
  return false;          // Ko�czymy z wynikiem false
}

// Procedura szukania �cie�ki
//---------------------------
void DFS_Path()
{
  visited = new bool [n];// Tworzymy tablice odwiedzin
  for(int i = 0; i < n; i++) // Tablic� visited zerujemy
    visited[i] = false;

  if(!DFS(vs)) cout << "BRAK";
  else
    while(!S.empty())   // Wypisujemy �cie�k�
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

  cin >> n >> m;               // Czytamy liczb� wierzcho�k�w i kraw�dzi

  A = new slistEl * [n];       // Tworzymy tablic� list s�siedztwa

  // Tablic� wype�niamy pustymi listami

  for(i = 0; i < n; i++) A[i] = NULL;

  // Odczytujemy kolejne definicje kraw�dzi

  for(i = 0; i < m; i++)
  {
    cin >> vs >> vk;    // Wierzcho�ek startowy i ko�cowy kraw�dzi
    p = new slistEl;    // Tworzymy nowy element
    p->v = vk;          // Numerujemy go jako vk
    p->next = A[vs];    // Dodajemy go na pocz�tek listy A[vs]
    A[vs] = p;
  }

  // Odczytujemy wierzcho�ek startowy i ko�cowy �cie�ki

  cin >> vs >> vk;

  cout << endl;

  // Szukamy �cie�ki

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
