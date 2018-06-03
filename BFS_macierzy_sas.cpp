#include <iostream>
#include <iomanip>

using namespace std;

// Typ element�w listy dla kolejki

struct slistEl
{
  slistEl * next;
  int data;
};

// Zmienne globalne

int n;                   // Liczba wierzcho�k�w
char ** A;               // Macierz s�siedztwa
bool * visited;          // Tablica odwiedzin

// Procedura przej�cia wszerz
//---------------------------
void BFS(int v)
{
  int i;
  slistEl *q,*head,*tail; // Kolejka

  q = new slistEl;        // W kolejce umieszczamy v
  q->next = NULL;
  q->data = v;
  head = tail = q;

  visited[v] = true;      // Wierzcho�ek v oznaczamy jako odwiedzony

  while(head)
  {
    v = head->data;       // Odczytujemy v z kolejki

    q = head;             // Usuwamy z kolejki odczytane v
    head = head->next;
    if(!head) tail = NULL;
    delete q;

    cout << setw(3) << v;

    for(i = 0; i < n; i++)
      if((A[v][i] == 1) && !visited[i])
      {
        q = new slistEl; // W kolejce umieszczamy nieodwiedzonych s�siad�w
        q->next = NULL;
        q->data = i;
        if(!tail) head = q;
        else tail->next = q;
        tail = q;
        visited[i] = true; // i oznaczamy ich jako odwiedzonych
      }
  }
}

// **********************
// *** PROGRAM G��WNY ***
// **********************

int main()
{
  int m,i,j,v1,v2;

  cin >> n >> m;         // Czytamy liczb� wierzcho�k�w i kraw�dzi

  A = new char * [n];    // Tworzymy tablic� wska�nik�w
  visited = new bool[n]; // Tworzymy tablic� odwiedzin

  for(i = 0; i < n; i++)
    A[i] = new char[n];  // Tworzymy wiersze

  // Macierz wype�niamy zerami

  for(i = 0; i < n; i++)
  {
    visited[i] = false;  // Zerujemy tablic� odwiedzin
    for(j = 0; j < n; j++) A[i][j] = 0;
  }

  // Odczytujemy kolejne definicje kraw�dzi

  for(i = 0; i < m; i++)
  {
    cin >> v1 >> v2;    // Wierzcho�ek startowy i ko�cowy kraw�dzi
    A[v1][v2] = 1;      // Kraw�d� v1->v2 obecna
  }

  cout << endl;

  // Przechodzimy graf wszerz

  BFS(0);

  // Usuwamy macierz

  for(i = 0; i < n; i++) delete A[i];
  delete [] A;
  delete [] visited;

  cout << endl;

  return 0;
}
