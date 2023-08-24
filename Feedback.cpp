
#include "Feedback.h"
#include "Gynecologist.h"
#include "Dermatologist.h"
#include "Oncologist.h"
#include "Orthopedic.h"

template <class T> void Feedback::validatingID(string filename, T t, bool& found, int id) {
	ifstream fin(filename, ios::binary | ios::app);

	while (fin.read((char*)&t, sizeof(t))) {

		if (id == t.getID()) {
			found = true;
		}

	}

	fin.close();
}

bool Feedback::validateDocID(int id) {

	Gynecologist gyne;
	Orthopedic Ortho;
	Oncologist Oncolo;
	Dermatlogist Derma;
	bool found = false;

	validatingID("Gynecologist", gyne, found, id);
	validatingID("Orthopedic", Ortho, found, id);
	validatingID("Oncologist", Oncolo, found, id);
	validatingID("Dermatlogist", Derma, found, id);


	return found;

}
Feedback::Feedback() {
	feedbackID = 0;
	doctorID = 0;
	stars = 0;
	review[0] = '\0';
	NoofReplies = 0;
	for (int i = 0; i < 20; i++)
		replies[i][0] = '\0';

}
int Feedback::getDocID() {
	return doctorID;
}
void Feedback::setFeedback(int docID) {


	if (!validateDocID(docID)) {
		system("CLS");
		cout << endl << endl << "Invalid Doc ID!" << endl << endl;
		return;
	}
	doctorID = docID;
	feedbackID = setID();

	cout << endl << endl << "~~~Feedback~~~" << endl << "        *" << endl << "      * *" << endl << "    * * *" << endl << "  * * * *" << endl << "* * * * *" << endl;
	cout << "Enter Rating out 5 stars: ";
	cin >> stars;

	cout << endl << endl << "Write Review: ";
	cin.ignore();
	cin.get(review, 500);
	cout << review;
	writeFeedback();


}
void Feedback::setReply(int docID, int feedbackID) {

	readFeedback(docID, feedbackID);

	cout << "Write Reply: ";
	cin.ignore();
	cin.get(replies[NoofReplies], 500);
	NoofReplies++;

	updateFeedback();

}
void Feedback::writeFeedback() {

	ofstream fout("Feedback", ios::binary | ios::app);
	fout.write((char*)&*this, sizeof(*this));
	fout.close();
}
void Feedback::readFeedback(int docID, int feedbackID) {


	ifstream fin("Feedback", ios::binary | ios::app);

	while (fin.read((char*)&*this, sizeof(*this))) {

		if (docID == doctorID && feedbackID == this->feedbackID)
			break;
	}

	fin.close();

}
int Feedback::setID() {

	Feedback F;
	int count = 0;
	ifstream fin("Feedback", ios::binary | ios::app);

	while (fin.read((char*)&*this, sizeof(*this))) {

		if (F.doctorID == doctorID) {
			count++;
		}

	}
	return count;
	fin.close();

}
void Feedback::displayFeedbacks(int docID) {

	if (!validateDocID(docID)) {
		system("CLS");
		cout << endl << endl << "Invalid Doc ID!" << endl << endl;
		return;
	}
	
	ifstream fin("Feedback", ios::binary | ios::app);

	while (fin.read((char*)&*this, sizeof(*this))) {
		if (docID == doctorID)
			displayfeedback();
	}
	fin.close();
}
void Feedback::displayfeedback() {

	cout << endl << endl 
		 << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"  << endl;
	cout << right << setw(40) << "Anonymous: " << stars << " ";
	for (int i = 0; i < int(stars); i++) cout << "*"; cout << endl;
	cout << right << setw(40) <<"Review: " << review << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
	cout << endl << right << setw(50) << "Replies" << endl;
	for (int i = 0; i < NoofReplies; i++) {
		cout << right << setw(50) << i + 1 << ". Anonymous" << endl;
		cout << right << setw(50) << " . " << replies[i] << endl << endl;
	}
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;

	system("PAUSE");

}
void Feedback::updateFeedback() {

	Feedback F;

	fstream f("Feedback", ios::out | ios::in | ios::binary);

	while (f.read((char*)&F, sizeof(F))) {
		//app.display();
		if (F.feedbackID == feedbackID && F.doctorID == doctorID) {

			//docSch.display();
			int a = f.tellg();
			int s = sizeof(Feedback);
			f.seekp(a - s, ios::beg);
			//app.display();
			system("PAUSE");
			f.write((char*)&*this, sizeof(*this));
			break;

		}

	}
	f.close();

}

double Feedback::getStars() {
	return stars;
}

void Feedback::operator = (const Feedback F) {
	feedbackID = F.feedbackID;
	doctorID = F.doctorID;
	stars = F.stars;
	strcpy_s(review, F.review);
	NoofReplies = F.NoofReplies;
	for (int i = 0; i < 20; i++)
		strcpy_s(replies[i], F.replies[i]);
}