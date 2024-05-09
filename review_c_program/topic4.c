#include<stdio.h>

#define SWAP_BYTES(x) \
    (((x & 0x000000FF) << 24) | \
	 ((x & 0x0000FF00) << 8)  | \
     ((x & 0x00FF0000) >> 8)  | \
     ((x & 0xFF000000) >> 24))

int checkEndian() {
	int i = 1;
	char *c = (char *)&i;
	return (*c == 1) ? 0 : 1;   // 0: little endian; 1: big endian
}

int main() {
	if (checkEndian()) {
		printf("Big Endian");
	} else {
		printf("Little  Endian");
	}
	
	unsigned int value = 0x00020001;
    printf("\n\nValue Before Converting: 0x%X\n", value);
    value = SWAP_BYTES(value);
    printf("Value After Converting: 0x%X\n", value);
	return 0;
}