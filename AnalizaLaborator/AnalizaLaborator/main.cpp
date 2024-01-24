#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Analiza {
private:
	string nume;

protected:
	int varsta;
	int* dataNasterii = nullptr; //DDMMYYYY => mereu 8 caractere
	int nrAnalizeEfectuate = 0;

public: 
	int cost;

	const static int NR_ANALIZE_GRATUITE = 10;

	void set_dataNasterii(int* newData) {
		if (newData != nullptr) {
			delete[] this->dataNasterii;
			this->dataNasterii = new int[8];
			for (int i = 0; i < 8; i++) {
				this->dataNasterii[i] = newData[i];
			}
		}
		else {
			cout << "Invalid newData" << endl;
		}
	}

	string get_nume() {
		return this->nume;
	}

	int get_analizeEfectuate() {
		return this->nrAnalizeEfectuate;
	}

	Analiza() {
		this->nume = "None";
		this->varsta = 0;
		this->cost = 0;
	}

	Analiza(string nume, int varsta, int* dataNasterii, int cost) {
		this->nume = nume;
		this->varsta = varsta;
		this->set_dataNasterii(dataNasterii);
		this->cost = cost;
	}

	Analiza(const Analiza& a) {
		this->nume = a.nume;
		this->varsta = a.varsta;
		this->cost = a.cost;
		this->set_dataNasterii(a.dataNasterii);
	}

	~Analiza() {
		delete[] this->dataNasterii;
	}

	friend ostream& operator<<(ostream& cons, Analiza& a);

	Analiza& operator=(Analiza& a) {
		if (this == &a) { return *this; }
		else {
			this->nume = a.nume;
			this->varsta = a.varsta;
			this->cost = a.cost;
			this->set_dataNasterii(a.dataNasterii);
			return *this;
		}
	}

	explicit operator float() {
		float varstaPrecisa = this->varsta;
		if (this->dataNasterii[2] == 0 && this->dataNasterii[3] < 7) {
			return varstaPrecisa;
		}
		else {
			return varstaPrecisa += 0.5;
		}
	}

	void operator++(int n) {
		this->cost += 1;
	}

	bool operator==(string nume) {
		return this->nume == nume;
	}

	void efectueazaAnaliza() {
		this->nrAnalizeEfectuate += 1;
	}

	bool analizePlatite(int nr) {
		return nr<this->NR_ANALIZE_GRATUITE;
	}

	void generareRaport(string nume_fis) {
		ofstream doc(nume_fis, ios::binary | ios::trunc);

		int numeLen = nume.length();
		doc.write((char*)&numeLen, sizeof(numeLen));
		doc.write(nume.c_str(), numeLen);

		doc.write((char*)&this->varsta, sizeof(int));

		if (this->dataNasterii != nullptr) {
			for (int i = 0; i < 8; i++) {
				doc.write((char*)&this->dataNasterii[i], sizeof(int));
			}
		}

		else {
			int data0 = 0;
			for (int i = 0; i < 8; i++) {
				doc.write((char*)&data0, sizeof(int));
			}
		}

		doc.write((char*)&this->nrAnalizeEfectuate, sizeof(int));
		doc.write((char*)&this->cost, sizeof(int));

		doc.close();
	}

	void citire_raport(string nume_fis) {
		ifstream doc(nume_fis, ios::binary);

		int numeLen = 0;
		doc.read((char*)&numeLen, sizeof(int));
		
		char* buffer = new char[numeLen + 1];
		doc.read(buffer, numeLen);
		buffer[numeLen] = '\0';

		string nume = string(buffer);
		delete[] buffer;

		int age = 0;
		doc.read((char*)&age, sizeof(age));

		int* data = new int[8];
		for (int i = 0; i < 8; i++) {
			doc.read((char*)&data[i], sizeof(int));
		}

		int nrAnalize = 0;
		doc.read((char*)&nrAnalize, sizeof(int));

		int costFis = 0;
		doc.read((char*)&costFis, sizeof(int));

		this->nume = nume;
		this->varsta = age;
		this->set_dataNasterii(data);
		this->nrAnalizeEfectuate = nrAnalize;
		this->cost = cost;
	}

	virtual int costConsultatie(int nrMin) {
		int price;
		price = nrMin * this->cost;
		return price;
	}
};

