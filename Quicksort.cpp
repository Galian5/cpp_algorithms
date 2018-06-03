#include<iostream>
using namespace std;
void quicksort(int tab[],unsigned int p,unsigned int k)
{
    int i=p;
    int j=k;
    int mid=tab[(p+k)/2];
    do{
        while(tab[i]<mid) i++;
        while(tab[j]>mid) j--;
        if(i<=j)
        {
            swap(tab[i],tab[j]);
            i++;
            j--;
        }
    }while(i<=j);

    if(p<j) quicksort(tab,p,j);
    if(k>i) quicksort(tab,i,k);
}


int main()
{
    int tab[13]={5,1,2,5,2,12,26,212,2,7,3,55,3};
    quicksort(tab,0,12);
    for(int i=0;i<13;i++)
    {
        cout << tab[i] << " ";
    }


}


