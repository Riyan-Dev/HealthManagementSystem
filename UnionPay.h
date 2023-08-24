#pragma once

#include "BankTransfer.h"

class UnionPay : public BankTransfer {
private:

public:
	void operator = (const UnionPay UP) {
		AmountToPay = UP.AmountToPay;
		AmountPaid = UP.AmountPaid;
		currentTime = UP.currentTime;
		CCNum = UP.CCNum;
		expDate = UP.expDate;
		strcpy_s(CCHolderName, UP.CCHolderName);

	}
};