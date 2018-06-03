#include <iostream>

using namespace std;

// Typy dla dynamicznej tablicy list s¹siedztwa i stosu

struct slistEl
{
  slistEl * next;
  int v;
};

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

// Funkcja bada graf pod k¹tem posiadania cyklu lub œcie¿ki Eulera
// n    - liczba wierzcho³ków w grafie
// graf - tablica list s¹siedztwa
// Wynik:
// 0 - graf nie zawiera œcie¿ki lub cyklu Eulera
// 1 - graf zawiera œcie¿kê Eulera
// 2 - graf zawiera cykl Eulera
//-----------------------------------------------------------------
int isEulerian(int n, slistEl ** graf)
{
  int no,nc,i,v,u;
  stack S;
  bool * visited;
  slistEl *p;

  for(i = 0; i < n && !graf[i]; i++); // Szukamy pierwszego wierzcho³ka z s¹siadami

  if(i == n) return 1;        // Graf nie ma krawêdzi

  visited = new bool [n];     // Tworzymy dynamicznie tablicê odwiedzin
  for(v = 0; v < n; v++)      // Wype³niamy j¹ wartoœciami false
    visited[v] = false;

  no = 0;                     // Zerujemy licznik wierzcho³ków o stopniu nieparzystym

  S.push(i);                  // Wierzcho³ek startowy na stos
  visited[i] = true;          // oznaczamy go jako odwiedzony

  // Uruchamiamy przejœcie DFS, aby wyznaczyæ spójn¹ sk³adow¹ zawieraj¹c¹
  // wierzcho³ek startowy oraz policzyæ stopnie wierzcho³ków i wyznaczyæ
  // liczbê wierzcho³ków o stopniach nieparzystych

  while(!S.empty())
  {
    v = S.top();              // Pobieramy do v wierzcho³ek ze stosu
    S.pop();                  // Pobrany wierzcho³ek usuwamy ze stosu

    nc = 0;                   // Licznik s¹siadów na zero

    for(p = graf[v]; p; p = p->next) // Przegl¹damy s¹siadów wierzcho³ka v
    {
      nc++;                   // Zwiêkszamy licznik s¹siadów
      u = p->v;
      if(!visited[u])         // Szukamy nieodwiedzonych s¹siadów
      {
        visited[u] = true;    // Zaznaczamy ich jako odwiedzonych
        S.push(u);            // i umieszczamy na stosie
      }
    }

    if(nc % 2 == 1) no++;     // Nieparzysta liczba s¹siadów?
  }

  for(v = i + 1; v < n; v++)  // Przegl¹damy pozosta³e wierzcho³ki grafu
    if(!visited[v] && graf[v])
    {
      delete [] visited;      // Usuwamy tablicê odwiedzin
      return 0;               // graf nie jest spójny
    }

  delete [] visited;          // Usuwamy tablicê odwiedzin

  if(!no) return 2;           // Graf zawiera cykl Eulera

  if(no == 2) return 1;       // Graf zawiera œcie¿kê Eulera

  return 0;                   // Graf nie posiada œcie¿ki lub cyklu Eulera
}

int main()
{
  int n,m,i,v1,v2;
  slistEl * p,* r,** A;

  cin >> n >> m;         // Czytamy liczbê wierzcho³ków i krawêdzi

  A = new slistEl * [n]; // Tworzymy tablicê list s¹siedztwa

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
    p = new slistEl;    // KrawêdŸ w drug¹ stronê, bo graf jest nieskierowany
    p->v = v1;
    p->next = A[v2];
    A[v2] = p;
  }

  cout << endl;

  int wynik=isEulerian(n,A)
  if(wynik==0)cout << "NOT AN EULERIAN GRAPH\n";
  else if(wynikk==1) cout << "SEMI-EULERIAN GRAPH\n"
  else cout << "EULERIAN GRAPH\n";


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
