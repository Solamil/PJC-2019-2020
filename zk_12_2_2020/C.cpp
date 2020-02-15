#include <stdio.h>
#include <stdlib.h>
/* program resici zadani zk z PJC ze dne 12_2_2020
1.	Napište program v C, kterı mít následující funkce:
	a.	Naètení pole long (pøedané jako parametr funkce) a pøedení long prvkù na int a to tak, 
		e se oddìlí první 4B z long == 1 int a druhé 4B z long == 2 int. Nové pole int se pak vrací do hlavního programu. Návratovou hodnotu je také pøípadná chyba (nepodaøilo se alokovat pamì atd.).
	b.	Funkci pro vytvoøení CRC obou polí a to tak, e se jak pole long tak i pole int ète po 1B a 
		dìlá se souèet naètenıch Byte (po 1 Byte). Funkce vrací jak CRC souèet long pole tak i int pole 
		do hlavního programu (vrací tedy dvì hodnoty).
	c.	Nepište ádné include ani main atd. jen co je nutné pro tyto dvì funkce.

*/

/* pomocne definice a alokace*/
#define SIZE 10
int alocateLongArray(long **return_array, int length) {
	long *temp_array;
	temp_array = (long *)malloc(length * sizeof(long));
	if (temp_array == NULL) return 1;
	else {
		int i = 0;
		for (i = 0; i < length; i++) temp_array[i] = (long)(i*100000);
		*return_array = temp_array;
		return 0;
	}
}

void printArray(long *in_array, int length) {
	if (in_array != NULL){
		int i = 0;
		for (i = 0; i < length; i++) printf("%ld ", in_array[i]);
	}	
}

void printArrayInt(int *in_array, int length) {
	printf("int array: \n");
	if (in_array != NULL) {
		int i = 0;
		for (i = 0; i < length; i++) printf("%d ", in_array[i]);
	}
}
/* konec - pomocne definice a alokace*/


/* TATO CAST STACILO MIT UZ ZK - AZ DO RADKU 140*/
/* 
funce pro nacteni pole long jako int
*/
int readLongArrayAsInt(int **int_array, long *long_array, int length) {
	/* 
	protoze mame vracet do hlavniho programu pripadnou chybu (v C je to jako napr. int), 
	je treba predat nove vytvorene pole int jako parametr pres pointer. 
	Jedna se o pole (tedy pointer) a proto je v hlavicce funkce int **int_array (tedy 2 x *) 
	misto jedne *.  
	int *temp_array je pomocny pointer abychom nemuseli pouzivat stale dve ** 
	*/
	int *temp_array;

	/* 
	nasim ukolem je cist pole long po int.
	K tomu lze vyuzit celou radu postupu, pres bitove operace(maskovani, posuny)
	az po z meho pohledu jednodussi postup, kdy vyuzijeme toho, ze C pristupuje k praci s pameti 
	jednotne a cte blok pameti po takovych usecich, ktere odpovidaji datovemu typu pouziteho ukazatele.
	Pouzijeme druhy zpusob. 
	Proto defunuji pointer typu int (chce cist pole jako int) int *temp_pointer_to_long_array
	*/
	int *temp_pointer_to_long_array; 
	/*
	nastavime pointer temp_pointer_to_long_array, aby zkazoval na zacatek pole long + nutne 
	pretypovani
	*/
	temp_pointer_to_long_array = (int *)long_array;
	/*
	alokujeme pole int, ktere bude 2* delsi nez pole long - long je dvakrat delsi nez int co se
	poctu bytu tyce.
	Nicme bz slo i pouzit:
	(int *)malloc(length * sizeof(long)); 
	Je Vam jasne proc?
	*/
	temp_array = (int *)malloc(2* length * sizeof(int));
	if (temp_array == NULL) return 1;
	int i = 0;
	/* 
	cteme po jednotlivych blocich, az do poctu lenght * 2 (vime ze int je polovicni vuci long a 
	malloc alokoval pole 2* length
	*/
	for (i = 0; i < length * 2; i++) {
		/*
		jednodusse se pak posouvame po bloku pameti, ktery odpovida poli long po blocich delky 
		rvonajici se delce pouziteho pointeru (v nasem pripade temp_pointer_to_long_array, coz je
		definovane jako int *)
		*/
		temp_array[i] = temp_pointer_to_long_array[i];
		/*
		chete-li se presvedcit, ze cteme po 4 byte, tak si nastavte debug watch na:
		long_array - adresa zacatku pole long
		&temp_pointer_to_long_array[i] - adresa aktualniho prvku
		pro prvni prvek by se adresy mely rovnat. Pro druhy prvek (i == 1)
		by mel byt rozdil adres 4 byte.
		*/
	}
	/*
	nastavime odpovidajici hodnotu do promenne int_array, kterou pak vracime jako navratovou hodnotu.
	*/
	*int_array = temp_array;
	return 0;
}

/*
funce pro nacteni pole long i int po byte

Jedna se o modifikaci pristupu z funce  readLongArrayAsInt, jen pouzijeme pointe na char
(tedy blok o delce 1 byte). 
*/
void  readArraysAsBytes(int *int_array, long *long_array, int length, int *long_CRC, int *int_CRC) {
	char * temp_int_array;
	char * temp_long_array;
	/*
	nastavime pointery aby zkazovaly na zacatek pole long a int + nutne	pretypovani
	*/
	temp_int_array = (char *)int_array;
	temp_long_array = (char *)long_array;
	
	int i = 0;
	int int_array_sum = 0;
	int long_array_sum = 0;
	/*
	delka bloku pameti, ktery chceme cist je dana delkou pole long * pocet byte datoveho typu long.
	*/
	for (i = 0; i < length*sizeof(long); i++) {
		/* 
		cteme bloky pameti po bloku odpovidajicimu velikosti datoveho typu pouziteho 
		pointeru, v nasem pripade chat tedy 1 byte a delame prosty soucet
		*/
		(*int_CRC) += temp_int_array[i];
		(*long_CRC) += temp_long_array[i];
	}
}

/*KONEC CASTI, KTEROU BYLO TREBA MIT U ZK */

int main() {
	long *long_array;
	if (alocateLongArray(&long_array, SIZE) != 0) return 1;

	printArray(long_array, SIZE);

	int *int_array;
	
	if ( readLongArrayAsInt(&int_array, long_array, SIZE) != 0) return 2;
	printArrayInt(int_array, SIZE*2);
	int long_CRC = 0; int int_CRC = 0;
	readArraysAsBytes(int_array, long_array, SIZE, &long_CRC, &int_CRC);
	printf(" \n result long : %d, int : %d \n", long_CRC, int_CRC);

	free((void*)long_array);
	free((void *) int_array);
	getchar();
	return 0;
}