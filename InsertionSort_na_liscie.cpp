#include<iostream>
using namespace std;
struct node
{
    int val;
    node *next;
};
void printlist(node *head)
{
    while(head!=NULL)
    {
        cout << head->val << " " ;
        head=head->next;
    }
}
void add(node* &head,int value)
{
    node* tmp=new node;
    tmp->val=value;
    tmp->next=head;
    head=tmp;
}
void insertsort(node *list, node *element)
{
    while(list->next!=NULL and ((list->next->val) <(element->val)))
    {
        list=list->next;
    }
    element->next=list->next;
    list->next=element;
}
node *sortlisti(node *head)
{
    node *result=new node;
    result->next=NULL;
    while(head->next!=NULL)
    {
        node *tmp=head->next;
        head->next=tmp->next;
        tmp->next=NULL;
        insertsort(result,tmp);
    }
    delete head;
    node *t=result;
    result=t->next;
    delete t;
    printlist(result);
    return result;
}

int main()
{
    node *head=NULL;
    add(head,1);
    add(head,4);
    add(head,3);
    add(head,123);
    add(head,31);
    add(head,3555);
    add(head,111111); // wartownik
    printlist(head);
    cout << "\n";
    sortlisti(head);



    return 0;
}
