#include <iostream>
using namespace std;

class Motor {
public:
	const int serieMotor;
	int putere = -1;
	int nrKm = -1 ;

	Motor() : serieMotor(213) {};

	Motor(int id, int putere, int km) : serieMotor(id), putere(putere), nrKm(km) {}

	friend ostream& operator<<(ostream& cons, const Motor& m);

	virtual void afisare() {
		cout << endl << "Serie Motor: " << this->serieMotor << endl;
		cout << "Putere: " << this->putere << endl;
		cout << "Nr Km: " << this->nrKm << endl;
	}

	virtual void operator+=(int km) {
		this->nrKm += km;
	}
};

ostream& operator<<(ostream& cons, const Motor& m) {
	cons << endl << "Serie Motor: " << m.serieMotor << endl;
	cons << "Putere: " << m.putere << endl;
	cons << "Nr Km: " << m.nrKm << endl;
	return cons;
}

class MotorBenzina;

class MotorElectric : virtual public Motor {
public:
	int consumElectric = -1;
	int nivelBaterie = 0;

	MotorElectric() {}
	
	MotorElectric(int id, int putere, int km, int consum, int nivel) 
		: Motor(id, putere, km), consumElectric(consum), nivelBaterie(nivel) {}

	friend ostream& operator<<(ostream& cons, const MotorElectric& me);

	void afisare() override {
		Motor::afisare();
		cout << "Consum Electric: " << this->consumElectric << endl;
	}

	bool verifica() {
		return this->nivelBaterie < 10;
	}

	MotorBenzina toTermic();

	void operator+=(int km) override {
		this->nrKm += km;
		if (this->consumElectric * km > this->nivelBaterie) {
			cout << "NU ai baterie, Dorele!!!" << endl;
		}
	}
};

ostream& operator<<(ostream& cons, const MotorElectric& me) {
	cons << Motor(me);
	cons << "Consum Electric: " << me.consumElectric << endl;
	return cons;
}

class MotorBenzina : virtual public Motor {
public:
	int consumBenzina = -1;
	int lBenzina = 0;

	MotorBenzina() {}

	MotorBenzina(int id, int putere, int km, int consum, int nivel)
		: Motor(id, putere, km), consumBenzina(consum), lBenzina(nivel) {}

	friend ostream& operator<<(ostream& cons, const MotorBenzina& mb);

	void afisare() override {
		Motor::afisare();
		cout << "Consum Benzina: " << this->consumBenzina << endl;
	}

	bool verifica() {
		return this->lBenzina < 10;
	}

	void operator+=(int km) override {
		this->nrKm += km;
		if (this->consumBenzina * km > this->lBenzina) {
			cout << "NU ai benzina, Dorele!!!" << endl;
		}
	}
};

ostream& operator<<(ostream& cons, const MotorBenzina& mb) {
	cons << Motor(mb);
	cons << "Consum Benzina: " << mb.consumBenzina << endl;
	return cons;
}

class MotorHibrid : public MotorBenzina, public MotorElectric {
public:
	int consumMediu = -1;

	void afisare()  {
		Motor::afisare();
		cout << "Consum Mediu Hibrid: " << this->consumMediu << endl;
	}

	void operator+=(int km) override {
		this->nrKm += km;
		if (this->consumBenzina * km > this->lBenzina && this->consumElectric * km > this->nivelBaterie) {
			cout << "Nu mai ai nimic, Dorele!!! Pe aer mergi!" << endl;
		}
	}
};

MotorBenzina MotorElectric::toTermic() {
	MotorBenzina mb_e(this->serieMotor, this->putere, this->nrKm, 5, 0);
	return mb_e;
}

int main() {
	Motor m1;

	MotorElectric me1;

	MotorBenzina mb1;

	cout << "Afisare prin operatorul << " << endl;
	cout << endl << "**********************************" << endl;
	cout << m1;
	cout << endl << "**********************************" << endl;
	cout << me1;
	cout << endl << "**********************************" << endl;
	cout << mb1;
	cout << endl << "**********************************" << endl;

	cout << endl << "----------------------------------" << endl;
	cout << "Afisare prin functie" << endl;
	cout << "----------------------------------" << endl;
	m1.afisare();
	cout << endl << "**********************************" << endl;
	me1.afisare();
	cout << endl << "**********************************" << endl;
	mb1.afisare();

	MotorHibrid mh1;
	cout << "Motor Hibrid serie motor: " << mh1.serieMotor << endl;

	cout << endl << endl << "----------------------------------" << endl << endl;

	Motor m2(100, 90, 15000);
	MotorElectric me2(101, 102, 17, 30, 5);
	MotorBenzina mb2(102, 95, 12021, 8, 3);
	cout << endl << "**********************************" << endl;
	cout << m2;
	cout << endl << "**********************************" << endl;
	cout << me2;
	cout << endl << "**********************************" << endl;
	cout << mb2;
	cout << endl << "**********************************" << endl;

	if (me2.verifica()) {
		cout << "Incarcaaa!!!" << endl;
	}

	if (mb2.verifica()) {
		cout << endl << "Alimeanteaazaaaa!!!" << endl;
	}

	MotorBenzina mb2_e = me2.toTermic();
	cout << mb2_e << endl;

	cout << "M2 km: " << m2.nrKm << endl;
	m2 += 1000;
	cout << "M2 km acum: " << m2.nrKm << endl;
	cout << endl;
	cout << "Me2 km: " << me2.nrKm << endl;
	me2 += 1000;
	cout << "Me2 km acum: " << me2.nrKm << endl;
	cout << endl;
	cout << "Mb2 km: " << mb2.nrKm << endl;
	mb2 += 1000;
	cout << "Mb2 km acum: " << mb2.nrKm << endl;

	char* dim = new char[6] {'1', '2', 'x', '2', '1'};
	for (int i = 0; i < 6; i++) {
		cout << dim[i];
		if (dim[i] == '\0') {
			cout << endl << "Este 0";
		}
	}

	cout << endl;

	char* dim2 = new char[strlen(dim) + 1];
	strcpy_s(dim2, strlen(dim) + 1, dim);
	for (int i = 0; i < 6; i++) {
		cout << dim2[i];
		if (dim2[i] == '\0') {
			cout << endl << "Este 0";
		}
	}

	cout << endl;

	delete[] dim;
	dim = new char[6];
	strcpy_s(dim, strlen(dim2) + 1, dim2);
	for (int i = 0; i < 6; i++) {
		cout << dim[i];
		if (dim[i] == '\0') {
			cout << endl << "Este 0";
		}
	}

	return 0;
}