#include"avl.h"
#include<string>
#include<algorithm>
using namespace std;




inline void update(AVL *p) {
	p->height = max(p->lchild->height, p->rchild->height) + 1;
}

inline int factor(AVL *p) {
	return p->lchild->height - p->rchild->height;
}

inline void lrotate(AVL *&p) {
	AVL *r;
	r = p->rchild;
	p->rchild = r->lchild;
	r->lchild = p;
	p = r;
	update(p);
}

inline void rrotate(AVL *&p) {
	AVL *l;
	l = p->lchild;
	p->lchild = l->rchild;
	l->rchild = p;
	p = l;
	update(p);
}

inline void check(AVL *&p) {
	int nf = factor(p);
	if (nf > 1) {
		int lf = factor(p->lchild);
		if (lf > 0) rrotate(p);
		else {
			lrotate(p->lchild);
			rrotate(p);
		}
	}
	else if (nf < -1) {
		int rf = factor(p->rchild);
		if (rf < 0) lrotate(p->rchild);
		else {
			rrotate(p->rchild);
			lrotate(p);
		}
	}
	else if (p != NULL) update(p);
}

bool insert(AVL *&p, long long hash) {
	if (p == NULL) {
		p = new AVL(hash);
		return true;
	}
	if (p->val == hash) return false;
	if (hash < p->val) return insert(p->lchild, hash);
	return insert(p->rchild, hash);
}

long long mod = 99999999999973;
long long Hash(string &s) {
	long long ret=0;
	int i;
	int len = s.length();
	for (i = 0; i < len; i++) {
		ret = (ret * 127 + s[i]) % mod;
	}
	return ret;
}

bool insertAVL(AVL *&root, string s) {
	return insert(root, Hash(s));
}