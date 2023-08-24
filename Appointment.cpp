
#include <iomanip>
#include "Appointment.h"
#include "Gynecologist.h"
#include "Dermatologist.h"
#include "Oncologist.h"
#include "Orthopedic.h"
#include "DocSchedule.h"


template <class T> void Appointment::validatingID(string filename, T t, bool& found, int id) {
	ifstream fin(filename, ios::binary | ios::app);

	while (fin.read((char*)&t, sizeof(t))) {

		if (id == t.getID()) {
			cout << "Getting Name: " << t.getName() << endl;
			strcpy_s(doctorCNIC, t.getCNIC());
			strcpy_s(doctorName, t.getName());
			cout << "Getting Name: " << doctorName << endl;
			mode->setRate(t.getRate());
			found = true;
		}

	}

	fin.close();
}

bool Appointment::validateDocID(int id) {

	Gynecologist gyne;
	Orthopedic Ortho;
	Oncologist Oncolo;
	Dermatlogist Derma;
	bool found = false;

	validatingID("Gynecologist", gyne, found, id);
	validatingID("Orthopedic", Ortho, found, id);
	validatingID("Oncologist", Oncolo, found, id);
	validatingID("Dermatlogist", Derma, found, id);


	if (found) {

		Appointment app;
		
		ifstream fin("Appointments", ios::binary | ios::app);

		while (fin.read((char*)&app, sizeof(app))) {
			char dummy[] = "PENDING";
			if ((!strcmp(app.getPatientUN(), PatientUN)) && (id == app.doctorID && !strcmp(app.status, dummy)))
				found = false;
				
		}
		fin.close();
	}

	cout << doctorName << endl;
	return found;

}

void Appointment::setAppointment(char* patientUN, char* patientCNIC, char* patientName) {


	DocSchedule docSch;


	appointmentID = setID();

	do {
		cout << endl << endl << "--- Mode of Appointment ---" << endl
			<< "1. Video Consultation" << endl
			<< "2. In person meeting" << endl
			<< "Choose Medium of Appointment (1-2): ";
		cin >> choice1;

		if (choice1 > 2 || choice1 <= 0) {
			system("CLS");
			cout << endl << "Invalid Option!!, Please Try Again...." << endl << endl;
		}

	} while (choice1 > 2 || choice1 <= 0);


	assignMode(choice1);

	strcpy_s(PatientUN, patientUN);
	strcpy_s(this->patientName, patientName);
	strcpy_s(this->patientCNIC, patientCNIC);

	while (1) {

		cout << "Enter DoctorID: ";
		cin >> doctorID;
		

		if (!validateDocID(doctorID)) {
			system("CLS");

			cout << endl << "Doctor ID do not exist or Appointment Already booked with this doctor!!" << endl << endl;
			continue;
		}

		break;
	}

	docSch.readSchedule(doctorID);

	docSch.display();

	cout << endl << endl << "Charges per appointment: " << mode->getRate() << endl << endl;

	//display();
	
	currentTime.input("Current");

	while (1) {
		time.input("Appointment");
		//cout << "Start Time: " << docSch.getStartTime() << endl
			//<< "EndTime: " << docSch.getEndTime() << endl
			//<< "availability: " << docSch.getAvailability(time.getHour(), time.daysDifference(currentTime)) << endl
			//<< "First Condition: " << !(docSch.getStartTime() <= time.getHour() && docSch.getEndTime() > time.getHour()) << endl
			//<< "days Difference: " << currentTime.daysDifference(time) << endl;
		if (!(docSch.getStartTime() <= time.getHour() && docSch.getEndTime() > time.getHour()) || docSch.getAvailability(time.getHour(), currentTime.daysDifference(time))) {
			cout << "Invalid Appointment Time, Either Doctor not available or already booked..." << endl << endl;
			continue;
		}
			
		break;
	}

	docSch.setAvailability(time.getHour(), currentTime.daysDifference(time));

	string stat = "PENDING";
	strcpy_s(status, stat.c_str());

	
	do {
		cout << endl << endl << "--- Method of Payment ---" << endl
			<< "1. JazzCash" << endl
			<< "2. EasyPaisa" << endl
			<< "3. Paypak" << endl
			<< "4. UnionPay" << endl
			<< "Choose payment method (1-4): ";
		cin >> choice2;

		if (choice2 > 4 || choice2 <= 0) {
			system("CLS");
			cout << endl << "Invalid Option!!, Please Try Again...." << endl << endl;
		}

	} while (choice2 > 4 || choice2 <= 0);


	assignPayment(choice2);

	writeAppointment();

	cout << endl << "Appointment have been set ith automated serial Number: " << appointmentID << " Remember it for future Refrence!.." << endl << endl;
	system("PAUSE");
}

void Appointment::assignMode(int choice) {
	switch (choice) {
	case 1: mode = &VC; break;
	case 2: mode = &IP; break;
	}
}
void Appointment::assignPayment(int choice) {
	switch (choice) {
	case 1: payment = &JC; break;
	case 2: payment = &EP; break;
	case 3: payment = &PP; break;
	case 4: payment = &UP; break;
	}
}

void Appointment::writeAppointment() {

	ofstream fout("Appointments", ios::binary | ios::app);
	fout.write((char*)&*this, sizeof(*this));
	fout.close();

}

