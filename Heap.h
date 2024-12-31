#pragma once
#include "config.h"
#include"Hashtable.h"

struct HuffmanNode {
	char data;
	int freq;
	HuffmanNode* parent;
	HuffmanNode* left;
	HuffmanNode* right;
	HuffmanNode(char d = 0, int n = 0)
		: data(d), freq(n), parent(nullptr), left(nullptr), right(nullptr) {
	}
};


class Heap :public HashTable {
protected:
	HuffmanNode** arr;
	int size;
	int capacity;
public:
	Heap(int cap);

	~Heap();

	HuffmanNode* top();

	HuffmanNode* pop();

	void down(int idx);

	void up(int idx);

	void push(HuffmanNode* node);

	int get_freq(int idx);
	void print_hashtable();

	HuffmanNode* create_huffman_tree();
};
