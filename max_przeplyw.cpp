#include <iostream>

using namespace std;

const int MAXINT = 2147483647;

// Definicja typu element�w listy
//-------------------------------
struct slistEl
{
  slistEl * next;
  int v,c,f;
};

// Definicja typu obiektowego queue
//---------------------------------
class queue
{
  private:
    slistEl * head;
    slistEl * tail;

  public:
    queue();      // konstruktor
    ~queue();     // destruktor
    bool empty(void);
    int  front(void);
    void push(int v);
    void pop(void);
};

//---------------------
// Metody obiektu queue
//---------------------

// Konstruktor - tworzy pust� list�
//---------------------------------
queue::queue()
{
  head = tail = NULL;
}

// Destruktor - usuwa list� z pami�ci
//-----------------------------------
queue::~queue()
{
  while(head) pop();
}

// Sprawdza, czy kolejka jest pusta
//---------------------------------
bool queue::empty(void)
{
  return !head;
}

// Zwraca pocz�tek kolejki.
// Warto�� specjalna to -MAXINT
//-----------------------------
int queue::front(void)
{
  if(head) return head->v;
  else     return -MAXINT;
}

// Zapisuje do kolejki
//--------------------
void queue::push(int v)
{
  slistEl * p = new slistEl;
  p->next = NULL;
  p->v = v;
  if(tail) tail->next = p;
  else     head = p;
  tail = p;
}

// Usuwa z kolejki
//----------------
void queue::pop(void)
{
  if(head)
  {
    slistEl * p = head;
    head = head->next;
    if(!head) tail = NULL;
    delete p;
  }
}

//---------------
// Program g��wny
//---------------

