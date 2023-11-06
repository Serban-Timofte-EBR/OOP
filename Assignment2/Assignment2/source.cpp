#include <iostream>
#include <string>
using namespace std;

class VehicleException {

};

enum VehicleType {petrol = 5, hybrid = 10, electric = 15};

class Vehicle {

	//Requirement 1. Set the default values for the class attributes.For brand use "-"
public:
	string brand = "-";
	char* model = nullptr;
	bool hasBattery = false;
	double price = 0.0;

	static int NO_VEHICLES;
	const static int LICENSE_MIN_LENGTH = 4;

	char licensePlatesNumber[10] = " ";

	//Requirement 2. Modify the default constructor of the Vehicle class defined above this will initialize brand with "Unknown", modelul with "Unknown"
	//hasBattery with false and price with 7000
	char* getModel() {
		if (this->model == nullptr) { return nullptr; }

		char* copy = new char[strlen(this->model) + 1];
		strcpy_s(copy, strlen(this->model) + 1, this->model);
		return copy;
	}

	void set_model_unknown() {
		delete[] this->model;
		this->model = new char[strlen("Unknown") + 1];
		strcpy_s(this->model, strlen("Unknown") + 1, "Unknown");
	}

	Vehicle(string brand = "Unknown", bool hasBattery = false, double price = 700) {
		this->brand = brand;
		set_model_unknown();
		this->hasBattery = hasBattery;
		this->price = price;
	}

	//Requirement 3. Modify the constructor with 3 parameters: brand, model, price this will initialize the 3 attributes with the received values
	void set_model(const char* vector) {
		delete[] model;
		this->model = new char[strlen(vector) + 1];
		strcpy_s(this->model, strlen(vector) + 1, vector);
	}

	Vehicle(string brand, const char* model, double price) {
		this->brand = brand;
		set_model(model);
		this->price = price;
	}

	/*Requirement 4. The function below return a variable of type enum (VehicleType, the enum defined above) modify the enum so it can have only three posible values
	Those are: 5 - petrol, 10 - hybrid, 15 - electric the function receives one parameter which is a string from the ones above
	("petrol", "hybrid", "electric") and returns the enum value*/

	static VehicleType getStandardType(string type) {
		if (type == "petrol") { return VehicleType::petrol; }
		else if (type == "hybrid") { return VehicleType::hybrid; }
		else if (type == "electric") { return VehicleType::electric; }
		return VehicleType::petrol;
	}

	/* Requirement 5. The function below return a variable of type enum (VehicleType, the enum defined above)
	Modify the enum so it can have only three posible values: 5 - PETROL, 10 - HYBRID, 15 - ELECTRIC
	The function must return ELECTRIC if the vehicle has battery. Otherwise must return PETROL
	*/
	VehicleType getType()
	{
		if (this->hasBattery) { return VehicleType::electric; }
		return VehicleType::petrol;
	}

	/*Requirement 6. Modify the applyDiscount method in order to give a discount from the price
	the discount is a percentage between 1% and 50%
	the function should modify the price with the value obtained after the discount is applied
	the function shoud throw an exception for values outside [1,50]	with throw VehicleException();
	*/

	void applyDiscount(int percent)
	{
		double discount = (percent / 100.0) * this->price;
		this->price -= discount;
	}

	/*Requirement 7. Add to the class a new attribute called 'licensePlatesNumber'
	this is a statically allocated char array with the maximum length 9
	Modify the methods setLicensePlatesNumber and getLicensePlatesNumber
	in such a manner that they will modify (first one) and return (second one) the value of this field
	*/

	void setLicensePlatesNumber(const char* licensePlates)
	{
		if (licensePlates == nullptr) { throw exception("Invalid Input for License Plate"); }
		strcpy_s(this->licensePlatesNumber, strlen(licensePlates) + 1, licensePlates);
	}

	char* getLicensePlatesNumber() {
		if (this->licensePlatesNumber == nullptr) { return nullptr; }
		char* copy = new char[strlen(this->licensePlatesNumber) + 1];
		strcpy_s(copy, strlen(this->licensePlatesNumber) + 1, this->licensePlatesNumber);
		return copy;
	}

	/*Requirement 8. Implement setModel in order to change the vehicle model
	The method should not do shallow copy
	The method should not generate memory leaks
	The method should validate that the model length is greater or equal than LICENSE_MIN_LENGTH. Otherwise throws exception with throw VehicleException();
	The method should validate that the model name starts with a capital letter (A - Z). Otherwise throws exception with throw VehicleException();
	*/

	void setModel(const char* model) {
		if(strlen(model) < this->LICENSE_MIN_LENGTH && !isupper(model[0])) {
			throw VehicleException();
		}
		delete[] this->model;
		char* copy = new char[strlen(model) + 1];
		strcpy_s(copy, strlen(model) + 1, model);
		this->model = copy;
	}

	/*Requirement 10. Add a desctructor to the class that will decrement NO_VEHICLES each time a vehicle is detroyed*/
	/*Already implemented in Requirement 2*/


};

//11. The function below receive as arguments an array of cars and its number of elements
//compute and return the todal value of the vehicles by adding the prices (pret) of all the cars from the array
double computeFleetValue(Vehicle vehicles[], int noVehicles)
{
	double sum = 0.0;
	
	for (int i = 0; i < noVehicles; i++) {
		sum += vehicles[i].price;
	}
	return sum;
}

//12. The function below receives as parameters a dinamically allocated array of pointers to Vehicle together with its number of elements
//Return the value of the most expensive car from this array
double getTheMostExpensiveVehicle(Vehicle** vector, int nr_masini)
{
	double maxPrice = 0.0;

	for (int i = 0; i < nr_masini; i++) {
		if (vector[i]->price > maxPrice) { maxPrice = vector[i]->price; }
	}
	return maxPrice;
}

int main() {
	Vehicle test;

	cout << "Brand: " << test.brand << endl;
	cout << "Model: " << test.getModel() << endl;
	cout << "hasBattery: " << test.hasBattery << endl;
	cout << "Price: " << test.price << endl;
	cout << "Electric?: " << test.getType() << endl;

	Vehicle car2("KIA", "123", 100.0);
	cout << "Brand: " << car2.brand << endl;
	cout << "Model: " << car2.getModel() << endl;
	cout << "Price: " << car2.price << endl;
	cout << "VehicleType: " << car2.getStandarType("electric") << endl;
	car2.applyDiscount(10);
	cout << "Price after discount: " << car2.price << endl;
	car2.setLicensePlatesNumber("B01EBR");
	cout << "Plate: " << car2.getLicensePlatesNumber() << endl;
	car2.set_model("OLV");
	cout << "Model: " << car2.getModel() << endl;

	Vehicle vehicles[3];
	vehicles[0] = Vehicle("Bentley", "Mulssene", 1000.0);
	vehicles[1] = Vehicle("Toyota", "Corolla", 150.0);
	vehicles[2] = Vehicle("Honda", "Civic", 140.0);

	double fleetValue = computeFleetValue(vehicles, 3);
	cout << "Total Fleet Value: " << fleetValue << endl;

	const int numVehicles = 3;
	Vehicle* vehicleArray[numVehicles];

	vehicleArray[0] = new Vehicle("Brand1", "Model1", 10000.0);
	vehicleArray[1] = new Vehicle("Brand2", "Model2", 15000.0);
	vehicleArray[2] = new Vehicle("Brand3", "Model3", 12000.0);


	double mostExpensivePrice = getTheMostExpensiveVehicle(vehicleArray, numVehicles);
	cout << "The most expensive vehicle has a price of: " << mostExpensivePrice << endl;



	return 0;
}
