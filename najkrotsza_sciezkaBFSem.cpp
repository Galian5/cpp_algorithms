#include <iostream>
#include <iomanip>

using namespace std;

const int MAXINT = -2147483647;

// Typy dla dynamicznej tablicy list s¹siedztwa i kolejki

struct slistEl
{
  slistEl * next;
  int v;
};

// Definicja typu obiektowego queue
//---------------------------------
class queue
{
  private:
    slistEl * head;
    slistEl * tail;

  public:
    queue();      // konstruktor
    ~queue();     // destruktor
    bool empty(void);
    int  front(void);
    void push(int v);
    void pop(void);
};
// Konstruktor - tworzy pust¹ listê
//---------------------------------
queue::queue()
{
  head = tail = NULL;
}

// Destruktor - usuwa listê z pamiêci
//-----------------------------------
queue::~queue()
{
  while(head) pop();
}

// Sprawdza, czy kolejka jest pusta
//---------------------------------
bool queue::empty(void)
{
  return !head;
}

// Zwraca pocz¹tek kolejki.
// Wartoœæ specjalna to -MAXINT
//-----------------------------
int queue::front(void)
{
  if(head) return head->v;
  else     return -MAXINT;
}

// Zapisuje do kolejki
//--------------------
void queue::push(int v)
{
  slistEl * p = new slistEl;
  p->next = NULL;
  p->v = v;
  if(tail) tail->next = p;
  else     head = p;
  tail = p;
}

// Usuwa z kolejki
//----------------
void queue::pop(void)
{
  if(head)
  {
    slistEl * p = head;
    head = head->next;
    if(!head) tail = NULL;
    delete p;
  }
}

// Zmienne globalne
//-----------------
int n;                   // Liczba wierzcho³ków
slistEl ** A;            // Macierz s¹siedztwa

// Procedura szukania œcie¿ki
// vs - numer wierzcho³ka startowego
// vk - numer wierzcho³ka koñcowego
//----------------------------------
void BFS_Path(int vs, int vk)
{
  queue Q;
  bool * visited, found;
  int  * P,v,u,i;
  slistEl * pv;

  visited = new bool[n];   // Tworzymy tablice odwiedzin
  for(i = 0; i < n; i++)   // Tablicê visited zerujemy
    visited[i] = false;

  P = new int[n];          // Tworzymy tablicê œcie¿ki

  P[vs] = -1;

  Q.push(vs);              // W kolejce umieszczamy wierzcho³ek startowy

  visited[vs] = true;      // i oznaczamy go jako startowy

  found = false;

  while(!Q.empty())
  {
    v = Q.front();         // Pobieramy z kolejki wierzcho³ek v
    Q.pop();

    if(v == vk)            // Sprawdzamy koniec œcie¿ki
    {
      found = true;        // Zaznaczamy sukces
      break;               // Przerywamy pêtlê
    }

    // Przegl¹damy s¹siadów wierzcho³ka v

    for(pv = A[v]; pv; pv = pv->next)
    {
      u = pv->v;
      if(!visited[u])
      {
        P[u] = v;          // W P zapisujemy fragment œcie¿ki
        Q.push(u);         // S¹siad zostaje umieszczony w kolejce
        visited[u] = true; // i oznaczony jako odwiedzony
      }
    }
  }

  if(!found) cout << "BRAK";// Œcie¿ka nie zosta³a znaleziona
  else
    while(v > -1)
    {
      cout << setw(3) << v;// Wypisujemy wierzcho³ki œcie¿ki
      v = P[v];            // Cofamy siê do poprzedniego wierzcho³ka œcie¿ki
    }

  delete [] P;
  delete [] visited;
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

  // Tablicê wype³niamy pustymi listami

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

  // Odczytujemy wierzcho³ek startowy i koñcowy œcie¿ki

  cin >> v1 >> v2;

  cout << endl;

  BFS_Path(v1,v2);      // Szukamy œcie¿ki

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

  cout << endl;

  return 0;
}
