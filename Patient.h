#pragma once



#include <fstream>
#include "User.h"
#include "Appointment.h"
#include "Gynecologist.h"
#include "Dermatologist.h"
#include "Oncologist.h"
#include "Orthopedic.h"

class Patient: public User {
private:
	int PatientID;
	int height;
	int weight;
	char bloodType[5];
	char contact[15];
	char address[50];
	int NoOfAppointments;
	Appointment* appointments;
public:

	Patient(): User() {
		PatientID = 0;
		height = 0;
		weight = 0;
		bloodType[0] = '\0';
		contact[0] = '\0';
		address[0] = '\0';
		NoOfAppointments = 0;
		appointments = nullptr;
	}
	void setAge() {

		system("CLS");

		cout << endl << "Enter Age: ";
		cin >> age;

		updatePatient();

		cout << "Age Updated Successfully!!" << endl;

		system("PAUSE");

	}
	void setHeight() {

		system("CLS");

		cout << endl << "Enter Height: ";
		cin >> height;

		updatePatient();

		cout << "Height Updated Successfully!!" << endl;

		system("PAUSE");

	}
	void setWeight() {

		system("CLS");

		cout << endl << "Enter Weight: ";
		cin >> weight;

		updatePatient();

		cout << "Weight Updated Successfully!!" << endl;

		system("PAUSE");

	}void setContact() {

		system("CLS");

		cout << endl << "Enter Contact Number: ";
		cin.ignore();
		cin.get(contact, 15);

		updatePatient();

		cout << "Contact Updated Successfully!!" << endl;

		system("PAUSE");

	}void setAddress() {

		system("CLS");

		cout << endl << "Enter Address: ";
		cin.ignore();
		cin.get(address, 50);

		updatePatient();

		cout << "Patient's Address Updated Successfully!!" << endl;

		system("PAUSE");

	}

	void Register() {
		PatientID = setID();
		
		string input;
		User::Register();

		cout << endl << "Enter height: ";
		cin >> height;

		cout << endl << "Enter weight: ";
		cin >> weight;

		cout << endl << "Enter bloodType: ";
		cin.ignore();
		cin.get(bloodType, 5);

		cout << endl << "Enter Contact No.: ";
		cin.ignore();
		cin.get(contact, 15);

		cout << endl << "Enter Address: ";
		cin.ignore();
		getline(cin, input);
		strcpy_s(address, input.c_str());

		cout << "Patient has been Registered with Automatic ID generator: " << PatientID << endl;

		system("PAUSE");
		system("CLS");

		writePatient("Patients", *this);
		

	}
	
	int setID() {
		int count = 0;

		Patient p;

		ifstream fin("Patients", ios::binary | ios::app);

		while (fin.read((char*)&p, sizeof(p))) {
			count++;
		}

		fin.close();

		return count+1;
	}

	void login() {

		bool found = false;

		while (!found) {

			User::login();
			readPatient("Patients", found);

			if (!found)
				system("CLS");
				cout << "Invalid Credentials!!";

		}
	}

	void resetPassword() {

		Patient p;
		string pass;
		fstream f("Patients", ios::in | ios::out | ios::binary);

		//system("PAUSE");

		while (f.read((char*)&p, sizeof(p))) {


			//cout << p.PatientID << " == " << PatientID << endl;

			if (p.PatientID == PatientID) {

				while (1) {

					cout << endl << "Enter Previous password: ";
					cin.ignore();
					getline(cin, pass);
					if (pass == "0")
						break;

					//cout << password << " == " << pass << endl;
					//cout << userName << endl;
					//system("PAUSE");
					if (!strcmp(pass.c_str(), password)) {
						p.setpassword();
						break;
					}
					else {
						system("CLS");
						cout << "Password dont match please try again and press 0 to go back!" << endl;
					}
				}

				int a = f.tellg();
				int s = sizeof(Patient);
				f.seekp(a - s, ios::beg);

				f.write((char*)&p, sizeof(p));
				break;


			}
		}

		f.close();

		system("PAUSE");
	}

