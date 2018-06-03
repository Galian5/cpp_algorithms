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
void add_to_list_at_end(node* &head,  int value ) // Nowy na koniec listy
{
    node *tmp=new node;     //Pomocnicza do swotrzenia elementu
    node *last;             // Pomocnicza ktora bedzie ostatnim elementem listy starej, do ktorej przypmniemy tmp
    tmp->val=value;
    tmp->next=NULL;         //Nowy element MUSI pokazywac teraz na koniec listy
    last=head;
    if(last!=NULL)
    {
        while(last->next!=NULL) last=last->next; // Przesuwamy sie na koniec listy
        last->next=tmp;     //Ostatni wskaznik pokazuje teraz na nasza nowa wartosc
    }
    else head=tmp;  // Jesli lista byla pusta

}
int get(node* &head)
{
    int tmp;
    if(head->next!=NULL)
    {
        tmp=head->val;
        head=head->next;
    }
    else if(head->next==NULL)
    {
        tmp=head->val;
        head=NULL;
    }
    return tmp;
}
node *concat(node *list1, node *list2, node *list3)
{
    node *tmp=list1;
    while(list1!=NULL and tmp->next!=NULL)
    {
        tmp=tmp->next;
    }
    node *tmp2=list2;
    while(list2!=NULL and tmp2->next!=NULL)
    {
        tmp2=tmp2->next;
    }
    if(list1!=NULL){
        tmp->next=list2;
        tmp2->next=list3;
        return list1;
    }
    else{
        tmp2->next=list3;
        return list2;
    }
}
node *quicksort(node *head)
{
    if(head==NULL) return head;
    int pivot=get(head);
    int tmp;
    node *lista1=NULL;
    node *lista2=NULL;
    node *lista3=NULL;
    add_to_list_at_end(lista2,pivot);
    while(head!=NULL)
    {
        tmp=get(head);
        if(tmp<pivot) add_to_list_at_end(lista1,tmp);
        else if(tmp > pivot) add_to_list_at_end(lista3,tmp);
        else add_to_list_at_end(lista2,tmp);
    }

    return concat(quicksort(lista1),lista2,quicksort(lista3));

}
int main()
{
    node *head=NULL;
    add_to_list_at_end(head,5);
    add_to_list_at_end(head,5);
    add_to_list_at_end(head,5);
    add_to_list_at_end(head,20);
    add_to_list_at_end(head,4);
    add_to_list_at_end(head,3);
    add_to_list_at_end(head,30);

    cout << "Lista przed sortowaniem: \n";
    printlist(head);
    head=quicksort(head);
    cout << "\nLista po sortowaniu: \n";
    printlist(head);

}

