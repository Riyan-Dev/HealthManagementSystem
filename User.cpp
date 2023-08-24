
#include "User.h"
#include "Patient.h"
#include "Gynecologist.h"
#include "Dermatologist.h"
#include "Oncologist.h"
#include "Orthopedic.h"

User::User() {
	userName[0] = '\0';
	password[0] = '\0';
	age = 0 ;
	name[0] = '\0';
	cnic[0] = '\0';
	email[0] = '\0';
}

char* User::getCNIC() {
	return cnic;
}
char* User::getUserName() {
	return userName;
}
char* User::getName() {
	return name;
}
char* User::getPassword() {
	return password;
}

template <typename T> void checkingUsername(string fileName, T t, bool& found, string username) {
	ifstream fin(fileName, ios::binary | ios::app);

	while (fin.read((char*)&t, sizeof(t))) {

		if (!strcmp(username.c_str(), t.getUserName()))
			found = true;

	}

	fin.close();
}

template <typename T> void checkingCNIC(string fileName, T t, bool& found, string cnic) {
	ifstream fin(fileName, ios::binary | ios::app);

	while (fin.read((char*)&t, sizeof(t))) {
		cout << fileName << endl;
		//t.Details();
		cout << cnic << " == " << t.getCNIC() << endl;
		//cout << t.getName();
		//cout << t.getPassword();
		//cout << t.getUserName();
		cout << strcmp(cnic.c_str(), t.getCNIC()) << endl;
		if (!strcmp(cnic.c_str(), t.getCNIC()))
			found = true;

	}

	fin.close();
}



bool User::checkUserName(string username) {

	Patient p;
	Gynecologist gyne;
	Orthopedic Ortho;
	Oncologist Oncolo;
	Dermatlogist Derma;
	bool found = false;

	/*ifstream fin("Patients", ios::binary | ios::app);

	while (fin.read((char*)&p, sizeof(p))) {
		//cout << fileName << endl;
		//p.Details();
		//cout << cnic << " == " << p.getCNIC() << endl;
		//cout << t.getName();
		//cout << t.getPassword();
		//cout << t.getUserName();
		cout << strcmp(username.c_str(), p.getUserName()) << endl;
		if (!strcmp(username.c_str(), p.getUserName()))
			found = true;

	}

	fin.close();*/

	checkingUsername("Patients", p, found, username);
	checkingUsername("Gynecologist", gyne, found, username);
	checkingUsername("Orthopedic", Ortho, found, username);
	checkingUsername("Oncologist", Oncolo, found, username);
	checkingUsername("Dermatlogist", Derma, found, username);

	return found;
}



bool User::checkCNIC(string cnic) {

	Patient p;
	Gynecologist gyne;
	Orthopedic Ortho;
	Oncologist Oncolo;
	Dermatlogist Derma;
	bool found = false;

	/*ifstream fin("Patients", ios::binary | ios::app);

	while (fin.read((char*)&p, sizeof(p))) {
		//cout << fileName << endl;
		p.Details();
		cout << cnic << " == " << p.getCNIC() << endl;
		//cout << t.getName();
		//cout << t.getPassword();
		//cout << t.getUserName();
		cout << strcmp(cnic.c_str(), p.getCNIC()) << endl;
		if (!strcmp(cnic.c_str(), p.getCNIC()))
			found = true;

	}

	fin.close();*/
	checkingCNIC("Patients", p, found, cnic);
	checkingCNIC("Gynecologist", gyne, found, cnic);
	checkingCNIC("Orthopedic", Ortho, found, cnic);
	checkingCNIC("Oncologist", Oncolo, found, cnic);
	checkingCNIC("Dermatlogist", Derma, found, cnic);

	return found;
}

void User::Register() {

	cout << endl << endl << "Registration Form" << endl;
	string input;
	cout << endl << endl << "Enter Name: ";
	cin.ignore();
	getline(cin, input);
	strcpy_s(name, input.c_str());

	cout << name << endl;


	while (1) {
		cout << endl << "Enter CNIC (XXXXX-XXXXXXX-X): ";
		getline(cin, input);
		strcpy_s(cnic, input.c_str());

		if (strlen(string(cnic).c_str()) != 15) {
			cout << "Invalid Cnic!!";
			continue;
		}
		
		if (checkCNIC(cnic)) {
			

			cout << "CNIC Already exisits!!" << endl << endl;
			continue;
		}

		break;
	}

	setpassword();

	while (1) {
		cout << endl << "Enter UserName: ";
		getline(cin, input);
		strcpy_s(userName, input.c_str());


		if (checkUserName(userName)) {
			cout << "UserName Already exisits!!" << endl << endl;
			continue;
		}

		break;
	}

	

	cout << endl << "Enter Email: ";
	cin.ignore();
	cin.get(email, 30);

	cout << endl << "Enter Age: ";
	cin >> age;


}
void User::setpassword() {
	string pass;
	string input;

	while (1) {
		cout << endl << "Enter Password: ";
		getline(cin, input);
		strcpy_s(password, input.c_str());
		cout << endl << "Rernter Password: ";
		getline(cin, pass);

		cout << password << " == " << pass << endl;

		if (strcmp(password, pass.c_str())) {
			cout << "Password don't match!!" << endl;
			continue;
		}

		break;
	}
}
void User::login() {

	cout << endl << endl << "Login Form" << endl;

	cout << endl << "Enter UserName: ";
	cin >> userName;

	cout << endl << "Enter Password: ";
	cin >> password;
}


