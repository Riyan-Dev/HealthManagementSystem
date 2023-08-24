#pragma once

#include <fstream>
#include "Doctor.h"


class Dermatlogist : public Doctor {
private:

public:

	void Register() {

		Doctor::Register();

		writeDermatlogist("Dermatlogist", *this);

	}

	void writeDermatlogist(string fileName, Dermatlogist d) {

		ofstream fout(fileName, ios::binary | ios::app);
		fout.write((char*)&d, sizeof(d));
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

		Dermatlogist d;

		fstream f("Dermatlogist", ios::out | ios::in | ios::binary);

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