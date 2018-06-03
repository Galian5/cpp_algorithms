#include<iostream>
#include<queue>
using namespace std;

struct vertex{
  bool kolejka; //czy dodany do kolejki

  vector <int> polaczenia; //do przechowywania po��cze�
  // dodatkowe opcje
};

vertex *w;

void odwiedz(int n)
{
  //wykonaj jakies czynnosci
  //w przypadku odwiedzenia wierzcholka o numerze n
  cout<<"Odwiedzono wierzcho�ek o numerze: "<<n<<endl;
}

void BFS(int n)
{
  queue<int> kolejka;    //utworzenie kolejki fifo
  kolejka.push(n);  //dodanie pierwszego wierzcholka do kolejki

  while(!kolejka.empty()) //dop�ki jest cos w kolejce
  {
    n = kolejka.front(); //pobranie pierwszego elementu w kolejce

      kolejka.pop(); //usu� pobrany element z kolejki
      odwiedz(n); //odwied� go i zr�b co�
      //oraz dodaj wszystkie jego nieodwiedzone i nie b�d�ce
      //w kolejce po��czenia do kolejki
      for(int i=0;i<w[n].polaczenia.size();i++)
        if(!w[w[n].polaczenia[i]].kolejka)
        {
          kolejka.push(w[n].polaczenia[i]);
          w[w[n].polaczenia[i]].kolejka = 1; //oznaczenie, �e dodano do kolejki
          cout<<"Dodano do kolejki wierzcholek nr "<<w[n].polaczenia[i]<<endl;
        }
  }
}

int main()
{
  cout<<"Podaj liczbe wierzcholkow w grafie: ";
  int n, p, a, b;
  cin>>n;
  w = new vertex [n+1];//przydzielenie pami�ci na wierzcho�ki grafu
  //wczytanie wierzcho�k�w grafu
  cout<<"Podaj liczbe polaczen: ";
  cin>>p;

  for(int i=0;i<p;i++)
  {
    cout<<"Podaj numery wierzcholkow, ktore chcesz ze soba polaczyc: ";
    cin>>a>>b;
    w[a].polaczenia.push_back(b); //po��czenie jest dwukierunkowe a-->b
    w[b].polaczenia.push_back(a); //b-->a
  }
  //przeszukaj graf
  BFS(1); //rozpoczynamy od wierzcho�ka o numerze 1

  delete [] w;
  return 0;
}
