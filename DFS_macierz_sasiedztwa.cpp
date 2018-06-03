#include <iostream>
#include <iomanip>

using namespace std;

// Zmienne globalne

int n;                   // Liczba wierzcho�k�w
char ** A;               // Macierz s�siedztwa
bool * visited;          // Tablica odwiedzin

// Rekurencyjna procedura przej�cia w g��b
//----------------------------------------
void DFS(int v)
{
  visited[v] = true;     // Zaznaczamy w�ze� jako odwiedzony
  cout << setw(3) << v;  // Przetwarzamy w�ze� (wypisujemy jego numer)

// Rekurencyjnie odwiedzamy nieodwiedzonych s�siad�w

  for(int i = 0; i < n; i++)
    if((A[v][i] == 1) && !visited[i]) DFS(i);
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

  // Przechodzimy graf w g��b

  DFS(0);

  // Usuwamy macierz

  for(i = 0; i < n; i++) delete A[i];
  delete [] A;
  delete [] visited;

  cout << endl;

  return 0;
}
