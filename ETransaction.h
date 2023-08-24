#pragma once

#include "Payment.h"
#include <iomanip>

class ETransaction : public Payment {
protected:
	int contactNo;
public:
	void setPayment(double charges) override {

		cout << "Enter Contact Number: ";
		cin >> contactNo;

		Payment::setPayment(charges);
	}

	void details() override{
		char dummy[30];

		strcpy_s(dummy, getStatus());

		cout << "---------------------------------------------------------------------------" << endl;
		cout << left << "contact No.: " << contactNo << endl;
		cout << "Total Amount: " << setw(20) << AmountToPay;
		cout << "Remaining Amount: " << remainingBalance() << endl;
		cout << "Status: " << dummy << endl << endl << endl;

	}
};