#include <iostream>
#include <iomanip>

using namespace std;

const int MAXINT = -2147483647;

// Typy dla dynamicznej tablicy list s�siedztwa i kolejki

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
// Konstruktor - tworzy pust� list�
//---------------------------------
queue::queue()
{
  head = tail = NULL;
}

// Destruktor - usuwa list� z pami�ci
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

// Zwraca pocz�tek kolejki.
// Warto�� specjalna to -MAXINT
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
int n;                   // Liczba wierzcho�k�w
slistEl ** A;            // Macierz s�siedztwa

// Procedura szukania �cie�ki
// vs - numer wierzcho�ka startowego
// vk - numer wierzcho�ka ko�cowego
//----------------------------------
void BFS_Path(int vs, int vk)
{
  queue Q;
  bool * visited, found;
  int  * P,v,u,i;
  slistEl * pv;

  visited = new bool[n];   // Tworzymy tablice odwiedzin
  for(i = 0; i < n; i++)   // Tablic� visited zerujemy
    visited[i] = false;

  P = new int[n];          // Tworzymy tablic� �cie�ki

  P[vs] = -1;

  Q.push(vs);              // W kolejce umieszczamy wierzcho�ek startowy

  visited[vs] = true;      // i oznaczamy go jako startowy

  found = false;

  while(!Q.empty())
  {
    v = Q.front();         // Pobieramy z kolejki wierzcho�ek v
    Q.pop();

    if(v == vk)            // Sprawdzamy koniec �cie�ki
    {
      found = true;        // Zaznaczamy sukces
      break;               // Przerywamy p�tl�
    }

    // Przegl�damy s�siad�w wierzcho�ka v

    for(pv = A[v]; pv; pv = pv->next)
    {
      u = pv->v;
      if(!visited[u])
      {
        P[u] = v;          // W P zapisujemy fragment �cie�ki
        Q.push(u);         // S�siad zostaje umieszczony w kolejce
        visited[u] = true; // i oznaczony jako odwiedzony
      }
    }
  }

  if(!found) cout << "BRAK";// �cie�ka nie zosta�a znaleziona
  else
    while(v > -1)
    {
      cout << setw(3) << v;// Wypisujemy wierzcho�ki �cie�ki
      v = P[v];            // Cofamy si� do poprzedniego wierzcho�ka �cie�ki
    }

  delete [] P;
  delete [] visited;
}

// **********************
// *** PROGRAM G��WNY ***
// **********************

int main()
{
  int m,i,v1,v2;
  slistEl *p,*r;

  cin >> n >> m;               // Czytamy liczb� wierzcho�k�w i kraw�dzi

  A = new slistEl * [n];       // Tworzymy tablic� list s�siedztwa

  // Tablic� wype�niamy pustymi listami

  for(i = 0; i < n; i++) A[i] = NULL;

  // Odczytujemy kolejne definicje kraw�dzi

  for(i = 0; i < m; i++)
  {
    cin >> v1 >> v2;    // Wierzcho�ek startowy i ko�cowy kraw�dzi
    p = new slistEl;    // Tworzymy nowy element
    p->v = v2;          // Numerujemy go jako v2
    p->next = A[v1];    // Dodajemy go na pocz�tek listy A[v1]
    A[v1] = p;
  }

  // Odczytujemy wierzcho�ek startowy i ko�cowy �cie�ki

  cin >> v1 >> v2;

  cout << endl;

  BFS_Path(v1,v2);      // Szukamy �cie�ki

  // Usuwamy tablic� list s�siedztwa

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
