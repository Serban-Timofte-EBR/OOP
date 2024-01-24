#pragma once

#include <iostream>
#include <string>
#include <fstream>

using namespace std;


class Grade {
public:
	string course = "*";	//course name | numele cursului
	int value = -1;			//grade value | valoare notei


	//1. implement the Grade default ctor and set course to "" and grade value to 0
	//1. implementati ctorul implicit și setați cursul la "" și valoarea notei la 0
	Grade() : course(""), value(0) {}

	//2. implement the parameters ctor
	//2. implementati ctorul cu parametri
	Grade(string course, int value) {
		this->course = course;
		this->value = value;
	}
};

//class to manage bachelor program data
//clasa pentru a gestiona programul de licenta

class Program {
public:
	string name = "";				//program name | numele programului
	char faculty[50] = "";			//faculty name | numele facultatii
	char* university = nullptr;		//university name | numele universitatii

	void set_faculty(string faculty) {
		strcpy_s(this->faculty, faculty.length() + 1, faculty.c_str());
	}

	void set_university(string university) {
		delete[] this->university;
		this->university = new char[university.length() + 1];
		strcpy_s(this->university, university.length() + 1, university.c_str());
	}

	Program() { }

	//3. implement the parameters ctor
	//3. implementati ctorul cu parametri
	Program(string name, string faculty, string university)
		:name(name) {
		this->set_faculty(faculty);
		this->set_university(university);
	}


	//4. implement the copy ctor
	//4. implementati constructorul de copiere
	Program(const Program& program) {
		this->name = program.name;
		this->set_faculty(program.faculty);
		this->set_university(program.university);
	}

	//5. overload equals
	//5. supraincarcati operatorul =
	Program operator=(const Program& program) {
		if (this == &program) { return *this; }
		this->name = program.name;
		this->set_faculty(program.faculty);
		this->set_university(program.university);
		return *this;
	}

	~Program() {
		delete[] university;
	}
};

//class to manage student data
//clasa pentru a gestiona datele unui student

class Student {

public:
	string name = "";			//student name | numele studentului
	int age = 0;				//student age | varsta studentului
	Program program;			//bachelor program | programul de licenta
	Grade* grades = nullptr;	//grades and their number | notele si numarul lor
	int noGrades = 0;
	bool hasScholarship = false;	//if has scholarship or not | daca are bursa


	Student() {

	}

	Student(string name, int age, string programName, string faculty, string university, bool hasScholarship)
		:name(name), age(age), program(programName, faculty, university), hasScholarship(hasScholarship) {
	}

	~Student() {
		delete[] grades;
	}


	//6. implement the next method that will add a new Grade
	//6. implementați următoarea metodă care va permite adaugarea unei note noi
	void addGrade(string course, int value) {
		Grade* copy = new Grade[this->noGrades + 1];
		for (int i = 0; i < this->noGrades; i++) {
			copy[i] = this->grades[i];
		}
		copy[this->noGrades] = Grade(course, value);

		delete[] this->grades;
		this->grades = copy;
		this->noGrades += 1;
	}

