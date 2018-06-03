#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Typ wêz³ów drzewa BST
//----------------------

struct BSTNode
{
  BSTNode * up, * left, * right;
  int key;
};

// Zmienne globalne
//-----------------

string cr,cl,cp;      // ³añcuchy do znaków ramek

// Procedura wypisuje drzewo
//--------------------------
void printBT(string sp, string sn, BSTNode * v)
{
  string s;

  if(v)
  {
    s = sp;
    if(sn == cr) s[s.length() - 2] = ' ';
    printBT(s + cp, cr, v->right);

    s = s.substr(0,sp.length()-2);
    cout << s << sn << v->key << endl;

    s = sp;
    if(sn == cl) s[s.length() - 2] = ' ';
    printBT(s + cp, cl, v->left);
  }
}

// Procedura DFS:postorder usuwaj¹ca drzewo
//-----------------------------------------
void DFSRelease(BSTNode * v)
{
  if(v)
  {
    DFSRelease(v->left);   // usuwamy lewe poddrzewo
    DFSRelease(v->right);  // usuwamy prawe poddrzewo
    delete v;              // usuwamy sam wêze³
  }
}

// Rotacja w lewo
//---------------
void rot_L(BSTNode * & root, BSTNode * A)
{
  BSTNode * B = A->right, * p = A->up;

  if(B)
  {
    A->right = B->left;
    if(A->right) A->right->up = A;

    B->left = A;
    B->up = p;
    A->up = B;

    if(p)
    {
      if(p->left == A) p->left = B; else p->right = B;
    }
    else root = B;
  }
}

// Rotacja w prawo
//----------------
void rot_R(BSTNode * & root, BSTNode * A)
{
  BSTNode * B = A->left, * p = A->up;

  if(B)
  {
    A->left = B->right;
    if(A->left) A->left->up = A;

    B->right = A;
    B->up = p;
    A->up = B;

    if(p)
    {
      if(p->left == A) p->left = B; else p->right = B;
    }
    else root = B;
  }
}

// Procedura Splay
// root - korzeñ drzewa
// k    - klucz
//---------------------
void splay(BSTNode * & root, int k)
{
  BSTNode * x, *y;

  x = root;                 // Poszukujemy wêz³a o kluczu k, poczynaj¹c od korzenia
  if(x)
  {
    do
    {
      if(x->key == k) break;
      y = x;                // Zapamiêtujemy adres wêz³a
      x = k < x->key ? x->left: x->right;
    } while(x);

    if(!x) x = y;           // Jeœli w drzewie nie ma takiego wêz³a, to za x
                            // bierzemy bezpoœredni nastêpnik lub poprzednik
    while(true)             // W pêtli wêze³ x przesuwamy do korzenia
    {
      if(!x->up) break;     // x jest korzeniem, koñczymy

      if(!x->up->up)
      {                     // Ojcem x jest korzeñ. Wykonujemy ZIG
        if(x->up->left == x) rot_R(root,x->up);
        else                 rot_L(root,x->up);
        break;              // Koñczymy
      }

      if((x->up->up->left == x->up) && (x->up->left == x))
      {                     // prawy ZIG-ZIG
        rot_R(root,x->up->up);
        rot_R(root,x->up);
        continue;
      }

      if((x->up->up->right == x->up) && (x->up->right == x))
      {                    // lewy ZIG-ZIG
        rot_L(root,x->up->up);
        rot_L(root,x->up);
        continue;
      }

      if(x->up->right == x)
      {                    // lewy ZIG, prawy ZAG
        rot_L(root,x->up);
        rot_R(root,x->up);
      }
      else
      {                    // prawy ZIG, lewy ZAG
        rot_R(root,x->up);
        rot_L(root,x->up);
      }
    }
  }
}

