#include "Heap.h"



inline Heap::Heap(int cap) : size(0), capacity(cap) {
	arr = (HuffmanNode**)malloc(capacity * sizeof(HuffmanNode*));
	for (int i = 0; i < size_hashtable; i++) {
		freq[i] = 0;
	}
}

inline Heap::~Heap() {
	free(arr);
}

inline HuffmanNode* Heap::top() {
	if (size > 0) {
		return arr[0];
	}
	return nullptr;
}

inline HuffmanNode* Heap::pop() {
	if (size == 0) {
		return nullptr;
	}
	HuffmanNode* top = arr[0];
	arr[0] = arr[size - 1];
	size--;
	down(0);
	return top;
}

inline void Heap::down(int idx) {
	while (true) {
		int left = 2 * idx + 1;
		int right = 2 * idx + 2;
		int smallest = idx;

		if (left < size && arr[left]->freq < arr[smallest]->freq) {
			smallest = left;
		}
		if (right < size && arr[right]->freq < arr[smallest]->freq) {
			smallest = right;
		}

		if (smallest == idx) {
			break;
		}

		std::swap(arr[idx], arr[smallest]);
		idx = smallest;
	}
}

inline void Heap::up(int idx) {
	while (idx > 0 && arr[idx]->freq < arr[(idx - 1) / 2]->freq) {
		std::swap(arr[idx], arr[(idx - 1) / 2]);
		idx = (idx - 1) / 2;
	}
}

inline void Heap::push(HuffmanNode* node) {
	if (size == capacity) {
		perror("堆已满，无法插入！");
		return;
	}
	arr[size] = node;
	++size;
	up(size - 1);
}

inline int Heap::get_freq(int idx) {
	if (freq[idx])
		return freq[idx];
	return 0;
}

inline void Heap::print_hashtable() {
	for (int i = 0; i < 64; ++i) {
		if (freq[i])
			printf("%d", freq[i]);
		else printf(" ");
	}
	printf("\n");
}

inline HuffmanNode* Heap::create_huffman_tree() {
	while (size > 1) {
		HuffmanNode* temp[2];
		temp[0] = pop();
		temp[1] = pop();
		HuffmanNode* node = new HuffmanNode();
		node->freq = temp[0]->freq + temp[1]->freq;
		node->left = temp[0];
		node->right = temp[1];
		temp[0]->parent = node;
		temp[1]->parent = node;
		push(node);
	}
	return arr[0];
}
