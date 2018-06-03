#include<iostream>
using namespace std;


void merge(int A[], int l, int pivot, int r)
{
    int pom[r+1];
    for(int i=l;i<=r;i++)
    {
        pom[i]=A[i];
    }
    int i=l,j=pivot+1,q=l;
    while(i<=pivot and j<=r)
    {
        if(pom[i]<pom[j]) A[q++]=pom[i++];
        else A[q++]=pom[j++];
    }
    while(i<=pivot) A[q++]=pom[i++];
    while(j<=r) A[q++]=pom[j++];
}
void mergesort(int A[],int l, int r)
{
    if(l<r)
    {
        int pivot=(l+r)/2;
        mergesort(A,l,pivot);
        mergesort(A,pivot+1 ,r);
        merge(A,l,pivot,r);
    }
}

int main()
{
    const int N=13;
    int tab[N]={5,1,2,5,2,12,26,212,2,7,3,55,3};
    mergesort(tab,0,N-1);
    for(int i=0;i<13;i++)
    {
        cout << tab[i] << " ";
    }

}