// Procedura wstawia do drzewa Splay nowy wêze³
// root - referencja do zmiennej przechowuj¹cej adres korzenia
// k    - klucz wstawianego wêz³a
//------------------------------------------------------------
void insertSplay(BSTNode * & root, int k)
{
  BSTNode * x = new BSTNode; // Tworzymy nowy wêze³

  x->left = x->right = NULL; // Ustawiamy pola nowego wêz³a
  x->key  = k;

  if(!root)
  {                          // Jeœli drzewo jest puste,
    x->up = NULL;            // to wêze³ x staje siê korzeniem
    root  = x;
  }
  else
  {
    splay(root,k);          // W korzeniu pojawia siê nastêpnik lub poprzedni
    x->up = root;           // Bêdzie on zawsze ojcem wêz³a x
    if(k < root->key)       // Wybieramy miejsce dla x
    {
      x->left = root->left;
      root->left = x;       // x staje siê lewym synem korzenia
      if(x->left) x->left->up = x;
    }
    else
    {
      x->right = root->right;
      root->right = x;      // x staje siê prawym synem korzenia
      if(x->right) x->right->up = x;
    }
  }
}

// Procedura usuwa wêze³ z drzewa Splay
// root - referencja do zmiennej z adresem korzenia
// k    - klucz wêz³a do usuniêcia
//-------------------------------------------------
void removeSplay(BSTNode * & root, int k)
{
  BSTNode *TL,*TR;

  if(root)
  {
    splay(root,k);        // Usuwany wêze³ idzie do korzenia
    if(root->key == k)    // Sprawdzamy, czy rzeczywiœcie tam trafi³
    {
      TL = root->left;    // Zapamiêtujemy synów wêz³a
      TR = root->right;
      delete root;        // Wêze³ usuwamy z pamiêci
      root = NULL;        // Teraz drzewo jest puste
      if(TL)              // Wybieramy niepuste poddrzewo
      {
        TL->up = NULL;    // Teraz TL wskazuje korzeñ
        splay(TL,k);      // Do korzenia trafia poprzednik usuniêtego wêz³a
        while(TL->right) rot_L(TL,TL); // idziemy na skraj drzewa
        TL->right = TR;   // TR staje siê prawym synem
        if(TR) TR->up = TL;
        root = TL;        // Uaktualniamy korzeñ
      }
      else if(TR)         // Przypadek symetryczny dla TR
      {
        TR->up = NULL;    // Teraz TR wskazuje korzeñ
        splay(TR,k);      // Do korzenia trafia nastêpnik usuniêtego wêz³a
        while(TR->left) rot_R(TR,TR); // idziemy na skraj drzewa
        TR->left = TL;    // TL staje siê lewym synem
        if(TL) TL->up = TR;
        root = TR;        // Uaktualniamy korzeñ
      }
    }
  }
}

int main()
{
  int i,i1,i2,x,T[30];
  BSTNode * root = NULL;

  // ustawiamy ³añcuchy znakowe, poniewa¿ nie wszystkie edytory pozwalaj¹
  // wstawiaæ znaki konsoli do tworzenia ramek.
  // cr = +--
  //      |

  // cl = |
  //      +--

  // cp = |
  //      |

  cr = cl = cp = "  ";
  cr[0] = 218; cr[1] = 196;
  cl[0] = 192; cl[1] = 196;
  cp[0] = 179;

  srand(time(NULL));        // inicjujemy generator pseudolosowy

  // W tablicy ustawiamy numery wêz³ów od 1 do 31

  for(i = 0; i < 30; i++) T[i] = i + 1;

  // Mieszamy tablicê

  for(i = 0; i < 300; i++)
  {
    i1 = rand() % 30; i2 = rand() % 30;
    x = T[i1]; T[i1] = T[i2]; T[i2] = x;
  }

  // Wyœwietlamy tablicê i tworzymy drzewo Splay

  for(i = 0; i < 30; i++)
  {
    cout << T[i] << " ";
    insertSplay(root,T[i]);
  }

  cout << endl << endl;

  printBT("","",root);  // Wyœwietlamy drzewo

  // Ponownie mieszamy tablicê

  for(i = 0; i < 300; i++)
  {
    i1 = rand() % 30; i2 = rand() % 30;
    x = T[i1]; T[i1] = T[i2]; T[i2] = x;
  }

  // Usuwamy wêz³y

  cout << endl << endl;

  for(i = 0; i < 10; i++)
  {
    cout << T[i] << " ";
    removeSplay(root,T[i]);
  }

  cout << endl << endl;

  printBT("","",root);  // Wyœwietlamy drzewo

  cout << endl << endl;

  DFSRelease(root);     // Usuwamy drzewo BST z pamiêci

  return 0;
}
