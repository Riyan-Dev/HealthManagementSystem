#pragma once

#include <iomanip>
#include "Payment.h"
#include "DateTime.h"

class BankTransfer : public Payment {
protected:
	long long int CCNum;
	char CCHolderName[30];
	DateTime expDate;
public:
	void setPayment(double charges) override {

		cout << "Enter Credit Card Number: ";
		cin >> CCNum;

		cout << "Enter Credit Card Holder Name: ";
		string dummy;
		cin.ignore();
		getline(cin, dummy);
		strcpy_s(CCHolderName, dummy.c_str());

		expDate.input("Expiry");

		Payment::setPayment(charges);
	}
	void details() override {
		char dummy[30];

		strcpy_s(dummy, getStatus());

		cout << "---------------------------------------------------------------------------" << endl;
		cout << left << "Credit Card Holder Name: " << CCHolderName << endl;
		cout << "Expiry Date: " << setw(20);
		expDate.display();
		cout << "Credit Card Number: " << CCNum << endl;
		cout << "Total Amount: " << setw(20) << AmountToPay; 
		cout << "Remaining Amount: " << remainingBalance() << endl;
		cout << "Status: " << dummy << endl << endl << endl;
	}
};