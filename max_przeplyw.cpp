#include <iostream>

using namespace std;

const int MAXINT = 2147483647;

// Definicja typu elementów listy
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

// Konstruktor - tworzy pust¹ listê
//---------------------------------
queue::queue()
{
  head = tail = NULL;
}

// Destruktor - usuwa listê z pamiêci
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

// Zwraca pocz¹tek kolejki.
// Wartoœæ specjalna to -MAXINT
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
// Program g³ówny
//---------------

int main()
{
  int m,n;                        // Liczba krawêdzi i wierzcho³ków w grafie
  slistEl ** L;                   // Tablica list s¹siedztwa
  int s,t;                        // Numer wierzcho³ka Ÿród³a s i ujscia t
  int fmax;                       // Maksymalny przep³yw sieciowy
  queue Q;                        // Kolejka
  int *P;                         // Tablica poprzedników
  int *CFP;                       // Tablica przepustowoœci rezydualnych dla œcie¿ek
  int i,cp,u,v;                   // Zmienne pomocnicze
  slistEl *x, *z;                 // WskaŸniki elementów listy s¹siedztwa
  bool test;

  // Najpierw odczytujemy liczbê wierzcho³ków i krawêdzi grafu

  cin >> n >> m;

  // Tworzymy i inicjujemy struktury dynamiczne

  L = new slistEl * [n];          // Tablica wskaŸników list
  for(i = 0; i < n; i++)
    L[i] = NULL;                  // Tablicê wype³niamy pustymi listami

  P   = new int [n];
  CFP = new int [n];

  // Teraz wczytujemy definicje poszczególnych krawêdzi grafu.
  // Ka¿da krawêdŸ jest zdefiniowana przez trzy liczby u, v i cp:
  // u  - wierzcho³ek pocz¹tkowy krawêdzi
  // v  - wierzcho³ek koñcowy krawêdzi
  // cp - przepustowoœæ krawêdzi

  for(i = 0; i < m; i++)
  {
    // Najpierw odczytujemy te trzy liczby

    cin >> u >> v >> cp;

    // Tworzymy nowy element listy

    x = new slistEl;

    // Wype³niamy jego pola danych

    x->v = v;
    x->c = cp;
    x->f = 0;                     // Zerujemy przep³yw

    // Element do³¹czamy do listy s¹siadów wierzcho³ka u

    x->next = L[u];
    L[u] = x;
  }

  // Na koniec odczytujemy numery wierzcho³ków Ÿród³a i ujœcia

  cin >> s >> t;

  //**************************************************
  //** Tutaj rozpoczyna siê algorytm Edmondsa-Karpa **
  //**************************************************

  // Zerujemy wartoœæ maksymalnego przep³ywu sieciowego

  fmax = 0;

  // Tworzymy w grafie strukturê sieci rezydualnej

  for(u = 0; u < n; u++)
  {
    for(x = L[u]; x; x = x->next)
    {
      // Sprawdzamy, czy na liœcie s¹siadów x jest wierzcho³ek u.
      // Jeœli tak, to krawêdŸ zwrotna istnieje i nie ma potrzeby
      // jej tworzenia.

      test = false;               // Zak³adamy brak krawêdzi zwrotnej
      for(z = L[x->v]; z; z = z->next)
        if(z->v == u)
        {
          test = true; break;
        }
      if(test) continue;          // Jeœli jest krawêdŸ, sprawdzamy kolejnego s¹siada

      // Tworzymy krawêdŸ zwrotn¹

      z = new slistEl;
      z->v = u;
      z->c = z->f = 0;
      z->next = L[x->v];
      L[x->v] = z;
    }
  }

  // Sieæ rezydualna zosta³a utworzona. Teraz zajmiemy siê wyznaczeniem
  // maksymalnych przep³ywów w sieci.

  while(1)
  {
    for(i = 0; i < n; i++)
      P[i] = -1;                  // Zerujemy tablicê poprzedników

    CFP[s] = MAXINT;              // Przepustowoœæ Ÿród³a jest nieskoñczona

    while(!Q.empty()) Q.pop();    // Zerujemy kolejkê

    Q.push(s);                    // W kolejce umieszczamy Ÿród³o s

    // Szukamy œcie¿ki w sieci rezudualnej od Ÿród³a s do ujœcia t

    while(!Q.empty())
    {
      test = false;             // Zak³adamy brak takiej œcie¿ki
      u = Q.front(); Q.pop();   // Pobieramy wierzcho³ek z kolejki

      // Przegl¹damy listê s¹siadów wierzcho³ka u

      for(x = L[u]; x; x = x->next)
      {
        // Wyznaczamy przepustowoœæ rezydualn¹ kana³u

        cp = x->c - x->f;

        // Przetwarzamy tylko istniej¹ce i nieodwiedzone jeszcze krawêdzie

        if(cp && (P[x->v] == -1))
        {
          // Zapamiêtujemy poprzednik na œcie¿ce

          P[x->v] = u;

          // Obliczamy przepustowoœæ rezydualn¹ do wêz³a x->v

          CFP[x->v] = cp < CFP[u] ? cp : CFP[u];

          // Sprawdzamy, czy œcie¿ka siêga do ujœcia

          if(x->v == t)
          {
             test = true;         // Sygnalizujemy znalezion¹ œcie¿kê
             break;               // Wychodzimy z pêtli for
          }
          else Q.push(x->v);      // Inaczej umieszczamy w kolejce wierzcho³ek x->v
        }
      }

      if(test) break;             // Jeœli jest œcie¿ka, wychodzimy z pêtli while
    }

    if (!test) break;             // Jeœli brak œcie¿ki, koñczymy algorytm

    // Zwiêkszamy przep³yw sieciowy

    fmax += CFP[t];

    // Cofamy siê po œcie¿ce od ujœcia t do Ÿród³a s

    for(v = t; v != s; v = u)
    {
      u = P[v];                   // u jest poprzednikiem v na œcie¿ce

      // Szukamy na liœcie s¹siadów u krawêdzi prowadz¹cej do v.

      for(z = L[u]; z; z = z->next)
        if(z->v == v)
        {
          z->f += CFP[t];         // W kierunku zgodnym ze œcie¿k¹ zwiêkszamy przep³yw
          break;
        }

      // Szukamy na liœcie s¹siadów v krawêdzi prowadz¹cej do u.

      for(z = L[v]; z; z = z->next)
        if(z->v == u)
        {
          z->f -= CFP[t];         // W kierunku przeciwnym do œcie¿ki zmnejszamy przep³yw
          break;
        }
    }
  }

  // Prezentujemy wyniki obliczeñ. Najpierw wypisujemy
  // wartoœæ maksymalnego przep³ywu

  cout << "\nfmax = " << fmax << endl << endl;

  // Nastêpnie wypisujemy znalezione przez algorytm przep³ywy w
  // kana³ach pierwotnej sieci przep³ywowej. Kana³y rozpoznajemy
  // po niezerowej wartoœci ich przepustowoœci.

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