ostream& operator<<(ostream& cons, Analiza& a) {
	cons << "Nume: " << a.nume << endl;
	cons << "Varsta: " << a.varsta << endl;
	cons << "Data Nasterii: ";
	for (int i = 0; i < 8; i++) {
		cons << a.dataNasterii[i];
		if (i % 2 != 0 && i != 5) { cons << " "; }
	}
	cons << endl;
	cons << "Cost: " << a.cost << endl;
	return cons;
}

class AnalizeDiabet : public Analiza {
protected:
	int glicemia;
	string doctorSpecialist;

public:
	AnalizeDiabet(string nume, int varsta, int* dataNasterii, int cost, int glicemia, string numeDoc)
		: Analiza(nume, varsta, dataNasterii, cost + 10) {
		this->glicemia = glicemia;
		this->doctorSpecialist = numeDoc;
	}

	void efectueazaAnaliza() {
		this->nrAnalizeEfectuate += 2;
	}
};

template<typename T>class OperatiiMatematiceCu2Operatori {
public:
	string nume;
	T op1;
	T op2;

	OperatiiMatematiceCu2Operatori(string nume, T op1, T op2) {
		this->nume = nume;
		this->op1 = op1;
		this->op2 = op2;
	}

	T suma() {
		return this->op1 + this->op2;
	}
};




int main() {
	Analiza a1;

	int* data = new int[8] { 1, 2, 1, 0, 1, 9, 9, 9 };
	Analiza a2("Ionel", 30, data, 10);
	cout << "A2 cost: " << a2.cost << endl;

	Analiza a3 = a2;
	cout << "A3 cost: " << a3.cost << endl;

	Analiza* aHeap = new Analiza;
	delete aHeap;

	cout << endl << endl << "Operator << " << endl;
	cout << a2 << endl;

	cout << endl << endl << "Operator = " << endl;
	Analiza a4;
	a4 = a3;
	cout << a4 << endl;

	cout << endl << endl << "Operator cast " << endl;
	float varstaPrecisa = float(a4);
	cout << varstaPrecisa << endl;

	cout << endl << endl << "Operator ++" << endl;
	a4++;
	cout << a4 << endl;

	cout << endl << endl << "Operator =" << endl;
	if (a4 == "Ionel") {
		cout << "Pacientul Ionel este inregistrat!" << endl;
	}

	a4.efectueazaAnaliza();
	cout << "A4 are " << a4.get_analizeEfectuate() << " analize efectuate" << endl;

	if (a4.analizePlatite(a4.get_analizeEfectuate())) {
		cout << "A4 mai are analize platite in abonament" << endl;
	}

	cout << endl << endl << "Sciere fisier binar" << endl;
	a4.generareRaport("RaportBin.bin");

	cout << endl << endl << "Citire fisier binar" << endl;
	a1.citire_raport("RaportBin.bin");
	cout << a1;

	AnalizeDiabet d1("Daniel", 45, data, 10, 300, "Ionescu");
	cout << "Cost analiza diabet (10+10): " << d1.cost << endl;

	cout << "A3: " << endl;
	cout << "\t" << "Cost: " << a3.cost << endl;
	cout << "\t" << "Cost consultatie 60 min: " << a3.costConsultatie(60) << endl;

	cout << "D1: " << endl;
	cout << "\t" << "Cost: " << d1.cost << endl;
	cout << "\t" << "Cost consultatie 60 min: " << d1.costConsultatie(60) << endl;

	cout << endl << endl;
	cout << "A4 are " << a4.get_analizeEfectuate() << " analize efectuate" << endl;

	d1.efectueazaAnaliza();
	cout << "D1 are " << d1.get_analizeEfectuate() << " analize efectuate" << endl;


	cout << endl << endl << "Vector si virtualizare: " << endl;
	Analiza* vector[3] { &a3, &a4, &d1 };
	for (int i = 0; i < 3; i++) {
		cout << "\tAnaliza " << i << " are un cost total per 60 de min de: " << vector[i]->costConsultatie(60) << 
			" (cost de: " << vector[i]->cost << ")" << endl;
	}

	cout << endl << endl << "STL-uri: " << endl;
	OperatiiMatematiceCu2Operatori<int> ad("adunare", 1, 2);
	cout << "Adunare int: " << ad.suma() << endl;

	OperatiiMatematiceCu2Operatori<string> adstr("adunare", "1", "2");
	cout << "Adunare string: " << adstr.suma() << endl;

	cout << endl << endl;

	return 0;
}