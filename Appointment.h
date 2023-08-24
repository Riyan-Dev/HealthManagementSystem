#pragma once

#include "DateTime.h"
#include <iostream>
#include <string>
#include "JazzCash.h"
#include "EasyPaisa.h"
#include "UnionPay.h"
#include "PakPay.h"
#include "VideoConsultation.h"
#include "InPerson.h"
#include "Mode.h"

class Appointment {
private: 
	int appointmentID;
	char status[20];
	char PatientUN[30];
	char patientName[30];
	char patientCNIC[16];
	char doctorCNIC[16];
	char doctorName[30];
	int doctorID;
	DateTime time;
	DateTime currentTime;


	VideoConsultation VC;
	InPerson IP;
	Mode* mode;
	int choice1;

	JazzCash JC;
	EasyPaisa EP;
	UnionPay UP;
	PakPay PP;
	Payment* payment;
	int choice2;

	bool validateDocID(int id);
	int setID();
	template <class T> void validatingID(string filename, T t, bool& found, int id);

	void writeAppointment();

public:

	void operator = (Appointment&);
	int getdocID() const;
	int getAppID() const;
	DateTime getAppTime() const;
	DateTime getCurrentTime() const;
	char* getPatientUN() ;
	Appointment();
	void setAppointment(char* patientUN, char* patientCNIC, char* patientName);
	void display();
	void updateAppointment();
	bool readAppointment(int id);
	void setStatus(int id, char* status);
	void setTime(int id);
	Payment* getPayment() const;
	Mode* getMode() const;

	void assignMode(int chocie);
	void assignPayment(int chocie);
};