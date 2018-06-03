#include<iostream>
using namespace std;
int LCS(char *A, char *B, int a, int b)
{
    int L[a+1][b+1];
   for (int i=0; i<=a; i++)
   {
     for (int j=0; j<=b; j++)
     {
       if (i == 0 || j == 0)
         L[i][j] = 0;

       else if (A[i-1] == B[j-1])
         L[i][j] = L[i-1][j-1] + 1;

       else
         L[i][j] = max(L[i-1][j], L[i][j-1]);
     }
   }
   return L[a][b];
}
int main()
{
      char A[] = "AGGTAB";
      char B[] = "GXTXAYB";

      cout << LCS(A,B,5,6);
}
