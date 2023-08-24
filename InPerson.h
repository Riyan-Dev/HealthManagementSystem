#pragma once

#include "Mode.h"

class InPerson : public Mode {
public:
	double calCharges() override {
		return rate;
	}
	void operator = (const InPerson IP) {
		rate = IP.rate;
	}
};