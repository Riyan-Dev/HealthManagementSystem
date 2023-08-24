#pragma once

#include "ETransaction.h"

class EasyPaisa : public ETransaction {
private:

public:
	void operator = (const EasyPaisa EP) {
		AmountToPay = EP.AmountToPay;
		AmountPaid = EP.AmountPaid;
		currentTime = EP.currentTime;
		contactNo = EP.contactNo;
	}
};