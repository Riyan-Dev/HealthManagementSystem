#pragma once

#include "User.h"
#include "Appointment.h"
#include "DocSchedule.h"
#include "Feedback.h"

class Doctor: public User {
protected:
	int doctorID;
	int rate;
	char location[30];
	char hospital[50];
	int yearsOfExperience;

	int NoOfAppointments;
	int NoOfFeedbacks;
	DocSchedule docSch;
	Appointment* appointments;
	Feedback* feedbacks;
	//void readSchedule(int docID);


public:

	Doctor();
	~Doctor();
	void Register();
	void login();
	int setID();
	int getID();
	char* getLocation();
	char* getHospital();
	int getRate();
	void details();
	DocSchedule getSchedule();
	void changeSchedule();
	template <class T> void readDoctor(string file_name, T t, bool&);
	//template <class T> void displayDoctorLocation(string file_name, char* location, T t);
	//template <class T> void displayDoctorHospital(string file_name, string hospital, T t);
	void readAppointments();
	void readFeedbacks();
	void displayAppointments();
	void paymentMenu();
	double calcAverageRating();
	void displayFeedbacks();

	virtual void setRate();
	virtual void setLocation();
	virtual void setHospital();
	virtual void setYOE();



};
