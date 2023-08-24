#pragma once

#include "BankTransfer.h"

class PakPay : public BankTransfer {
private:

public:
	void operator = (const PakPay PP) {
		AmountToPay = PP.AmountToPay;
		AmountPaid = PP.AmountPaid;
		currentTime = PP.currentTime;
		CCNum = PP.CCNum;
		expDate = PP.expDate;
		strcpy_s(CCHolderName, PP.CCHolderName);

	}

};