#pragma once
#include "config.h"
#define size_hashtable 64

class HashTable {
protected:
	int freq[size_hashtable];
public:
	void count(uschar key);
	int bin_to_dec(uschar byte) {
		int sum = 0, a = 1;
		while (byte) {
			sum += (byte % 10) * a;
			a *= 10;
			byte /= 10;
		}
		return sum;
	}
};

