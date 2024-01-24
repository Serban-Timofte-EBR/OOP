#include <iostream>
#include <fstream>
using namespace std;

enum class TipFisier {PDF, JPEG, HFILE, CPPFILE};

class Tema {
private:
	string* cerinte = nullptr;
	int nrCerinte = 0;

protected:
	string termentLimita;
	int numarTema;

public:
	TipFisier tipFisier;
	int puncte;

	const static int NR_CERINTE_MAXIM = 14;

	void set_cerinte(string* enunt, int nrEnunts) {
		if(enunt != nullptr && nrEnunts > 0) {
			delete[] this->cerinte;
			this->cerinte = new string[nrEnunts];
			for (int i = 0; i < nrEnunts; i++) {
				this->cerinte[i] = enunt[i];
			}
			this->nrCerinte = nrEnunts;
		}
		else {
			throw exception("Invalid input for set_cerinte!");
		}
	}

	string* get_cerinte() {
		string* copy = new string[this->nrCerinte];
		for (int i = 0; i < this->nrCerinte; i++) {
			copy[i] = this->cerinte[i];
		}
		return copy;
	}

	int get_nrCerinte() {
		return this->nrCerinte;
	}

	Tema() {
		this->termentLimita = "Unknown";
		this->numarTema = 0;
		this->tipFisier = TipFisier::PDF;
		this->puncte = 0;
	}

	Tema(string* cerinte, int nrCerinte, string deadline, int nrTema, TipFisier fis, int pct) 
	: termentLimita(deadline), numarTema(nrTema), tipFisier(fis), puncte(pct) {
		this->set_cerinte(cerinte, nrCerinte);
	}

	Tema(const Tema& t) {
		this->set_cerinte(t.cerinte, t.nrCerinte);
		this->termentLimita = t.termentLimita;
		this->numarTema = t.numarTema;
		this->tipFisier = t.tipFisier;
		this->puncte = t.puncte;
	}

	Tema& operator=(const Tema& t) {
		if (this == &t) { return *this; }
		else {
			this->set_cerinte(t.cerinte, t.nrCerinte);
			this->termentLimita = t.termentLimita;
			this->numarTema = t.numarTema;
			this->tipFisier = t.tipFisier;
			this->puncte = t.puncte;
			return *this;
		}
	}

	~Tema() {
		delete[] this->cerinte;
	}

	Tema& operator+=(int val) {
		this->puncte += val;
		return *this;
	}

	void generare_raport(string nume_fis) {
		ofstream doc(nume_fis, ios::binary | ios::trunc);
		doc.write((char*)&this->nrCerinte, sizeof(int));
		for (int i = 0; i < this->nrCerinte; i++) {
			int lenCer = this->cerinte[i].length();
			doc.write((char*)&lenCer, sizeof(lenCer));
			doc.write(this->cerinte[i].c_str(), lenCer);
		}
		int lenTerm = this->termentLimita.length();
		doc.write((char*)&lenTerm, sizeof(lenTerm));
		doc.write(this->termentLimita.c_str(), lenTerm);

		doc.write((char*)&this->numarTema, sizeof(int));

		int tipFisInt = int(this->tipFisier);
		doc.write((char*)&tipFisier, sizeof(int));

		doc.write((char*)&this->puncte, sizeof(int));

		doc.close();
	}

	Tema& citire_raport(string nume_fis) {
		ifstream doc(nume_fis, ios::binary);

		int nrCerDoc = 0;
		doc.read((char*)&nrCerDoc, sizeof(int));

		string* cerDoc = new string[nrCerDoc];
		for (int i = 0; i < nrCerDoc; i++) {
			int lenCer = 0;
			doc.read((char*)&lenCer, sizeof(int));

			char* buffer = new char[lenCer + 1];
			doc.read(buffer, lenCer);
			buffer[lenCer] = '\0';
			cerDoc[i] = string(buffer);
			delete[] buffer;
		}

		this->set_cerinte(cerDoc, nrCerDoc);
		delete[] cerDoc;

		int lenTerm = 0;
		doc.read((char*)&lenTerm, sizeof(int));
		char* buffer2 = new char[lenTerm + 1];
		doc.read(buffer2, lenTerm);
		buffer2[lenTerm] = '\0';
		this->termentLimita = string(buffer2);

		int nrTemaDoc = 0;
		doc.read((char*)&nrTemaDoc, sizeof(int));
		this->numarTema = nrTemaDoc;

		int fisINTDoc = 0;
		doc.read((char*)&fisINTDoc, sizeof(int));
		this->tipFisier = TipFisier(fisINTDoc);

		int pctDoc = 0;
		doc.read((char*)&pctDoc, sizeof(int));
		this->puncte = pctDoc;

		doc.close();

		return *this;
	}
};

class MapaDeTemeSeminar {
public:
	Tema* temeSeminar = nullptr;
	int nrTeme = 0;

	void set_temeSeminar(Tema* temeList, int nr) {
		if (temeList == nullptr || nr <= 0) {
			throw exception("Invalid inputs for set_temeSemianr!");
		}
		else {
			delete[] this->temeSeminar;
			this->temeSeminar = new Tema[nr];
			for (int i = 0; i < nr; i++) {
				this->temeSeminar[i] = temeList[i];
			}
			this->nrTeme = nr;
		}
	}

	MapaDeTemeSeminar() {}

	MapaDeTemeSeminar(Tema* list, int nr) {
		this->set_temeSeminar(list, nr);
	}

	void operator+=(Tema& t) {
		Tema* copyTem = new Tema[this->nrTeme + 1];
		for (int i = 0; i < this->nrTeme; i++) {
			copyTem[i] = this->temeSeminar[i];
		}

		copyTem[this->nrTeme] = t;
		
		delete[] this->temeSeminar;
		this->temeSeminar = copyTem;
		this->nrTeme += 1;
		delete[] copyTem;
	}

};

int main() {
	Tema t1;
	cout << "T1 terment puncte: " << t1.puncte << endl;

	try {
		string* cerinteT2 = new string[3];
		cerinteT2[0] = "Scrie Hello World in C++";
		cerinteT2[1] = "Scrie Hello World in C#";
		cerinteT2[2] = "Scrie Hello World in Java";

		Tema t2(cerinteT2, 3, "21-02-2024", 1, TipFisier::HFILE, 10);
		cout << "T2 terment puncte: " << t2.puncte << endl;
		delete[] cerinteT2;

		cout << endl << "Creste punctajul t2 +=: " << endl;
		t2 += 5;
		cout << "T2 terment puncte: " << t2.puncte << endl;

		t2.generare_raport("raport.bin");

		t1.citire_raport("raport.bin");
		cout << "T1 terment puncte dupa citire raport: " << t1.puncte << endl;

		Tema* temeSem = new Tema[2]{ t1, t2 };

		MapaDeTemeSeminar oop(temeSem, 2);

		cout << "Mapa Teme Seminar OOP are: " << oop.nrTeme << " teme" << endl;

		string* cerinteT3 = new string[3];
		cerinteT3[0] = "Fa un calculator in C++";
		cerinteT3[1] = "Fa un calculator in C#";
		cerinteT3[2] = "Fa un calculator in Java";

		Tema t3(cerinteT3, 3, "10-01-2023", 3, TipFisier::HFILE, 20);
		delete[] cerinteT3;

		oop += t3;
		cout << "Mapa Teme Seminar OOP are: " << oop.nrTeme << " teme" << endl;

	}

	catch (exception& e) {
		cout << "Error: " << e.what() << endl;
	}

	catch (...) {
		cout << "End of try - catch execution for T2" << endl;
	}
}