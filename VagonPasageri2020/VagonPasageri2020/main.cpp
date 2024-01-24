#include <iostream>
#include <string>
#include <fstream>
using namespace std;

enum class TipVagon {ClasaI, ClasaII, Cuseta};

class VagonPasageri {
private:
	string codVagon;
	TipVagon tip;
	int nrLocuri;
	int* locuriOcupate;; // elementul este 0 => loc liber
	bool esteOcupat; // vagon full ocupat

	static int NR_MAXIM_LOCURI;

public:

	string get_codVagon() { return this->codVagon; }

	int* get_locuriOcupate() {
		int* copy = new int[this->nrLocuri];
		for (int i = 0; i < this->nrLocuri; i++) {
			copy[i] = this->locuriOcupate[i];
		}
		return copy;
	}

	int get_nrLocuri() { return this->nrLocuri; }

	void set_codVagon(string cod) {
		if (cod == "") { cout << "Invalid cod!" << endl; }
		else {
			this->codVagon = cod;
		}
	}

	void set_locuri(int* locuri, int nrLocuriNou) {
		if (nrLocuriNou < 0 || nrLocuriNou > this->NR_MAXIM_LOCURI) {
			cout << "Invalid nrLocuriNou!" << endl;
		}
		else {
			delete[] this->locuriOcupate;
			this->locuriOcupate = new int[nrLocuriNou];
			for (int i = 0; i < nrLocuriNou; i++) {
				this->locuriOcupate[i] = locuri[i];
			}
			this->nrLocuri = nrLocuriNou;
		}
	}

	TipVagon get_tip() { return this->tip; }

	VagonPasageri() {
		this->codVagon = "";
		this->tip = TipVagon::ClasaII;
		this->nrLocuri = 0;
		this->locuriOcupate = nullptr;
		this->esteOcupat = false;
	}

	VagonPasageri(string codVagon, TipVagon tip, int nrLocuri, int* locuriOcupate) {
		this->set_codVagon(codVagon);
		this->tip = tip;
		this->set_locuri(locuriOcupate, nrLocuri);
	}

	VagonPasageri(const VagonPasageri& vag) {
		this->codVagon = vag.codVagon + "_duplicat";
		this->tip = vag.tip;
		this->set_locuri(vag.locuriOcupate, vag.nrLocuri);
		this->esteOcupat = vag.esteOcupat;
	}

	~VagonPasageri() {
		delete[] this->locuriOcupate;
	}

	void operator=(const VagonPasageri& vag) {
		this->codVagon = vag.codVagon;
		this->tip = vag.tip;
		this->set_locuri(vag.locuriOcupate, vag.nrLocuri);
		this->esteOcupat = vag.esteOcupat;
	}
	friend ostream& operator<<(ostream& cons, const VagonPasageri& vag);

	explicit operator float() {
		int nrLocuriOcupate = 0;
		for (int i = 0; i < this->nrLocuri; i++) {
			if (this->locuriOcupate[i] == 1) { nrLocuriOcupate += 1; }
		}
		float gradOcupare = float(nrLocuriOcupate) / float(this->nrLocuri);
		return gradOcupare;
	}

	bool esteOcupatVagonul() {
		if (this->nrLocuri >= this->nrLocuri) {
			this->esteOcupat = true;
		}
		else {
			this->esteOcupat = false;
		}
		return this->esteOcupat;
	}

	bool operator[](int index) {
		if (index < 1 || index > this->nrLocuri) {
			cout << "Invalid index!" << endl;
		}
		
		if (this->locuriOcupate[index - 1] == 0) {
			return true;
		}
		else { return false; }
	}

	void raport() {
		ofstream doc("RaportVagon.txt", ios::app);
		doc << this->codVagon << endl;
		for (int i = 0; i < this->nrLocuri; i++) {
			if (this->locuriOcupate[i] == 1) { doc << i << " "; }
		}
		doc << endl;
		for (int i = 0; i < this->nrLocuri; i++) {
			if (this->locuriOcupate[i] == 0) { doc << i << " "; }
		}
		doc << endl;
	}
};

int VagonPasageri::NR_MAXIM_LOCURI = 250;

ostream& operator<<(ostream& cons, const VagonPasageri& vag) {
	cons << "Cod vagon: " << vag.codVagon << endl;
	cons << "Tip: ";
	if (vag.tip == TipVagon::ClasaI) { cout << "ClasaI" << endl; }
	else if (vag.tip == TipVagon::ClasaII) { cout << "ClasaII" << endl; }
	else if (vag.tip == TipVagon::Cuseta) { cout << "Cuseta" << endl; }
	cons << "Nr Locuri: " << vag.nrLocuri << endl;  
	cons << "Harta Locurilor: ";
	for (int i = 0; i < vag.nrLocuri; i++) {
		cons << vag.locuriOcupate[i] << " ";
	}
	cons << endl;
	cons << "Este ocupat: " << vag.esteOcupat << endl;
	return cons;
}

class GarnituraTren {
private:
	string numeTren;
	int nrVagoane;
	VagonPasageri* vagoane;
public:

	string get_numeTren() { return this->numeTren; }

	int get_nrVagoane() { return this->nrVagoane; }

