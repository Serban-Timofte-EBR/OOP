#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Vehicul {
private:
	char* denumire;
	int nrCarac;

	string* nrInmatriculare;
	int nrNumere;
	double tarifDeBaza;

	static int nrAutomobile;
public:
	int capacitate;
	const int serie;

	void set_denumire(string nume) {
		delete[] this->denumire;

		this->nrCarac = nume.length();
		this->denumire = new char[this->nrCarac + 1];

		strcpy_s(this->denumire, this->nrCarac + 1, nume.c_str());
	}

	char* get_denumire() {
		if (this->denumire == nullptr) {
			return nullptr;
		}
		char* copy = new char[this->nrCarac + 1];
		strcpy_s(copy, this->nrCarac + 1, this->denumire);

		return copy;
	}

	int get_nrCarac() { return this->nrCarac; }

	int get_nrCaracInmatriculare() { return this->nrNumere; }

	string* get_nrInmatriculare() {
		string* copy = new string[this->nrNumere];

		for (int i = 0; i < this->nrNumere; i++) {
			copy[i] = this->nrInmatriculare[i];
		}

		return copy;
	}

	void set_nrInmatriculare(string* numere, int nrNumere) {
		delete[] this->nrInmatriculare;

		this->nrInmatriculare = new string[nrNumere + 1];
		this->nrNumere = nrNumere;

		for (int i = 0; i < this->nrNumere; i++) {
			this->nrInmatriculare[i] = numere[i];
		}
	}

	double get_tarif() {
		return this->tarifDeBaza;
	}

	void set_tarif(double tarif) {
		this->tarifDeBaza = tarif;
	}

	Vehicul() : serie(++nrAutomobile), tarifDeBaza(0), capacitate(0) {}
	Vehicul(string denumire, string numereImat[], int nrNumereInmat, double tarif, int capacitate) : serie(++nrAutomobile), tarifDeBaza(tarif), capacitate(capacitate) {
		this->set_denumire(denumire);
		this->set_nrInmatriculare(numereImat, nrNumereInmat);
	}

	~Vehicul() {
		delete[] this->denumire;
		delete[] this->nrInmatriculare;
	}

	virtual void afiseaza_detalii(ofstream& nume_fisier) = 0;
	virtual void afiseaza_detalii_binar(string nume_fisier_binar) = 0;

	virtual double citeste_tarif_actual(ifstream& nume_fisier) = 0;
};

int Vehicul::nrAutomobile = 0;

class Automobil : public Vehicul {
private:
	int nrUsi;

public:
	Automobil(string denumire, string numereImat[], int nrNumereImat, double tarif, int capacitate, int nrUsi) : Vehicul(denumire, numereImat, nrNumereImat, tarif, capacitate) {
		this->nrUsi = nrUsi;
	}

	void afiseaza_detalii(ofstream& nume_fisier) {
		int nrInmat = Automobil::get_nrCaracInmatriculare();
		string* istoricNrInmat = new string[nrInmat];
		istoricNrInmat = Automobil::get_nrInmatriculare();

		nume_fisier << "Raportul Vehiculului cu numere de inmatriculare: ";
		for (int i = 0; i < nrInmat; i++) {
			nume_fisier << istoricNrInmat[i] << " ";
		}
		nume_fisier << endl;
		nume_fisier << "Denumire: " << Automobil::get_denumire() << endl;
		nume_fisier << "Tarif de baza: " << Automobil::get_tarif() << endl;
		nume_fisier << "Capacitate: " << Automobil::capacitate << endl;
		nume_fisier << "Numar Usi: " << Automobil::nrUsi << endl;
	}

	void afiseaza_detalii_binar(string nume_fisier_binar){
		ofstream doc(nume_fisier_binar, ios::binary || ios::trunc);
		if (doc.is_open()) {
			cout << "Fisier binar not opened!" << endl;
		}
		else {
		char* denumireVeh = Automobil::get_denumire();
		doc.write("Denumire vehicul: ", 18);
		doc.write(denumireVeh, strlen(denumireVeh));

		string header2 = "Numere de inmatriculare";
		doc.write(header2.c_str(), header2.length());

		int nrInmat = Automobil::get_nrCaracInmatriculare();
		string* istoricNrInmat = new string[nrInmat];
		istoricNrInmat = Automobil::get_nrInmatriculare();
		for (int i = 0; i < nrInmat; i++) {
			doc.write(istoricNrInmat[i].c_str(), istoricNrInmat[i].length());
		}

		delete[] istoricNrInmat;
		doc.close();
		}
	}

