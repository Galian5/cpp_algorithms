#include<iostream>
using namespace std;
struct vertex
{
    vertex *next;
    int v;
};
struct node
{
    node *parent;
    int rank;
    int val;
};
node *MAKESET(vertex *a)
{
    node *s=new node;
    s->parent=s;
    s->val=a->v;
    s->rank=0;
    return s;
}
node *FIND(node *x) {

	if (x->parent != x) {
		node *y = FIND(x->parent);
		x->parent = y;
		return y;
	}
	else
		return x;
}
void UNION(node *x, node *y) {
	node *Px = FIND(x);
	node *Py = FIND(y);
	if(Px!=Py)
    {
       if (Py->rank < Px->rank)
            Py->parent = Px;
       else {
            Px->parent = Py;
            if (Px->rank == Py->rank)
                Px->rank++;
            }
    }
}
void AP(vertex **G)
{

}
int main()
{
    vertex **G;
    int n,m,v1,v2; // liczba wierzcholkow, krawedzi
    cin >> n >> m;
    G= new vertex *[n];
    for(int i=0; i<n;i++)
    {
        G[i]=NULL;
    }
    for(int i=0;i<m;i++)
    {
        cin >> v1 >> v2;
        vertex *p,*q;
        p = new vertex;    // Tworzymy nowy element
        p->v = v2;          // Numerujemy go jako v2
        p->next = G[v1];    // Dodajemy go na pocz¹tek listy A[v1]
        G[v1] = p;
        q = new vertex;    // Tworzymy nowy element
        q->v = v1;          // Numerujemy go jako v2
        q->next = G[v2];    // Dodajemy go na pocz¹tek listy A[v1]
        G[v2] = p;
    }
}