	//7. implement the next method that will read Student data (read Readme.txt) from a binary file
	//7. implementați următoarea metodă care va citi datele unui Student (citește Readme.txt) dintr-un fișier binar
	void deserialize(string fileName) {
		ifstream doc(fileName, ios::binary | ios::in);
		if (!doc.is_open()) {
			cout << "File not opened!" << endl;
			return;
		}

		int lenOfName = 0;
		doc.read((char*)&lenOfName, sizeof(lenOfName));
		char* studentName = new char[lenOfName];
		doc.read(studentName, lenOfName);
		name = string(studentName, lenOfName - 1);  // Exclude the null terminator
		delete[] studentName;

		doc.read((char*)&age, sizeof(age));

		int lenOfProgramName;
		doc.read((char*)&lenOfProgramName, sizeof(lenOfProgramName));
		char* programNameDoc = new char[lenOfProgramName];
		doc.read(programNameDoc, lenOfProgramName);
		program.name = string(programNameDoc, lenOfProgramName - 1);  // Exclude the null terminator
		delete[] programNameDoc;

		doc.read(program.faculty, sizeof(program.faculty));

		int lenOfUnivName = 0;
		doc.read((char*)&lenOfUnivName, sizeof(lenOfUnivName));
		program.university = new char[lenOfUnivName];
		doc.read(program.university, lenOfUnivName);
		program.university[lenOfUnivName - 1] = '\0';  // Ensure null-termination

		doc.read((char*)&hasScholarship, sizeof(hasScholarship));

		doc.read((char*)&noGrades, sizeof(noGrades));
		delete[] grades;  // Clear existing grades if any
		grades = new Grade[noGrades];
		for (int i = 0; i < noGrades; i++) {
			int lenOfCourseName;
			doc.read((char*)&lenOfCourseName, sizeof(lenOfCourseName));
			char* courseName = new char[lenOfCourseName];
			doc.read(courseName, lenOfCourseName);
			grades[i].course = string(courseName, lenOfCourseName - 1);  // Exclude the null terminator
			delete[] courseName;

			doc.read((char*)&grades[i].value, sizeof(grades[i].value));
		}

		doc.close();
	}
};

class StudentList {
public:
	Student* list = nullptr;
	int noStudents = 0;

	StudentList() {	}

	//8. implement the next method that will read Students data (read Readme.txt) from a binary file
	//8. implementați următoarea metodă care va citi datele mai multor Studenti (citește Readme.txt) dintr-un fișier binar
	void deserialize(string fileName) {
		ifstream doc(fileName, ios::binary | ios::in);
		if (!doc.is_open()) {
			cout << "File not opened!" << endl;
			return;
		}

		doc.read((char*)&noStudents, sizeof(noStudents));
		delete[] list;  // Clear existing list if any
		list = new Student[noStudents];

		for (int i = 0; i < noStudents; i++) {
			int lenOfName;
			doc.read((char*)&lenOfName, sizeof(lenOfName));
			char* studentName = new char[lenOfName];
			doc.read(studentName, lenOfName);
			list[i].name = string(studentName, lenOfName - 1);  // Exclude the null terminator
			delete[] studentName;

			doc.read((char*)&list[i].age, sizeof(list[i].age));

			int lenOfProgramName;
			doc.read((char*)&lenOfProgramName, sizeof(lenOfProgramName));
			char* programNameDoc = new char[lenOfProgramName];
			doc.read(programNameDoc, lenOfProgramName);
			list[i].program.name = string(programNameDoc, lenOfProgramName - 1);  // Exclude the null terminator
			delete[] programNameDoc;

			doc.read(list[i].program.faculty, sizeof(list[i].program.faculty));

			int lenOfUnivName;
			doc.read((char*)&lenOfUnivName, sizeof(lenOfUnivName));
			list[i].program.university = new char[lenOfUnivName];
			doc.read(list[i].program.university, lenOfUnivName);
			list[i].program.university[lenOfUnivName - 1] = '\0';  // Ensure null-termination

			doc.read((char*)&list[i].hasScholarship, sizeof(list[i].hasScholarship));

			doc.read((char*)&list[i].noGrades, sizeof(list[i].noGrades));
			delete[] list[i].grades;  // Clear existing grades if any
			list[i].grades = new Grade[list[i].noGrades];
			for (int j = 0; j < list[i].noGrades; j++) {
				int lenOfCourseName;
				doc.read((char*)&lenOfCourseName, sizeof(lenOfCourseName));
				char* courseName = new char[lenOfCourseName];
				doc.read(courseName, lenOfCourseName);
				list[i].grades[j].course = string(courseName, lenOfCourseName - 1);  // Exclude the null terminator
				delete[] courseName;

				doc.read((char*)&list[i].grades[j].value, sizeof(list[i].grades[j].value));
			}
		}

		doc.close();
	}
};