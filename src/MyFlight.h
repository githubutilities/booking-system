#ifndef MYFLIGHT_H
#define MYFLIGHT_H

#include "MyVector.h"
#include "MyQueue.h"
#include "MyCustomer.h"
#include <string>
#include <fstream>
#include <stdio.h>
#include <string.h>
using namespace std;

#define CUSTOMER_NOT_FOUND -1
#define RETURN_TICKET_SUCCESS 0
#define INVALID_TICKET_NUM 1
class MyFlight {
public:
	bool init(istream &fin);
	void write(ostream &fout);
	void setDest(string dest);
	void setFlightID(string fid);
	void setPlaneID(string pid);
	void setRemainingTicket(int num);
	void addCustomer(MyCustomer * &user);
	void joinQueue(MyCustomer * user);
	int returnTicket(string username, int num);
	string getDest();
	string getFlightID();
	string getPlaneID();
	string getDate();
	int getPassLimit();
	int getRemainingTicket();


	bool operator == (const MyFlight &b) const;
private:
	string destination;					//�յ�վ��
	string flightID;					//�����
	string planeID;						//�ɻ���
	int date;							//�º��շֱ�����λ����ʾ��������λ��
	int passagerLimit;					//��Ա����
	int remainingTicket;				//��Ʊ��

	MyVector<MyCustomer *> onBoard;
	MyQueue<MyCustomer *> waiting;
	// converts Gregorian date to integer (Julian day number)
	int dateToInt(int m, int d, int y);
	// converts integer (Julian day number) to Gregorian date: month/day/year
	void intToDate(int jd, int &m, int &d, int &y);
};

int cmpByFlightID(MyFlight *a, MyFlight *b);
bool findByFlightID(MyFlight *a, MyFlight *b);
int cmpByPlaneID(MyFlight *a, MyFlight *b);
bool findByPlaneID(MyFlight *a, MyFlight *b);
int cmpByDest(MyFlight *a, MyFlight *b);
bool findByDest(MyFlight *a, MyFlight *b);

#endif