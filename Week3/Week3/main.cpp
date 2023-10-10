#include <iostream>
using namespace std;

int main() {
	//vectori - recap
	//siruri de caractere
	//vectori de numere/obiecte/entitati

	//static
	//dinamic - de preferat

	unsigned char caracter = 48; //valori numerice pe 1 byte -> usigned volosesc doar valori pozitive
	caracter += 1;
	cout << endl << "Caracterul este: " << caracter; //caracterul printabil 0 are codul ASCII 48 ( sau 1 pentru 49 )

	caracter = 'a'; // 'a'-> un caracter | "a" -> sir de caractere (2 caractere in sir)
	cout << endl << "Caracterul este: " << caracter;

	//Definire siruri de caractere statice -> orice vector statisc este gestionat de un pointer
	char nume[20];
	char prenume[] = "Gigel";

	//initializare siruri de caractere
	strcpy_s(nume, 20, "Popescu"); //copiaza si \0 si 20 este dimensiunea ( functioneaza si fara dimensiune )
	cout << endl << "Numele este: " << nume; //a continuat afisarea pana ce a dat de \0 a vectorului prenume

	//Siruri Dinamice
	char* adresa;

	//Initializare siruri dinamice
		//alocare spatiu + copiere adresa
	adresa = new char[strlen("Calea Dorobanti") + 1]; //aloc inca un spatiu pentru \0
	strcpy_s(adresa, strlen("Calea Dorobanti") + 1, "Calea Dorobanti");
	cout << endl << "Adresa este: " << adresa;

	//evitam memory leak prin eliberarea spatiului alocat anterior
	delete[] adresa;
	adresa = new char[strlen("Calea Victoriei") + 1];
	strcpy_s(adresa, strlen("Calea Victoriei") + 1, "Calea Victoriei");
	cout << endl << "Adresa este: " << adresa;

	delete[] adresa;

	return 0;
}