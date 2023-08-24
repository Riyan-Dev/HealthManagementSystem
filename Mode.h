#pragma once

class Mode {
protected:
	double rate;
public:
	void setRate(int rate) {
		this->rate = rate;
	}
	int getRate() {
		return rate;
	}
	virtual double calCharges() = 0;
};