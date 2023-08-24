
#include "Doctor.h"
#include "Gynecologist.h"
#include "Dermatologist.h"
#include "Oncologist.h"
#include "Orthopedic.h"
#include "DocSchedule.h"
#include "Feedback.h"

Doctor::Doctor() : docSch() {
	doctorID = 0;
	rate = 0;
	location[0] = '\0';
	hospital[0] = '\0';
	yearsOfExperience = 0;
	NoOfAppointments = 0;
	NoOfFeedbacks = 0;
	appointments = nullptr;
	feedbacks = nullptr;
}

int Doctor::getID() {
	return doctorID;
}

void Doctor::Register() {

	User::Register();

	doctorID = setID();

	cout << endl << "Enter rate per appointment: ";
cin >> rate;

cout << "Enter Location (City or Specific Area): ";
cin >> location;

cout << "Enter Hospital Name: ";
cin >> hospital;

cout << "Enter Years of Experience: ";
cin >> yearsOfExperience;



cout << "You have been Registered with Automatic ID generator: " << doctorID << endl;

docSch.setSchedule(doctorID);

//docSch.display();

system("PASUE");
}

template <class T> void calculatingID(string fileName, T t, int& count) {

	ifstream fin(fileName, ios::binary | ios::app);

	while (fin.read((char*)&t, sizeof(t))) {
		count++;
	}
	fin.close();
}
DocSchedule Doctor::getSchedule() {
	return docSch;
}
int Doctor::setID() {

	Gynecologist gyne;
	Orthopedic Ortho;
	Oncologist Oncolo;
	Dermatlogist Derma;
	int count = 0;

	calculatingID("Gynecologist", gyne, count);
	calculatingID("Orthopedic", Ortho, count);
	calculatingID("Oncologist", Oncolo, count);
	calculatingID("Dermatlogist", Derma, count);

	return count + 1;
}
void Doctor::login() {

	Gynecologist gyne;
	Orthopedic Ortho;
	Oncologist Oncolo;
	Dermatlogist Derma;
	bool found = false;

	while (!found) {

		User::login();
		readDoctor("Gynecologist", gyne, found);
		readDoctor("Orthopedic", Ortho, found);
		readDoctor("Oncologist", Oncolo, found);
		readDoctor("Dermatlogist", Derma, found);

		system("CLS");
		if (!found)
			cout << "Invalid Credentials!!" << endl << endl;
	}


}
void Doctor::changeSchedule() {


	cout << endl << "WARNING!!!! All Appointments will be lost..." << endl << endl;

	docSch.setSchedule(doctorID);
	docSch.updateSchedule();


}
void Doctor::details() {


	cout << endl << endl << "-------- " << name << " - ID: " << doctorID << " ---------" << endl
		<< "CNIC: " << cnic << endl
		<< "Email: " << email << endl
		<< "Age: " << age << " Rate: " << rate << endl
		<< "Username: " << userName << endl
		<< "Location: " << location << " Hospital: " << hospital << endl
		<< "Year Of Experience: " << yearsOfExperience << endl
		<< "Average Rating: " << calcAverageRating() << " " << setw(int(calcAverageRating())) << endl;

	cout << "------------------------------------------------" << endl;

}
double Doctor::calcAverageRating() {

	readFeedbacks();

	double answer = 0;

	for (int i = 0; i < NoOfFeedbacks;i++) {
		answer += feedbacks[i].getStars();
	}

	return answer / NoOfFeedbacks;

}
template <class T> void Doctor::readDoctor(string file_name, T t, bool &found)
{


	ifstream fin(file_name, ios::binary | ios::app);

	while (fin.read((char*)&t, sizeof(t))) {
		if (!strcmp(userName, t.userName) && !strcmp(password, t.password)) {
			strcpy_s(this->email, t.email);
			strcpy_s(this->name, t.name);
			strcpy_s(this->cnic, t.cnic);
			strcpy_s(this->location, t.location);
			strcpy_s(this->hospital, t.hospital);

			rate = t.rate;
			yearsOfExperience = t.yearsOfExperience;
			doctorID = t.doctorID;
			
			docSch.readSchedule(doctorID);
			found = true;
		}
	}



	fin.close();

}

