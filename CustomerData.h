/****************************************************
CIS 22C
Programmer: Duong Hoang Vu

Assistants: Tung Lin Lee ()
******************************************************/

#ifndef CUSTOMERDATA_H_INCLUDED
#define CUSTOMERDATA_H_INCLUDED

#include <iostream>
#include <string>
#include <ctime>
using namespace std;

class customerData
{
private:
	static const int tableSize = 50;
	string plateNumber, name, brand;
	int timeIn, timeOut, timeLength;
public:
	customerData();
	customerData(string entryName);
	~customerData(){}

	void setPlate(string);
	void setName(string);
	void setBrand(string);

	string getPlate() const;
	string getName() const;
	string getBrand()const;

	void setTimeIn(int);
	void getTimeIn();
	void getTimeOut();
	int getTimeLength();

	bool operator < (const customerData& b) const;
	bool operator <= (const customerData& b) const;
	bool operator == (const customerData& b) const;
	bool operator > (const customerData& b) const;
	bool operator >= (const customerData& b) const;
	bool operator != (const customerData& b) const;
	friend ostream& operator << (ostream& os, const customerData& obj);


	bool operator << (const customerData& b) const;
	bool operator <<= (const customerData& b) const;
	bool operator *= (const customerData& b) const;
	bool operator >> (const customerData& b) const;
	bool operator >>= (const customerData& b) const;
	bool operator |= (const customerData& b) const;

};
#endif // CUSTOMERDATA_H_INCLUDED
