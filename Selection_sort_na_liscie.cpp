#include<iostream>
using namespace std;

struct node
{
    int val;
    node *next;
};
void new_obj(node* &head, int value)
{
    node *tmp=new node;
    tmp->val=value;
    tmp->next=head;
    head=tmp;
}
void printlist(node *head)
{
    while(head!=NULL)
    {
        cout << head->val << " ";
        head=head->next;
    }
}
node* el_max(node* &p)
{
    node *max_prev=NULL;
    node *prev=NULL;
    int max_v=p->val;
    node *res=p;
    while(res!=NULL)
    {
        if(res->val>max_v)
        {
            max_v=res->val;
            max_prev=prev;
        }
        prev=res;
        res=res->next;
    }
    node *tmp;
    if(max_prev==NULL)
    {

        tmp=p;
        p=p->next;
    }
    else
    {
        //node *tmp;
        tmp=max_prev->next;
        max_prev->next=tmp->next;
    }
    return tmp;

}
node *sel_sort(node* head)
{
    node *result=NULL;
    while(head!=NULL)
    {
        node *tmp=el_max(head);
        tmp->next=result;
        result=tmp;
    }
    printlist(result);
    return result;
}
int main()
{
    node *head=NULL;
    new_obj(head,1);
    new_obj(head,5);
    new_obj(head,4);
    printlist(head);
    cout << "\n";
    sel_sort(head);
    //printlist(head);
    return 0;
}

