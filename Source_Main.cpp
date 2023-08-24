
#include <stdlib.h>
#include "OlaDoc.h"
#include "User.h"
#include "Patient.h"
#include "Doctor.h"
#include "Gynecologist.h"
#include "Dermatologist.h"
#include "Oncologist.h"
#include "Orthopedic.h"
#include "Admin.h"

void doctorSpeciality();
//void loginRegister(OlaDoc& od, Patient& p);
template <class T> void DoctorloginRegister(OlaDoc& od, T& p);
void patientMenu(Patient &);
template <class D>void doctorMenu(D d);
void bookAppointment(char* patientUN, char* patientCNIC, char* patientName);
void cancelAppointment();
void changeTimings();
template <class T> void updateDocProfile(T& t);
void updatePatProfile(Patient& p);
void AdminMenu(OlaDoc& od, Admin& A);
template <class D> void editDocData(string filename, D d, int id);
void viewPatients();
//template <class D> void docChangeStatus(D d);
//void paymentMenu();

int main() {

	while (1) {
		cout << "welcome to OlaDoc!!" << endl << endl;
		cout << "How would you like to use this application: " << endl << "1. Doctor" << endl << "2. Patient" << endl << "3. Admin" << endl;

		cout << "Enter Your choice: " << endl;

		int choice = 1;

		cin >> choice;

		if (choice == 1) {
			doctorSpeciality();

		}
		else if (choice == 2) {

			User* usr = new Patient;
			Patient p;
			OlaDoc od(usr);

			DoctorloginRegister(od, p);
			//p.Details();
			system("CLS");
			patientMenu(p);
		}

		else if (choice == 3) {
			User* usr = new Admin;
			Admin A;
			OlaDoc od(usr);

			AdminMenu(od, A);

		}
			
		else {

			cout << "Invalid Input!!";
		}
	}
	
}
void doctorSpeciality() {

	system("CLS");

	int choice;

	cout << endl << "1.Gynecologist " << endl << "2.Orthopedic" << endl << "3.Oncologist" << endl << "4.Dermatologist" << endl;
	cout << "Enter Your choice: " << endl;
	cin >> choice;
	while (1) {
		if (choice == 1) {
			User* usr = new Gynecologist;
			Gynecologist g;
			OlaDoc od(usr);

			DoctorloginRegister(od, g);
			doctorMenu(g);


			break;
		}
		else if (choice == 2) {
			User* usr = new Orthopedic;
			Orthopedic ortho;
			OlaDoc od(usr);

			DoctorloginRegister(od, ortho);
			doctorMenu(ortho);

			break;
		}
		else if (choice == 3) {
			User* usr = new Oncologist;
			Oncologist oncolo;
			OlaDoc od(usr);

			DoctorloginRegister(od, oncolo);
			doctorMenu(oncolo);


			break;
		}
		else if (choice == 4) {
			User* usr = new Dermatlogist;
			Dermatlogist derma;
			OlaDoc od(usr);

			DoctorloginRegister(od, derma);
			doctorMenu(derma);

			break;
		}

		else {
			system("CLS");
			cout << "Invalid Input!!" << endl;
		}
	}

}

template <class T> void DoctorloginRegister(OlaDoc& od, T& p) {


	system("CLS");

	int choice;

	cout << endl << "1.Login " << endl << "2.Register" << endl;
	cout << "Enter Your choice: ";
	cin >> choice;

	while (1) {
		if (choice == 1) {

			p.login();
			//p.Details();
			break;
		}
		else if (choice == 2) {

			od.getUser()->Register();
			system("CLS");
			p.login();
			//p.Details();
			p.getCNIC();
			break;
		}
		else {
			system("CLS");
			cout << "Invalid Input!!" << endl;
		}
	}

}