	double citeste_tarif_actual(ifstream& nume_fisier) {
		string linie = "";
		double tarifActual = 0.0;

		while (getline(nume_fisier, linie)) {
			size_t lastSpace = linie.find_last_of(" ");
			if (lastSpace != string::npos) {
				string tarifSTR = linie.substr(lastSpace + 1);
				tarifActual = stod(tarifSTR);
			}
		}

		return tarifActual;
	}
};

enum class TaxiType {UBER, BOLT, BLACK_CAB, CLASSIC, OTHER};

class Taxi {
private:
	const int taxiID;
	string lastDestination = "";
	int noRides = -1;
	float* kmPerRide = nullptr;
	double pricePerKm = 0.0;
	TaxiType type = TaxiType::OTHER;

public:
	static int NO_UBER_TAXIES;
	const static int MIN_KM_PER_RIDE = 5;

	//void set_kmPerRide(float* listOfKms, int nr) {
	//	if (listOfKms == nullptr) { cout << "Invalid input listOfKms in set_kmPerRide!" << endl; }
	//	else if (nr < 1) { cout << "Invalid input nr in set_kmPerRide!" << endl; }
	//	else {
	//		delete[] this->kmPerRide;
	//		
	//		this->kmPerRide = new float[nr];
	//		for (int i = 0; i < nr; i++) {
	//			this->kmPerRide[i] = listOfKms[i];
	//		}
	//		this->noRides = nr;
	//	}
	//}

	template<typename T> void set_kmPerRide(T* listOfKms, int nr) {
		if (listOfKms == nullptr) { cout << "Invalid input listOfKms in set_kmPerRide!" << endl; }
		else if (nr < 1) { cout << "Invalid input nr in set_kmPerRide!" << endl; }
		else {
			delete[] this->kmPerRide;

			this->kmPerRide = new float[nr];
			for (int i = 0; i < nr; i++) {
				this->kmPerRide[i] = listOfKms[i];
			}
			this->noRides = nr;
		}
	}

	void add_ride(float kmOfRide) {
		if (this->noRides == -1) {
			this->noRides = 0;
		}
		float* copy = new float[this->noRides + 1];
		for (int i = 0; i < this->noRides; i++) {
			copy[i] = this->kmPerRide[i];
		}
		copy[this->noRides] = kmOfRide;
		delete[] this->kmPerRide;
		this->kmPerRide = copy;
		this->noRides += 1;
	}

	template<typename T> T* get_kmPerRide() {
		T* copy = new T[this->noRides];
		for (int i = 0; i < this->noRides; i++) {
			copy[i] = this->kmPerRide[i];
		}
		return copy;
	}

	/*float* get_kmPerRide() {
		if (this->kmPerRide == nullptr) { return nullptr; }
		float* copy = new float[this->noRides];
		for (int i = 0; i < this->noRides; i++) {
			copy[i] = this->kmPerRide[i];
		}
		return copy;
	}

	int* get_kmPerRideINT() {
		if (this->kmPerRide == nullptr) { return nullptr; }
		int* copy = new int[this->noRides];
		for (int i = 0; i < this->noRides; i++) {
			copy[i] = this->kmPerRide[i];
		}
		return copy;
	}*/

	double get_pricePerKm() { return this->pricePerKm; }

	int get_noRides() { return this->noRides; }

	void set_taxiType(TaxiType newType) {
		if (this->type == TaxiType::UBER) { this->NO_UBER_TAXIES -= 1; }
		this->type = newType;
		if (newType == TaxiType::UBER) { this->NO_UBER_TAXIES += 1; }
	}