void Doctor::readFeedbacks() {

	Feedback F;
	int count = 0;
	ifstream fin("Feedback", ios::binary | ios::app);

	while (fin.read((char*)&F, sizeof(F))) {
		if (F.getDocID() == doctorID)
			count++;
	}
	fin.close();

	ifstream fin1("Feedback", ios::binary | ios::app);
	feedbacks = new Feedback[count];

	count = 0;
	while (fin1.read((char*)&F, sizeof(F))) {
		if (F.getDocID() == doctorID)
			feedbacks[count++] = F;
	}
	NoOfFeedbacks = count;
	fin1.close();
}
void Doctor::readAppointments() {

	Appointment app;
	int count = 0;
	ifstream fin("Appointments", ios::binary | ios::app);

	while (fin.read((char*)&app, sizeof(app))) {
		if (app.getdocID() == doctorID)
			count++;
	}
	fin.close();

	ifstream fin1("Appointments", ios::binary | ios::app);
	appointments = new Appointment[count];

	count = 0;
	while (fin1.read((char*)&app, sizeof(app))) {
		if (app.getdocID() == doctorID)
			appointments[count++] = app;
	}
	NoOfAppointments = count;
	fin1.close();
}
void Doctor::paymentMenu() {

	int choice;
	int appointmentID;
	do {

		displayAppointments();

		cout << endl << endl << "1. To change Status of Appointment." << endl;
		cout << "2. To Check Payment Details" << endl;
		cout << "3. To Add fine. " << endl;

		cout << "Press 0 to go back" << endl << endl;
		cin >> choice;

		if (choice == 0)
			break;
		else if (choice == 1 || choice == 2 || choice == 3) {
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

			char statuses[2][20] = { "APPROVED", "COMPLETED" };
			int status;


			switch (choice) {
			case 1:

				cout << "1. Approved" << endl << "2. Completed" << endl;
				cout << "Enter Status (1 or 2): ";
				cin >> status;

				app.setStatus(appointmentID, statuses[status - 1]);

				break;
			case 2:
				app.getPayment()->details();
				system("PAUSE");
				break;
			case 3:
				DateTime currentDate;
				currentDate.input("Current");

				app.getPayment()->fine(app.getAppTime().daysDifference(currentDate));
				app.updateAppointment();
				break;
			}
		}

	} while (choice != 0 || choice != 1 || choice != 2 || choice != 3);
}
void Doctor::displayAppointments() {


	readAppointments();

	system("CLS");

	for (int i = 0; i < NoOfAppointments; i++) {
		cout << endl << "------ Appointment " << i + 1 << " -------" << endl << endl;
		appointments[i].display();
	}

	system("PAUSE");
}
int Doctor::getRate() {
	return rate;
}
Doctor::~Doctor(){
	delete[] appointments;
}

void Doctor::displayFeedbacks(){

	readFeedbacks();

	for (int i = 0; i < NoOfFeedbacks; i++) {
		feedbacks[i].displayfeedback();
	}
}

char* Doctor::getLocation() {
	return location;
}char* Doctor::getHospital() {
	return hospital;
}

void Doctor::setRate() {

	system("CLS");

	cout << endl << "Enter New Rate per appointment: ";
	cin >> rate;


	cout << "Rate Updated Successfully!!";

	system("PAUSE");

}

void Doctor::setLocation() {

	system("CLS");

	cout << endl << "Enter New Location: ";
	cin.ignore();
	cin.get(location, 30);



	cout << "Location Updated Successfully!!";

	system("PAUSE");

}
void Doctor::setHospital() {

	system("CLS");

	cout << endl << "Enter New Hospital: ";
	cin.ignore();
	cin.get(hospital, 50);



	cout << "Hospital Updated Successfully!!";

	system("PAUSE");

}
void Doctor::setYOE() {

	system("CLS");

	cout << endl << "Enter Years Of Experience: ";
	cin >> yearsOfExperience;


	cout << "Years of Experience Updated Successfully!!";

	system("PAUSE");

}

