#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Petitie {
private:
	char* continut =nullptr;
	int nrInregistrare;
	string semnatar;
public:

	void set_continut(string text) {
		delete[] this->continut;

		this->continut = new char[text.length() + 1];
		strcpy_s(this->continut, text.length() + 1, text.c_str());
	}

	char* get_continut() {
		char* copy = new char[strlen(this->continut) + 1];
		strcpy_s(copy, strlen(this->continut) + 1, this->continut);
		return copy;
	}

	int get_continutLen() {
		return strlen(this->continut) + 1;
	}

	int get_nrInregistrare() { return this->nrInregistrare; }

	string get_semnatar() { return this->semnatar; }

	Petitie() {
		this->continut = nullptr;
		this->nrInregistrare = 0;
		this->semnatar = "None";
	}
	
	Petitie(string text) {
		this->nrInregistrare = 0;
		this->semnatar = "None";
		this->set_continut(text);
	}

	Petitie(int nrInreg, string nume, string text) {
		this->nrInregistrare = nrInreg;
		this->semnatar = nume;
		this->set_continut(text);
	}

	Petitie(const Petitie& pet) {
		this->nrInregistrare = pet.nrInregistrare;
		this->semnatar = pet.semnatar;
		this->set_continut(pet.continut);
	}

	~Petitie() {
		delete[] this->continut;
	}

	Petitie& operator=(const Petitie& pet) {
		this->nrInregistrare = pet.nrInregistrare;
		this->semnatar = pet.semnatar;
		this->set_continut(pet.continut);
		return *this;
	}

	void operator++(int nr) {
		this->nrInregistrare += 1;
	}

	void change_semnatar(string newSemnatar, string newText) {
		this->semnatar = newSemnatar;
		this->set_continut(newText);
	}

	static void report_generator(Petitie* list, int nrPetitii) {
		ofstream doc("Report.txt", ios::trunc);
		for (int i = 0; i < nrPetitii; i++) {
			doc << list[i].nrInregistrare << endl;
			doc << list[i].semnatar << endl;
			doc << list[i].continut << endl;
		}
		doc.close();
	}

	static Petitie* report_decoder(int nr) {
		ifstream doc("Report.txt");
		if (!doc.is_open()) {
			throw exception("Doc Not Opened!");
		}
		else {
			Petitie* listDecoder = new Petitie[nr];
			for (int i = 0; i < nr; i++) {
				int nrInregDoc;
				doc >> nrInregDoc;

				string semnatarDoc;
				doc >> semnatarDoc;
				semnatarDoc += "\0";

				char buffer[80];
				string text;
				doc.getline(buffer, 80);
				text = string(buffer) + '\0';
	
				listDecoder[i] = Petitie(nrInregDoc, semnatarDoc, text);
			}
			doc.close();
			return listDecoder;
		}
	}
};

ostream& operator<<(ostream& cons, Petitie& pet) {
	cons << "Nr Inregistrare: " << pet.get_nrInregistrare() << endl;
	cons << "Semnatar: " << pet.get_semnatar() << endl;
	int lenCont = pet.get_continutLen();
	char* text = new char[lenCont];
	text = pet.get_continut();
	cons << "Continut: " << endl;
	cons << "\t" << text << endl;
	return cons;
}

int main() {
	Petitie pet1("Animalutele sunt bune!");
	int lenPet = pet1.get_continutLen();
	char* text = new char[lenPet + 1];
	text = pet1.get_continut();
	cout << text << endl;
	delete[] text;

	cout << endl << endl << "Copy Constructor" << endl;
	Petitie pet2 = pet1;
	int lenPet2 = pet2.get_continutLen();
	char* text2 = new char[lenPet2 + 1];
	text2 = pet2.get_continut();
	cout << text2 << endl;
	delete[] text2;

	cout << endl << endl << "Operator =" << endl;
	Petitie pet3("Oamenii sunt buni!");
	pet3 = pet2;
	int lenPet3 = pet3.get_continutLen();
	char* text3 = new char[lenPet3];
	text3 = pet3.get_continut();
	cout << text3 << endl;

	cout << endl << endl << "Operator <<" << endl;
	cout << pet3;

	cout << endl << endl << "Change Semnatar + Operator ++" << endl;
	pet3.change_semnatar("Serban", "Animalutele trebuie protejate!");
	pet3++;
	cout << endl << pet3;
	cout << endl;

	cout << endl << endl << "Fisier" << endl;
	Petitie* listaPetiti = new Petitie[3];
	listaPetiti[0] = pet1;
	listaPetiti[1] = pet2;
	listaPetiti[2] = pet3;

	Petitie::report_generator(listaPetiti, 3);
	delete[] listaPetiti;

	cout << endl << "**************" << endl << endl;

	try {
		Petitie* docList = Petitie::report_decoder(3);
		for (int i = 0; i < 3; i++) {
			cout << docList[i];
			cout << endl << endl;
		}
		delete[] docList;
	}
	catch (exception e) {
		cout << e.what() << endl;
	}

	return 0;
}