#include <iostream>
using namespace std;

// POINTERS RECAP

// Conventii:
// variabile -> lower camel case notation
// classes -> camel case notation

void afisareValori(int valoare1, int valoare2)
{
    cout << "Valoare 1: " << valoare1 << endl
         << " valaore 2: " << valoare2 << endl;
}

//nu face interschimbarea in main, deoarece sunt alte zone de memorie
//gestionam prin adrese => pointers
void interschimbare(int valoare1, int valoare2)
{
    int temp = valoare1;
    valoare1 = valoare2;
    valoare2 = temp;
}

//se pot pune pointers doar in paramaetrii
void interschimbare2(int* pv1, int* pv2) //primesc adresa de memorie
{   
    //cu * accesez valoarea de la adresa
    int temp = *pv1; 
    *pv1 = *pv2;
    *pv2 = temp;
}


int main()
{

    int nrStudenti = 0; // lower camel case notation

    // Pointers -> pointer = left value => scriu & pointer = right value => citesc
    // Definire pointeri
    int *pointerNrStudenti = nullptr; // pointerul este o variabile numerica
                                      // pointerul stocheaza numere ce sunt adrese de memorie
    nrStudenti = 1000;
    // pointerNrStudenti = 1000; ->eroare de compilare
    // pointerNrStudenti = (int*)1000; -> ajung la adresa 1000 si pot citi RAM - ul de la adresa 1000

    pointerNrStudenti = &nrStudenti; // pointerNrStudenti primeste adresa de memorie a variabilei nrStudenti
    // citire valoare de la o anumita adresa
    cout << "\n Valoare primita de la adresa 1000: " << *pointerNrStudenti << endl;

    // scriem/modificam valoare la o anumita adresa
    *pointerNrStudenti = 3000;
    cout << "Noua valuare prin pointer: " << nrStudenti << endl;

    // de ce avem nevoie de pointeri?
    //  1. gestionarea spatiului in HEAP

    int *valori = new int[10]; // alocare dinamica de memorie
    int *valoare = new int;    // alocare dinamica de memorie

    // stergere spatiu alocat

    delete[] valori; // am alocat un vector de intregi, sterg un vector de intregi
    delete valoare;  // am alocat un intreg, sterg un intreg

    // initializam pointerii cu nullptr

    valori = nullptr;
    valoare = nullptr;

    // 2. functii care modifica mai multe valori

    int valoare1 = 10;
    int valoare2 = 20;

    cout << "Valoare 1: " << valoare1 << endl
         << " Valoare 2: " << valoare2 << endl;

    interschimbare(valoare1, valoare2);
    afisareValori(valoare1, valoare2);

    interschimbare2(&valoare1, &valoare2); //la trasmiterea prin adresa, se trimite adresa cu &
    afisareValori(valoare1, valoare2);

    return 0;
}

//IMPORTANT: prin * accesez valoarea unui pointer si transmit adresa prin &
//           * -> valoare, & -> adresa
//          pui pointeri in functii cand vrei sa modifici mai multe valori la acele valori