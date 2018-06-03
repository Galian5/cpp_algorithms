#include<iostream>
using namespace std;

const int tableLength=10;
struct data
{
    int x,y;
    string bleble;
};
struct element
{
    string key;
    bool deleted;
    data *d;

};
int hash( string key ) // Funkcja haszujaca
{
    int value = 0;
    for ( int i = 0; i < key.length(); i++ )
        value += key[i];
    return value % tableLength;
}

data *search(element* hashTab, int n, string key) // n- dlugosc tablo
{
    int i=hash(key);
    int k=1;

    while(hashTab[i].key!=key and (hashTab[i].key!="" or hashTab[i].deleted!=false))
    {
        i=(i+1)%n;
        k++;
        if(k==n)
            return NULL;
    }
    if(hashTab[i].key==key)
        return hashTab[i].d;
    else
        return NULL;
}
void insert(element *hashTab,int n, string key, data *d)
{
    int i=hash(key);
    int k=1;
    while(k<=n)
    {
        if(hashTab[i].deleted or hashTab[i].key=="")
        {
            hashTab[i].key=key;
            hashTab[i].d=d;
            hashTab[i].deleted=false;
            return;
        }
        i=(i+1)%n;
        k++;
    }
}
void remove(element *hashTab, int n, string key, data *d)
{
    int i=hash(key);
    int k=1;
    while(k<=n)
    {
        if(hashTab[i].d==d)
        {
            hashTab[i].key="";
            hashTab[i].d=NULL;
            hashTab[i].deleted=true;
            return;
        }
        i=(i+1)%n;
        k++;
    }
}

int main()
{

}
