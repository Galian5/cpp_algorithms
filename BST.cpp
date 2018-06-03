#include<iostream>
using namespace std;

struct BSTnode
{
    int val;
    BSTnode *right;
    BSTnode *left;
    BSTnode *parent;
};

BSTnode* findNode(BSTnode *root, int value)
{
    if(root==NULL)
        return NULL;
    if(root->val==value)
        return root;
    else if(value<root->val)
        return findNode(root->left,value);
    else
        return findNode(root->right,value);
}

void add_node(BSTnode* &root,int value)
{
    BSTnode *tmp=new BSTnode;
    tmp->val=value;
    tmp->left=tmp->right=tmp->parent=NULL;
    if(root==NULL)
    {
        root=tmp;
        return;
    }

    BSTnode *p=root; // element do przeszukiwania
    BSTnode *q=NULL; // previous dla parenrta

    while(p!=NULL)
    {
        if(p->val<tmp->val)
        {
            q=p;
            p=p->right;
        }
        else
        {
            q=p;
            p=p->left;
        }
    }
    if(q->val<value)
        q->right=tmp;
    else
        q->left=tmp;

    tmp->parent=q;

}
int min(BSTnode *root)
{
    while(root->left!=NULL)
    {
        root=root->left;
    }
    return root->val;
}
int max(BSTnode *root)
{
    while(root->right!=NULL)
    {
        root=root->right;
    }
    return root->val;
}
BSTnode *succ(BSTnode *node) // zwraca nastepnika
{
    if(node->right!=NULL)
    {
        node=node->right;
        while(node->left!=NULL)
                node=node->left;
        return node;
    }
    else
    {
        while(node->parent!=NULL and node->parent->val<node->val)
            node=node->parent;
        return node;
    }

}
BSTnode *prev(BSTnode *node) // poprzednik
{
    if(node->left!=NULL)
    {
        node=node->left;
        while(node->right!=NULL)
            node=node->right;
        return node;
    }
    else
    {
        while(node->parent!=NULL and node->parent->val>node->val)
            node=node->parent;
        return node;
    }
}
int countInterval(BSTnode *T, int a, int b)
{
    if(!T)
        return 0;
    if(T->val==b and T->val==a)
        return 1;
    if(T->val<=b and T->val>=a)
        return 1+countInterval(T->left,a,b)+countInterval(T->right,a,b);
    else if(T->val<a)
        return countInterval(T->right,a,b);
    else
        return countInterval(T->left,a,b);

}
int sumBST(BSTnode *T)
{
    if(!T)
        return 0;
    if(T->left==NULL and T->right==NULL)
        return T->val;
    else
        return T->val + sumBST(T->left) + sumBST(T->right);
}
int nodesAmount(BSTnode *T)
{
    if(!T)
        return 0;
    if(T->left==NULL and T->right==NULL)
        return 1;
    else
        return 1 + nodesAmount(T->left) + nodesAmount(T->right);
}
double avarge(BSTnode *T)
{
    double sum=sumBST(T);
    double amount=nodesAmount(T);

    return sum/amount;
}
double avarge2(BSTnode *T, double &count, double &sum){
	if (T == NULL) return 0;
	avarge2(T->left, count, sum);
	avarge2(T->right, count, sum);
	if (T != NULL) {
		sum += T->val;
		count++;
	}
	if (T->parent == NULL) return sum/count ;
}
int main()
{
    BSTnode *tree=NULL;
    add_node(tree,15);
    add_node(tree,11);
    add_node(tree,20);
    add_node(tree,7);
    add_node(tree,12);
    add_node(tree,19);
    add_node(tree,30);
    add_node(tree,8);
    double c=0,s=0;
    cout << "ilosc z przedzialu [a,b] to " << countInterval(tree,5,12) <<endl;
    cout << "suma wartosci wezlow w drzewie to " << sumBST(tree) << endl;
    cout << "ilosc wezlow w drzewie to " << nodesAmount(tree) << endl;
    cout << "srednia wartosc wezla to " << avarge2(tree,c,s) << endl;
}
