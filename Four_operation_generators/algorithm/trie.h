#pragma once
#include<cstdlib>
#include<string>
using namespace std;

class Trie;
class C {
public:
	char c;	//��һ���ַ�
	Trie *nxt;	//��һ���ַ��� Trie ���ڵ�ָ��
	C *next;	//�ֵܽڵ�ָ��
	C();
	C(char cc);
};

class Trie {
public:
	//������洢���ӽڵ㣬��ʡ�ռ�
	C *c;	//�洢��һ���ַ���ʲô���Լ���Ӧ�� Trie ���ڵ�
	bool flag;
	Trie();
	bool Insert(string s);
};