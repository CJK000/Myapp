#include"trie.h"


C::C() {
	nxt = NULL;
	next = NULL;
}

C::C(char cc) {
	c = cc;
	nxt = new Trie();
	next = NULL;
}

Trie::Trie() {
	c = new C();
	flag = false;
}


bool Trie::Insert(string s) {
	int len = s.length();
	Trie *p = this; 
	C *q;
	C *f;
	for (int i = 0; i < len; i++) {
		q = p->c;
		if (s[i] == ' ' || s[i] == '=')continue;
		for (f = q->next; f != NULL; f = f->next) {
			q = f;
			if (f->c == s[i]) {
				break;
			}
		}
		if (f != NULL) {
			p = f->nxt;
		}
		else {
			q->next = new C(s[i]);
			p = q->next->nxt;
		}
	}
	if (p->flag == false) {
		p->flag = true;
		return true;
	}
	else {
		return false;
	}
}