#pragma once
#include<string>
using namespace std;


struct AVL {
	AVL *lchild, *rchild;	//���Ҷ���ָ��
	long long val;	//�洢�Ĺ�ϣֵ
	int height;	//����
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