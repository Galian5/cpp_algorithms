#include <iostream>

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

//---------------------
// Metody obiektu queue
//---------------------

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

// Funkcja testuje dwudzielno�� grafu
// n - liczba wierzcho�k�w grafu
// A - tablica list s�siedztwa
//-----------------------------------
bool isBipartite(int n, slistEl ** A)
{
  queue Q;
  int * C;
  int v,u,i;
  slistEl * p;

  C = new int [n];         // Tworzymy tablic� kolor�w
  for(i = 0; i < n; i++) C[i] = 0;

  for(i = 0; i < n; i++)   // Przechodzimy przez kolejne wierzcho�ki
    if(!C[i])              // Szukamy wierzcho�ka szarego
    {
      C[i] = 1;            // Wierzcho�ek startowy kolorujemy na czerwono
      Q.push(i);           // i umieszczamy w kolejce

      while(!Q.empty())    // Przej�cie BFS
      {
        v = Q.front();     // Pobieramy wierzcho�ek z kolejki
        Q.pop();           // Pobrany wierzcho�ek usuwamy z kolejki
        for(p = A[v]; p; p = p->next) // Przegl�damy s�siad�w wierzcho�ka v
        {
          u = p->v;        // pobieramy z listy s�siedztwa numer s�siada
          if(C[u] == C[v])
          {
            delete [] C;
            return false;  // S�siad ma ten sam kolor
          }

          if(!C[u])        // Je�li wierzcho�ek nie jest odwiedzony,
          {
            C[u] = -C[v];  // kolorujemy go na kolor przeciwny
            Q.push(u);     // i umieszczamy w kolejce
          }
        }
      }
    }
  delete [] C;

  return true;
}


int main()
{
  int n,m,i,v1,v2;
  slistEl * p,* r,** A;

  cin >> n >> m;         // Czytamy liczb� wierzcho�k�w i kraw�dzi

  A = new slistEl * [n]; // Tworzymy tablic� list s�siedztwa

  // Tablice wype�niamy pustymi listami

  for(i = 0; i < n; i++) A[i] = NULL;

  // Odczytujemy kolejne definicje kraw�dzi

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

  if(isBipartite(n,A)) cout << "BIPARTITE GRAPH"; else cout << "NOT A BIPARTITE GRAPH";

  cout << endl;

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

  return 0;
}
