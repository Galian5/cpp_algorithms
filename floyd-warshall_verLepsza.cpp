#include <iostream>

using namespace std;

const int MAXINT = 2147483647;    // "plus niesko�czono��"


// Funkcja wyznaczania koszt�w doj�cia oraz
// minimalnych �cie�ek w grafie wa�onym
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
// �cie�ki z macierzy poprzednik�w p
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
  int **d, **p;                     // Macierze koszt�w oraz poprzenik�w
  int n,m;

  cin >> n >> m;                  // Czytamy liczb� wierzcho�k�w oraz kraw�dzi

  d = new int * [n];
  p = new int * [n];

  for(i = 0; i < n; i++)
  {
    d[i] = new int [n];
    p[i] = new int [n];
    for(j = 0; j < n; j++)
    {
      d[i][j] = MAXINT;          // Wiersz d wype�niamy najwi�ksz� liczb� dodatni�
      p[i][j] = -1;              // Wiersz p wype�niamy liczbami -1 (brak poprzednika)
    }
    d[i][i] = 0;                 //  na przek�tnej d wpisujemy 0
  }

  for(i = 0; i < m; i++)
  {
    cin >> x >> y >> w;          // Czytamy definicj� kraw�dzi
    d[x][y] = w;                 // Wag� kraw�dzi umieszczamy w macierzy d
    p[x][y] = x;                 // Poprzednikiem y jest x
  }
  // korzystajac z list sasiedztwa nale�aloby wpisywac dane wierzcholki do macierzy w czasie O(E)
  cout << endl;

  if(FloydWarshall(d,p,n))
  {
    // Wy�wietlamy wyniki
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
