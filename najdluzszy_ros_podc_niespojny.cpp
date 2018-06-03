#include<iostream>
using namespace std;
void printsolution(int A[], int P[], int i)
{
    int x=i;
    if(P[i]!=-1 and x--)
        printsolution(A,P,P[i]); // nie wypisze 1 elementu jesli jest na miejscu a[0]
    cout << A[i];

}
int lis(int A[],int n)
{
    int F[n],P[n];
    int max=0;
    F[0]=1;
    P[0]=1;
    for(int i=1;i<n;i++)
    {
        F[i]=1;
        P[i]=1;
        for(int j=0; j<i;j++)
        {
            if(A[j]<A[i] and F[j]+1>F[i])
            {
                F[i]=F[j]+1;
                P[i]=j;
            }
            if(F[max]<F[i])
                max=i;
        }
    }
    printsolution(A,P,max);
    return F[max];
}
int main()
{
    int a[4]={2,5,2,6};
    int w=lis(a,4);
    cout << "\n" << w;

}
