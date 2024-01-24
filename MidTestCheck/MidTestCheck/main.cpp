#include <iostream>
using namespace std;

enum class TipCamera { DSLR, Compact, ActionCam };

class CameraDigitala {
private:
	const string serie;
	string brand = "";
	TipCamera tip = TipCamera::DSLR;
	bool areCardMemorie = false;
	string* poze = nullptr;
	int nrPoze = 0;
	float nivelBaterie = 0.0;

	static const int MAX_POZE = 10000;
public:

	void setPoze(string* newPoze, int noNewPoze) {
		if (newPoze == nullptr || noNewPoze < 1) { throw exception("Invalid newPoze input!"); }
		delete[] this->poze;
		this->poze = new string[noNewPoze];
		for (int i = 0; i < noNewPoze; i++) {
			this->poze[i] = newPoze[i];
		}
		this->nrPoze = noNewPoze;
	}

	string* getPoze() {
		string* copy = new string[this->nrPoze];
		for (int i = 0; i < this->nrPoze; i++) {
			copy[i] = this->poze[i];
		}
		return copy;
	}

	int getNrPoze() {
		return this->nrPoze;
	}

	CameraDigitala(string serie, string brand, TipCamera type) : serie(serie) {
		if (brand.length() > 4) {
			this->brand = brand;
		}
		else {
			throw exception("Brand too short!");
		}
		this->tip = type;
	}

	string getSerie() {
		return this->serie;
	}

	string getTip() {
		if (this->tip == TipCamera::ActionCam) {
			return "ActionCam";
		}

		if (this->tip == TipCamera::DSLR) {
			return "DSLR";
		}

		if (this->tip == TipCamera::Compact) {
			return "Compact";
		}
	}

	string getBrand() {
		return this->brand;
	}

	~CameraDigitala() {
		delete[] this->poze;
	}

	CameraDigitala(const CameraDigitala& c) : serie(c.serie) {
		this->brand = c.brand;
		this->tip = c.tip;
		this->areCardMemorie = c.areCardMemorie;
		setPoze(c.poze, c.nrPoze);
		this->nivelBaterie = c.nivelBaterie;
	}

	void adaugaCardMemorie() {
		this->areCardMemorie = true;
	}

	bool getCardMem() {
		return this->areCardMemorie;
	}

	float getSpatiuLiber() {
		float spatiu = float(this->MAX_POZE) - float(this->nrPoze);
		return spatiu;
	}

	CameraDigitala& operator=(const CameraDigitala& c) {
		if (this == &c) { return *this; }
		this->brand = c.brand;
		this->tip = c.tip;
		this->areCardMemorie = c.areCardMemorie;
		setPoze(c.poze, c.nrPoze);
		this->nivelBaterie = c.nivelBaterie;
	}

	friend ostream& operator<<(ostream& cons, CameraDigitala& c);

	bool operator==(const CameraDigitala& c) {
		bool flag = true;
		if (this->serie != c.serie) { flag = false; }
		if (this->brand != c.brand) { flag = false; }
		return flag;
	}

	explicit operator float() {
		float ocupat;
		ocupat = float(this->nrPoze) / float(this->MAX_POZE);
		ocupat = ocupat * 100;
		return ocupat;
	}

	CameraDigitala operator+(string newPoza) {
		CameraDigitala cam(*this);

		string* copy = new string[cam.nrPoze + 1];
		for (int i = 0; i < cam.nrPoze; i++) {
			copy[i] = cam.poze[i];
		}
		copy[cam.nrPoze] = newPoza;
		
		delete[] cam.poze;
		cam.poze = copy;
		cam.nrPoze++;
		return cam;
	}

	bool estePoza(string title) {
		bool flag = false;
		for (int i = 0; i < this->nrPoze; i++) {
			if (this->poze[i] == title) {
				flag = true;
			}
		}

		return flag;
	}
};

ostream& operator<<(ostream& cons, CameraDigitala& c) {
	cons << "Serie: " << c.serie << endl;
	cons << "Brand: " << c.brand << endl;
	cons << "Tip: " << c.getTip() << endl;
	string* pozeGet = new string[c.getNrPoze()];
	pozeGet = c.getPoze();
	cons << "Poze Get: " << endl;
	for (int i = 0; i < c.getNrPoze(); i++)
	{
		cons << pozeGet[i] << " ";
	}
	cons << endl;
	cons << "Nr Poze: " << c.nrPoze << endl;
	cons << "Niv. Bat: " << c.nivelBaterie << endl;
	return cons;
}

int main() {
	CameraDigitala d1("N123", "Nikon", TipCamera::DSLR);
	cout << d1.getSerie() << endl;
	cout << d1.getBrand() << endl;
	cout << d1.getTip() << endl;

	string poze[] = { "Poza1", "Poza2", "Poza3" };
	int nrPoze = 3;
	d1.setPoze(poze, nrPoze);

	string* pozeGet = new string[d1.getNrPoze()];
	pozeGet = d1.getPoze();
	cout << "Poze Get: " << endl;
	for (int i = 0; i < d1.getNrPoze(); i++)
	{
		cout << pozeGet[i] << " ";
	}
	cout << endl;

	CameraDigitala d2(d1);
	cout << "D2 Copy: " << endl;
	cout << d2.getSerie() << endl;

	d1.adaugaCardMemorie();
	cout << "Card Mem: " << d1.getCardMem() << endl;

	float spatiuLiber = d1.getSpatiuLiber();
	cout << "Spatiu Liber: " << spatiuLiber << endl;

	CameraDigitala d3("S1", "Canon", TipCamera::DSLR);
	d3 = d1;
	cout << d3.getBrand() << endl;

	cout << endl << endl << "Operator <<: " << endl;
	cout << d1;

	cout << endl << endl << endl;
	cout << endl << endl << "Operator CameraDigitala + string: " << endl;
	d2 = d1 + "Poza Vacanta";
	cout << "d1: " << endl;
	cout << d1;
	cout << endl << "d2: " << endl;
	cout << d2;
	cout << endl << endl << endl;

	cout << "d1: " << endl;
	cout << d1;
	cout << endl << "d2: " << endl;
	cout << d2;
	cout << endl;
	if (d1 == d2) { cout << "Identice" << endl; }
	else { cout << "No!" << endl; }

	float ocupat = float(d1);
	cout << "Cast: Ocupat: " << ocupat << endl;

	cout << "Functia care verifica daca este salvata in poze: ";
	cout << d1.estePoza("Poza1") << endl;

	{
		CameraDigitala cam("L123456", "Nikon", TipCamera::DSLR);
	}

	return 0;
}