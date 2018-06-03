#include <iostream>

using namespace std;

// Typy danych
const int MAXINT = 2147483647;
struct slistEl
{
  slistEl * next;
  int v,w;                        // numer wêz³a docelowego i waga krawêdzi
};
 //d             Tablica kosztów dojœcia
 //p             Tablica poprzedników
 //QS            Zbiory Q i S
 //h             Kopiec
 //hp            Pozycje w kopcu
 //S             Stos
 //sptr          WskaŸnik stosu
void dijkstra(int v,int n,slistEl **graf,int dest)
{
    int hlen = n,x,u,parent,left,right,dmin,pmin,sptr=0;
    int d[n],p[n],h[n],hp[n],S[n];
    bool QS[n]; // false w Q true w S
    for(int i = 0; i < n; i++)
    {
        d[i] = MAXINT;
        p[i] = -1;
        QS[i] = false;
        h[i] = hp[i] = i;
    }

    d[v] = 0;                       // Koszt dojœcia v jest zerowy
    x = h[0]; h[0] = h[v]; h[v] = x; // odtwarzamy w³asnoœæ kopca
    hp[v] = 0; hp[0] = v;

    // Wyznaczamy œcie¿ki

    for(int i = 0; i < n; i++)
    {
        u = h[0];                     // Korzeñ kopca jest zawsze najmniejszy

        // Usuwamy korzeñ z kopca, odtwarzaj¹c w³asnoœæ kopca

        h[0] = h[--hlen];             // W korzeniu umieszczamy ostatni element
        hp[h[0]] = parent = 0;        // Zapamiêtujemy pozycjê elementu w kopcu
        while(true)                   // W pêtli idziemy w dó³ kopca, przywracaj¹c go
        {
              left  = parent + parent + 1; // Pozycja lewego potomka
              right = left + 1;           // Pozycja prawego potomka
              if(left >= hlen) break;     // Koñczymy, jeœli lewy potomek poza kopcem
              dmin = d[h[left]];          // Wyznaczamy mniejszego potomka
              pmin = left;
              if((right < hlen) && (dmin > d[h[right]]))
              {
                    dmin = d[h[right]];
                    pmin = right;
              }
              if(d[h[parent]] <= dmin) break; // Jeœli w³asnoœæ kopca zachowana, koñczymy
              x = h[parent]; h[parent] = h[pmin]; h[pmin] = x; // Przywracamy w³asnoœæ kopca
              hp[h[parent]] = parent; hp[h[pmin]] = pmin;      // na danym poziomie
              parent = pmin;              // i przechodzimy na poziom ni¿szy kopca
        }

        // Znaleziony wierzcho³ek przenosimy do S

        QS[u] = true; // true w S zbiorze, false w Q

        // Modyfikujemy odpowiednio wszystkich s¹siadów u, którzy s¹ w Q

        for(slistEl *pw = graf[u]; pw; pw = pw->next)
          if(!QS[pw->v] && (d[pw->v] > d[u] + pw->w))
          {
                d[pw->v] = d[u] + pw->w;
                p[pw->v] = u;

            // Po zmianie d[v] odtwarzamy w³asnoœæ kopca, id¹c w górê

                for(int child = hp[pw->v]; child; child = parent)
                {
                      parent = child / 2;
                      if(d[h[parent]] <= d[h[child]]) break;
                      x = h[parent]; h[parent] = h[child]; h[child] = x;
                      hp[h[parent]] = parent; hp[h[child]] = child;
                }
          }
          if(u==dest) break;
      }
    cout << endl;

        cout << dest << ": ";
        // Œcie¿kê przechodzimy od koñca ku pocz¹tkowi,
        // Zapisuj¹c na stosie kolejne wierzcho³ki
        for(int j = dest; j > -1; j = p[j]) S[sptr++] = j;
        // Wyœwietlamy œcie¿kê, pobieraj¹c wierzcho³ki ze stosu
        while(sptr) cout << S[--sptr] << " ";
        // Na koñcu œcie¿ki wypisujemy jej koszt
        cout << "$" << d[dest] << endl;

}

int main()
{
  int m,n,v,w,x,y;
  slistEl **graf;                 // Tablica list s¹siedztwa
  slistEl *pw,*rw,*xx;

  cin >> v >> n >> m;             // Wêze³ startowy, liczba wierzcho³ków i krawêdzi
  graf = new slistEl * [n];       // Tablica list s¹siedztwa

  // Inicjujemy tablice dynamiczne

  for(int i = 0; i < n; i++)
  {
    graf[i] = NULL;
  }
  // Odczytujemy dane wejœciowe

  for(int i = 0; i < m; i++)
  {
    cin >> x >> y >> w;           // Odczytujemy krawêdŸ z wag¹
    pw = new slistEl;             // Tworzymy element listy s¹siedztwa
    pw->v = y;                    // Wierzcho³ek docelowy krawêdzi
    pw->w = w;                    // Waga krawêdzi
    pw->next = graf[x];
    graf[x] = pw;
    xx=new slistEl;
    xx->v=x;
    xx->w=w;
    xx->next=graf[y];
    graf[y]=xx;                 // Element do³¹czamy do listy
  }

  dijkstra(v,n,graf,1);
  for(int i = 0; i < n; i++)
  {
    pw = graf[i];
    while(pw)
    {
      rw = pw;
      pw = pw->next;
      delete rw;
    }
  }

  delete [] graf;

  return 0;
}

