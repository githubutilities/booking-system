#include "MyFlight.h"

bool MyFlight::init(istream &fin) {
	string indate;
	if (!(fin >> destination)) return false;
	fin >> flightID >> planeID >> indate
		>> passagerLimit >> remainingTicket;
	int y, m, d; sscanf(indate.c_str(), "%d.%d.%d", &y, &m, &d);
	date = dateToInt(m, d, y);
	int cnt; fin >> cnt;
	while (cnt--) {
		MyCustomer * pp = new MyCustomer();
		pp->init(fin);
		onBoard.push_back(pp);
	}
	fin >> cnt;
	while (cnt--) {
		MyCustomer * pp = new MyCustomer();
		pp->init(fin);
		waiting.push(pp);
	}
	return true;
}

void MyFlight::write(ostream &fout) {
	fout << destination << endl;
	fout << flightID << endl;
	fout << planeID << endl;
	int y, m, d; intToDate(date, m, d, y);
	fout << y << "." << m << "." << d << endl;
	fout << passagerLimit << endl;
	fout << remainingTicket << endl;
	int cnt = onBoard.size();
	fout << cnt << " ";
	for (int i = 0; i < cnt; i++) {
		onBoard[i]->write(fout);
	} fout << endl;
	cnt = waiting.size();
	fout << cnt << " ";
	while (cnt--) {
		MyCustomer *tmp = waiting.front(); waiting.pop();
		tmp->write(fout);
	}
	fout << endl;
	fout << endl;
}

void MyFlight::setDest(string dest) {
	destination = dest;
}

void MyFlight::setFlightID(string fid) {
	flightID = fid;
}

void MyFlight::setPlaneID(string pid) {
	planeID = pid;
}

void MyFlight::setRemainingTicket(int num) {
	remainingTicket = num;
}

void MyFlight::addCustomer(MyCustomer * &user) {
	for (int i = 0; i < onBoard.size(); i++) {
		if (onBoard[i]->getName() == user->getName()) {
			onBoard[i]->addNeed(user->getNeed());
			return;
		}
	}
	onBoard.push_back(user);
}

void MyFlight::joinQueue(MyCustomer * user) {
	waiting.push(user);
}

int MyFlight::returnTicket(string username, int num) {
	int i;
	for (i = 0; i < onBoard.size(); i++) if (onBoard[i]->getName() == username) break;
	if (onBoard.size() == i) return CUSTOMER_NOT_FOUND;
	int bookedNum = onBoard[i]->getNeed();
	if (num > bookedNum) return INVALID_TICKET_NUM;
	else if (num == bookedNum) onBoard.del(i);
	else onBoard[i]->addNeed(-num);
	return RETURN_TICKET_SUCCESS;
}

string MyFlight::getDest() {
	return destination;
}

string MyFlight::getFlightID() {
	return flightID;
}

string MyFlight::getPlaneID() {
	return planeID;
}

string MyFlight::getDate() {
	int y, m, d; intToDate(date, m, d, y);
	char ret[20];
	sprintf(ret, "%d.%d.%d", y, m, d);
	return string(ret);
}

int MyFlight::getPassLimit() {
	return passagerLimit;
}

int MyFlight::getRemainingTicket() {
	return remainingTicket;
}

bool MyFlight::operator==(const MyFlight &b) const {
	return destination == b.destination &&
		flightID == b.flightID &&
		planeID == b.planeID &&
		date == b.date;
}

int MyFlight::dateToInt(int m, int d, int y){
	return
		1461 * (y + 4800 + (m - 14) / 12) / 4 +
		367 * (m - 2 - (m - 14) / 12 * 12) / 12 -
		3 * ((y + 4900 + (m - 14) / 12) / 100) / 4 +
		d - 32075;
}

void MyFlight::intToDate(int jd, int &m, int &d, int &y){
	int x, n, i, j;

	x = jd + 68569;
	n = 4 * x / 146097;
	x -= (146097 * n + 3) / 4;
	i = (4000 * (x + 1)) / 1461001;
	x -= 1461 * i / 4 - 31;
	j = 80 * x / 2447;
	d = x - 2447 * j / 80;
	x = j / 11;
	m = j + 2 - 12 * x;
	y = 100 * (n - 49) + i + x;
}

int cmpByFlightID(MyFlight *a, MyFlight *b) { 
	if ((*a) == (*b)) return 0;
	return a->getFlightID() <= b->getFlightID() ? -1 : 1;
}
bool findByFlightID(MyFlight *a, MyFlight *b) { return a->getFlightID() == b->getFlightID(); }
int cmpByPlaneID(MyFlight *a, MyFlight *b) { 
	if ((*a) == (*b)) return 0;
	return a->getPlaneID() <= b->getPlaneID() ? -1 : 1;
}
bool findByPlaneID(MyFlight *a, MyFlight *b) { return a->getPlaneID() == b->getPlaneID(); }
int cmpByDest(MyFlight *a, MyFlight *b) { 
	if ((*a) == (*b)) return 0;
	return a->getDest() <= b->getDest() ? -1 : 1;
}
bool findByDest(MyFlight *a, MyFlight *b) { return a->getDest() == b->getDest(); }