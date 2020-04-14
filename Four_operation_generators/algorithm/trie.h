#pragma once
#include<cstdlib>
#include<string>
using namespace std;

class Trie;
class C {
public:
	char c;	//下一个字符
	Trie *nxt;	//下一个字符的 Trie 树节点指针
	C *next;	//兄弟节点指针
	C();
	C(char cc);
};

class Trie {
public:
	//用链表存储儿子节点，节省空间
	C *c;	//存储下一个字符是什么，以及对应的 Trie 树节点
	bool flag;
	Trie();
	bool Insert(string s);
};