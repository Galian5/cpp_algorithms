#include<iostream>
using namespace std;
struct node // struktura elementow listy
{
    int val;
    node *next;
};
void printlist(node *head) // wypisane listy
{
    while(head!=NULL)
    {
        cout << head->val << " " ;
        head=head->next;
    }
}
void add(node* &head,int value) // dodawanie elementu na poczatek listy
{
    node* tmp=new node;
    tmp->val=value;
    tmp->next=head;
    head=tmp;
}
node *getTail(node *head) //funkcja zwracajaca wskaznik na ostatni element
{
    while(head!=NULL and head->next!=NULL)
    {
        head=head->next;
    }
    return head;
}
node *partition_f(node *head, node *end, node * &newHead, node* &newEnd)
{  //Funkcja dzielaca liste na elementy mniejsze od pivota i wieksze
    node *pivot=end; // pivot to ostatni element w tym przypadku
    node *prev=NULL; // wskaznik na trzymanie wartosci przed ta ktora bedzimy przepinac w srodku
    node *current=head; // aktualnie przegladany element
    node *tail=pivot; // ogon

    while(current!=pivot) // dopoki aktaulny element nie stanie na miejscu pivota
    {
        if(current->val < pivot->val) // dla elementow mniejszych od pivota
        {
            if(newHead==NULL) newHead=current; //pierwszy nieprzepiety element na koniec zostaje glowa nowej listy

            prev=current; // przenosimy aktualny wskaznik na nastepny i zostawimy prev aby przepiac
            current=current->next;
        }
        else // dla wiekszych od pivota
        {
            if(prev!=NULL) prev->next=current->next; // wiemy ze element nie jest z brzegu a w srodku wiec przepinamy poprzedni na 2 do przodu

            node *tmp=current->next; // tmp jest natepnym po aktualnym
            current->next=NULL; // odpinamy na koniec wiec NULL
            tail->next=current; // przypinamy
            tail=current; // ogon jest teraz tym przepietym na koniec
            current=tmp; // aktaulny na natepny

        }

    }

    if(newHead==NULL) newHead=pivot; // jesli wszysko przepinalismy na koniec to pivot=newHEAD

    newEnd=tail; // nowy koniec listy to ogon

    return pivot;
} // zwracamy wskaznik na pivota i przez referencje te noew wskazniki
node *quickSortRec(node *head, node *end)
{ // sortowanie
    if(head==end or !head)return head; // head == head!=NULL !head==head==NULL
    // warunek konca, 1 pokazauje na nulla lub 1 elemntowa
    node *newHead=NULL;
    node *newEnd=NULL;
    node *pivot=partition_f(head, end, newHead, newEnd); // wskazanie pivota

    if(newHead!=pivot) // jesli rowne to nie sortujemy lewej storny
    {
        node *tmp=newHead;
        while(tmp->next!=pivot) // szukamy konca lewej storny
        {                       // szukamy az do pivota
            tmp=tmp->next;
        }
        tmp->next=NULL; // i null zeby wiedziec gdzie skonczyc sortowac

        newHead=quickSortRec(newHead,tmp); // sort
        tmp=getTail(newHead); // szukamy ostatniego elementu
        tmp->next=pivot; // przypinamy do pivota

    }

    pivot->next=quickSortRec(pivot->next, newEnd); // to samo z prawa strona, lecz jej nie musimy przypinac
    return newHead; // posortowana lista
}
void quickSort(node* &head)
{
    head=quickSortRec(head,getTail(head)); // wywolanie na liscie ktora chcemy sortowac
}
int main()
{
    node *head=NULL;
    add(head,5);
    add(head,20);
    add(head,4);
    add(head,3);
    add(head,30);

    cout << "Lista przed sortowaniem: \n";
    printlist(head);
    quickSort(head);
    cout << "\nLista po sortowaniu: \n";
    printlist(head);
}
