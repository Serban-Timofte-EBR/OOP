#include <iostream>
#include <string>
using namespace std;

class Medic {
	const int codParafa;
	char* nume;
	char specializare[20];
	int tarifConsulatatie;

public:

	static int NR_DOC;

	Medic() :codParafa(0) {
		this->nume = new char[sizeof("Anonim") + 1];
		strcpy_s(this->nume, sizeof("Anonim") + 1, "Anonim");
		strcpy_s(this->specializare, sizeof("generala") + 1, "generala");
		this->tarifConsulatatie = 0;
	}

	Medic(int cod, string nume, string sectie, int tarif) : codParafa(cod) {
		this->nume = new char[nume.length() + 1];
		strcpy_s(this->nume, nume.length() + 1, nume.c_str());
		strcpy_s(this->specializare, sectie.length() + 1, sectie.c_str());
		this->tarifConsulatatie = tarif;
	}

	Medic(const Medic& med) : codParafa(med.codParafa) {
		this->nume = new char[strlen(med.nume) + 1];
		strcpy_s(this->nume, strlen(med.nume) + 1, med.nume);
		strcpy_s(this->specializare, strlen(med.specializare) + 1, med.specializare);
		this->tarifConsulatatie = med.tarifConsulatatie;
	}

	Medic& operator=(Medic& med) {
		if (this == &med) { return *this; }
		else {
			delete[] this->nume;
			this->nume = new char[strlen(med.nume) + 1];
			strcpy_s(this->nume, strlen(med.nume) + 1, med.nume);
			strcpy_s(this->specializare, strlen(med.specializare) + 1, med.specializare);
			this->tarifConsulatatie = med.tarifConsulatatie;
			return *this;
		}
	}

	~Medic() {
		delete[] this->nume;
	}


	friend istream& operator>>(istream& cons, Medic& med);
	friend ostream& operator<<(ostream& cons, Medic& med);

	void setSpecializare(string spec) {
		if (spec.length() < 2) {
			cout << "Invalid input!" << endl;
			return;
		}
		else {
			strcpy_s(this->specializare, spec.length() + 1, spec.c_str());
		}
	}

	int get_tarif() { return this->tarifConsulatatie; }

	int get_parafa() { return this->codParafa; }
};

istream& operator>>(istream& cons, Medic& med) {
	cout << "Introdu numele: ";
	string nume;
	getline(cons, nume);
	cout << endl;

	cout << "Introdu specializarea: ";
	string spec;
	getline(cons, spec);
	cout << endl;

	cout << "Introdu tariful: ";
	int tarif;
	cons >> tarif;
	cout << endl;

	delete[] med.nume;
	med.nume = new char[nume.length() + 1];
	strcpy_s(med.nume, nume.length() + 1, nume.c_str());
	strcpy_s(med.specializare, spec.length() + 1, spec.c_str());
	med.tarifConsulatatie = tarif;

	return cons;
}

ostream& operator<<(ostream& cons, Medic& med) {
	cons << endl;
	cons << med.codParafa << endl;
	cons << med.nume << endl;
	cons << med.specializare << endl;
	cons << med.tarifConsulatatie << endl;
	cons << endl;
	return cons;
}

int Medic::NR_DOC = 0;

class Spital {
	Medic* medici;
	int nrMedici;
	char* denumire;
	char tip;

public: 

	static int nrSpitalePublice;
	static int nrSpitalePrivate;

	Spital() {
		this->medici = nullptr;
		this->nrMedici = 0;
		this->denumire = nullptr;
		this->tip = 'N';
	}

	Spital(Medic* lista, int nrMed, string den, char sp) {
		this->tip = sp;
		if (this->tip == 'P') { this->nrSpitalePrivate += 1; }
		else if (this->tip == 'S') { this->nrSpitalePublice += 1; }
		this->denumire = new char[den.length() + 1];
		strcpy_s(this->denumire, den.length() + 1, den.c_str());

		this->medici = new Medic[nrMed];
		for (int i = 0; i < nrMed; i++) {
			this->medici[i] = lista[i];
		}
		this->nrMedici = nrMed;
	}

	Spital(const Spital& spit) {
		this->tip = spit.tip;
		if (this->tip == 'P') { this->nrSpitalePrivate += 1; }
		else if (this->tip == 'S') { this->nrSpitalePublice += 1; }
		this->denumire = new char[strlen(spit.denumire) + 1];
		strcpy_s(this->denumire, strlen(spit.denumire) + 1, spit.denumire);
		this->medici = new Medic[spit.nrMedici];
		for (int i = 0; i < spit.nrMedici; i++) {
			this->medici[i] = spit.medici[i];
		}
		this->nrMedici = spit.nrMedici;
	}

