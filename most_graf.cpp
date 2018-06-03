#include <iostream>

using namespace std;

// Typy dla dynamicznej tablicy list s�siedztwa i listy most�w

struct slistEl
{
  slistEl * next;
  int v;
};

// Zmienne globalne

int n,m,cv;                   // Liczba wierzcho�k�w, kraw�dzi, numeracja
slistEl ** graf;              // Tablica list s�siedztwa
int *D;                       // Numery DFS
slistEl * L;                  // Lista most�w

// Funkcja rekurencyjna wyszukuj�ca mosty
// v  - numer bie��cego wierzcho�ka
// vf - ojciec bie��cego wierzcho�ka na drzewie rozpinaj�cym
// Reszta parametr�w to zmienne globalne
//----------------------------------------------------------
int DFSb(int v, int vf)
{
  int Low,temp,u;
  slistEl * p;

  // Numerujemy wierzcho�ek, ustalamy wst�pn� warto�� Low oraz zwi�kszamy numeracj�

  D[v] = Low = cv++;

  for(p = graf[v]; p; p = p->next) // Przegl�damy list� s�siad�w
  {
    u = p->v;                 // u - numer wierzcho�ka s�siada
    if(u != vf)               // u nie mo�e by� ojcem v
    {
      if(!D[u])               // Je�li s�siad u nie by� odwiedzany, to
      {
        temp = DFSb(u,v);     // rekurencyjnie odwiedzamy go
        if(temp < Low) Low = temp;
      }
      else if(D[u] < Low) Low = D[u];
    }
  }

  // Wszyscy s�siedzi zostali odwiedzeni. Teraz robimy test na most

  if((vf > -1) && (Low == D[v]))
  {
    p = new slistEl;         // Mamy most. Dodajemy go do listy L
    p->v = v;
    p->next = L;
    L = p;
    p = new slistEl;
    p->v = vf;
    p->next = L;
    L = p;
  }

  return Low;                // Wynik
}

int main()
{
  int i,u,v;                 // Numery wierzcho�k�w
  slistEl *p,*r;

  cin >> n >> m;             // Odczytujemy liczb� wierzcho�k�w i kraw�dzi

  graf = new slistEl * [n]; // Tworzymy zmienne dynamiczne
  D = new int[n];
  L = NULL;

  for(i = 0; i < n; i++)
  {
    graf[i] = NULL;
    D[i]    = 0;
  }

  // Odczytujemy kolejne definicje kraw�dzi

  for(i = 0; i < m; i++)
  {
    cin >> v >> u;           // Wierzcho�ki tworz�ce kraw�d�
    p = new slistEl;         // Tworzymy nowy element
    p->v = u;                // Numerujemy go jako w
    p->next = graf[v];       // Dodajemy go na pocz�tek listy graf[v]
    graf[v] = p;
    p = new slistEl;         // To samo dla kraw�dzi w drug� stron�
    p->v = v;
    p->next = graf[u];
    graf[u] = p;
  }

  // Szukamy most�w

  for(i = 0; i < n; i++)
    if(!D[i])               // Szukamy nieodwiedzonego wierzcho�ka
    {
      cv   = 1;             // Pocz�tek numeracji DFS
      DFSb(i,-1);           // Szukamy most�w
    }

  cout << endl;

  // Wypisujemy znalezione mosty

  v = 0;

  while(L)
  {
    cout << L->v << " ";
    v ^= 1;
    if(!v) cout << endl;
    p = L;
    L = L->next;
    delete p;
  }

  // Usuwamy struktury dynamiczne

  delete [] D;

  for(i = 0; i < n; i++)
  {
    p = graf[i];
    while(p)
    {
      r = p;
      p = p->next;
      delete r;
    }
  }

  delete graf;

  return 0;
}
