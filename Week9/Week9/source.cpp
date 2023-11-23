#include <iostream>
#include <string>
using namespace std;

class TestLaborator {
	string data = "";		//Format: dd/mm/yyyy
	int durataMinute = 0;
	string* studenti = nullptr;
	int nrStudenti = 0;

public:
	static int const DURATA_MINIMA = 30;
	static int NR_TOTAL_SOLUTII;

	void set_data(string data) {
		if (data.size() != 10 || data[2] != '/' || data[5] != '/') {
			throw exception("Data are format gresit!");
		}
		this->data = data;
	}

	void set_durata(int min) {
		if (min < TestLaborator::DURATA_MINIMA) {
			throw exception(("Durata minima este " + to_string(DURATA_MINIMA)).c_str());
		}
		this->durataMinute = min;
	}

	void prezenta(string numeStudent) {
		string* lista = new string[this->nrStudenti + 1];
		for (int i = 0; i < this->nrStudenti; i++) {
			lista[i] = this->studenti[i];
		}
		delete[] this->studenti;
		this->studenti = lista;
		lista[this->nrStudenti] = numeStudent;
		this->nrStudenti += 1;
	}

	void incarcaSolutie(string numeStudent) {
		bool estePrezent = false;
		for (int i = 0; i < this->nrStudenti; i++) {
			if (this->studenti[i] == numeStudent) {
				estePrezent = true;
				break;
			}
		}

		if (!estePrezent) { throw exception("Studentul incarca solutia fara a fi prezent!"); }

		TestLaborator::NR_TOTAL_SOLUTII += 1;
	}

	explicit operator int() {
		return this->durataMinute;
	}

	string& operator[](int index) {
		if (index < 0 || index >= this->nrStudenti) { throw exception("Index invalid"); }
		return this->studenti[index];
	}

	string operator()(int index) {
		if (index < 0 || index >= this->nrStudenti) { throw exception("Invalid index!"); }
		return this->studenti[index];
	}
};

int TestLaborator::NR_TOTAL_SOLUTII = 0;

int main() {
	TestLaborator test;
	test.set_data("28/11/2023");
	test.set_durata(60);

	test.prezenta("Gigel");
	test.prezenta("Ana");
	test.prezenta("Ionut");

	test.incarcaSolutie("Ana");

	int durata = (int)test;
	cout << "Durata este: " << durata << endl;

	//operator indexare
	cout << "Operator indexare: " << endl << endl;
	cout << "Primul student este: " << test[0] << endl;
	test[0] = "dorel";
	cout << "Primul student este acum: " << test[0] << endl;

	cout << endl << endl;
	//parametru functie
	string nume = test(2);
	cout << "Numele op functie: " << nume << endl;

	return 0;
}