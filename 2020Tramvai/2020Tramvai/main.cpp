#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

class Tramvai {
protected:
	const int nrTramvai;
	string numeVatman;
	int numarStatii;
	int* minuteStatie;

public:

	int get_id() { return this->nrTramvai; }

	string get_numeVatmant() { return this->numeVatman; }

	int* get_minStatii() {
		int* copy = new int[this->numarStatii];
		for (int i = 0; i < this->numarStatii; i++) {
			copy[i] = this->minuteStatie[i];
		}
		return copy;
	}

	int get_nrStatii() { return this->numarStatii; }

	void set_numeVatman(string nume) {
		if (nume != "" || nume != " ") {
			this->numeVatman = nume;
		}
		else {
			return;
		}
	}

	void set_minStatie(int* lista, int nr) {
		delete[] this->minuteStatie;
		this->minuteStatie = new int[nr];
		for (int i = 0; i < nr; i++) {
			this->minuteStatie[i] = lista[i];
		}
		this->numarStatii = nr;
	}

	Tramvai() : nrTramvai(-1) {
		this->numeVatman = "";
		this->numarStatii = 0;
		this->minuteStatie = nullptr;
	}

	Tramvai(int nrTramvai, string numeVatman) : nrTramvai(nrTramvai) {
		this->set_numeVatman(numeVatman);
		this->numarStatii = 0;
		this->minuteStatie = nullptr;
	}

	Tramvai(const Tramvai& tram) : nrTramvai(tram.nrTramvai) {
		this->set_numeVatman(tram.numeVatman);
		this->set_minStatie(tram.minuteStatie, tram.numarStatii);
	}

	~Tramvai() {
		delete[] this->minuteStatie;
	}

	Tramvai& operator=(Tramvai& tramv) {
		if (this == &tramv) {
			return *this;
		}
		else {
			this->set_numeVatman(tramv.numeVatman);
			this->set_minStatie(tramv.minuteStatie, tramv.numarStatii);
			return *this;
		}
	}

	int calculMinuteStationate(int indexStatieStart, int indexStatieEnd) {
		int nrMin = 0;
		for (int i = indexStatieStart; i < indexStatieEnd; i++) {
			nrMin += this->minuteStatie[i];
		}
		return nrMin;
	}

	virtual int totalMinuteStationate() {
		int totalMin = 0;
		for (int i = 0; i < this->numarStatii; i++) {
			totalMin += this->minuteStatie[i];
		}
		return totalMin;
	}

	void adaugaStatie(int nrMinute) {
		int* copy = new int[this->numarStatii + 1];
		for (int i = 0; i < this->numarStatii; i++) {
			copy[i] = this->minuteStatie[i];
		}
		copy[this->numarStatii] = nrMinute;

		delete[] this->minuteStatie;
		this->minuteStatie = copy;
		this->numarStatii += 1;
	}

	friend ostream& operator<<(ostream& cons, const Tramvai& tramv);

	int& operator[](int index) {
		if (index < 0 || index > this->numarStatii - 1) { throw exception("Invalid index!"); }
		else {
			return this->minuteStatie[index];
		}
	}

	void raport(string nume_fisier) {
		ofstream doc(nume_fisier, ios::trunc);
		doc << this->nrTramvai << endl;
		doc << this->numeVatman << endl;
		doc << this->numarStatii << endl;
		for (int i = 0; i < this->numarStatii; i++) {
			doc << this->minuteStatie[i] << endl;
		}
	}

	Tramvai decodeRaport(string nume_fisier) {
		ifstream doc(nume_fisier);
		int nrTramvai;
		doc >> nrTramvai;

		string numeVat;
		doc >> numeVat;

		int nrStatii;
		doc >> nrStatii;

		int* minList = new int[nrStatii];
		for (int i = 0; i < nrStatii; i++) {
			doc >> minList[i];
		}

		Tramvai ret(nrTramvai, numeVat);
		ret.set_minStatie(minList, nrStatii);

		delete[] minList;
		return ret;
	}
};

ostream& operator<<(ostream& cons, const Tramvai& tramv) {
	cons << "NrTramvai: " << tramv.nrTramvai << endl;
	cons << "Nume Vatman: " << tramv.numeVatman << endl;
	cons << "Nr statii: " << tramv.numarStatii << endl;
	cons << "Minute Statii: ";
	for (int i = 0; i < tramv.numarStatii; i++) {
		cons << tramv.minuteStatie[i] << " ";
	}
	cons << endl;
	return cons;
}

class TramvaiHibrid : public Tramvai {
	int capacitateBaterie;
	int timpIncarcare;

public:
	TramvaiHibrid(int nrTramvai, string numeVatman) 
		: Tramvai(nrTramvai, numeVatman) {
		this->timpIncarcare = 20;
	}

	TramvaiHibrid() : Tramvai() {
		this->timpIncarcare = 20;
	}

	~TramvaiHibrid() {
		capacitateBaterie = 0;
		timpIncarcare = 0;
	}

	TramvaiHibrid& operator=(const TramvaiHibrid& tramH) {
		if (this == &tramH) { return *this; }
		else {
			this->set_numeVatman(tramH.numeVatman);
			this->set_minStatie(tramH.minuteStatie, tramH.numarStatii);
			this->capacitateBaterie = tramH.capacitateBaterie;
			this->timpIncarcare = tramH.capacitateBaterie;
			return *this;
		}
	}

	friend ostream& operator<<(ostream& cons, const TramvaiHibrid& tramv);

