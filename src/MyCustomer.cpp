#include"MyCustomer.h"

void MyCustomer::init(istream &fin) {
	string tmp; fin >> tmp;
	char nn[100];
	sscanf(tmp.c_str(), "%*[ \"]%[^\"]%*[\"]%d", nn, &need);
	name = string(nn);
}

void MyCustomer::write(ostream &fout) {
	fout << "\"" << name << "\"" << need << " ";
}

string MyCustomer::getName() {
	return name;
}

int MyCustomer::getNeed() {
	return need;
}

void MyCustomer::addNeed(int num) {
	need += num;
}