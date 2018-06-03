#include <iostream>
#include <time.h>
#include <cstdlib>
#include <climits>
#define INF 2147483647
using namespace std;
const int max_lvl = 7;
int min(int a, int b) {
	if (a > b) return b;
	return a;
}
struct SLNode {
	int value;
	SLNode ** next;
};
struct SkipList {
	SLNode *first;
	SLNode *last;
	int max_lvl;
};
int level() {
	int lvl = 1;
	int x = rand()%100;
	while (x < 50) {
		lvl++;
		x = rand()%100;
	}
	return min(lvl, max_lvl);


}

SLNode *search_node(SkipList *S, int val)
{
    int lvl=S->max_lvl-1;
    SLNode *tmp=S->first;
    for(;lvl<=0;lvl--)
    {
        while(tmp->next[lvl]->value<val)
        {
            tmp=tmp->next[lvl];
        }
    }
    tmp=tmp->next[0];
    if(tmp->value==val)
        return tmp;
    else
        return NULL;
}

void add(int val, SkipList a){
	int lvl = level();
	SLNode *temp = new SLNode;
	temp->next = new SLNode*[lvl];
	temp->value = val;
	lvl--;
	for (int i = max_lvl-1; i >= 0; i--)
	{
		while (a.first->next[i]->value < val)
			a.first = a.first->next[i];
		if (i <= lvl)
		{
			temp->next[i] = a.first->next[i];
			a.first->next[i] = temp;
		}

	}
}
SLNode* del(SkipList a, int val){
	int moment = max_lvl;
	SLNode *tmp;
	tmp = NULL;
	for (; moment >0;) {
		moment--;
		while (a.first->next[moment]->value < val)
			a.first = a.first->next[moment];
		if (a.first->next[moment]->value == val) {
			a.first->next[moment] = a.first->next[moment]->next[moment];
		}

	}
    if (a.first->next[moment]->value == val) {
			tmp = a.first->next[moment];
			a.first->next[moment] = a.first->next[moment]->next[moment];
			delete[] tmp->next;
			return tmp;
		}
	else
		return NULL;

}


int main() {
	srand(time(NULL));
	SkipList S;
	S.max_lvl = max_lvl;
	SLNode *first = new SLNode;
	first->value = -INF -1;
	first->next = new SLNode*[S.max_lvl];
	SLNode *last = new SLNode;
	last->value = INF;
	last->next = new SLNode*[S.max_lvl];
	for (int i = 0; i < 7; i++){
		first->next[i] = last;
		last->next[i] = NULL;
	}
	S.first = first;
	S.last = last;
	int d;
	for (int i = 0; i < 10; i++)
	{
		d = i;
		cout << d << "   ";
		add(d, S);
	}
	cout << endl;
	SLNode *tmp;
	tmp = S.first;
	for (int i = 6; i >= 0; i--) {
		tmp = S.first;

		while (tmp->next[i] != NULL)
		{
			cout << tmp->value;
			tmp = tmp->next[i];
			cout << "   ";
		}
		cout << endl;
	}
	cout << "-----------------" << endl;
	del(S, 4);
	del(S, 0);
	del(S, 7);
	for (int i = 6; i >= 0; i--) {
		tmp = S.first;

		while (tmp->next[i] != NULL)
		{
			cout << tmp->value;
			tmp = tmp->next[i];
			cout << "   ";
		}
		cout << endl;
	}
	int dummy;
	cin >> dummy;
}
