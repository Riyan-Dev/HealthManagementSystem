#pragma once

#include <fstream>
#include "Doctor.h"


class Gynecologist: public Doctor {
private:

public:

	void Register() {

		Doctor::Register();

		writeGynecologist("Gynecologist", *this);
		
	}

	void writeGynecologist(string fileName, Gynecologist g) {

		ofstream fout(fileName, ios::binary | ios::app);
		fout.write((char*)&g, sizeof(g));
		fout.close();
		
	}
	void setRate() {

		Doctor::setRate();

		updateDoctor();

		details();


	}void setHospital() {

		Doctor::setHospital();

		updateDoctor();

		details();


	}void setLocation() {

		Doctor::setLocation();

		updateDoctor();

		details();


	}void setYOE() {

		Doctor::setYOE();

		updateDoctor();

		details();


	}
	void updateDoctor() {

		Gynecologist d;

		fstream f("Gynecologist", ios::out | ios::in | ios::binary);

		while (f.read((char*)&d, sizeof(d))) {
			//app.display();
			if (d.doctorID == doctorID) {

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