#include <stdio.h>
#include <stdlib.h>

/* a.	Napište funkci, která urèí kolik je volné pamìti v poèítaèi, výsledek zobrazí v kB. */
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

/*b.	Napište funkci, která zjistí jaký je nejvìtší souvislí blok volné pamìti v poèítaèi, výsledek zobrazí v MB.*/

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