	void Details() {

		system("CLS");

		cout << endl << endl << "-------- " << name << " - ID: "<< PatientID << " --------" << endl
			<< "CNIC: " << cnic << endl
			<< "Email: " << email << endl
			<< "Age: " << age << "  Blood Type: " << bloodType << endl
			<< "Username: " << userName << endl
			<< "Height: " << height << " Weight: " << weight << endl
			<< "Address: " << address << endl;

		cout << endl << "Press Enter key to go back!";
		
		system("PAUSE");
	}

	void writePatient(string fileName, Patient patient) {


		ofstream fout(fileName, ios::binary | ios::app);
		fout.write((char*)&patient, sizeof(patient));
		fout.close();
	}

	void readPatient(string file_name, bool& found) 

	{
		Patient p;

		ifstream fin(file_name, ios::binary | ios::app);

		while (fin.read((char*)&p, sizeof(p))) {

			

			//p.Details();
			//cout << p.getPassword() << endl;
			if (!strcmp(userName, p.userName) && !strcmp(password, p.password)) {
				//cout << "Hello: " << endl;
				strcpy_s(this->email, p.email);
				strcpy_s(this->name, p.name);
				strcpy_s(this->cnic, p.cnic);
				strcpy_s(this->bloodType, p.bloodType);
				strcpy_s(this->contact, p.contact);
				strcpy_s(this->address, p.address);

				//cout << name << " == " << p.name << endl;
				
				age = p.age;
				height = p.height;
				weight = p.weight;
				PatientID = p.PatientID;


				readAppointments(userName);
				found = true;
			}
		}

		

		fin.close();

	}
	
	void displayAppointments() {


		readAppointments(userName);

		system("CLS");

		for (int i = 0; i < NoOfAppointments; i++) {
			cout << endl << "------ Appointment " << i + 1 << " -------" << endl << endl;
			appointments[i].display();
		}

		system("PAUSE");

	}

	void readAppointments(char* patientUN) {
		
		Appointment app;
		int count = 0;
		ifstream fin("Appointments", ios::binary | ios::app);

		while (fin.read((char*)&app, sizeof(app))) {
			if (!strcmp(app.getPatientUN(), patientUN))
				count++;
		}
		fin.close();

		ifstream fin1("Appointments", ios::binary | ios::app);
		appointments = new Appointment[count];

		count = 0;
		while (fin1.read((char*)&app, sizeof(app))) {
			if (!strcmp(app.getPatientUN(), patientUN))
				appointments[count++] = app;
		}
		NoOfAppointments = count;
		fin1.close();
	}

	~Patient(){
		delete[] appointments;
	}

