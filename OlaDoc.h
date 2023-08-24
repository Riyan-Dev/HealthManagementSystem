#pragma once

#include "user.h"

class OlaDoc {
private:
	User* user;
public:
	OlaDoc() {
		user = nullptr;
	}
	OlaDoc(User* user) {
		this->user = user;
	}
	User* getUser() {
		return user;
	}
};