template <class D>void doctorMenu(D d) {

	while (1) {

		system("CLS");

		cout << "----------Welcome " << d.getName() << " ----------" << endl;
		cout << endl << "1. My Details" << endl
			<< "2. View Appointments" << endl
			<< "3. View Schedule" << endl
			<< "4. Set Availibity" << endl
			<< "5. Update Profile" << endl
			<< "6. Set Hourly charge." << endl
			<< "7. Logout" << endl;

		int choice;

		cout << "Enter Your choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			system("CLS");

			d.details();
			d.displayFeedbacks();
			system("PAUSE");
			break;
		case 2:
			system("CLS");

			d.paymentMenu();

		
			break;
		case 3:

			d.getSchedule().display();

			break;

		case 4:

			d.changeSchedule();

			break;

		case 5:
			updateDocProfile(d);
			break;
		case 6:
			d.setRate();

			break;
		case 7:
			break;

		}

		if (choice == 7)
			break;

	}

	system("CLS");
}



void patientMenu(Patient& p) {

	while (1) {


		system("CLS");

		cout << "----------Welcome " << p.getName() << " ----------" << endl;
		cout << endl << "1. Patient Details" << endl
			<< "2. Search Doctors" << endl
			<< "3. Book Appointment" << endl
			<< "4. Cancel Appointment" << endl
			<< "5. change Appointment Timings" << endl
			<< "6. Scheduled Appointments" << endl
			<< "7. Reset Password" << endl
			<< "8. Update Profile" << endl
			<< "9. Logout" << endl;

		int choice;

		cout << "Enter Your choice: ";
		cin >> choice;

	
		switch (choice) {
		case 1:

			p.Details();

			break;

		case 2:

			p.displayDoctors();
			
			p.feedback();
			break;

		case 3:

			bookAppointment(p.getUserName(), p.getCNIC(), p.getName());

			break;
		case 4:

			cancelAppointment();

			break;

		case 5:

			changeTimings();

			break;
		case 6:

			p.displayAppointments();

			p.paymentMenu();

			break;
		case 7:

			p.resetPassword();
			break;
		case 8:
			updatePatProfile(p);
			break;
		case 9: 

			break;
		}

		if (choice == 9)
			break;
	}
	system("CLS");

}

void changeTimings() {

	system("CLS");

	int appointmentID;

	cout << "Enter Appointment ID for which you want to change timings: ";
	cin >> appointmentID;

	Appointment app;

	app.setTime(appointmentID);

	system("PAUSE");
}

void cancelAppointment() {

	system("CLS");
	int appointmentID;

	cout << "Enter Appointment ID for which you want to cancel: ";
	cin >> appointmentID;

	Appointment app;
	char dummy[] = "CANCELLED";
	app.setStatus(appointmentID, dummy);

	

	system("PAUSE");

}

void bookAppointment(char* patientUN, char* patientCNIC, char* patientName) {

	Appointment app;

	app.setAppointment(patientUN, patientCNIC, patientName);
}

template <class T> void updateDocProfile(T& t) {

	system("CLS");

	int choice;

	while (1) {
		cout << endl << endl << "1. Change Location" << endl
			<< "2. Change Hospital" << endl
			<< "3. Change Year of Experience" << endl 
			<< "0. Return to Main Menu" << endl << endl;
		cout << "Enter choice: ";
		cin >> choice;

		if (choice == 0)
			return;
		else if (choice < 0 || choice > 3) {
			system("CLS");
			cout << endl << endl << "Invalid Choice!!" << endl;
			continue;
		}
		else
			break;

	}

	switch (choice) {

	case 1:
		t.setLocation();
		break;
	case 2:
		t.setHospital();
		break;
	case 3:
		t.setYOE();
		break;
	}
}
void updatePatProfile(Patient& p) {

	system("CLS");

	int choice;

	while (1) {
		cout << endl << endl << "1. Change Age" << endl
			<< "2. Change Height" << endl
			<< "3. Change Weight" << endl 
			<< "4. Change Contact" << endl 
			<< "5. Change Address" << endl 
			<< "0. Return to Main Menu" << endl << endl;
		cout << "Enter choice: ";
		cin >> choice;

		if (choice == 0)
			return;
		else if (choice < 0 || choice > 5) {
			system("CLS");
			cout << endl << endl << "Invalid Choice!!" << endl;
			continue;
		}
		else
			break;

	}

	switch (choice) {

	case 1:
		p.setAge();
		break;
	case 2:
		p.setHeight();
		break;
	case 3:
		p.setWeight();
		break;
	case 4:
		p.setContact();
		break;
	case 5:
		p.setAddress();
		break;
	}
}