	Taxi() : taxiID(-1) {
		lastDestination = "Unknown";
		pricePerKm = 2.5;
		type = TaxiType::CLASSIC;
	}

	Taxi(int id, TaxiType type, double price) : taxiID(id) {
		this->lastDestination = "None";
		this->type = type;
		this->pricePerKm = price;
	}

	Taxi(int id, TaxiType type, double price, int* records, int noPreviousRides)
		: taxiID(id) {
		this->lastDestination = "None";
		this->type = type;
		if (this->type == TaxiType::UBER) { this->NO_UBER_TAXIES += 1; }
		this->pricePerKm = price;
		this->set_kmPerRide<int>(records, noPreviousRides);
	}

	Taxi(const Taxi& taxi) : taxiID(taxi.taxiID) {
		this->lastDestination = taxi.lastDestination;
		this->pricePerKm = taxi.pricePerKm;
		this->type = taxi.type;
		this->set_kmPerRide<float>(taxi.kmPerRide, taxi.noRides);
		if (taxi.type == TaxiType::UBER) {
			this->NO_UBER_TAXIES += 1;
		}
	}

	~Taxi() {
		delete[] this->kmPerRide;
	}

	void operator=(const Taxi& taxi) {
		if (this == &taxi) { return; }
		else {
			this->lastDestination = taxi.lastDestination;
			this->pricePerKm = taxi.pricePerKm;
			this->type = taxi.type;
			this->set_kmPerRide<float>(taxi.kmPerRide, taxi.noRides);
			if (taxi.type == TaxiType::UBER) {
				this->NO_UBER_TAXIES += 1;
			}
		}
	}

	float getTotalRevenue()
	{
		double totalRevenue = 0;
		for (int i = 0; i < this->noRides; i++) {
			totalRevenue += this->kmPerRide[i] * pricePerKm;
		}
		return totalRevenue;
	}

	static double computeFleetValue(Taxi vehicles[], int noVehicles) {
		double fleetRevenue = 0;
		for (int i = 0; i < noVehicles; i++) {
			for (int j = 0; j < vehicles[i].noRides; j++) {
				fleetRevenue += vehicles[i].kmPerRide[j] * vehicles[i].pricePerKm;
			}
		}
		return fleetRevenue;
	}

	friend ostream& operator<<(ostream& cons, const Taxi& taxi);
	friend istream& operator>>(istream& cons, Taxi& taxi);

	Taxi& operator+(int kmLastRide) {
		this->add_ride(kmLastRide);
		return *this;
	}

	friend Taxi& operator+(int kmLastRide, Taxi& taxi);

	void operator*=(int mult) {
		this->pricePerKm *= mult;
	}

	Taxi& operator++() {
		this->pricePerKm += 1;
		return *this;
	}

	Taxi& operator++(int nr) {
		this->pricePerKm += 1;
		return *this;
	}

	bool operator==(Taxi& taxi) {
		float totalRev1 = this->getTotalRevenue();
		float totalRev2 = taxi.getTotalRevenue();
		return totalRev1 == totalRev2;
	}

	bool operator!() {
		return this->getTotalRevenue() == 0;
	}

	float operator()(int start, int end) {
		if (start < 0 || start > end || end > this->noRides) { cout << "Invalid indexes!" << endl; return -1; }
		else {
			float partialRevenue = 0.0;
			for (int i = start - 1; i < end; i++) {
				partialRevenue += this->kmPerRide[i] * this->pricePerKm;
			}
			return partialRevenue;
		}
	}

	float& operator[](int index) {
		float dummy;
		if (index < 0 || index >this->noRides) { return dummy; }
		else {
			return this->kmPerRide[index - 1];
		}
	}

};

ostream& operator<<(ostream& cons, const Taxi& taxi) {
	cons << endl << "ID: " << taxi.taxiID << endl;
	cons << "List of rides: ";
	for (int i = 0; i < taxi.noRides; i++) {
		cons << taxi.kmPerRide[i] << " ";
	}
	cons << endl;
	cons << "Price of taxi: " << taxi.pricePerKm << endl;
	if (taxi.type == TaxiType::UBER) { cons << "UBER car!" << endl; }
	else { cons << "Other type of car!" << endl; }
	cons << endl;
	return cons;
}

