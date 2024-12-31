//#include <stdio.h>
//#include <stdlib.h>
//#include <stdint.h>
//#define uschar unsigned char
//const char base64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
//"abcdefghijklmnopqrstuvwxyz0123456789+/";
//void print_binary(int byte) {
//	for (int i = 7; i >= 0; i--) {
//		putchar((byte & (1 << i)) ? '1' : '0');
//	}
//}
//int bin_to_dec(uschar byte) {
//	int sum = 0, a = 1;
//	while (byte) {
//		sum += (byte % 10) * a;
//		a *= 10;
//		byte /= 10;
//	}
//	return sum;
//}
//
//void encode_base64(uschar* buffer, uschar* output, size_t size_file) {
//	int i = 0, j = 0;
//
//	while (i < size_file) {
//		uschar temp[3] = { 0 };
//		for (int k = 0; k < 3; ++k) {
//			if (i < size_file) {
//				temp[k] = buffer[i++];
//			}
//			else {
//				temp[k] = 0;
//			}
//		}
//
//		output[j++] = base64_table[(temp[0] >> 2) & 0x3F];
//		output[j++] = base64_table[((temp[0] << 4) | (temp[1] >> 4)) & 0x3F];
//		output[j++] = base64_table[((temp[1] << 2) | (temp[2] >> 6)) & 0x3F];
//		output[j++] = base64_table[temp[2] & 0x3F];
//	}
//
//	if (size_file % 3 == 1) {
//		output[j - 1] = '=';
//		output[j - 2] = '=';
//	}
//	else if (size_file % 3 == 2) {
//		output[j - 1] = '=';
//	}
//
//	output[j] = '\0';
//}
//
//int main() {
//	FILE* fp = fopen("words.txt", "rb");
//	if (fp == NULL) {
//		perror("打开文件失败");
//		return 1;
//	}
//
//	fseek(fp, 0, SEEK_END);
//	int size_file = ftell(fp);
//	rewind(fp);
//	printf("%d字节\n", size_file);
//	// '\0'占1字节，编码补位向上取整加1
//	int size_output = 1 + 4 * (1 + size_file / 3);
//	uschar* buffer = (uschar*)malloc(size_file);
//	uschar* output = (uschar*)malloc(size_output);
//	if (!buffer || !output) {
//		perror("内存分配失败！");
//		return -1;
//	}
//
//	for (size_t i = 0; i < size_file; ++i) {
//		buffer[i] = fgetc(fp);
//		print_binary(buffer[i]);
//		printf(" %d", buffer[i]);
//		printf(" %d", bin_to_dec(buffer[i]));
//		putchar('\n');
//	}
//	encode_base64(buffer, output, size_file);
//	printf("%s", output);
//
//
//
//	return 0;
//}
