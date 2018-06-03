#include <iostream>

using namespace std;

const int MAXINT = 2147483647;    // "plus nieskoñczonoœæ"


// Funkcja wyznaczania kosztów dojœcia oraz
// minimalnych œcie¿ek w grafie wa¿onym
//------------------------------------------
bool FloydWarshall(int **d, int **p,int n)
{
  int w; // koszt

  for(int k = 0; k < n; k++)
    for(int i = 0; i < n; i++)
      for(int j = 0; j < n; j++)
      {
        if((d[i][k] == MAXINT) || (d[k][j] == MAXINT)) continue;
        w = d[i][k] + d[k][j];
        if(d[i][j] > w)
        {
          d[i][j] = w;
          p[i][j] = p[k][j];
        }
      }
  for(int i = 0; i < n; i++)
    if(d[i][i] < 0) return false; // Ujemny cykl
  return true;
}

// Rekurencyjna procedura odtwarzania minimalnej
// œcie¿ki z macierzy poprzedników p
//----------------------------------------------
void FWPath(int i, int j,int **p)
{
  if(i == j) cout << i << " ";
  else if(p[i][j] == -1) cout << "NO PATH";
  else
  {
    FWPath(i,p[i][j],p);
    cout << j << " ";
  }
}

int main()
{
  int i,j,x,y,w;
  int **d, **p;                     // Macierze kosztów oraz poprzeników
  int n,m;

  cin >> n >> m;                  // Czytamy liczbê wierzcho³ków oraz krawêdzi

  d = new int * [n];
  p = new int * [n];

  for(i = 0; i < n; i++)
  {
    d[i] = new int [n];
    p[i] = new int [n];
    for(j = 0; j < n; j++)
    {
      d[i][j] = MAXINT;          // Wiersz d wype³niamy najwiêksz¹ liczb¹ dodatni¹
      p[i][j] = -1;              // Wiersz p wype³niamy liczbami -1 (brak poprzednika)
    }
    d[i][i] = 0;                 //  na przek¹tnej d wpisujemy 0
  }

  for(i = 0; i < m; i++)
  {
    cin >> x >> y >> w;          // Czytamy definicjê krawêdzi
    d[x][y] = w;                 // Wagê krawêdzi umieszczamy w macierzy d
    p[x][y] = x;                 // Poprzednikiem y jest x
  }
  // korzystajac z list sasiedztwa nale¿aloby wpisywac dane wierzcholki do macierzy w czasie O(E)
  cout << endl;

  if(FloydWarshall(d,p,n))
  {
    // Wyœwietlamy wyniki
    for(i = 0; i < n; i++)
      for(j = 0; j < n; j++)
      {
        cout << i << "-" << j << " : ";
        FWPath(i,j,p);
        if(d[i][j] < MAXINT) cout << "$" << d[i][j];
        cout << endl;
      }
  }
  else cout << "Negative cycle found" << endl;

  cout << endl;

  // Usuwamy macierze dynamiczne

  for(i = 0; i < n; i++)
  {
    delete [] d[i];
    delete [] p[i];
  }
  delete [] d;
  delete [] p;

  return 0;
}