istream& operator>>(istream& cons,Taxi& taxi) {
	string inpLastDestination;
	cout << "Input the last destination: " << endl;
	cons >> inpLastDestination;
	taxi.lastDestination = inpLastDestination;

	int inpNoRides;
	cout << "Input the number of rides: " << endl;
	cons >> inpNoRides;
	taxi.noRides = inpNoRides;

	float* inpRidesList = new float[inpNoRides];
	for (int i = 0; i < inpNoRides; i++) {
		cout << "Input element " << i << " from the list: ";
		cons >> inpRidesList[i];
		cout << endl;
	}
	taxi.set_kmPerRide<float>(inpRidesList, inpNoRides);

	double inpPrice;
	cout << "Input the price per km: " << endl;
	cons >> inpPrice;
	taxi.pricePerKm = inpPrice;

	int inpType;
	cout << "Input the nr. for Taxi Type: " << endl;
	cons >> inpType;
	taxi.type = TaxiType(inpType);

	if (taxi.type == TaxiType::UBER) { taxi.NO_UBER_TAXIES += 1; }
	
	return cons;
}

Taxi& operator+(int kmLastRide, Taxi& taxi) {
	taxi.add_ride(kmLastRide);
	return taxi;
}

int Taxi::NO_UBER_TAXIES = 0;

