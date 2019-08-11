/****************************************************
CIS 22C
Programmer: Duong Hoang Vu
This file will deal with hashing the data into the hash table

Assistants: Tung Lin Lee(Function developer), Risako Numamoto(Check the stability & statistic & load factor)
******************************************************/

#ifndef HASH_H_INCLUDED
#define HASH_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;
template <class ItemType>
class HashList
{
private:
	static const int TABLE_SIZE = 50;
	struct Item
	{
		string code;
		Item *next;
		ItemType data;
		Item();
		Item(const string& code, const ItemType& data);
	};
	int itemCount;
	Item* hashTable[TABLE_SIZE];
public:
	HashList();
	int randomNum() const;
	int hashAddress(string key) const;
	bool removeItem(string code);
	bool search(string code);
	bool add(ItemType data, string plateNum);
	void printTable() const;
	void printItemsInIndex(int index) const;
	void output();
	void stattistic();
};

template <class ItemType>
HashList<ItemType>::Item::Item()
{
	code = "";
	next = NULL;
}

template <class ItemType>
HashList<ItemType>::Item::Item(const string &code, const ItemType &data)
{
	this->code = code;
	this->data = data;
	next = NULL;
}

template <class ItemType>
HashList<ItemType>::HashList()
{
	itemCount = 0;
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		hashTable[i] = NULL;
	}
}


template <class ItemType>
int HashList<ItemType>::randomNum() const
{
	srand(time(0));
	int randomNum1 = 0, randomNum2 = 0, randomNum3 = 0, result = 0;
	randomNum1 = rand() % 9 + 1;
	for (int i = 0; i < randomNum1; i++)
	{
		randomNum2 = rand() % 5 + 1;
		randomNum3  = rand() % 6 + 1;
		result = (randomNum2 + randomNum3) / 2;
	}
	return result;
}

template <class ItemType>
int HashList<ItemType>::hashAddress(string key) const
{
	int index = 0, sum = 0, ranNum = 0;
	ranNum = randomNum();
	int *ascii = new int[key.length()];
	for (int i = 0; i < key.length(); i++)
	{
		ascii[i] = (int)key[i];
		sum = sum + ascii[i];
	}
	index = (sum * sum * sum *  ranNum * ranNum) % TABLE_SIZE;
	return index;
}

template <class ItemType>
bool HashList<ItemType>::add(ItemType entryData, string encode)
{
	int index = hashAddress(encode);
	Item* n = new Item(encode, entryData);
	if (hashTable[index] == NULL)
	{
		hashTable[index] = n;
	}
	else
	{
		Item* ptr = hashTable[index];
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
		}
		ptr->next = n;
	}
	itemCount++;
	return true;
}

template <class ItemType>
void HashList<ItemType>::printTable() const
{
	cout << endl<<"The number of cars is: " << itemCount << endl;
	cout << "Listed by plate number (Primary key): " << endl;
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		printItemsInIndex(i);
	}
}

template <class ItemType>
void HashList<ItemType>::printItemsInIndex(int index) const
{
	Item* ptr = hashTable[index];
	if (ptr != NULL)
	{
		cout << "--------------------------" << endl;
		cout << "index [" << index << "] contains the following item." << endl;
		while (ptr != NULL)
		{
			cout << ptr->data;
			ptr = ptr->next;
		}
	}
}

template <class ItemType>
bool HashList<ItemType>::removeItem(string encode)
{
	bool status = false;
	int index = hashAddress(encode);
	Item *ptr = hashTable[index];
	Item *prev = NULL;

	while (ptr != NULL)
	{
		if (ptr->code == encode)
		{
			if (prev == NULL && ptr->next != NULL)
			{
				hashTable[index] = ptr->next;
			}
			else if (prev == NULL && ptr->next == NULL)
			{
				hashTable[index] = NULL;
			}
			else
			{
				prev->next = ptr->next;
			}
			delete ptr;
			status = true;
			cout << "Have deleted..." << endl;
			break;
		}
		prev = ptr;
		ptr = ptr->next;
	}
	return status;
}

template <class ItemType>
void HashList<ItemType>::output()
{
	ofstream fout;
	const char fileName[] = "output.txt";
	fout.open(fileName);
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		Item* ptr = hashTable[i];
		if (ptr != NULL)
		{
			while (ptr != NULL)
			{
				fout << ptr->code << " " << ptr->data << endl;
				ptr = ptr->next;
			}
		}
	}
}

template <class ItemType>
bool HashList<ItemType>::search(string entryCode)
{
	int index = hashAddress(entryCode);
	bool status = false;
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		Item *ptr = hashTable[i];
		while (ptr)
		{
			if (ptr->code == entryCode)
			{
				status = true;
				break;
			}
			ptr = ptr->next;
		}
	}
	return status;
}

template <class ItemType>
void HashList<ItemType>::stattistic()
{
	int index = 0;
	int linkedListCnt = 0, counter[TABLE_SIZE] = { 0 };
	for (int i = 0; i < TABLE_SIZE; i++)
	{
		Item *ptr = hashTable[i];
		while (ptr)
		{
			if (ptr->next != NULL)
			{
				if (i > 0 && counter[i - 1] < counter[i])
				{
					index = i;
				}
				counter[i]++;
			}
			ptr = ptr->next;
		}
		if (counter[i] > 0)
		{
			linkedListCnt++;
		}
	}
	double tempLinkedListCut = linkedListCnt, tempTABLE_SIZE = TABLE_SIZE;
	cout << "The hash table has " << TABLE_SIZE << "spots" << endl;
	cout << "This hash table includes [" << linkedListCnt << "] linked lists" << endl;
	cout << "So, the load factor is " << linkedListCnt << "/" << TABLE_SIZE << " = " << (linkedListCnt * 100) / TABLE_SIZE << "%" << endl;
	cout << "The longest list with index [" << index << "] is: " << counter[index] << endl;
}
#endif // HASH_H_INCLUDED
