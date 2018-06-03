#include <iostream>

using namespace std;

// Typy dla dynamicznej tablicy list s¹siedztwa i listy mostów

struct slistEl
{
  slistEl * next;
  int v;
};

// Zmienne globalne

int n,m,cv;                   // Liczba wierzcho³ków, krawêdzi, numeracja
slistEl ** graf;              // Tablica list s¹siedztwa
int *D;                       // Numery DFS
slistEl * L;                  // Lista mostów

// Funkcja rekurencyjna wyszukuj¹ca mosty
// v  - numer bie¿¹cego wierzcho³ka
// vf - ojciec bie¿¹cego wierzcho³ka na drzewie rozpinaj¹cym
// Reszta parametrów to zmienne globalne
//----------------------------------------------------------
int DFSb(int v, int vf)
{
  int Low,temp,u;
  slistEl * p;

  // Numerujemy wierzcho³ek, ustalamy wstêpn¹ wartoœæ Low oraz zwiêkszamy numeracjê

  D[v] = Low = cv++;

  for(p = graf[v]; p; p = p->next) // Przegl¹damy listê s¹siadów
  {
    u = p->v;                 // u - numer wierzcho³ka s¹siada
    if(u != vf)               // u nie mo¿e byæ ojcem v
    {
      if(!D[u])               // Jeœli s¹siad u nie by³ odwiedzany, to
      {
        temp = DFSb(u,v);     // rekurencyjnie odwiedzamy go
        if(temp < Low) Low = temp;
      }
      else if(D[u] < Low) Low = D[u];
    }
  }

  // Wszyscy s¹siedzi zostali odwiedzeni. Teraz robimy test na most

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
  int i,u,v;                 // Numery wierzcho³ków
  slistEl *p,*r;

  cin >> n >> m;             // Odczytujemy liczbê wierzcho³ków i krawêdzi

  graf = new slistEl * [n]; // Tworzymy zmienne dynamiczne
  D = new int[n];
  L = NULL;

  for(i = 0; i < n; i++)
  {
    graf[i] = NULL;
    D[i]    = 0;
  }

  // Odczytujemy kolejne definicje krawêdzi

  for(i = 0; i < m; i++)
  {
    cin >> v >> u;           // Wierzcho³ki tworz¹ce krawêdŸ
    p = new slistEl;         // Tworzymy nowy element
    p->v = u;                // Numerujemy go jako w
    p->next = graf[v];       // Dodajemy go na pocz¹tek listy graf[v]
    graf[v] = p;
    p = new slistEl;         // To samo dla krawêdzi w drug¹ stronê
    p->v = v;
    p->next = graf[u];
    graf[u] = p;
  }

  // Szukamy mostów

  for(i = 0; i < n; i++)
    if(!D[i])               // Szukamy nieodwiedzonego wierzcho³ka
    {
      cv   = 1;             // Pocz¹tek numeracji DFS
      DFSb(i,-1);           // Szukamy mostów
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
