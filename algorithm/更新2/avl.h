#pragma once
#include<string>
using namespace std;


struct AVL {
	AVL *lchild, *rchild;	//左右儿子指针
	long long val;	//存储的哈希值
	int height;	//树高
	AVL() {};
	AVL(long long n) {
		val = n;
		lchild = NULL;
		rchild = NULL;
	}
};


inline void update(AVL *p);
inline int factor(AVL *p);
inline void check(AVL *&p);
inline void lrotate(AVL *&p);
inline void rrotate(AVL *&p);
bool insert(AVL *&p, long long hash);



bool insertAVL(AVL *&root, string s);