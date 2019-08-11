/****************************************************
CIS 22C
Programmer: Duong Hoang Vu

Assistants: Tung Lin Lee(Check the stability)
******************************************************/
#include "CustomerData.h"
#include <string>
#include <ctime>
#include <cmath>
#include <iomanip>

customerData::customerData()
{
	plateNumber.clear();
	name.clear();
	brand.clear();
	timeIn = 0;
	timeOut = 0;
	timeLength = 0;
}

customerData::customerData(string entryName)
{
	this->name = entryName;
}

void customerData::setPlate(string plateNumber)
{
	this->plateNumber = plateNumber;
}

void customerData::setName(string name)
{
	this->name = name;
}

void customerData::setBrand(string brand)
{
	this->brand = brand;
}

string customerData::getPlate() const
{
	return plateNumber;
}

string customerData::getName() const
{
	return name;
}

string customerData::getBrand() const
{
	return brand;
}

void customerData::getTimeIn()
{
	time_t t = time(0); // get time now
	struct tm in;
	localtime_s(&in,&t);
	cout << "Time In: "<<in.tm_hour << ":" << in.tm_min << endl;
}

void customerData::getTimeOut()
{

	time_t t = time(0); // get time now
	struct tm out;
	localtime_s(&out, &t);
	timeOut = out.tm_hour * 60 + out.tm_min;
	cout << "Time Out: " << out.tm_hour << ":" << out.tm_min << endl;
}

void customerData::setTimeIn(int time)
{
	timeIn = time;
}

int customerData::getTimeLength()
{
	if (timeOut >= timeIn)
		return timeOut - timeIn;
	else return 0;
}

bool customerData::operator < (const customerData& b) const
{
	return this->plateNumber < b.plateNumber;
}

bool customerData::operator <= (const customerData& b) const
{
	return this->plateNumber <= b.plateNumber;
}

bool customerData::operator == (const customerData& b) const
{
	return this->plateNumber == b.plateNumber;
}

bool customerData::operator > (const customerData& b) const
{
	return this->plateNumber > b.plateNumber;
}

bool customerData::operator >= (const customerData& b) const
{
	return this->plateNumber >= b.plateNumber;
}

bool customerData::operator != (const customerData& b) const
{
	return this->plateNumber != b.plateNumber;
}
/////////////////////////////////////////////////////////////


bool customerData::operator << (const customerData& b) const
{
	return this->name < b.name;
}

bool customerData::operator <<= (const customerData& b) const
{
	return this->name <= b.name;
}

bool customerData::operator *= (const customerData& b) const
{
	return this->name == b.name;
}

bool customerData::operator >> (const customerData& b) const
{
	return this->name > b.name;
}

bool customerData::operator >>= (const customerData& b) const
{
	return this->name >= b.name;
}

bool customerData::operator |= (const customerData& b) const
{
	return this->name != b.name;
}

ostream& operator << (ostream& os, const customerData& obj)
{
	os << "[ "<< left << setw(7) << obj.getPlate() << " | " << left << setw(16) << obj.getName() << " | " << left << setw(9) << obj.getBrand() <<" ]" << endl;
	return os;
}
