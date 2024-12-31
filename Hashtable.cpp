#include "Hashtable.h"

inline void HashTable::count(uschar key) {
	int index = bin_to_dec(key);
	if (index != -1) {
		freq[index]++;
	}
}
