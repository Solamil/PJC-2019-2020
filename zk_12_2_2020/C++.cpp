/* program resici zadani zk z PJC ze dne 12_2_2020
	2.	Napište v C++ program, který bude realizovat tabulku / grid pro zobrazení záznamù.
		a.	Deklarujte odpovídající tøídy a metody, které umožní uživateli využít grid pro zobrazení 
			libovolných dat(pøedaných napø.jako pole èi vector / list).
		b.	Deklarujte, co musím uživatel a jeho data splòovat, aby mohla být zobrazena ve vašem gridu
			(deklarujte odpovídající struktury)
*/

/* jedna se pouze o nastineni programu, nepujde tedy spustit.*/


/*
	Zakladni ukolem je zobrazovat obecne prvky na obrazovku (v nasem pripade se jedna o grid).
	Otazka tedy je, jak to zaridit. Potrebujeme ziskat jakousi textovou hodnotu obecneho objektu,
	ktery je pak zobrazen v gridu. 
	Muzeme si ale vzpomenout, na kurz JAVA, kde kazdy objekt mel zakladni metody 
	(protoze dedil od v JAVE definovane tridy Object) a jedna z nich byla toString(). 
	A mame reseni. Proc nepuzit vedomosti a postupu z jineho jazyku. 

*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;
/* 
definujeme tedy tridu Column, ktera definuje virtualni metodu toString()
*/
class Column {
public:
	virtual string toString() = 0;
};

/*
Nasleduje vlasnit trida Grid.
Tam jen definujeme, ze umime zobrazit cokoli, co implementuje metodu toString tridy Column.
Data si pak ulozime jako vector (ekvivalent ArrayList JAVY)
Pro vlozeni dat pouzime metodu - setter).
Vlastni zobrazeni pak resi metoda display.
*/

class Grid {
private:
	vector<Column *> columns;
public:
	void addColumn(Column * column);
	void addColumns(vector<Column *> columns);

	void display();
};

/*
vlastni implementce je tu jen pro ukazku, u zk jsem ji nepotreboval.
*/
void Grid::display() {
	cout << "printing columns:";
	for (vector<Column *>::iterator it = columns.begin(); it != columns.end(); ++it)
		cout << ' ' << (*it)->toString();
	cout << '\n';
}

/*
toto v podtate staci, nic vic neni treba. Kdzy nekdo chce nas Grid pouzit musi naimplementovat 
metodu toSting tridy Column
Existuji jiste i obecnejsi reseni, ale pro ucely zkousky to je dostacujici takto. 
Jak jsem nakonec rikal nespocentnekrat na prednasce i cviceni, jak budete mit vice kodu nez na 
jednu  A4, tak to asi nebude dobre.

Pokud by to nekoho zajimalo, tak se muzete podivat na https://docs.oracle.com/javase/tutorial/uiswing/components/table.html
kde je to same, ale realne pouzitene pro Javu - knohovna SWING (pro tvobu GUI)
*/