	void displayDoctors() {

		system("CLS");

		int choice;

		while (1) {
			
			

			cout << endl << endl << "~~ Search Doctor ~~"
				<< "1. All Doctors" << endl
				<< "2. Location (city)" << endl
				<< "3. Hospital" << endl
				<< "4. Specilizition" << endl
				<< "0. To go back to Main menu" << endl << endl;
			cout << "Enter Choice: ";
			cin >> choice;

			if (choice == 0)
				return;
			else if (choice < 0 || choice > 4) {
				system("CLS");
				cout << endl << endl << "Invalid Choice!!" << endl;
				continue;
			} else 
				break;

		}

		Gynecologist gyne;
		Orthopedic Ortho;
		Oncologist Oncolo;
		Dermatlogist Derma;
		Doctor d;

		char input[50];

		switch (choice) {
		case 1:
			cout << "--------------------------------------------" << endl;
			cout << "             Gynecologist" << endl;
			cout << "--------------------------------------------" << endl;
			readDoctors("Gynecologist", gyne);
			cout << endl << endl;
			cout << "--------------------------------------------" << endl;
			cout << "             Orthopedic" << endl;
			cout << "--------------------------------------------" << endl;
			readDoctors("Orthopedic", Ortho);
			cout << endl << endl;
			cout << "--------------------------------------------" << endl;
			cout << "             Oncologist" << endl;
			cout << "--------------------------------------------" << endl;
			readDoctors("Oncologist", Oncolo);
			cout << endl << endl;
			cout << "--------------------------------------------" << endl;
			cout << "             Dermatlogist" << endl;
			cout << "--------------------------------------------" << endl;
			readDoctors("Dermatlogist", Derma);
			break;
		case 2:

			system("CLS");

			cout << "Location(city): ";
			cin.ignore();
			cin.get(input, 50);

			cout << "--------------------------------------------" << endl;
			cout << "             Gynecologist" << endl;
			cout << "--------------------------------------------" << endl;
			displayDoctorLocation("Gynecologist", input, gyne);
			cout << endl << endl;
			cout << "--------------------------------------------" << endl;
			cout << "             Orthopedic" << endl;
			cout << "--------------------------------------------" << endl;
			displayDoctorLocation("Orthopedic", input, Ortho);
			cout << endl << endl;
			cout << "--------------------------------------------" << endl;
			cout << "             Oncologist" << endl;
			cout << "--------------------------------------------" << endl;
			displayDoctorLocation("Oncologist", input, Oncolo);
			cout << endl << endl;
			cout << "--------------------------------------------" << endl;
			cout << "             Dermatlogist" << endl;
			cout << "--------------------------------------------" << endl;
			displayDoctorLocation("Dermatlogist", input, Derma);

			break;
		case 3:
			system("CLS");

			cout << "Hospital: ";
			cin.ignore();
			cin.get(input, 50);

			cout << "--------------------------------------------" << endl;
			cout << "             Gynecologist" << endl;
			cout << "--------------------------------------------" << endl;
			displayDoctorHospital("Gynecologist", input, gyne);
			cout << endl << endl;
			cout << "--------------------------------------------" << endl;
			cout << "             Orthopedic" << endl;
			cout << "--------------------------------------------" << endl;
			displayDoctorHospital("Orthopedic", input, Ortho);
			cout << endl << endl;
			cout << "--------------------------------------------" << endl;
			cout << "             Oncologist" << endl;
			cout << "--------------------------------------------" << endl;
			displayDoctorHospital("Oncologist", input, Oncolo);
			cout << endl << endl;
			cout << "--------------------------------------------" << endl;
			cout << "             Dermatlogist" << endl;
			cout << "--------------------------------------------" << endl;
			displayDoctorHospital("Dermatlogist", input, Derma);

			break;
		case 4:

			system("CLS");
	

			while (1) {

				cout << endl << "1.Gynecologist " << endl << "2.Orthopedic" << endl << "3.Oncologist" << endl << "4.Dermatologist" << endl << "0. To go back to Main menu" << endl << endl;;
				cout << "Enter Your choice: " << endl;
				cin >> choice;

				if (choice == 0)
					return;
				else if (choice < 0 || choice > 4) {
					system("CLS");
					cout << endl << endl << "Invalid Choice!!" << endl;
					continue;
				}
				else
					break;

			}

			switch (choice) {
			case 1:
				cout << "--------------------------------------------" << endl;
				cout << "             Gynecologist" << endl;
				cout << "--------------------------------------------" << endl;
				readDoctors("Gynecologist", gyne);
				cout << endl << endl;
				break;
			case 2:
				cout << "--------------------------------------------" << endl;
				cout << "             Orthopedic" << endl;
				cout << "--------------------------------------------" << endl;
				readDoctors("Orthopedic", Ortho);
				cout << endl << endl;
				break;
			case 3:
				cout << "--------------------------------------------" << endl;
				cout << "             Oncologist" << endl;
				cout << "--------------------------------------------" << endl;
				readDoctors("Oncologist", Oncolo);
				cout << endl << endl;
				break;
			case 4:
				cout << "--------------------------------------------" << endl;
				cout << "             Dermatlogist" << endl;
				cout << "--------------------------------------------" << endl;
				readDoctors("Dermatlogist", Derma);
			}
		}

		

		cout << endl << endl;
		//system("PAUSE");
	}

