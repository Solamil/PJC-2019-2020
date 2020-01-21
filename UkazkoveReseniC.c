#include <stdio.h>
#include <stdlib.h>

/* a.	Napi�te funkci, kter� ur�� kolik je voln� pam�ti v po��ta�i, v�sledek zobraz� v kB. */
long maxAvailableMemory() {
	long size = 10;
	char *memory;
	memory = (char *)malloc(sizeof(char)*size * 1024);
	while (memory != NULL) {
		size += 10;
		memory = (char *)malloc(sizeof(char)*size);
	}
	return size;
}

/*b.	Napi�te funkci, kter� zjist� jak� je nejv�t�� souvisl� blok voln� pam�ti v po��ta�i, v�sledek zobraz� v MB.*/

long maxAvailableMemoryBlock() {
	long size = 1;
	int split = 1;
	char *memory;
	while (1) {
		memory = (char *)malloc(sizeof(char)*size*1024*1024);
		if (memory != NULL) {
			free((void *)memory);
			memory = NULL;
			size += (size/split) * 2;
		}
		else {
			if (size < split) break; // that needs tuning for sure, is it ok anyway? :)
			size -= ((size/split) / 2);
			split += split+2;
		}
	}

	return size;
}



int main() {

	printf(" Max Memory Block: %ld \n", (maxAvailableMemoryBlock()));

	printf(" Max Memory: %ld \n", (maxAvailableMemory()));
	
	getchar();  

}


