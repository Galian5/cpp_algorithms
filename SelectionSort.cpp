#include<iostream>
using namespace std;
void seletion_sort(int tab[], int n)
{
    int k;
    for( int i = 0; i < n; i++ )
    {
        k = i;
        for( int j = i + 1; j < n; j++ )
        if( tab[ j ] < tab[ k ] )
             k = j;

        swap( tab[ k ], tab[ i ] );
    }
}

int main()
{
    int tab[13]={5,1,2,5,2,12,26,212,2,7,3,55,3};
    seletion_sort(tab,13);
    for(int i=0;i<13;i++)
    {
        cout << tab[i] << " ";
    }


}
