#include <iostream>
#include <string>
using namespace std;

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

	//Requirement 2. Modify the default constructor of the Vehicle class defined above this will initialize brand with "Unknown", modelul with "Unknown"
	//hasBattery with false and price with 7000
	char* get_model() {
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

	static VehicleType getStandarType(string type) {
		if (type == "petrol") { return (VehicleType)5; }
		else if (type == "hybrid") { return (VehicleType)10; }
		else if (type == "electric") { return (VehicleType)15; }
	}

	/* Requirement 5. The function below return a variable of type enum (VehicleType, the enum defined above)
	Modify the enum so it can have only three posible values: 5 - PETROL, 10 - HYBRID, 15 - ELECTRIC
	The function must return ELECTRIC if the vehicle has battery. Otherwise must return PETROL
	*/
	VehicleType getType()
	{
		if (this->hasBattery) { return (VehicleType)15; }
		return (VehicleType)5;
	}
};

int main() {
	Vehicle test;

	cout << "Brand: " << test.brand << endl;
	cout << "Model: " << test.get_model() << endl;
	cout << "hasBattery: " << test.hasBattery << endl;
	cout << "Price: " << test.price << endl;
	cout << "Electric?: " << test.getType() << endl;

	Vehicle car2("KIA", "123", 123.21);
	cout << "Brand: " << car2.brand << endl;
	cout << "Model: " << car2.get_model() << endl;
	cout << "Price: " << car2.price << endl;
	cout << "VehicleType: " << car2.getStandarType("electric") << endl;

	return 0;
}