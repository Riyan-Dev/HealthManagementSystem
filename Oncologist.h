#pragma once

#include <fstream>
#include "Doctor.h"


class Oncologist : public Doctor {
private:

public:

	void Register() {

		Doctor::Register();

		writeOncologist("Oncologist", *this);

	}

	void writeOncologist(string fileName, Oncologist O) {

		ofstream fout(fileName, ios::binary | ios::app);
		fout.write((char*)&O, sizeof(O));
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

		Oncologist d;

		fstream f("Oncologist", ios::out | ios::in | ios::binary);

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