int main()
{
  int m,n;                        // Liczba kraw�dzi i wierzcho�k�w w grafie
  slistEl ** L;                   // Tablica list s�siedztwa
  int s,t;                        // Numer wierzcho�ka �r�d�a s i ujscia t
  int fmax;                       // Maksymalny przep�yw sieciowy
  queue Q;                        // Kolejka
  int *P;                         // Tablica poprzednik�w
  int *CFP;                       // Tablica przepustowo�ci rezydualnych dla �cie�ek
  int i,cp,u,v;                   // Zmienne pomocnicze
  slistEl *x, *z;                 // Wska�niki element�w listy s�siedztwa
  bool test;

  // Najpierw odczytujemy liczb� wierzcho�k�w i kraw�dzi grafu

  cin >> n >> m;

  // Tworzymy i inicjujemy struktury dynamiczne

  L = new slistEl * [n];          // Tablica wska�nik�w list
  for(i = 0; i < n; i++)
    L[i] = NULL;                  // Tablic� wype�niamy pustymi listami

  P   = new int [n];
  CFP = new int [n];

  // Teraz wczytujemy definicje poszczeg�lnych kraw�dzi grafu.
  // Ka�da kraw�d� jest zdefiniowana przez trzy liczby u, v i cp:
  // u  - wierzcho�ek pocz�tkowy kraw�dzi
  // v  - wierzcho�ek ko�cowy kraw�dzi
  // cp - przepustowo�� kraw�dzi

  for(i = 0; i < m; i++)
  {
    // Najpierw odczytujemy te trzy liczby

    cin >> u >> v >> cp;

    // Tworzymy nowy element listy

    x = new slistEl;

    // Wype�niamy jego pola danych

    x->v = v;
    x->c = cp;
    x->f = 0;                     // Zerujemy przep�yw

    // Element do��czamy do listy s�siad�w wierzcho�ka u

    x->next = L[u];
    L[u] = x;
  }

  // Na koniec odczytujemy numery wierzcho�k�w �r�d�a i uj�cia

  cin >> s >> t;

  //**************************************************
  //** Tutaj rozpoczyna si� algorytm Edmondsa-Karpa **
  //**************************************************

  // Zerujemy warto�� maksymalnego przep�ywu sieciowego

  fmax = 0;

  // Tworzymy w grafie struktur� sieci rezydualnej

  for(u = 0; u < n; u++)
  {
    for(x = L[u]; x; x = x->next)
    {
      // Sprawdzamy, czy na li�cie s�siad�w x jest wierzcho�ek u.
      // Je�li tak, to kraw�d� zwrotna istnieje i nie ma potrzeby
      // jej tworzenia.

      test = false;               // Zak�adamy brak kraw�dzi zwrotnej
      for(z = L[x->v]; z; z = z->next)
        if(z->v == u)
        {
          test = true; break;
        }
      if(test) continue;          // Je�li jest kraw�d�, sprawdzamy kolejnego s�siada

      // Tworzymy kraw�d� zwrotn�

      z = new slistEl;
      z->v = u;
      z->c = z->f = 0;
      z->next = L[x->v];
      L[x->v] = z;
    }
  }

  // Sie� rezydualna zosta�a utworzona. Teraz zajmiemy si� wyznaczeniem
  // maksymalnych przep�yw�w w sieci.

  while(1)
  {
    for(i = 0; i < n; i++)
      P[i] = -1;                  // Zerujemy tablic� poprzednik�w

    CFP[s] = MAXINT;              // Przepustowo�� �r�d�a jest niesko�czona

    while(!Q.empty()) Q.pop();    // Zerujemy kolejk�

    Q.push(s);                    // W kolejce umieszczamy �r�d�o s

    // Szukamy �cie�ki w sieci rezudualnej od �r�d�a s do uj�cia t

    while(!Q.empty())
    {
      test = false;             // Zak�adamy brak takiej �cie�ki
      u = Q.front(); Q.pop();   // Pobieramy wierzcho�ek z kolejki

      // Przegl�damy list� s�siad�w wierzcho�ka u

      for(x = L[u]; x; x = x->next)
      {
        // Wyznaczamy przepustowo�� rezydualn� kana�u

        cp = x->c - x->f;

        // Przetwarzamy tylko istniej�ce i nieodwiedzone jeszcze kraw�dzie

        if(cp && (P[x->v] == -1))
        {
          // Zapami�tujemy poprzednik na �cie�ce

          P[x->v] = u;

          // Obliczamy przepustowo�� rezydualn� do w�z�a x->v

          CFP[x->v] = cp < CFP[u] ? cp : CFP[u];

          // Sprawdzamy, czy �cie�ka si�ga do uj�cia

          if(x->v == t)
          {
             test = true;         // Sygnalizujemy znalezion� �cie�k�
             break;               // Wychodzimy z p�tli for
          }
          else Q.push(x->v);      // Inaczej umieszczamy w kolejce wierzcho�ek x->v
        }
      }

      if(test) break;             // Je�li jest �cie�ka, wychodzimy z p�tli while
    }

    if (!test) break;             // Je�li brak �cie�ki, ko�czymy algorytm

    // Zwi�kszamy przep�yw sieciowy

    fmax += CFP[t];

    // Cofamy si� po �cie�ce od uj�cia t do �r�d�a s

    for(v = t; v != s; v = u)
    {
      u = P[v];                   // u jest poprzednikiem v na �cie�ce

      // Szukamy na li�cie s�siad�w u kraw�dzi prowadz�cej do v.

      for(z = L[u]; z; z = z->next)
        if(z->v == v)
        {
          z->f += CFP[t];         // W kierunku zgodnym ze �cie�k� zwi�kszamy przep�yw
          break;
        }

      // Szukamy na li�cie s�siad�w v kraw�dzi prowadz�cej do u.

      for(z = L[v]; z; z = z->next)
        if(z->v == u)
        {
          z->f -= CFP[t];         // W kierunku przeciwnym do �cie�ki zmnejszamy przep�yw
          break;
        }
    }
  }

  // Prezentujemy wyniki oblicze�. Najpierw wypisujemy
  // warto�� maksymalnego przep�ywu

  cout << "\nfmax = " << fmax << endl << endl;

  // Nast�pnie wypisujemy znalezione przez algorytm przep�ywy w
  // kana�ach pierwotnej sieci przep�ywowej. Kana�y rozpoznajemy
  // po niezerowej warto�ci ich przepustowo�ci.

  for(i = 0; i < n; i++)
    for(z = L[i]; z; z = z->next)
      if(z->c)
        cout << i << " -> " << z->v << " " << z->f << ":" << z->c << endl;

  cout << endl;

  // Koniec, usuwamy struktury dynamiczne

  for(i = 0; i < n; i++)
  {
    x = L[i];
    while(x)
    {
      z = x;
      x = x->next;
      delete z;
    }
  }

  delete [] L;
  delete [] P;
  delete [] CFP;

  return 0;
}