void AdminMenu(OlaDoc& od, Admin& A) {

	od.getUser()->login();
	Patient P;
	Doctor d;
	system("CLS");

	int choice;

	while (1) {
		cout << endl << endl << "1. View Patients" << endl
			<< "2. Doctors" << endl
			<< "3. Update Doctor Details" << endl
			<< "0. Return to Main Menu" << endl << endl;
		cout << "Enter choice: ";
		cin >> choice;

		if (choice == 0)
			return;
		else if (choice < 0 || choice > 3) {
			system("CLS");
			cout << endl << endl << "Invalid Choice!!" << endl;
			continue;
		}
		else
			break;

	}
	int id;
	switch (choice) {

	case 1:
		viewPatients();
		break;
	case 2:
		P.displayDoctors();
		break;
	case 3:


		cout << "Enter Doctor id: ";
		cin >> id;

		Gynecologist gyne;
		Orthopedic Ortho;
		Oncologist Oncolo;
		Dermatlogist Derma;
		
		editDocData("Gynecologist", gyne, id);
		editDocData("Orthopedic", Ortho, id);
		editDocData("Oncologist", Oncolo, id);
		editDocData("Dermatlogist", Derma, id);

		break;
	
	}


}
void viewPatients() {

	Patient p;

	ifstream fin3("Patients", ios::binary | ios::app);

	while (fin3.read((char*)&p, sizeof(p))) {
		p.Details();
	}

}
template <class D> void editDocData(string filename , D d, int id) {

	bool found = false;

	ifstream fin3(filename, ios::binary | ios::app);

	while (fin3.read((char*)&d, sizeof(d)) && !found) {
		if (d.getID() == id) {
			found = true;
			break;
		}
	}
	fin3.close();

	if (found)
		updateDocProfile(d);



}
/*template <class D> void docChangeStatus(D d) {

	int choice;

	while (1) {

		system("CLS");

		d.displayAppointments();

		cout << endl << endl << "1. To change Status of Appointment." << endl
			<< "0. To go back." << endl;
		cin >> choice;

		if (choice == 0)
			break;
		else if (choice == 1) {

			int appointmentID;

			system("CLS");

			cout << "Press 0 to go back" << endl << endl;
			cout << "Enter Appointment ID for which you want to cancel: ";
			cin >> appointmentID;

			if (appointmentID == 0)
				continue;

			Appointment app;
			int status;

			cout << "1. Approved" << endl << "2. Completed" << endl;
			cout << "Enter Status (1 or 2): ";
			cin >> status;

			char statuses[2][20] = { "APPROVED", "COMPLETED" };

			app.setStatus(appointmentID, statuses[status-1]);

			break;
		}
		else {
			cout << "Invalid Choice!!" << endl << endl;
		}
	}

}*/



/*void loginRegister(OlaDoc& od, Patient& p) {

	int choice;

	cout << endl << "1.Login " << endl << "2.Register" << endl;
	cout << "Enter Your choice: ";
	cin >> choice;

	while (1) {
		if (choice == 1) {

			p.login();
			//p.Details();
			break;
		}
		else if (choice == 2) {

			od.getUser()->Register();
			system("CLC");
			p.login();
			//p.Details();
			p.getCNIC();
			break;
		}
		else {
			system("CLC");
			cout << "Invalid Input!!" << endl;
		}
	}

}*/
