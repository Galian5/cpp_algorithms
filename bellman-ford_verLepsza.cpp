#include <iostream>

using namespace std;

const int MAXINT = 2147483647;    // Najwiêksza liczba ca³kowita

// Typy danych
struct slistEl
{
  slistEl * next;
  int v,w;
};
void wypisz(long long *d, int *p, int n)
{
    int *S = new int [n];              // Tworzymy prosty stos
    int sptr = 0;

    for(int i = 0; i < n; i++)
    {
      cout << i << ": ";
      for(int x = i;x != -1;x = p[x]) // Wierzcho³ki œcie¿ki umieszczamy na stosie
        S[sptr++] = x;            // w kolejnoœci od ostatniego do pierwszego

      while(sptr)                 // Wierzcho³ki ze stosu drukujemy
        cout << S[--sptr] << " "; // w kolejnoœci od pierwszego do ostatniego

      cout << "$" << d[i] << endl; // Na koñcu wyœwietlamy koszt
    }
    delete [] S;
}
bool BF(int v,int n, slistEl **A)
{
  int i,x,p[n];
  long long d[n];
  bool test;
  slistEl * pv;
  for(i = 0; i < n; i++)          // Inicjujemy struktury danych
  {
    d[i] = MAXINT;
    p[i] = -1;
  }


  d[v] = 0;                       // Zerujemy koszt dojœcia do v
  for(i = 1; i < n; i++)          // Pêtla relaksacji
  {
    test = true;                  // Oznacza, ¿e algorytm nie wprowadzi³ zmian do d i p
    for(x = 0; x < n; x++)        // Przechodzimy przez kolejne wierzcho³ki grafu
      for(pv = A[x]; pv; pv = pv->next) // Przegl¹damy listê s¹siadów wierzcho³ka x
        if(d[pv->v] > d[x] + pv->w) // Sprawdzamy warunek relaksacji
        {
          test = false;           // Jest zmiana w d i p
          d[pv->v] = d[x] + pv->w; // Relaksujemy krawêdŸ z x do jego s¹siada
          p[pv->v] = x;           // Poprzednikiem s¹siada bêdzie x
        }
    if(test)
    {
        wypisz(d,p,n);
        return true;
    }    // Jeœli nie by³o zmian, to koñczymy
  }

  // Sprawdzamy istnienie ujemnego cyklu

  for(x = 0; x < n; x++)
    for(pv = A[x];pv;pv = pv->next)
      if(d[pv->v] > d[x] + pv->w) return false; // ujemny cykl!!

  wypisz(d,p,n);
  return true;
}

int main()
{
  int v,x,y,w;
  slistEl *rv,*pv;
  int m,n;                          // Liczba krawêdzi i wierzcho³ków w grafie
  slistEl ** A;                     // Tablica dynamiczna list s¹siedztwa

  cin >> v >> n >> m;             // Wierzcho³ek startowy, liczba wierzcho³ków i krawêdzi

  A = new slistEl * [n];          // Tworzymy tablicê list s¹siedztwa
  for(int i = 0; i < n; i++)          // Inicjujemy struktury danych
  {
    A[i] = NULL;
  }

  for(int i = 0; i < m; i++)
  {
    cin >> x >> y >> w;           // Czytamy wierzcho³ki krawêdzi oraz jej wagê
    pv = new slistEl;             // Tworzymy element listy
    pv->v = y;                    // Inicjujemy go
    pv->w = w;
    pv->next = A[x];              // Dodajemy go na pocz¹tek listy s¹siadów wierzcho³ka x
    A[x] = pv;

  }

  cout << endl;

  if(BF(v,n,A));
  else cout << "Negative Cycle found!" << endl;

  for(int i = 0; i < n; i++)
  {
    pv = A[i];
    while(pv)
    {
      rv = pv;
      pv = pv->next;
      delete rv;
    }
  }

  delete [] A;

  return 0;
}