	Spital& operator=(const Spital& spit) {
		if (this == &spit) { return *this; }
		else {
			delete[] this->denumire;
			this->denumire = new char[spit.nrMedici];
			strcpy_s(this->denumire, strlen(spit.denumire) + 1, spit.denumire);
			this->tip = spit.tip;
			if (this->tip == 'P') { this->nrSpitalePrivate += 1; }
			else if (this->tip == 'S') { this->nrSpitalePublice += 1; }
			delete[] this->medici;
			this->medici = new Medic[spit.nrMedici];
			for (int i = 0; i < spit.nrMedici; i++) {
				this->medici[i] = spit.medici[i];
			}
			this->nrMedici = spit.nrMedici;
		}
	}

	Spital& operator+=(Medic& m) {
		Medic* medTemp = new Medic[this->nrMedici + 1];
		for (int i = 0; i < this->nrMedici; i++) {
			medTemp[i] = this->medici[i];
		}
		medTemp[this->nrMedici] = m;

		delete[] this->medici;
		this->medici = medTemp;
		this->nrMedici += 1;
		return *this;
	}

	friend ostream& operator<<(ostream& cons, const Spital& s);

	void setTip(char tip) {
		if (tip == 'S' || tip == 's' || tip == 'P' || tip == 'p') {
			this->tip = tip;
		}
		else {
			return;
		}
	}

	bool operator>(const Spital& s) {
		if (this->nrMedici > s.nrMedici) {
			return true;
		}
		else {
			return false;
		}
	}
	
	bool operator<(const Spital& s) {
		if (this->nrMedici < s.nrMedici) {
			return true;
		}
		else {
			return false;
		}
	}

	bool operator==(const Spital& s) {
		if (this->nrMedici == s.nrMedici) {
			return true;
		}
		else {
			return false;
		}
	}

	explicit operator double() {
		double tarifMed = 0.0;
		for (int i = 0; i < this->nrMedici; i++) {
			tarifMed += this->medici[i].get_tarif();
		}

		tarifMed = tarifMed / this->nrMedici;
		return tarifMed;
	}

	Spital& operator-=(Medic m) {
		for (int i = 0; i < this->nrMedici; i++) {
			if (this->medici[i].get_parafa() == m.get_parafa()) {
				for (int j = i; j < this->nrMedici - 1; j++) {
					this->medici[j] = this->medici[j + 1];
				}
				this->nrMedici--;
				break;
				cout << "**** Medic Deleted! ****" << endl;
			}
		}
		return *this;
	}
};

int Spital::nrSpitalePrivate = 0;
int Spital::nrSpitalePublice = 0;

ostream& operator<<(ostream& cons, const Spital& s) {
	cons << "______________________" << endl;
	cons << "Denumire: " << s.denumire << endl;
	cons << "Tip: " << s.tip << endl;
	cons << "Nr medici: " << s.nrMedici << endl;
	for (int i = 0; i < s.nrMedici; i++) {
		cons << s.medici[i];
		cons << endl;
	}
	return cons;
}

int main() {
	Medic m1;
	Medic m2(123, "Gh Marinescu", "medicina interna", 100);
	Medic m3 = m1;
	Medic m4;
	cin >> m4;
	m1 = m4;
	cout << m1 << m2 << m3 << m4;
	cout << endl;

	Medic vect[4] = { m1, m2, m3, m4 };
	Spital s1;
	Spital s2(vect, 4, "Clinic de urgenta", 'S');
	Spital s3 = s2;
	s1 = s3;
	Medic m5(456, "Costel Popescu", "oftalmologie", 150);
	s1 += m5;
	cout << "**************************" << endl;
	cout << s1 << s2 << s3;
	cout << endl;

	m5.setSpecializare("medicina de familie");
	cout << endl << endl << "SetSpecializare" << endl;
	cout << m5;
	cout << endl;

	s1.setTip('S');
	cout << endl << endl << "ChangeTip" << endl;
	cout << s1;
	cout << endl;

	cout << "Sunt " << Spital::nrSpitalePrivate << " private" << endl;
	cout << "Sunt " << Spital::nrSpitalePublice << " publice" << endl;

	if (s1 > s3) {
		cout << "S1 are mai multi medici ca s3" << endl;
	}
	else if (s1 < s3) {
		cout << "Ramura 2" << endl;
	}
	else if (s1 == s3) {
		cout << "Ramura 3" << endl;
	}

	cout << s3 << endl;
	cout << "Tarif mediu: " << (double)s2 << endl;

	s3 -= m2;
	cout << s3;
	
	return 0;
}