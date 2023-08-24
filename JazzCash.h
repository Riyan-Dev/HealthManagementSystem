#pragma once

#include "ETransaction.h"


class JazzCash : public ETransaction {
private:

public:
	void operator = (const JazzCash JC) {
		AmountToPay = JC.AmountToPay;
		AmountPaid = JC.AmountPaid;
		currentTime = JC.currentTime;
		contactNo = JC.contactNo;
	}
};