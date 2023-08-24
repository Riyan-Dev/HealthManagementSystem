#pragma once

#include <iostream>
#include <string>
#include "User.h"
//#include "Patient.h"
using namespace std;

class User {

private: 
	bool checkCNIC(string cnic);
	bool checkUserName(string username);


protected:
	char userName[30];
	char password[30];
	int age;
	char name[30];
	char cnic[20];
	char email[30];

	

public:

	User();

	virtual void Register();

	
	char* getUserName();
	char* getName();
	char* getCNIC();
	char* getPassword();

	virtual void login();

	void setpassword();
};

template <typename T> void checkingCNIC(string fileName, T t, bool& found, string cnic);
template <typename T> void checkingUsername(string fileName, T t, bool& found, string username);