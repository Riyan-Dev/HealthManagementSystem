#pragma once


#include <iomanip>
#include <iostream>

using namespace std;

class Feedback {
private:
	int feedbackID;
	int doctorID;
	double stars;
	char review[500];
	int NoofReplies;
	char replies[20][500];

	template <class T> void validatingID(string filename, T t, bool& found, int id);

	bool validateDocID(int id);


public:
	Feedback();
	int getDocID();
	void setFeedback(int docID);
	void setReply(int docID, int feedbackID);
	void writeFeedback();
	void readFeedback(int docID, int feedbackID);
	int setID();
	void displayFeedbacks(int docID);
	void displayfeedback();
	void updateFeedback();

	double getStars();

	void operator = (const Feedback F);
};