#include <iostream>
using namespace std;

#define GRAVITY 9.8; //directiva de recompilare
const float pi = 3.14; //constanta

int main() {

    int a = 5;

    int* p = nullptr;

    p = &a;

    cout << p << endl;
    cout << *p << endl;

    p++;

    cout << p << endl;

    int* q = p;

    q = p + 12;
    cout << q << endl;

    q = p - 3;
    cout << q << endl; 

    cout << p - q << endl;

    const int* w = &a;
    // *w = 7; -> eroare
    int* z = (int*)w;
    *z = 7;

    int& r = a; //referinta -> salveaza adresa lui a, dar face automat defirentierea
    cout << r << endl;

    void* v = &a;
    cout << *(int*)v << endl; // fac cast pentru a sti tipul la care pointeaza

    return 0;
}