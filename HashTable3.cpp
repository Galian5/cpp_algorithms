#include <iostream>
using namespace std;
#include <string>



struct HT {
	string *key;
	int *data;
	bool *free;
	int size;
};

int hashK(string key, int size){
	return 1;
};

bool checkHT(HT *ht) {
	int i = 0;
	int startSeries = 0;
	while (i < ht->size && ht->free[i] == false) i++;		// szukamy pierwszej dziury znalezlismy to i wskazuje na pierwsze pole za dziur¹

	while (i < ht->size) {
		if (ht->free[i] == true) {							// sprawdzamy czy pole na ktorym jestesmy nie jest przpadkiem wolne jesli jest idziemy dalej i szukamy pierwszego zajetego
			i++;											// po tym przypadku w petli jestesmy indeksem i na pierwszym zajetym polu po dziurze
			startSeries = i;								// ustawiamy poczatek ciagu na ten element(pierwszy za dziura)
		}
		else {												// przypadek ze nie jestesmy na dziurze
			int h = hashK(ht->key[i], ht->size);			// hashujemy indeks key ma odpowiadaæ indeksowi w tablicy danych czyli jesli dane sa przesuniete to key tez bedzie na przesunietym polu
			if (h < startSeries || h > i) return false;		// sprawdzamy czy po 1. nasz hash ktory powinien wskazywac na dany element nie wskazuje na dziurê/lub inny ci¹g
			i++;											// po 2 czy nasz hash nie wskazuje dalej niz powinien wtedy tez nie odnajdziemy elementu bo jezeli znajduje sie on na [3] a hash wskazuje na[4] to dupa
		}
	}														// po tym wszystkim startseries jest na ostatnim ciagu w tablicy
	i = 0;													// oraz wiemy ze narazie wszystko oprocz pierwzsego ciagu w tablicy sie zgadza
	while (i < ht->size && ht->free[i] == false) {			// idziemy po tablicy od poczatku je¿eli nie ma dziury
		int h = hashK(ht->key[i], ht->size);
		if (h < startSeries && h > i) return false;			// 1. sprawdzamy czy hash jest wiekszy rowny niz poczatek ostatniego ciagu jestli jest to wszystko jest w porzadku jesli nie to :
		i++;												// 2. oznacza ze musi wskazywaæ gdzies na poczatek tablicy wiec nie moze wskazywaæ za sprawdzane pole
	}
	return true;
}
