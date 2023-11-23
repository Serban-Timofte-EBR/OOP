#include <iostream>
#include <string>
using namespace std;

class TaxiExeption {

};

enum TaxiType { UBER, BOLT, BLACK_CAB, CLASSIC, OTHER};

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
		if (t.type == TaxiType::UBER) { this->NO_UBER_TAXIES++; }
		
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

int main() {
	cout << "Teste R1 - R10" << endl;
	Taxi taxi;
	cout << "Last Destination: " << taxi.lastDestination << endl;
	cout << "Price Per Km: " << taxi.pricePerKm << endl;
	cout << "Taxi Type: " << taxi.type << endl;
	cout << "NO UBER TAXIES: " << taxi.NO_UBER_TAXIES << endl;

	cout << endl; 

	Taxi taxi2(231, TaxiType::CLASSIC, 3.5);
	cout << "Last Destination: " << taxi2.taxiId << endl;
	cout << "Taxi Type: " << taxi2.type << endl;
	cout << "Price Per Km: " << taxi2.pricePerKm << endl;
	cout << "Last Destination: " << taxi2.lastDestination << endl;
	cout << "NO UBER TAXIES: " << taxi2.NO_UBER_TAXIES << endl;

	cout << endl;

	cout << "Req. 4:" << endl;
	int records[] = { 12, 21, 8 };

	Taxi taxi3(231, TaxiType::CLASSIC, 3.5, records, 3);
	cout << "ID: " << taxi3.taxiId << endl;
	cout << "Taxi Type: " << taxi3.type << endl;
	cout << "Price Per Km: " << taxi3.pricePerKm << endl;
	cout << "Last Destination: " << taxi3.lastDestination << endl;
	cout << "Km Per Ride: ";
	for (int i = 0; i < 3; i++) {
		cout << taxi3.kmPerRide[i] << " ";
	}
	cout << endl;
	cout << "No Of Rides: " << taxi3.noRides << endl;
	cout << "NO UBER TAXIES: " << taxi3.NO_UBER_TAXIES << endl;

	cout << endl;
	cout << "Req. 5: " << endl;
	
	Taxi taxi4(231, TaxiType::UBER, 3.5);
	cout << "Last Destination: " << taxi4.taxiId << endl;
	cout << "Taxi Type: " << taxi4.type << endl;
	cout << "Price Per Km: " << taxi4.pricePerKm << endl;
	cout << "Last Destination: " << taxi4.lastDestination << endl;
	cout << "NO UBER TAXIES: " << taxi4.NO_UBER_TAXIES << endl;

	cout << endl;

	int records2[] = { 3, 5, 2, 10 };

	Taxi taxi5(231, TaxiType::UBER, 3.5, records2, 4);
	cout << "Last Destination: " << taxi5.taxiId << endl;
	cout << "Taxi Type: " << taxi5.type << endl;
	cout << "Price Per Km: " << taxi5.pricePerKm << endl;
	cout << "Last Destination: " << taxi5.lastDestination << endl;
	cout << "Km Per Ride: ";
	for (int i = 0; i < 4; i++) {
		cout << taxi5.kmPerRide[i] << " ";
	}
	cout << endl;
	cout << "No Of Rides: " << taxi5.noRides << endl;
	cout << "NO UBER TAXIES: " << taxi5.NO_UBER_TAXIES << endl;

	cout << endl;

	Taxi taxi6(231, TaxiType::CLASSIC, 3.5);
	cout << "Last Destination: " << taxi6.taxiId << endl;
	cout << "Taxi Type: " << taxi6.type << endl;
	cout << "Price Per Km: " << taxi6.pricePerKm << endl;
	cout << "Last Destination: " << taxi6.lastDestination << endl;
	cout << "NO UBER TAXIES: " << taxi6.NO_UBER_TAXIES << endl;
	cout << "Total Revenue: " << taxi6.getTotalRevenue() << endl;

	cout << endl;
	cout << "R8: = operator taxiEQL = taxi3: " << endl;

	cout << "taxiEQL: " << endl;
	Taxi taxiEQL;
	taxiEQL = taxi3;
	cout << "ID: " << taxiEQL.taxiId << endl;
	cout << "Taxi Type: " << taxiEQL.type << endl;
	cout << "Price Per Km: " << taxiEQL.pricePerKm << endl;
	cout << "Last Destination: " << taxiEQL.lastDestination << endl;
	cout << "Km Per Ride: ";
	for (int i = 0; i < 3; i++) {
		cout << taxiEQL.kmPerRide[i] << " ";
	}
	cout << endl;
	cout << "No Of Rides: " << taxiEQL.noRides << endl;
	cout << "NO UBER TAXIES: " << taxiEQL.NO_UBER_TAXIES << endl;
	cout << "Total Revenue: " << taxiEQL.getTotalRevenue() << endl;

	cout << endl;

	cout << "taxi3: " << endl;
	cout << "ID: " << taxi3.taxiId << endl;
	cout << "Taxi Type: " << taxi3.type << endl;
	cout << "Price Per Km: " << taxi3.pricePerKm << endl;
	cout << "Last Destination: " << taxi3.lastDestination << endl;
	cout << "Km Per Ride: ";
	for (int i = 0; i < 3; i++) {
		cout << taxi3.kmPerRide[i] << " ";
	}
	cout << endl;
	cout << "No Of Rides: " << taxi3.noRides << endl;
	cout << "NO UBER TAXIES: " << taxi3.NO_UBER_TAXIES << endl;
	cout << "Total Revenue: " << taxi3.getTotalRevenue() << endl; 

	cout << endl;
	Taxi vechicles[] = {taxi3, taxiEQL};
	cout << "Total Revenue for the Fleet: " << Taxi::computeFleetValue(vechicles, 2) << endl;

	cout << endl << endl << endl;
	cout << "Operatori: " << endl << endl;
	cout << "<<: " << endl;

	cout << taxi3;
	
	cout << endl << endl;
	cout << ">>: " << endl;
	cin >> taxi;
	cout << taxi;

	cout << endl << endl;
	cout << "taxi+20: " << endl;
	taxi3 = taxi3 + 20;
	cout << taxi3;

	cout << endl << endl;
	cout << "15+taxi: " << endl;
	taxi3 = 15 + taxi3;
	cout << taxi3;

	cout << endl << endl;
	cout << "taxi*=2: " << endl;
	taxi3 *= 2;
	cout << taxi3;

	cout << endl << endl;
	cout << "Taxi copy = taxi++: " << endl;
	Taxi copy = taxi3++;
	cout << "Copie: " << endl;
	cout << copy;
	cout << "Original: " << endl;
	cout << taxi3;

	cout << endl << endl;
	cout << "Taxi copy = ++taxi: " << endl;
	Taxi othercopy = ++taxi3;
	cout << "Copie: " << endl;
	cout << othercopy;
	cout << "Original: " << endl;
	cout << taxi3;

	cout << endl << endl;
	cout << "partialRevenue = taxi(1, 3): " << endl;
	float partialRevenue = taxi3(1, 3);
	cout << partialRevenue << endl;

	cout << endl << endl;
	cout << "int secondRide = taxi3[1]: " << endl;
	int secondRide = taxi3[1];
	cout << secondRide << endl;

	cout << endl << endl;
	cout << "taxi3[1] = 5: " << endl;
	taxi3[1] = 5;
	cout << taxi3;

	return 0;
}