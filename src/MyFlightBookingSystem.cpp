#include "MyFlightBookingSystem.h"

MyFlightBookingSystem::MyFlightBookingSystem() {
	fliByDest = new MySet<MyFlight *>(cmpByDest);
	fliByflightID = new MySet<MyFlight *>(cmpByFlightID);
}

MyFlightBookingSystem::~MyFlightBookingSystem() {
	fliByDest->~MySet();
	fliByflightID->~MySet();
	delete fliByDest;
	delete fliByflightID;
}

void MyFlightBookingSystem::init(istream &fin) {
	MyFlight * pp = NULL;
	while (1) {
		pp = new MyFlight();
		if (!pp->init(fin)) {
			delete pp;
			break;
		}
		fliByDest->insert(pp);
		fliByflightID->insert(pp);
	}
}

void MyFlightBookingSystem::write(ostream &fout) {
	MyVector<MyFlight *> list; fliByDest->toArray(list);
	for (int i = 0; i < list.size(); i++) {
		list[i]->write(fout);
	}
}

bool MyFlightBookingSystem::queryByDest(string q, MyVector<MyFlight *> &ret) {
	MyFlight query; query.setDest(q);
	fliByDest->findAll(ret, &query, findByDest);
	return ret.size() != 0;
}

bool MyFlightBookingSystem::queryByFlightID(string q, MyVector<MyFlight*> &ret) {
	MyFlight query; query.setFlightID(q);
	fliByflightID->findAll(ret, &query, findByFlightID);
	return ret.size() != 0;
}

int MyFlightBookingSystem::book(string username, MyFlight *want, int num) {
	if (num > want->getPassLimit()) return INVALID_TICKET_NUM;
	int rem = want->getRemainingTicket();
	if (num > rem) return NOT_ENOUGH_TICKET;
	rem -= num;
	want->setRemainingTicket(rem);

	MyCustomer * user = new MyCustomer(username, num);
	want->addCustomer(user);
	return BOOK_SUCCESS;
}

void MyFlightBookingSystem::joinQueue(string username, MyFlight *want, int num) {
	if (num > want->getPassLimit()) return;
	MyCustomer * user = new MyCustomer(username, num);
	want->joinQueue(user);
}

int MyFlightBookingSystem::returnTicket(string username, MyFlight *want, int num) {
	int ret = want->returnTicket(username, num);
	return ret;
}