#pragma once

class Payment {
protected:
	double AmountToPay;
	double AmountPaid;
	DateTime currentTime;
public:
	Payment(){
		AmountToPay = 0;
		AmountPaid = 0;
	}
	double remainingBalance() {
		return AmountToPay - AmountPaid;
	}
	void refund(int days) {
		switch (days) {
		case 0: AmountToPay *= 0.0; break;
		case 1: AmountToPay *= 0.4; break;
		case 2: AmountToPay *= 0.7; break;
		}
	}
	void fine(int days) {
		switch (days) {
		case 0: AmountToPay += AmountToPay*0.0; break;
		case 1: AmountToPay += AmountToPay*0.3; break;
		case 2: AmountToPay += AmountToPay*0.6; break;
		}
	}
	virtual void setPayment(double charges) {

		AmountToPay = charges;

		double dummy;
		cout << endl << endl << "Total Amount to be Paid: " << AmountToPay << endl;
		cout << endl << "Enter Amount you want to pay: ";
		cin >> dummy;
		AmountPaid += dummy;
		cout << endl;

		currentTime.input("Current");

		cout << endl << "Remaining Amount: " << remainingBalance();

	}

	DateTime getTime() {
		return currentTime;
	}

	char* getStatus() {

		char statuses[3][20] = { "PENDING", "PAID", "REFUND"};

		if (remainingBalance() > 0)
			return statuses[0];
		else if (remainingBalance() == 0)
			return statuses[1];
		else
			return statuses[2];
	}

	virtual void details() = 0;
	
};