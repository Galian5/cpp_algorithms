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
    int F[n];
    F[0]=A[0];
    int max=A[0];
    for(int i=1;i<n;i++)
    {
        F[i]=A[i];
        for(int j=0; j<i;j++)
        {
            if(A[j]<A[i] and F[j]+A[i]>F[i])
            {
                F[i]=F[j]+A[i];

            }
            if(max<F[i])
                max=F[i];
        }
    }
    return max;
}
int main()
{
    int a[5]={1,5,2,3,4};
    int w=lis(a,5);
    cout  << w;

}