	int totalMinuteStationate() {
		int totalMin = this->timpIncarcare;
		for (int i = 0; i < this->numarStatii; i++) {
			totalMin += this->minuteStatie[i];
		}
		return totalMin;
	}
};

ostream& operator<<(ostream& cons, const TramvaiHibrid& tramv) {
	cons << "NrTramvai: " << tramv.nrTramvai << endl;
	cons << "Nume Vatman: " << tramv.numeVatman << endl;
	cons << "Nr statii: " << tramv.numarStatii << endl;
	cons << "Minute Statii: ";
	for (int i = 0; i < tramv.numarStatii; i++) {
		cons << tramv.minuteStatie[i] << " ";
	}
	cons << endl;
	cons << "Capacitate baterie: " << tramv.capacitateBaterie << endl;
	cons << "Timp incarcare: " << tramv.timpIncarcare << endl;
	return cons;
}

int main() {
	Tramvai t1;
	cout << "T1 id: " << t1.get_id() << endl << endl;

	Tramvai t2(32, "Gigel");
	cout << "T2 id: " << t2.get_id() << endl;
	cout << "T2 nume vatman: " << t2.get_numeVatmant() << endl;

	cout << endl << "Set T2 mins"<<endl;
	int* listaMin = new int[3] {5, 2, 10};
	t2.set_minStatie(listaMin, 3);
	delete[] listaMin;

	int* gettedList = new int[3];
	gettedList = t2.get_minStatii();
	cout << "Lista min t2: ";
	for (int i = 0; i < t2.get_nrStatii(); i++) {
		cout << gettedList[i] << " ";
	}
	cout << endl;
	delete[] gettedList;

	cout << "Copy constr: " << endl;
	Tramvai t2_copy = t2;
	cout << "T2_copy nume vatman: " << t2_copy.get_numeVatmant() << endl;
	int* gettedList2 = new int[3];
	gettedList2 = t2_copy.get_minStatii();
	cout << "Lista min t2: ";
	for (int i = 0; i < t2_copy.get_nrStatii(); i++) {
		cout << gettedList2[i] << " ";
	}
	cout << endl;
	delete[] gettedList2;

	cout << "=: " << endl;
	Tramvai t3;
	t3 = t2;
	cout << "T3 nume vatman: " << t3.get_numeVatmant() << endl;

	cout << "Calc Min Statie: " << endl;
	cout << t3.calculMinuteStationate(0, 2) << endl;

	cout << "Total Min: " << endl;
	cout << t3.totalMinuteStationate() << endl;

	cout << "Adauga statie: " << endl;
	t2.adaugaStatie(4);
	int* gettedList3 = new int[3];
	gettedList3 = t2.get_minStatii();
	cout << "Lista min t2: ";
	for (int i = 0; i < t2.get_nrStatii(); i++) {
		cout << gettedList3[i] << " ";
	}
	cout << endl;
	delete[] gettedList3;

	cout << endl << "Opeartor <<: " << endl;
	cout << t2;

	cout << endl << "Opeartor []: " << endl;
	try {
		t2[0] = 10;
		cout << t2 << endl;

		t2[4] = 21;
	}
	catch (exception e) {
		cout << e.what();
	}

	t2.raport("Raport.txt");

	cout << endl << endl << "Deocode doc: " << endl;
	Tramvai t2Read = t2.decodeRaport("Raport.txt");
	cout << t2Read << endl;

	cout << endl << endl <<endl<<endl<< "Tramvai Hibrid: " << endl;
	cout << endl << "TH1: " << endl;
	TramvaiHibrid th1;
	cout << th1;

	cout << endl << "TH2: " << endl;
	TramvaiHibrid th2(1, "Ion");
	cout << th2 << endl;

	cout << "Operator = for TH:" << endl;
	th1 = th2;
	cout << th1;

	int* listaMin2 = new int[3] {5, 2, 10};
	t2.set_minStatie(listaMin2, 3);
	th2.set_minStatie(listaMin2, 3);
	delete[] listaMin2;

	cout << "Virtual total min: " << endl;
	cout << "T2 total min: " << t2.totalMinuteStationate() << endl;
	cout << "TH2 total min: " << th2.totalMinuteStationate() << endl;

	cout << endl << endl << endl << endl << "Vector ex 8: " << endl;
	int maxTramv = 5;
	Tramvai** tramvaie = new Tramvai * [maxTramv];
	tramvaie[0] = &t2;
	tramvaie[1] = &t2;
	tramvaie[2] = &t2;
	tramvaie[3] = &th2;
	tramvaie[4] = &th2;

	int totalMin = 0;
	for (int i = 0; i < maxTramv; i++) {
		totalMin += tramvaie[i]->totalMinuteStationate();
		cout << "Mins added: " << tramvaie[i]->totalMinuteStationate() << endl;
	}

	cout << "Total Minute Stationate: " << totalMin << endl;

	delete[] tramvaie;

	vector<Tramvai*> tramvaieSTL;
	tramvaieSTL.push_back(&t2);
	tramvaieSTL.push_back(&th2);

	sort(tramvaieSTL.begin(), tramvaieSTL.end(), [](Tramvai* a, Tramvai* b) {
		return a->totalMinuteStationate() < b->totalMinuteStationate();
		});
	
	cout << endl << endl;
	for (int i = 0; i < 2; i++) {
		cout << *tramvaieSTL[i];
		cout << endl << endl;
	}

	return 0;
}