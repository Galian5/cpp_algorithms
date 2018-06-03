#include<iostream>
using namespace std;
void subsetsum(int *A, int n, int T)
{
    bool F[T+1][n+1];
    for(int i=0;i<n;i++)
    {
        F[0][i]=true;
    }
    for(int i=0;i<T;i++)
    {
        F[i][0]=false;
    }
    for(int i=1;i<T;i++)
        for(int j=1;j<n;j++)
        {
            F[i][j]=F[i][j-1];
            if(i>=A[j-1])
                F[i][j]=(F[i][j] or F[i-A[j-1]][j-1]);
        }
}
bool SS(int A[], int n, int T){
	bool SUMS[n][T+1];
	for (int i = 0; i < n; i++)
		SUMS[i][0] = true;			// uzupelniamy pierwsza kolumne jako true bo sume zero mozemy zawsze stworzyc z pustego zbioru
	for (int i = 1; i <= T; i++)
		SUMS[0][i] = false;			// uzupelniam pierwszy wiersz(oprocz pierwzsego pola) jako false
	if (A[0] <= T && A[0] >= 1)
		SUMS[0][A[0]] = true;		// tutaj uzupelniam sume == wyrazowi jesli takowa jest w zakresie
	for (int i = 1; i < n; i++){	// lecimy od 2 wiersza
		for (int j = 1; j <= T; j++){		// od 2 kolumny bo 1 jest true
			SUMS[i][j] = SUMS[i-1][j];		// przypisujemy z automatu t¹ góry bo tak mozna
			if (A[i] <= j && SUMS[i][j] == false)		// jezeli wyraz jest wiekszy od sumy na ktora patrzymy z automatu wskakuje to co by³o wy¿ej je¿eli jest true to te¿ nei ma co sprawdzac
				SUMS[i][j] = SUMS[i - 1][j - A[i]];		// ca³y trick
		}
	}
	return SUMS[n - 1][T];
}
int main()
{
    int A[10]={1,5,3,5,4,12,8,100,2,6};
    int T=121;
    cout << SS(A,10,T);

}
