#include <iostream>
#include <iomanip>

using namespace std;

// Typy danych

struct dlistEl
{
  dlistEl *next,*prev;
  int v;
};

int m,n;                        // Liczba krawêdzi i wierzcho³ków
char **graf;                    // Dynamiczna macierz s¹siedztwa
bool * visited;                 // Tablica odwiedzin

// Procedury obs³ugi listy dwukierunkowej
//---------------------------------------

// Procedura do³¹cza do listy nowy element
// za elementem wskazywanym przez p
//------------------------------------------
void addC(int x, dlistEl *p)
{
  dlistEl * r;

  r = new dlistEl;
  r->v = x;
  r->next = p->next;
  if(r->next) r->next->prev = r;
  r->prev = p;
  p->next = r;
}

// Procedura usuwa z listy element wskazywany przez p
//---------------------------------------------------
void remC(dlistEl *p)
{
  if(p->next) p->next->prev = p->prev;
  if(p->prev) p->prev->next = p->next;
  delete p;
}

// Rekurencyjna funkcja dodaj¹ca do listy nowy cykl
// v - wierzcho³ek startowy i koñcowy cyklu
// w - wierzcho³ek bie¿¹cy
// p - referencja do wskazania punktu wstawiania na liœcie
//--------------------------------------------------------
bool DFSaddCycle(int v, int w, dlistEl * & p)
{
  int u;

  visited[w] = true;            // Oznaczamy v jako odwiedzony
  addC(w,p);                    // Dodajemy w do cyklu
  p = p->next;                  // p wskazuje dodany element
  for(u = 0; u < n; u++)        // Przegl¹damy s¹siadów w
    if(graf[w][u])
    {
      if(u == v)                // Cykl znaleziony?
      {
        addC(v,p);              // Zamykamy cykl na liœcie C
        do
        {
          graf[p->v][p->next->v] = 0; // Usuwamy krawêdzie cyklu
          if(p->v == v) return true;
          p = p->prev;
        } while(true);
      }
      if(!visited[u] && DFSaddCycle(v,u,p)) return true;
    }
  p = p->prev;                 // Z listy usuwamy w
  remC(p->next);
  return false;
}
int main()
{
  int i,j,v1,v2;
  dlistEl *C,*p;

  cin >> n >> m;                // Czytamy liczbê wierzcho³ków i krawêdzi

  // Tworzymy tablice dynamiczne

  graf    = new char * [n];
  visited = new bool [n];
  for(i = 0; i < n; i++)
  {
    graf[i] = new char [n];
    for(j = 0; j < n; j++) graf[i][j] = 0;
  }

  // Odczytujemy definicje krawêdzi grafu

  for(i = 0; i < m; i++)
  {
    cin >> v1 >> v2;
    graf[v1][v2] = 1;
  }

  C = new dlistEl;              // Tworzymy listê z wierzcho³kiem v1
  C->v = v1;
  C->next = NULL;
  C->prev = NULL;

  for(p = C; p; p = p->next)    // Przegl¹damy listê C
    for(i = 0; i < n; i++)      // Szukamy s¹siadów
      if(graf[p->v][i])
      {
        for(j = 0; j < n; j++) visited[j] = false;
        DFSaddCycle(p->v,i,p);  // Dla ka¿dego s¹siada uruchamiamy szukanie cyklu
      }

  cout << endl;

  // Wyœwietlamy zawartoœæ listy C, czyli pe³ny cykl Eulera

  for(p = C; p; p = p->next) cout << setw(3) << p->v;

  cout << endl;

  // Usuwamy zmienne dynamiczne

  p = C;
  while(p)
  {
    p = C->next;
    remC(C);
    C = p;
  }

  for(i = 0; i < n; i++) delete [] graf[i];

  delete [] graf;
  delete [] visited;

  return 0;
}
