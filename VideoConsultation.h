#pragma once

#include "Mode.h"

class VideoConsultation: public Mode {

public:
	double calCharges() override {
		return rate*0.7;
	}
	void operator = (const VideoConsultation VC) {
		rate = VC.rate;
	}
};