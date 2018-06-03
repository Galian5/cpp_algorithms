#include <iostream>
#include <string>

using namespace std;

// Definicja wêz³a drzewa kodu bezprzystankowego
//----------------------------------------------
struct HTNode
{
  HTNode * next;
  HTNode * left;
  HTNode * right;
  char ch;
  int count;
};

// Tworzy listê wierzcho³ków
//--------------------------
void MakeList(HTNode * & root, string s)
{
  unsigned int i,x;
  char cx;
  HTNode * p;
  bool t;

  root = NULL;                    // Tworzymy pust¹ listê
  for(i = 0; i < s.length(); i++) // Tworzymy wêz³y i zliczamy znaki
  {
    p = root;                     // Szukamy na liœcie znaku s[i]
    while (p && (p->ch != s[i])) p = p->next;
    if(!p)                        // Jeœli go nie ma, to
    {
      p = new HTNode;             // tworzymy dla niego nowy wêze³
      p->next  = root;            // Wêze³ trafi na pocz¹tek listy
      p->left  = NULL;            // Ustawiamy pola wêz³a
      p->right = NULL;
      p->ch    = s[i];
      p->count = 0;
      root     = p;               // Wstawiamy wêze³ na pocz¹tek listy
    }
    p->count++;                   // Zwiêkszamy licznik wyst¹pieñ znaku
  }
  do                              // Listê sortujemy rosn¹co wzglêdem count
  {
    t = true;                     // Zak³adamy posortowanie listy
    p = root;                     // Sortujemy od pierwszego elementu
    while(p->next)
    {
      if(p->count > p->next->count)
      {
        cx = p->ch;               // Wymieniamy zawartoœæ dwóch kolejnych elementów
        p->ch = p->next->ch;
        p->next->ch = cx;
        x = p->count;
        p->count = p->next->count;
        p->next->count = x;
        t = false;                // Sygnalizujemy nieposortowanie listy
      }
      p = p->next;                // Przechodzimy do nastêpnego elementu
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
    v1 = root;                    // Pobieramy z listy dwa pierwsze wêz³y
    v2 = v1->next;

    if(!v2) break;                // Jeœli tylko jeden element, zakoñcz

    root = v2->next;              // Lista bez v1 i v2

    p = new HTNode;               // Tworzymy nowy wêze³
    p->left = v1;                 // Do³¹czamy do niego v1 i v2
    p->right = v2;                // i wyliczamy now¹ czêstoœæ
    p->count = v1->count + v2->count;

    // Wêze³ wstawiamy z powrotem na listê tak, aby by³a uporz¹dkowana

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

// Drukuje zawartoœæ drzewa Huffmana
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

  for(i = 0; i < s.length(); i++)  // Kodujemy poszczególne znaki
    CodeT(s[i],root,"");
}

// Procedura DFS:postorder usuwaj¹ca drzewo
//-----------------------------------------
void DFSRelease(HTNode * v)
{
  if(v)
  {
    DFSRelease(v->left);          // usuwamy lewe poddrzewo
    DFSRelease(v->right);         // usuwamy prawe poddrzewo
    delete v;                     // usuwamy sam wêze³
  }
}

int main()
{
  HTNode * root;                  // Pocz¹tek listy / korzeñ drzewa
  string s;                       // Przetwarzany ³añcuch

  getline(cin,s);                 // Czytamy ³añcuch wejœciowy

  MakeList(root,s);               // Tworzymy listê wierzcho³ków
  MakeTree(root);                 // Tworzymy drzewo kodu Huffmana
  PrintTree(root,"");             // Wyœwietlamy kody znaków
  CodeHuffman(root,s);            // Kodujemy i wyœwietlamy wynik

  DFSRelease(root);               // Usuwamy drzewo z pamiêci

  cout << endl << endl;

  return 0;
}