	void set_vagoane(VagonPasageri* vags, int nrVagoaneNou) {
		if (vags == nullptr) { cout << "Invalid" << endl; return; }
		else {
			VagonPasageri* newVags = new VagonPasageri[nrVagoaneNou];
			for (int i = 0; i < nrVagoaneNou; i++) {
				newVags[i] = vags[i];
			}

			delete[] this->vagoane;
			this->vagoane = newVags;
			this->nrVagoane = nrVagoaneNou;
		}
	}

	GarnituraTren() {
		this->numeTren = "";
		this->nrVagoane = 0;
		this->vagoane = nullptr;
	}

	GarnituraTren(string numeTren, int nrVagoane, VagonPasageri* vags) {
		this->numeTren = numeTren;
		this->set_vagoane(vags, nrVagoane);
	}

	GarnituraTren(const GarnituraTren& gar) {
		this->numeTren = gar.numeTren;
		this->set_vagoane(gar.vagoane, gar.nrVagoane);
	}

	~GarnituraTren() {
		delete[] this->vagoane;
	}

	void operator=(const GarnituraTren& gar) {
		this->numeTren = gar.numeTren;
		this->set_vagoane(gar.vagoane, gar.nrVagoane);
	}

	GarnituraTren operator+=(const VagonPasageri& vag) {
		VagonPasageri* safeCopy = new VagonPasageri[this->nrVagoane + 1];
		for (int i = 0; i < this->nrVagoane; i++) {
			safeCopy[i] = this->vagoane[i];
		}
		safeCopy[this->nrVagoane] = vag;
		this->set_vagoane(safeCopy, this->nrVagoane + 1);
		delete[] safeCopy;
		return *this;
	}

	float totalIncasari(float pretBazaBilet) {
		float revenue =0.0;
		for (int i = 0; i < this->nrVagoane; i++) {
			float pretCL2 = pretBazaBilet;
			float pretCL1 = pretBazaBilet + 0.5 * pretBazaBilet;
			float pretCUS = pretBazaBilet * 2;
			if (this->vagoane[i].get_tip() == TipVagon::ClasaII) {
				int dim = this->vagoane[i].get_nrLocuri();
				int* listaVag = new int[dim];
				listaVag = this->vagoane[i].get_locuriOcupate();
				for (int j = 0; j < this->vagoane[i].get_nrLocuri(); j++) {
					if (listaVag[j] == 1) {
						revenue += pretCL2;
					}
				}
				delete[] listaVag;
			}
			else if (this->vagoane[i].get_tip() == TipVagon::ClasaI) {
				int dim = this->vagoane[i].get_nrLocuri();
				int* listaVag = new int[dim];
				listaVag = this->vagoane[i].get_locuriOcupate();
				for (int j = 0; j < this->vagoane[i].get_nrLocuri(); j++) {
					if (listaVag[j] == 1) {
						revenue += pretCL1;
					}
				}
				delete[] listaVag;
			}
			else if (this->vagoane[i].get_tip() == TipVagon::Cuseta) {
				int dim = this->vagoane[i].get_nrLocuri();
				int* listaVag = new int[dim];
				listaVag = this->vagoane[i].get_locuriOcupate();
				for (int j = 0; j < this->vagoane[i].get_nrLocuri(); j++) {
					if (listaVag[j] == 1) {
						revenue += pretCUS;
					}
				}
				delete[] listaVag;
			}
		}
		return revenue;
	}
};

int main() {
	VagonPasageri v1;

	int* locuri = new int[3] {0, 1, 1};
	VagonPasageri v2("BF", TipVagon::ClasaI, 3, locuri);
	cout << "V2 cod: " << v2.get_codVagon() << endl;

	VagonPasageri v2_duplicat = v2;
	cout << "V2 duplicat cod: " << v2_duplicat.get_codVagon() << endl;

	cout << endl << "Operator = ofr class 1" << endl;
	v1 = v2;
	cout << v1;

	cout << endl << endl << "Operator <<: " << endl;
	cout << v2;

	cout << endl << "Operator cast explicit: " << endl;
	float gradOcupare = float(v2);
	cout << "Gradul de ocupare este: " << gradOcupare << endl;

	cout << "Este ocupat vagonul V2? " << v2.esteOcupatVagonul() << endl;

	cout << "Verificare loc: " << endl;
	bool vfLoc = v2[2];
	cout << "Locul v2[1] este: " << bool(vfLoc) << endl;

	//v2.raport();

	cout << endl << endl << "GarnituraTren: " << endl;
	VagonPasageri* vags = new VagonPasageri[3];
	vags[0] = v1;
	vags[1] = v2;
	vags[2] = v2_duplicat;
	GarnituraTren tren1("Tren1", 3, vags);
	cout << "Nume tren 1: " << tren1.get_numeTren() <<endl;

	cout << "Garnitura copy constructor" << endl;
	GarnituraTren tren2 = tren1;
	cout << "Nume tren 2: " << tren2.get_numeTren() << endl;

	cout << "Garnitura operator =: " << endl;
	GarnituraTren trenEGL;
	trenEGL = tren1;
	cout << "Nume trenEGL: " << trenEGL.get_numeTren() << endl;

	cout << endl << "Garnitura operator +=: " << endl;
	cout << "Tren 1 are initial: " << tren1.get_nrVagoane() << " vagoane!" << endl;
	tren1 += v1;
	cout << "Tren 1 are ACUM: " << tren1.get_nrVagoane() << " vagoane!" << endl;

	cout << "Total Incasari: " << tren1.totalIncasari(12.3) << endl;

	return 0;
}