	void feedback() {

		Feedback F;

		

		int choice;

		while (1) {

			cout << endl << endl << "1. To View Detailed Feedback press." << endl
				<< "2. To Give Feedback." << endl
				<< "0. To Go back to Main Menu." << endl << endl;
			cout << "Enter Choice: ";
			cin >> choice;

			if (choice == 0)
				break;
			else if (choice < 0 || choice > 2)
				continue;

			int docID,  FBID;

			cout << endl << endl << "Enter Doctor ID for which you want to view/give feedback: ";
			cin >> docID;

			switch (choice) {
			case 1: 
				F.displayFeedbacks(docID);

				cout << endl << endl << "1. To reply to a review Enter the review Number." << endl
					<< "0. To go back to Main menu." << endl;

				cout << "Enter Choice: ";
				cin >> choice;

				if (choice == 1) {
					system("CLS");

					F.displayFeedbacks(docID);

					cout << "Enter Feedback Number you want to reply to or 0 to go back to main menu: ";
					cin >> FBID;

					if (FBID != 0) {
						F.setReply(docID, FBID);
					}

				}

				break;
			case 2:
				F.setFeedback(docID);
				break;
			}

			if (choice == 0)
				break;

			system("CLS");
		}
		

	}
	template <class T> void displayDoctorHospital(string file_name, char* hospital, T t)
	{


		ifstream fin(file_name, ios::binary | ios::app);

		while (fin.read((char*)&t, sizeof(t))) {
			if (!strcmp(t.getHospital(), hospital))
				t.details();
		}

		fin.close();

	}template <class T> void displayDoctorLocation(string file_name, char* location, T t)
	{


		ifstream fin(file_name, ios::binary | ios::app);

		while (fin.read((char*)&t, sizeof(t))) {
			if (!strcmp(t.getLocation(), location))
				t.details();
		}

		fin.close();

	}
	template <class T> void readDoctors(string file_name, T t)
	{


		ifstream fin(file_name, ios::binary | ios::app);

		while (fin.read((char*)&t, sizeof(t))) {
			t.details();
			
		}

		fin.close();

	}
	void paymentMenu() {

		int choice;
		int appointmentID;
		do {

			cout << endl << endl << "1. To Check Payment Details" << endl;
			cout << "2. To Pay using your prefered mode of payment. " << endl;
			cout << "Press 0 to go back" << endl << endl;
			cin >> choice;

			if (choice == 0)
				break;
			else if (choice == 1 || choice == 2) {
				system("CLS");

				cout << "Press 0 to go back" << endl << endl;
				cout << "Enter Appointment ID : ";
				cin >> appointmentID;

				if (appointmentID == 0)
					continue;

				Appointment app;

				bool found = false;

				for (int i = 0; i < NoOfAppointments; i++)
					if (appointmentID == appointments[i].getAppID()) {
						found = true;
						app = appointments[i];
					}

				if (!found) {
					cout << endl << "Appointment With this ID not Found!!" << endl << endl;
					continue;
				}

				switch (choice) {
				case 1:
					app.getPayment()->details();
					system("PAUSE");
					break;
				case 2:
					app.getPayment()->setPayment(app.getMode()->calCharges());
					app.updateAppointment();
					break;
				}
			}

		} while (choice != 0 || choice != 1 || choice != 2);
	}





	void updatePatient() {

		Patient p;

		fstream f("Patients", ios::out | ios::in | ios::binary);

		while (f.read((char*)&p, sizeof(p))) {
			//app.display();
			if (p.PatientID == PatientID) {

				//docSch.display();
				int a = f.tellg();
				int s = sizeof(Feedback);
				f.seekp(a - s, ios::beg);
				//app.display();
				system("PAUSE");
				f.write((char*)&*this, sizeof(*this));
				break;

			}

		}
		f.close();
	}
};



