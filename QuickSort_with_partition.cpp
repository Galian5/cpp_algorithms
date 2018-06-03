#include<iostream>
using namespace std;
int partition(int A[],int l, int r)
{
    int pivot=A[r];
    int i=l-1;
    for(int j=l;j<r;j++)
    {
        if(A[j]<=pivot)
        {
            i++;
            swap(A[i],A[j]);
        }
    }
    swap(A[r],A[i+1]);
    return i+1;
}
void quicksort(int A[],int l, int r)
{
    if(l<r)
    {
        int pivot=partition(A,l,r);
        quicksort(A,l,pivot-1);
        quicksort(A,pivot+1,r);
    }
}
int main()
{
    int tab[14]={5,1,2,5,2,12,26,212,2,7,3,55,3,21};
    quicksort(tab,0,13);
    for(int i=0;i<14;i++)
    {
        cout << tab[i] << " ";
    }

}
