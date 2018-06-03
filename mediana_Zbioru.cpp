#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <time.h>

using namespace std;
int mediana(int *Z,int N)
{
  int m = N >> 1; // m/=2;
  int ip = 0, ik = N - 1,v,i,j,x;
  while(ip < ik)
  {
    v = Z[m]; i = ip; j = ik;
    do
    {
      while(Z[i] < v) i++;
      while(v < Z[j]) j--;
      if(i <= j)
      {
        x = Z[i]; Z[i] = Z[j]; Z[j] = x;
        i++; j--;
      }
    } while(i <= j);
    if(j < m) ip = i;
    if(m < i) ik = j;
  }
   cout <<setw(4) << Z[m] << endl << endl;
}
int main()
{
  const int N = 99;

  int Z[N - 1];

  srand((unsigned)time(NULL));

  // Przygotowujemy tablicê Z[]

  for(int i = 0; i < N; i++) Z[i] = rand() % 1000;

  // Wyœwietlamy tablicê Z[]

  for(int i = 0; i < N; i++) cout << setw(4) << Z[i];
  cout << endl << endl;

  mediana(Z,N);

  return 0;
}