Appointment::Appointment() {
	appointmentID = 0;
	status[0] = '\0';
	PatientUN[0] = '\0';
	patientName[0] = '\0';
	patientCNIC[0] = '\0';
	doctorCNIC[0] = '\0';
	doctorName[0] = '\0';
	doctorID = 0;
	payment = nullptr;
	mode = nullptr;
	choice1 = 0;
	choice2 = 0;
}

char* Appointment::getPatientUN() {
	return PatientUN;
}

int Appointment::getdocID() const {
	return doctorID;
}

void Appointment::operator=(Appointment& app) {


	appointmentID = app.appointmentID;
	strcpy_s(status, app.status);
	strcpy_s(PatientUN, app.PatientUN);
	strcpy_s(patientName, app.patientName);
	strcpy_s(patientCNIC, app.patientCNIC);
	strcpy_s(doctorCNIC, app.doctorCNIC);
	strcpy_s(doctorName, app.doctorName);
	doctorID = app.doctorID;
	time = app.time;
	currentTime = app.currentTime;

	choice1 = app.choice1;
	choice2 = app.choice2;

	JC = app.JC;
	EP = app.EP;
	PP = app.PP;
	UP = app.UP;
	assignPayment(choice2);

	VC = app.VC;
	IP = app.IP;
	assignMode(choice1);

}

int Appointment::setID() {
	int count = 0;

	Appointment A;

	ifstream fin("Appointments", ios::binary | ios::app);

	while (fin.read((char*)&A, sizeof(A))) {
		count++;
	}

	fin.close();

	return count + 1;
}

void Appointment::display() {
	
	cout << left << " ----- Appointment Serial No. : " << appointmentID << " -----" << endl;
	cout  << "Patient Name: " << setw(20) << patientName << "Patient CNIC: " << setw(20) << patientCNIC << endl;
	cout  << "Doctor Name: " << setw(21) << doctorName << "Doctor CNIC: " << setw(20) << doctorCNIC << endl;
	time.display();
	cout  << "Status " << status << endl;

}

void Appointment::updateAppointment() {

	Appointment app;

	fstream f("Appointments", ios::out | ios::in | ios::binary);

	while (f.read((char*)&app, sizeof(app))) {
		//app.display();
		if (app.appointmentID == appointmentID) {

			app = *this;
			//docSch.display();
			int a = f.tellg();
			int s = sizeof(Appointment);
			f.seekp(a - s, ios::beg);
			//app.display();
			system("PAUSE");
			f.write((char*)&*this, sizeof(*this));
			break;

		}
		
	}
	f.close();
}

bool Appointment::readAppointment(int id) {

	Appointment app;
	bool found = false;

	fstream f("Appointments", ios::out | ios::in | ios::binary);

	while (f.read((char*)&app, sizeof(app))) {
		if (app.appointmentID == id) {
			found = true;
			*this = app;
		}
	}
	f.close();

	return found;
}

void Appointment::setStatus(int id, char* status) {

	if (!readAppointment(id)) {
		cout << endl << "Appointment With this ID not Found!!" << endl << endl;
		return;
	}

	if (!strcmp(this->status, status)) {
		cout << endl << "Status Already set to desired status!!" << endl << endl;
		return;
	}

	string dummy = "CANCELLED";

	DateTime currentDate;
	currentDate.input("Current");

	if (!strcmp(dummy.c_str(), status))
		payment->refund(currentTime.daysDifference(currentDate));

	DocSchedule docSch;

	docSch.readSchedule(doctorID);

	strcpy_s(this->status, status);

	docSch.setAvailability(time.getHour(), currentTime.daysDifference(time));

	updateAppointment();

	display();

	cout << endl << "Appointment Successfully Cancelled!!!" << endl << endl;
}


void Appointment::setTime(int id) {

	char dummy[] = "CANCELLED";

	if ((!readAppointment(id)) || !strcmp(status, dummy)) {
		cout << endl << "Appointment With this ID not Found or appointment cancelled!!" << endl << endl;
		return;
	}

	DocSchedule docSch;

	docSch.readSchedule(doctorID);

	docSch.display();

	cout << endl << endl;

	docSch.setAvailability(time.getHour(), currentTime.daysDifference(time));

	currentTime.input("Current");

	while (1) {
		time.input("Appointment");

		if (!(docSch.getStartTime() <= time.getHour() && docSch.getEndTime() > time.getHour()) || docSch.getAvailability(time.getHour(), currentTime.daysDifference(time))) {
			cout << "Invalid Appointment Time, Either Doctor not available or already booked..." << endl << endl;
			continue;
		}

		break;
	}

	docSch.setAvailability(time.getHour(), currentTime.daysDifference(time));

	updateAppointment();


	display();

	cout << endl << "Appointment Successfully Moved Forward!!!" << endl << endl;

}

Payment* Appointment::getPayment() const{
	return payment;
}
Mode* Appointment::getMode() const {
	return mode;
}
int Appointment::getAppID() const {
	return appointmentID;
}
DateTime Appointment::getAppTime() const {
	return time;
}
DateTime Appointment::getCurrentTime() const {
	return currentTime;
}