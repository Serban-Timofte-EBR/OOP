#pragma once
#include <iostream>
#include <string>
using namespace std;

class TaxiExeption {

};

enum TaxiType { UBER, BOLT, BLACK_CAB, CLASSIC, OTHER };

class Taxi {
public:
	/*R1*/
	const int taxiId;
	string lastDestination = "*";
	int noRides = -1;
	float* kmPerRide = nullptr;
	double pricePerKm = 0.0;
	TaxiType type = TaxiType::OTHER;

	static int NO_UBER_TAXIES;
	const static int MIN_KM_PER_RIDE = 5;

	/*R2*/
	Taxi() :taxiId(-1) {
		this->lastDestination = "Unknown";
		this->pricePerKm = 2.5;
		this->type = TaxiType::CLASSIC;
	}

	/*R3*/
	Taxi(int id, TaxiType type, double price) : taxiId(id), type(type), pricePerKm(price) {
		this->lastDestination = "None";
		if (type == TaxiType::UBER) { this->NO_UBER_TAXIES++; }
	}

	/*R4*/
	Taxi(int id, TaxiType type, double price, int* records, int noPreviousRides) : taxiId(id), type(type), pricePerKm(price), noRides(noPreviousRides) {
		delete[] this->kmPerRide;
		this->kmPerRide = new float[noPreviousRides];
		for (int i = 0; i < noPreviousRides; i++) {
			this->kmPerRide[i] = float(records[i]);
		}
		this->lastDestination = "None";
		if (type == TaxiType::UBER) { this->NO_UBER_TAXIES++; }
	}

	/*R5 is upper*/

	/*R6*/
	Taxi(const Taxi& taxi) : taxiId(taxi.taxiId) {
		this->lastDestination = taxi.lastDestination;
		this->noRides = taxi.noRides;
		this->pricePerKm = taxi.pricePerKm;
		this->type = taxi.type;
		if (this->type == TaxiType::UBER) { this->NO_UBER_TAXIES++; }
		delete[] this->kmPerRide;
		this->kmPerRide = new float[taxi.noRides];
		for (int i = 0; i < taxi.noRides; i++) {
			this->kmPerRide[i] = taxi.kmPerRide[i];
		}
	}

	~Taxi() {
		if (this->type == TaxiType::UBER) { this->NO_UBER_TAXIES--; }
		delete[] this->kmPerRide;
	}

	/*R8*/
	Taxi& operator=(const Taxi& t) {
		if (this == &t) { return *this; }
		this->lastDestination = t.lastDestination;
		this->noRides = t.noRides;
		this->pricePerKm = t.pricePerKm;
		this->type = t.type;
		if (this->type == TaxiType::UBER) { this->NO_UBER_TAXIES++; }

		delete[] this->kmPerRide;

		if (t.noRides > 0 && t.kmPerRide != nullptr) {
			this->kmPerRide = new float[t.noRides];
			for (int i = 0; i < t.noRides; i++) {
				this->kmPerRide[i] = t.kmPerRide[i];
			}
		}
		else { this->kmPerRide = nullptr; }

		return *this;
	}

	/*R9*/
	float getTotalRevenue() {
		float totalRevenue = 0.0;
		for (int i = 0; i < this->noRides; i++) {
			totalRevenue += this->kmPerRide[i] * this->pricePerKm;
		}
		return totalRevenue;
	}

	/*R10*/
	static double computeFleetValue(Taxi vechicles[], int noVehicles) {
		double totalRevenue = 0.0;

		for (int vehiclePoz = 0; vehiclePoz < noVehicles; vehiclePoz++) {
			for (int i = 0; i < vechicles[vehiclePoz].noRides; i++) {
				totalRevenue += vechicles[vehiclePoz].kmPerRide[i] * vechicles[vehiclePoz].pricePerKm;
			}
		}

		return totalRevenue;
	}

	Taxi operator+(int kmOfLastRide) {
		Taxi rezultat = *this;
		float* actualRides = new float[rezultat.noRides + 1];
		for (int i = 0; i < rezultat.noRides; i++) {
			actualRides[i] = rezultat.kmPerRide[i];
		}
		actualRides[rezultat.noRides] = kmOfLastRide;

		rezultat.noRides++;
		delete[] rezultat.kmPerRide;
		rezultat.kmPerRide = new float[rezultat.noRides];
		for (int i = 0; i < rezultat.noRides; i++) {
			rezultat.kmPerRide[i] = actualRides[i];
		}
		return rezultat;
	}

	friend Taxi operator+(int kmOfLastRide, Taxi& t);

	Taxi operator*=(int multiplicator) {
		this->pricePerKm = this->pricePerKm * multiplicator;
		return *this;
	}

	Taxi operator++(int) {
		Taxi rezultat = *this;
		this->pricePerKm += 1;
		return rezultat;
	}

	Taxi operator++() {
		Taxi rezultat = *this;
		this->pricePerKm += 1;
		rezultat.pricePerKm += 1;
		return rezultat;
	}

	float operator()(int start, int end) {
		if (start < 0 || end >= this->noRides || start > end) { return 0; }

		float revenue = 0.0;
		for (int i = start - 1; i < end; i++) {
			revenue += this->kmPerRide[i] * this->pricePerKm;
		}

		return revenue;
	}

	float& operator[](int index) {
		return this->kmPerRide[index - 1];
	}
};

int Taxi::NO_UBER_TAXIES = 0;

void operator<<(ostream& consola, Taxi& t) {
	consola << "ID: " << t.taxiId << endl;;
	consola << "Last Destination: " << t.lastDestination << endl;
	consola << "No Rides: " << t.noRides << endl;
	consola << "KM Per Ride: ";
	for (int i = 0; i < t.noRides; i++) {
		consola << t.kmPerRide[i] << " ";
	}
	consola << endl;
	consola << "Price Per KM: " << t.pricePerKm << endl;
	consola << "Type: " << t.type << endl;
}

void operator>>(istream& consola, Taxi& t) {
	string lastDestination;
	cout << "Last Destination: " << endl;
	consola >> lastDestination;
	t.lastDestination = lastDestination;

	int noRides;
	cout << "NoRides: " << endl;
	consola >> noRides;
	t.noRides = noRides;

	double pricePerKm;
	cout << "Price Per KM: " << endl;
	consola >> pricePerKm;
	t.pricePerKm = t.pricePerKm;

	int type;
	cout << "Enter type as int (0-4): " << endl;
	consola >> type;
	t.type = TaxiType(type);

	delete[] t.kmPerRide;
	t.kmPerRide = new float[noRides];
	for (int i = 0; i < noRides; i++) {
		cout << "Enter km for Ride " << (i + 1) << ": ";
		consola >> t.kmPerRide[i];
	}
}

Taxi operator+(int kmOfLastRide, Taxi& t) {
	Taxi rezultat = t;

	float* rides = new float[rezultat.noRides + 1];
	for (int i = 0; i < rezultat.noRides; i++) {
		rides[i] = rezultat.kmPerRide[i];
	}
	rides[rezultat.noRides] = kmOfLastRide;

	rezultat.noRides++;
	delete[] rezultat.kmPerRide;
	rezultat.kmPerRide = new float[rezultat.noRides];
	for (int i = 0; i < rezultat.noRides; i++) {
		rezultat.kmPerRide[i] = rides[i];
	}

	return rezultat;
}