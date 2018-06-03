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

node *Merge( node *a,node *b) // scalanie dwoch posortowanych list
{
    node *result=NULL; //wynik scalania
    if(a==NULL) return b; // jesli lista a pusta to zwracamay b
    else if(b==NULL) return a; // odworotnie

    if(a->val <= b->val) // spr jak sortoowac
    { // jesli el z listy a wiekszy niz b
        result =a ; // pierwszy element, zaczynamy od tego przypinac
        result->next=Merge(a->next,b); // reszte wykonujjmey rekurencyjnie, skaczac na kolejne i porownujac az do NULL na jakies
    }
    else
    {
        result=b; // identyczny przypadke jak wyzej z tym ze pierwszy el mogl byc z listy b
        result->next=Merge(a,b->next);
    }

    return result;
}
void split(node *head, node* &begList, node* &pivotPionter)
{
    // szukanie mergepointa przez 2 wskanziki: 1skacze o 1, 2skacze o 2
    node* TwoSteps; // skok o 2
    node *OneStep; // o 1
    if(head==NULL or head->next==NULL) // jesli 1 lub 0 elemenowa to oddaj poczatek na begList a koniec na pivota
    {
        begList=head;
        pivotPionter=NULL;
    }
    else // jesli dluzsze
    {
        TwoSteps=head->next; //liczenie od kolejnego elementu
        OneStep=head;
        while(TwoSteps!=NULL) // petla do nulla
        {
            TwoSteps=TwoSteps->next;
            if(TwoSteps!=NULL) // nie robimy TS=TW->next->next bo okaze sie ze w ktorejs iteracji wyjdziemy poza liste, bo moze byc niearzysta ilosc
            {
                OneStep=OneStep->next;
                TwoSteps=TwoSteps->next;
            }

        }

        begList=head; // beg jest poczatkiem listy
        pivotPionter=OneStep->next; // pivot jest kolejnem elementem po znalezionym srodku
        OneStep->next=NULL; // NULL zeby wiedziec gdzie sie konczy i dokadd sortowac


    }
}
void MergeSort(node* &head)
{
    node *tmp=head; // tmp zeby nie zniszczyc listy
    node *a; // lancuch nr1
    node *b; // nr 2

    if(tmp==NULL or tmp->next==NULL) return; // warunek konca rekurencji, 1 element lub zero

    split(tmp, a, b); // rozdzielenie listy na 2 lanuchy a i b
    MergeSort(a); // sortowane rekurencyjne a
    MergeSort(b); // --||-- b

    head=Merge(a,b); //wsakznik na head scalonej posortowanej listy
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
    MergeSort(head);
    cout << "\nLista po sortowaniu: \n";
    printlist(head);
}
