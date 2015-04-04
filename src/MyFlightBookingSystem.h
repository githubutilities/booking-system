#ifndef MYFLIGHTBOOKINGSYSTEM_H
#define MYFLIGHTBOOKINGSYSTEM_H

#include "MyVector.h"
#include "MyFlight.h"
#include "MySet.h"
#include <string>
#include <fstream>
using namespace std;

#define BOOK_SUCCESS 2
#define NOT_ENOUGH_TICKET 3
class MyFlightBookingSystem {
public:
	MyFlightBookingSystem();
	~MyFlightBookingSystem();

	void init(istream &fin);
	void write(ostream &fout);
	bool queryByDest(string q, MyVector<MyFlight*> &ret);
	bool queryByFlightID(string q, MyVector<MyFlight*> &ret);
	int book(string username, MyFlight *want, int num);
	void joinQueue(string username, MyFlight *want, int num);
	int returnTicket(string username, MyFlight *want, int num);

private:
	MySet<MyFlight *> *fliByDest;
	MySet<MyFlight *> *fliByflightID;
};

#endif