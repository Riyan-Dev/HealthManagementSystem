#pragma once

#include <iostream>

using namespace std;

class DateTime {
private:
	int hour;
	int date;
	int month;
	int year;

public:
	DateTime(int h = 0, int d = 0, int m = 0, int y = 0) {
		hour = h;
		date = d;
		month = m;
		year = y;
	}


	void input(string prompt) {

		cout << "Enter " << prompt << " hour: ";
		cin >> hour;

		cout << "Enter " << prompt << " date: ";
		cin >> date;

		cout << "Enter " << prompt << " month: ";
		cin >> month;

		cout << "Enter " << prompt << " year (XXXX): ";
		cin >> year;
	}

	int daysDifference(DateTime d1) {
		int days = 0;
		//cout << "appointment Date: " << d1.date << "Current date: " << date << endl;
		days += (d1.year - year) * 360;
	//	cout << "days: " << days << endl;
		days += (d1.month - month) * 60;
		//cout << "days: " << days << endl;
		days += d1.date - date;
		//cout << "days: " << days <<  endl;

		return days;
	}
	int getHour() {
		return hour;
	}
	void operator = (DateTime d) {

		hour = d.hour;
		date = d.date;
		month = d.month;
		year = d.year;
	}

	void display() {
		cout << "Time: " << hour << ":00 hours" << endl
			<< "Date: " << date << "/" << month << "/" << year << endl;
	}
};