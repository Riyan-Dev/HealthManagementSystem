#pragma once

#include "User.h"
#include "Patient.h"
#include "Doctor.h"

class Admin: public User{

public:
	void login() override {

		while (1) {

			User::login();

			char pass[] = "admin123";
			char UserN[] = "admin";

			if (!strcmp(pass, password) && !strcmp(UserN, userName))
				break;
			else {
				system("CLS");
				cout << "Invalid Credentials!!" << endl << endl;
				continue;
			}
		}

	}
};