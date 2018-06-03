#include <iostream>
#include <string>

using namespace std;

// Definicja w�z�a drzewa kodu bezprzystankowego
//----------------------------------------------
struct HTNode
{
  HTNode * next;
  HTNode * left;
  HTNode * right;
  char ch;
  int count;
};

// Tworzy list� wierzcho�k�w
//--------------------------
void MakeList(HTNode * & root, string s)
{
  unsigned int i,x;
  char cx;
  HTNode * p;
  bool t;

  root = NULL;                    // Tworzymy pust� list�
  for(i = 0; i < s.length(); i++) // Tworzymy w�z�y i zliczamy znaki
  {
    p = root;                     // Szukamy na li�cie znaku s[i]
    while (p && (p->ch != s[i])) p = p->next;
    if(!p)                        // Je�li go nie ma, to
    {
      p = new HTNode;             // tworzymy dla niego nowy w�ze�
      p->next  = root;            // W�ze� trafi na pocz�tek listy
      p->left  = NULL;            // Ustawiamy pola w�z�a
      p->right = NULL;
      p->ch    = s[i];
      p->count = 0;
      root     = p;               // Wstawiamy w�ze� na pocz�tek listy
    }
    p->count++;                   // Zwi�kszamy licznik wyst�pie� znaku
  }
  do                              // List� sortujemy rosn�co wzgl�dem count
  {
    t = true;                     // Zak�adamy posortowanie listy
    p = root;                     // Sortujemy od pierwszego elementu
    while(p->next)
    {
      if(p->count > p->next->count)
      {
        cx = p->ch;               // Wymieniamy zawarto�� dw�ch kolejnych element�w
        p->ch = p->next->ch;
        p->next->ch = cx;
        x = p->count;
        p->count = p->next->count;
        p->next->count = x;
        t = false;                // Sygnalizujemy nieposortowanie listy
      }
      p = p->next;                // Przechodzimy do nast�pnego elementu
    }
  } while(!t);
}

// Tworzy z listy drzewo Huffmana
//-------------------------------
void MakeTree(HTNode * & root)
{
  HTNode *p, *r, *v1, *v2;

  while(true)
  {
    v1 = root;                    // Pobieramy z listy dwa pierwsze w�z�y
    v2 = v1->next;

    if(!v2) break;                // Je�li tylko jeden element, zako�cz

    root = v2->next;              // Lista bez v1 i v2

    p = new HTNode;               // Tworzymy nowy w�ze�
    p->left = v1;                 // Do��czamy do niego v1 i v2
    p->right = v2;                // i wyliczamy now� cz�sto��
    p->count = v1->count + v2->count;

    // W�ze� wstawiamy z powrotem na list� tak, aby by�a uporz�dkowana

    if(!root || (p->count <= root->count))
    {
      p->next = root;
      root = p;
      continue;
    }

    r = root;

    while (r->next && (p->count > r->next->count)) r = r->next;

    p->next = r->next;
    r->next = p;
  }
}

// Drukuje zawarto�� drzewa Huffmana
//----------------------------------
void PrintTree(HTNode * p, string b)
{
  if(!p->left) cout << p->ch << " " << b << endl;
  else
  {
    PrintTree(p->left, b + "0");
    PrintTree(p->right,b + "1");
  }
}

// Koduje znak
//------------
bool CodeT(char c, HTNode * p, string b)
{
  if(!p->left)
  {
    if(c != p->ch) return false;
    else
    {
      cout << b;
      return true;
    }
  }
  else return CodeT(c,p->left,b+"0") || CodeT(c,p->right,b+"1");
}

// Koduje tekst kodem Huffmana
//----------------------------
void CodeHuffman(HTNode * root, string s)
{
  unsigned int i;

  for(i = 0; i < s.length(); i++)  // Kodujemy poszczeg�lne znaki
    CodeT(s[i],root,"");
}

// Procedura DFS:postorder usuwaj�ca drzewo
//-----------------------------------------
void DFSRelease(HTNode * v)
{
  if(v)
  {
    DFSRelease(v->left);          // usuwamy lewe poddrzewo
    DFSRelease(v->right);         // usuwamy prawe poddrzewo
    delete v;                     // usuwamy sam w�ze�
  }
}

int main()
{
  HTNode * root;                  // Pocz�tek listy / korze� drzewa
  string s;                       // Przetwarzany �a�cuch

  getline(cin,s);                 // Czytamy �a�cuch wej�ciowy

  MakeList(root,s);               // Tworzymy list� wierzcho�k�w
  MakeTree(root);                 // Tworzymy drzewo kodu Huffmana
  PrintTree(root,"");             // Wy�wietlamy kody znak�w
  CodeHuffman(root,s);            // Kodujemy i wy�wietlamy wynik

  DFSRelease(root);               // Usuwamy drzewo z pami�ci

  cout << endl << endl;

  return 0;
}
