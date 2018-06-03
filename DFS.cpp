#include<iostream>
#include<vector>
using namespace std;

struct wierzcholki{
  vector <unsigned int> polaczenia;
  bool odwiedzony;

};

wierzcholek *w;

void w_glab(int k)
{
  cout<<"Odwiedzono "<<k<<" wierzcholek\n";
  w[k].odwiedzony = 1;
  for(int i=0; i<w[k].polaczenia.size(); i++)
        if(!w[w[k].polaczenia[i]].odwiedzony)
            w_glab(w[k].polaczenia[i]);
}

int main()
{
  unsigned int n, pol, pocz, a, b;
  cout<<"Podaj liczbe wierzcholkow w grafie: ";
  cin>>n;
  cout<<"Podaj liczbe polaczen w grafie: ";
  cin>>pol;
  cout<<"Podaj wierzcholek, z ktorego zaczynamy przeszukiwanie: ";
  cin>>pocz;

  w = new wierzcholki[n+1];

  cout<<"Podaj kolejne polaczenia wierzcholkow: \n";
  for(int i=0; i<pol; i++)
  {
    cin>>a>>b;
    cout<<a<<" <--> "<<b<<endl;
    w[a].polaczenia.push_back(b);
    w[b].polaczenia.push_back(a);
  }
  cout<<"\nOdwiedzano wierzcholki w nastepuj¹cej kolejnosci:\n";
  w_glab(pocz);

  delete [] w;

  cin.ignore();
  cin.get();

  return 0;
}
