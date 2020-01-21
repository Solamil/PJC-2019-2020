/* 1. chceme mít možnost uložit do seznamu libovolný prvek.
Definujte si tedy základní střídu, která nám určí, co musím všechny třídy, které bude chtít uživatel do našeho seznamu vložit splňovat.
*/

class LinkedListObject {
private:
public:
protected:

};
/* ve finále se v tomto případě a pro potřeby zkoušky můžeme spokojit s touto jednoduchou definicí. Vždy prosím pište jen to, co je zadáno. To co zadáno není Vám nepřinese nic navíc, spíše mínus body za pokus opít mě rohlíkem .
Pokud by v zadání bylo řečeno, že např. musí být možnost vytisknout třídu na obrazovku, pak
je nutné dodefinovat metodu toString(), která ale musím být čistě virtuální, tedy == 0.
Tím říkáme, že každá třída, co bude vložitelná do seznamu se musí postarat o definici takovéto metody.
Cože je v pořádku, protože my jako tvůrci seznamu nemáme tušení, jak obecnou třídy vytisknout na obrazovku
Po úpravě tedy:
*/
class MyLinkedListObject {
private:
public:
	string toString() == 0;
protected:
};


/*
Dalším krokem je vytvoření vlastního objektu seznamu:
používáme pointery, protože pracujeme s objekty a ty mohou být velké a pokud bychom pointer nepoužili,
tak se nám celý objekt bude kopírovat - to budu u zk považovat za důležité, že se chováme ke zdrojům počítače rozumně.
*/

class MyLinkedListNode {
private:
	MyLinkedListObject * data;
	MyLinkedListObject* next;
public:
protected:
};


/* poslední prvkem je vlastní spojový seznam. Vzhledem k tomu, že v části C++ nebudu chtít vidět konkrétní implementaci (pokud to nebude explicitně řečeno a konkrétní třídy),
tak bude stačit jen definovat hlavičky základních metod a atributy nutné pro správnou funkci.
Tedy bohatě bude stačit naznačit funkci pro vložení, kde využijeme námi definovanou třídu.
Případné implementace již nechám na Vás*/

class MyLinkedList {
private:
	MyLinkedListNode *head, *tail;
public:
	void insertnode(MyLinkedListNode node) {}
	void diplay() {}
	void sort() {}
}

