#include <iostream>

using namespace std;

// Typy danych
const int MAXINT = 2147483647;
struct slistEl
{
  slistEl * next;
  int v,w;                        // numer w�z�a docelowego i waga kraw�dzi
};
void dijkstra(int v,int n,slistEl **graf)
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

    d[v] = 0;                       // Koszt doj�cia v jest zerowy
    x = h[0]; h[0] = h[v]; h[v] = x; // odtwarzamy w�asno�� kopca
    hp[v] = 0; hp[0] = v;

    // Wyznaczamy �cie�ki

    for(int i = 0; i < n; i++)
    {
        u = h[0];                     // Korze� kopca jest zawsze najmniejszy

        // Usuwamy korze� z kopca, odtwarzaj�c w�asno�� kopca

        h[0] = h[--hlen];             // W korzeniu umieszczamy ostatni element
        hp[h[0]] = parent = 0;        // Zapami�tujemy pozycj� elementu w kopcu
        while(true)                   // W p�tli idziemy w d� kopca, przywracaj�c go
        {
              left  = parent + parent + 1; // Pozycja lewego potomka
              right = left + 1;           // Pozycja prawego potomka
              if(left >= hlen) break;     // Ko�czymy, je�li lewy potomek poza kopcem
              dmin = d[h[left]];          // Wyznaczamy mniejszego potomka
              pmin = left;
              if((right < hlen) && (dmin > d[h[right]]))
              {
                    dmin = d[h[right]];
                    pmin = right;
              }
              if(d[h[parent]] <= dmin) break; // Je�li w�asno�� kopca zachowana, ko�czymy
              x = h[parent]; h[parent] = h[pmin]; h[pmin] = x; // Przywracamy w�asno�� kopca
              hp[h[parent]] = parent; hp[h[pmin]] = pmin;      // na danym poziomie
              parent = pmin;              // i przechodzimy na poziom ni�szy kopca
        }

        // Znaleziony wierzcho�ek przenosimy do S

        QS[u] = true; // true w S zbiorze, false w Q

        // Modyfikujemy odpowiednio wszystkich s�siad�w u, kt�rzy s� w Q

        for(slistEl *pw = graf[u]; pw; pw = pw->next)
          if(!QS[pw->v] && (d[pw->v] > d[u] + pw->w))
          {
                d[pw->v] = d[u] + pw->w;
                p[pw->v] = u;

            // Po zmianie d[v] odtwarzamy w�asno�� kopca, id�c w g�r�

                for(int child = hp[pw->v]; child; child = parent)
                {
                      parent = child / 2;
                      if(d[h[parent]] <= d[h[child]]) break;
                      x = h[parent]; h[parent] = h[child]; h[child] = x;
                      hp[h[parent]] = parent; hp[h[child]] = child;
                }
          }
      }
    cout << endl;
    for(int i = 0; i < n; i++)
    {
        cout << i << ": ";
        // �cie�k� przechodzimy od ko�ca ku pocz�tkowi,
        // Zapisuj�c na stosie kolejne wierzcho�ki
        for(int j = i; j > -1; j = p[j]) S[sptr++] = j;
        // Wy�wietlamy �cie�k�, pobieraj�c wierzcho�ki ze stosu
        while(sptr) cout << S[--sptr] << " ";
        // Na ko�cu �cie�ki wypisujemy jej koszt
        cout << "$" << d[i] << endl;
    }
}

int main()
{
  int m,n,v,w,x,y;
  slistEl **graf;                 // Tablica list s�siedztwa
  slistEl *pw,*rw,*xx;

  cin >> v >> n >> m;             // W�ze� startowy, liczba wierzcho�k�w i kraw�dzi
  graf = new slistEl * [n];       // Tablica list s�siedztwa

  // Inicjujemy tablice dynamiczne

  for(int i = 0; i < n; i++)
  {
    graf[i] = NULL;
  }
  // Odczytujemy dane wej�ciowe

  for(int i = 0; i < m; i++)
  {
    cin >> x >> y >> w;           // Odczytujemy kraw�d� z wag�
    pw = new slistEl;             // Tworzymy element listy s�siedztwa
    pw->v = y;                    // Wierzcho�ek docelowy kraw�dzi
    pw->w = w;                    // Waga kraw�dzi
    pw->next = graf[x];
    graf[x] = pw;
    xx=new slistEl;
    xx->v=x;
    xx->w=w;
    xx->next=graf[y];
    graf[y]=xx;                 // Element do��czamy do listy
  }

  dijkstra(v,n,graf);
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
