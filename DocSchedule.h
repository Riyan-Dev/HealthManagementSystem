#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;

class DocSchedule {
private:
	int startTime;
	int endTime;
	int availability[7][24];
	int docID;
public:
	void setSchedule(int docID) {

		this->docID = docID;

		cout << endl << endl << "Enter Start time as hours (eg 17h as 5 pm): ";
		cin >> startTime;

		cout << endl << "Enter End time as hours (eg 17h as 5 pm): ";
		cin >> endTime;

		for (int i = 0; i < 7;i++)
			for (int j = 0; j < 24; j++)
				availability[i][j] = false;

		writeSchedule(*this);
		
	}
	void writeSchedule(DocSchedule docSch) {

		ofstream fout("DocSchedule", ios::binary | ios::app);
		fout.write((char*)&docSch, sizeof(docSch));
		fout.close();

	}
	int getDocID() {
		return docID;
	}
	void operator = (DocSchedule DS) {


		//cout << "Hello" << endl;

		startTime = DS.startTime;
		endTime = DS.endTime;
		docID = DS.docID;

		for (int i = 0; i < 7;i++)
			for (int j = startTime-1; j < endTime - 1; j++) {

				//cout << "availability[" <<i << "][" << j << "]: " << availability[i][j] << " = DS.availability[" << i << "][" << j << "]: " << DS.availability[i][j] << endl;
				availability[i][j] = DS.availability[i][j];

				
			}
	}

	void display() {

		for (int i = 0; i < 7; i++) {

			if (i == 0)
				cout << endl << "Today" << endl;
			else if (i == 1)
				cout << endl << "Tomorrow" << endl;
			else
				cout << endl << i + 1 << " Days from Today" << endl;


			for (int j = startTime - 1; j < endTime - 1; j++)
				cout << left << "Slot " << setw(10) << j - startTime + 2;

			cout << endl;
			for (int j = startTime - 1; j < endTime - 1; j++)
				cout << left << j + 1 << setw(13) << ":00";

			cout << endl;

			for (int j = startTime - 1; j < endTime - 1; j++)
				if (availability[i][j] == false)
					cout << left << setw(15) << "Available";
				else
					cout << left << setw(15) << "Booked";

			cout << endl;
		}

		system("PAUSE");
	}

	void readSchedule(int docID) {

		DocSchedule docSch;

		ifstream fin("DocSchedule", ios::binary | ios::app);

		while (fin.read((char*)&docSch, sizeof(docSch))) {

			if (docSch.getDocID() == docID) {
				*this = docSch;
				break;
			}
		}

		fin.close();

	}

	int getStartTime() {
		return startTime;
	}

	int getEndTime() {
		return endTime;
	}

	bool getAvailability(int hour, int day) {
		return availability[day][hour-1];
	}

	void setAvailability(int hour, int day) {
		if (availability[day][hour - 1])
			availability[day][hour - 1] = false;
		else
			availability[day][hour - 1] = true;

		updateSchedule();

	}

	void updateSchedule() {

		DocSchedule docSch;

		fstream f("DocSchedule", ios::out | ios::in | ios::binary);

		while (f.read((char*)&docSch, sizeof(docSch))) {
			//display();
			if (docSch.getDocID() == docID) {

				docSch = *this;
				//docSch.display();
				int a = f.tellg();
				int s = sizeof(DocSchedule);
				f.seekp(a - s, ios::beg);

				f.write((char*)&docSch, sizeof(docSch));
				break;

			}
		}
		f.close();

	}


};