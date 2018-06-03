#include <iostream>
#include <iomanip>

using namespace std;

// Zmienne globalne

int n;                   // Liczba wierzcho³ków
char ** A;               // Macierz s¹siedztwa
bool * visited;          // Tablica odwiedzin

// Rekurencyjna procedura przejœcia w g³¹b
//----------------------------------------
void DFS(int v)
{
  visited[v] = true;     // Zaznaczamy wêze³ jako odwiedzony
  cout << setw(3) << v;  // Przetwarzamy wêze³ (wypisujemy jego numer)

// Rekurencyjnie odwiedzamy nieodwiedzonych s¹siadów

  for(int i = 0; i < n; i++)
    if((A[v][i] == 1) && !visited[i]) DFS(i);
}

// **********************
// *** PROGRAM G£ÓWNY ***
// **********************

int main()
{
  int m,i,j,v1,v2;

  cin >> n >> m;         // Czytamy liczbê wierzcho³ków i krawêdzi

  A = new char * [n];    // Tworzymy tablicê wskaŸników
  visited = new bool[n]; // Tworzymy tablicê odwiedzin

  for(i = 0; i < n; i++)
    A[i] = new char[n];  // Tworzymy wiersze

  // Macierz wype³niamy zerami

  for(i = 0; i < n; i++)
  {
    visited[i] = false;  // Zerujemy tablicê odwiedzin
    for(j = 0; j < n; j++) A[i][j] = 0;
  }

  // Odczytujemy kolejne definicje krawêdzi

  for(i = 0; i < m; i++)
  {
    cin >> v1 >> v2;    // Wierzcho³ek startowy i koñcowy krawêdzi
    A[v1][v2] = 1;      // KrawêdŸ v1->v2 obecna
  }

  cout << endl;

  // Przechodzimy graf w g³¹b

  DFS(0);

  // Usuwamy macierz

  for(i = 0; i < n; i++) delete A[i];
  delete [] A;
  delete [] visited;

  cout << endl;

  return 0;
}
