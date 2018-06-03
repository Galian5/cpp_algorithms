#include<iostream>
using namespace std;
void insertion_sort(int tab[], int n)
{
    int i, j, el;
    for ( i = 1; i < n; ++i )
        {
        el = tab[i];
        for ( j = i; j > 0 && tab[j - 1] > el; j-- )
        {
            tab[j] = tab[j - 1];
            tab[j-1]=el;
        }

    }
}
int main()
{
    int tab[13]={5,1,2,5,2,12,26,212,2,7,3,55,3};
    insertion_sort(tab,13);
    for(int i=0;i<13;i++)
    {
        cout << tab[i] << " ";
    }


}