int main() {
	cout << "***********This is Assignment 3 Recap***********" << endl;
	float* ridesForTest = new float[3];
	ridesForTest[0] = 10.2;
	ridesForTest[1] = 11.2;
	ridesForTest[2] = 15.5;
	cout << "Taxi t1: " << endl;
	Taxi t1;
	t1.set_kmPerRide<float>(ridesForTest, 3);
	t1.add_ride(21.2);
	/*int t1_noRides = t1.get_noRides();
	float* t1_rides = new float[t1_noRides];
	t1_rides = t1.get_kmPerRide<float>();
	cout << "T1 rides are: ";
	for (int i = 0; i < t1_noRides; i++) {
		cout << t1_rides[i] << " ";
	}
	cout << endl;
	delete[] t1_rides;*/
	cout << t1;
	t1.set_taxiType(TaxiType::UBER);
	cout << "We have " << Taxi::NO_UBER_TAXIES << " UBER cars!" << endl;
	cout << "T1 total revenue is: " << t1.getTotalRevenue() << endl;
	/*t1.set_taxiType(TaxiType::BLACK_CAB);
	cout << "Altered the t1 Type to decrease the NO_UBER_TAXIES!" << endl;
	cout << "We have " << Taxi::NO_UBER_TAXIES << " UBER cars!" << endl;*/


	cout << endl << "Taxi t2: " << endl;
	int* ridesINT = new int[3];
	ridesINT[0] = 21;
	ridesINT[1] = 22;
	ridesINT[2] = 23;
	Taxi t2(385, TaxiType::BLACK_CAB, 9.8, ridesINT, 3);
	t2.add_ride(24);
	/*int t2_noRides = t2.get_noRides();
	int* t2_rides = new int[t2_noRides];
	t2_rides = t2.get_kmPerRide<int>();
	cout << "T2 rides are: ";
	for (int i = 0; i < t2_noRides; i++) {
		cout << t2_rides[i] << " ";
	}
	cout << endl;
	delete[] t2_rides;*/
	cout << t2;

	delete[] ridesForTest;
	delete[] ridesINT;

	cout << endl << "Taxi t3: " << endl;
	Taxi t3 = t1;
	int t3_noRides = t3.get_noRides();
	float* t3_rides = new float[t3_noRides];
	t3_rides = t3.get_kmPerRide<float>();
	cout << "T3 rides are: ";
	for (int i = 0; i < t3_noRides; i++) {
		cout << t3_rides[i] << " ";
	}
	cout << endl;
	cout << "We have " << Taxi::NO_UBER_TAXIES << " UBER cars!" << endl;

	cout << endl << "Taxi t4: " << endl;
	Taxi t4;
	t4 = t1;
	int t4_noRides = t4.get_noRides();
	float* t4_rides = new float[t4_noRides];
	t4_rides = t4.get_kmPerRide<float>();
	cout << "T4 rides are: ";
	for (int i = 0; i < t4_noRides; i++) {
		cout << t4_rides[i] << " ";
	}
	cout << endl;
	cout << "We have " << Taxi::NO_UBER_TAXIES << " UBER cars!" << endl;
	t1.add_ride(121.5);
	cout << "Added a trip to t1" << endl;

	cout << "Total Fleet Revenue Calculator" << endl;
	int* trips1 = new int[3] {21, 44, 21};
	int* trips2 = new int[3] {12, 9, 8};
	int* trips3 = new int[3] {15, 19, 18};
	Taxi taxi_fleet1(41, TaxiType::UBER, 3.5, trips1, 3);
	Taxi taxi_fleet2(51, TaxiType::BOLT, 3.3, trips2, 3);
	Taxi taxi_fleet3 = taxi_fleet2;
	cout << "Now, we have " << Taxi::NO_UBER_TAXIES << endl;
	cout << taxi_fleet1 << taxi_fleet2 << taxi_fleet3;
	cout << "Value of the fleet is ";
	Taxi* vehicles = new Taxi[3] {taxi_fleet1, taxi_fleet2, taxi_fleet3};
	cout << Taxi::computeFleetValue(vehicles, 3) << endl;

	Taxi taxi(1, TaxiType::UBER, 2.5);
	taxi.add_ride(100);
	taxi.add_ride(10);
	/*cout << endl << "Operator >>" << endl;
	cin >> taxi;
	cout << endl << endl;
	cout << taxi;*/

	cout << endl << endl << "Operator +" << endl;
	taxi = taxi + 20;
	taxi = 15 + taxi;
	cout << taxi;

	cout << endl << endl << "Operator *=" << endl;
	cout << "Taxi price per KM: " << taxi.get_pricePerKm() << endl;
	taxi *= 2;
	cout << "Taxi price per KM after update: " << taxi.get_pricePerKm() << endl;

	cout << endl << endl << "Operator taxi++" << endl;
	Taxi copy = taxi++;
	cout << copy;

	cout << endl << endl << "Operator ++taxi" << endl;
	Taxi otherCopy = ++taxi;
	cout << otherCopy;
	cout << copy;

	cout << endl << endl << "Operator otherCopy == copy" << endl;
	if (otherCopy == copy) {
		cout << "They same the same total revenue!" << endl;
	}

	cout << endl << endl << "Operator otherCopy !taxi" << endl;
	Taxi nullTaxi;
	if (!nullTaxi) {
		cout << "Total revenue is 0" << endl;
	}

	cout << endl << endl << "Operator otherCopy (1,3)" << endl;
	cout << taxi;
	float partialRevenue = taxi(1, 3);
	cout << partialRevenue << endl;

	cout << endl << endl << "Operator [1]" << endl;
	int secondRide = taxi[1];
	cout << "Second Ride: " << secondRide << endl;

	cout << endl << endl << "Operator taxi[1] = 5" << endl;
	taxi[2] = 5;
	cout << taxi << endl;

	cout << endl << endl << endl << endl << endl << "***********This is the initial project to practice (Vehicul + Automobile)***********" << endl << endl << endl;

	string numereInmat[] = { "B 123 EBR", "B 225 OCH" };

	Automobil ferrari("Ferrari 911 Turbo GT", numereInmat, 2, 150.5, 2, 2);

	ifstream tarifList("tarif.txt");
	if (!tarifList.is_open()) { cout << "Fisierul cu lista de tarife nu a putu fi deschis" << endl; }

	double tarifActual = ferrari.citeste_tarif_actual(tarifList);
	ferrari.set_tarif(tarifActual);
	cout << "Tariful automobilului " << ferrari.get_denumire() << " este de " << tarifActual << "." << endl;

	ofstream raport("Raport Ferrari.txt", ios::ate);
	ferrari.afiseaza_detalii(raport);
	raport.close();

	ferrari.afiseaza_detalii_binar("Raport Ferrari.bin");

	return 0;
}