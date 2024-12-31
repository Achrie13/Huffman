#include "Heap.h"
#include "config.h"
const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz0123456789+/";

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

void print_binary(int byte) {
	for (int i = 7; i >= 0; i--) {
		putchar((byte & (1 << i)) ? '1' : '0');
	}
}

void encode_base64(uschar* buffer, uschar* output, size_t size_file, Heap& h) {
	int i = 0, j = 0;

	while (i < size_file) {
		uschar temp[3] = { 0 };
		for (int k = 0; k < 3; ++k) {
			if (i < size_file) {
				temp[k] = buffer[i++];
			}
			else {
				temp[k] = 0;
			}
		}

		h.count((temp[0] >> 2) & 0x3F);
		h.count(((temp[0] << 4) | (temp[1] >> 4)) & 0x3F);
		h.count(((temp[1] << 2) | (temp[2] >> 6)) & 0x3F);
		h.count(temp[2] & 0x3F);	
		h.print_hashtable();

		output[j++] = base64_table[(temp[0] >> 2) & 0x3F];
		output[j++] = base64_table[((temp[0] << 4) | (temp[1] >> 4)) & 0x3F];
		output[j++] = base64_table[((temp[1] << 2) | (temp[2] >> 6)) & 0x3F];
		output[j++] = base64_table[temp[2] & 0x3F];
	}

	if (size_file % 3 == 1) {
		output[j - 1] = '=';
		output[j - 2] = '=';
	}
	else if (size_file % 3 == 2) {
		output[j - 1] = '=';
	}

	output[j] = '\0';
}

void preorder_traversal(HuffmanNode* node) {
	if (node == nullptr) {
		return;
	}
	printf("%c %d\n", node->data,node->freq);

	preorder_traversal(node->left);
	preorder_traversal(node->right);
}




int main(void) {
	FILE* fp = fopen("words.txt", "rb");
	if (fp == NULL) {
		perror("打开文件失败");
		return 1;
	}

	fseek(fp, 0, SEEK_END);
	int size_file = ftell(fp);
	rewind(fp);
	printf("%d字节\n", size_file);
	for (int i = 0; i < 64; ++i)
		printf("%c", base64_table[i]);
	printf("\n");
	// '\0'占1字节，编码补位向上取整加1
	int size_output = 1 + 4 * (1 + size_file / 3);
	uschar* buffer = (uschar*)malloc(size_file);
	uschar* output = (uschar*)malloc(size_output);
	if (!buffer || !output) {
		perror("内存分配失败！");
		return -1;
	}

	for (size_t i = 0; i < size_file; ++i) {
		buffer[i] = fgetc(fp);
	}

	Heap h(size_output);	
	encode_base64(buffer, output, size_file,h);
	printf("%s\n", output);
	printf("\n");

	
	for (int i = 0; i < 64; ++i) {
		int n = h.get_freq(i);
		if (n) {
			HuffmanNode* node = new HuffmanNode(base64_table[i], n);
			h.push(node);
		}
	}
	HuffmanNode* root = h.create_huffman_tree();
	cout << "\nHuffman Tree Root Frequency: " << root->freq << endl;
	preorder_traversal(root);
	return 0;
}
