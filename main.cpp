/****************************************************
CIS 22C Team # 3
Team members: Tung Lin Lee, Hoang Duong Vu,Nithin Nediyanchath ,Risako Numamoto 
Programmer: Tung Lin Lee
Team Project: Smart Valet Parking Service
Date: 12/9/2016
IDE: Visual Studio
This program will put the customer's information into the
hash table and BST. Then, it will start operate the menu.

Assistants: Hoang Duong Vu(Function deleloper), Nithin Nediyanchath(Check the stability) ,Risako Numamoto(check the stability) 
******************************************************/

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <ctime>

#include "BinarySearchTreePlate.h"
#include "BinarySearchTreeName.h"
#include "CustomerData.h"
#include "Hash.h"
#include "Stack.h"
#define MAX_SIZE 50
using namespace std;
void introduction();
int buildList(const char fileName[], BinarySearchTreePlate<customerData>* treePtrPlate, BinarySearchTreeName<customerData>* treePtrName, HashList<customerData> &h, customerData data[]);
void menu(BinarySearchTreePlate<customerData>* treePtrPlate, BinarySearchTreeName<customerData>* treePtrName, HashList<customerData> h, customerData data[], int& countData);
void display(customerData & anItem);
void backUp(const char fileName[]);

int main()
{
	customerData data[MAX_SIZE];
	const char fileName[] = "customerInfo.txt";
	BinarySearchTreePlate<customerData>* treePtrPlate= new BinarySearchTreePlate<customerData>;
	BinarySearchTreeName<customerData>* treePtrName = new BinarySearchTreeName<customerData>;
	HashList<customerData> h;

	// indroction info
	introduction();

	// Build the hash table, BST
	int countData = buildList(fileName, treePtrPlate, treePtrName, h, data);

	// operate the menu
	menu(treePtrPlate, treePtrName, h, data, countData);

	// save a copy of the original file
	backUp(fileName);

	return 0;
}

void introduction()
{
	cout << "---------------------- Welcome to Smart Valet Parking Service ----------------------" << endl;
	cout << "****************************************************************************************" << endl;
	cout << "This service can drop & go our cars like the parking service in the mall or De Anza school." << endl;
	cout << "The application is to put new data on the new car coming in the parking." << endl;
	cout << "The owner can access to search his / her car and ask for picking up." << endl;
	cout << "Based on the information, we can delete car data after it leaves, count the parking fee according to "
		<< "length of time. (cent / hour)" << endl;
	cout << "****************************************************************************************" << endl;
}

int buildList(const char fileName[], BinarySearchTreePlate<customerData>* treePtrPlate, BinarySearchTreeName<customerData>* treePtrName, HashList<customerData> &h, customerData data[])
{
	int timeIn;
	time_t t = time(0);
	struct tm in;
	localtime_s(&in, &t);
	timeIn = in.tm_hour * 60 + in.tm_min;

	int countData = 0;
	ifstream fin;
	fin.open(fileName);
	string carPlateNum, userName, carBrand;
	if (!fin)
	{
		cerr << "error for opening " << fileName << endl;
		exit(111);
	}
	while (!(fin.eof()))
	{
		fin >> carPlateNum;
		fin >> carBrand;
		fin.ignore();
		getline(fin, userName);
		data[countData].setPlate(carPlateNum);
		data[countData].setBrand(carBrand);
		data[countData].setName(userName);
		data[countData].setTimeIn(timeIn);
		h.add(data[countData], carPlateNum);
		treePtrPlate->insert(data[countData]);
		treePtrName->insert(data[countData]);
		countData++;
	}
	return countData;
}

void menu(BinarySearchTreePlate<customerData>* treePtrPlate, BinarySearchTreeName<customerData>* treePtrName, HashList<customerData> h, customerData data[], int& countData)
{
	Stack<customerData> undoList;
	string carPlateNum, userName, carBrand;
	char choice;
	do{
		cout << "\nA - Add new data" << endl;
		cout << "D - Delete data" << endl;
		cout << "S - Search the information(primary key/secondary key)" << endl;
		cout << "L - List unsorted data/ sorted by primary key/ sorted by secondary key/ indented list" << endl;
		cout << "W - Write data to a file" << endl;
		cout << "T - Statistics" << endl <<endl;
		cout << "U - Undo Delete" << endl;
		cout << "Please enter your choice: ";
		cin >> choice;
		cout << "You Enter [" << choice << "]" << endl << endl << endl;
		switch (tolower(choice))
		{
		case('a') :
		{
			if (countData <= MAX_SIZE)
			{
				int timeIn;
				time_t t = time(0);
				struct tm in;
				localtime_s(&in, &t);
				timeIn = in.tm_hour * 60 + in.tm_min;
				cout << "------------------------------------------" << endl;
				cout << "Please enter the car plate's number: ";
				cin >> carPlateNum;
				cout << "Please enter the Name: ";
				cin.ignore();
				getline(cin, userName);
				cout << "Please enter the brand of car: ";
				cin >> carBrand;
				cout << "Adding data..." << endl;
				data[countData].setPlate(carPlateNum);
				data[countData].setBrand(carBrand);
				data[countData].setName(userName);
				data[countData].getTimeIn();
				data[countData].setTimeIn(timeIn);
				h.add(data[countData], carPlateNum);
				treePtrPlate->insert(data[countData]);
				treePtrName->insert(data[countData]);
				countData++;
			}
			else 
				cout << "There is not enough space for more car. You need to move car out" << endl;
			cout << "-------------------------------------------\n" << endl;
			break;
		}
		case('d') :
		{ 
			cout << "Please enter the car plate number: ";
			cin >> carPlateNum;
			cout << "Please enter the car user name: ";
			cin.ignore();
			getline(cin, userName);
			int check = false;
			int tempindex = 0;
			h.removeItem(carPlateNum);
				while (tempindex < countData&&data[tempindex].getPlate() != carPlateNum)
				{
					tempindex++;
					if (tempindex < countData && data[tempindex].getPlate() == carPlateNum)
						check = true;
				}
						if (tempindex == 0 || check)
						{
							data[tempindex].getTimeOut();
							cout << "The total charge of parking is: " << data[tempindex].getTimeLength() * 4 << " cnets" << endl;		
							cout << "Car has been found and move out from parking lot" << endl;
							treePtrPlate->remove(data[tempindex]);
							treePtrName->remove(data[tempindex]);
							undoList.push(data[tempindex]);
						}			  
					break;
		}
		case('s') :
		{
			int searchChoice, currentPrice = 0;
					  bool found = false;
					  cout << "-------------------------" << endl;
					  cout << "Which method would you like to search?" << endl;
					  cout << "By car plate's number (1)" << endl;
					  cout << "By user's name (2)? " << endl;
					  cout << "Search by synonym (3)" << endl;
					  cin >> searchChoice;
					  if (searchChoice == 1)
					  {
						  cout << "Please enter the car plate's number you wish to search: ";
						  cin >> carPlateNum;
						  found = h.search(carPlateNum);
						  int tempindex;
						  for (tempindex = 0; tempindex < countData && data[tempindex].getPlate() != carPlateNum; tempindex++)
						  {
							  if (data[tempindex + 1].getPlate() == carPlateNum)
							  {
								  found = true;
								  cout << "[Found] Customer info:" << endl;
								  cout << data[tempindex + 1].getPlate() << " " << data[tempindex + 1].getBrand() << " " << data[tempindex + 1].getName() << endl;
							  }
						  }
						  if (found = false)
							  cerr << "[Failed] Sorry. " << carPlateNum << " does exist in this database." << endl;
					  }
					  else if (searchChoice == 2)
					  {
						  cout << "Please enter the owner name you wish to search: ";
						  cin.ignore();
						  getline(cin, userName);
						  cout << "Please enter the car plate's number: ";
						  cin >> carPlateNum;
						  int tempindex;
						  for (tempindex = 0; tempindex < countData; tempindex++)
						  {
							  if (data[tempindex + 1].getName() == userName)
							  {
								  
								  if (data[tempindex + 1].getPlate() == carPlateNum)
								  {
									  found = true;
									  cout << "[Found]" << endl;
									  cout << data[tempindex + 1].getPlate() << " " << data[tempindex + 1].getBrand() << " " << data[tempindex + 1].getName() << endl;
								  }
							  }
						  }

						  if (found != true)
						  {
							  cerr << "[ Failed ]" << endl;
						  }
					  }
					  else if (searchChoice == 3)
					  {
						  cout << "Please enter the synonym you wish to search: ";
						  cin.ignore();
						  getline(cin, userName);
						  int tempindex;
						  for (tempindex = 0; tempindex < countData; tempindex++)
						  {
							  if (data[tempindex + 1].getName() == userName)
							  {
									  found = true;
									  cout << "Found the synonym - ";
									  cout << data[tempindex + 1].getPlate() << " " << data[tempindex + 1].getBrand() << " " << data[tempindex + 1].getName() << endl;
							  }
						  }
						  if (found != true)
						  {
							  cerr << "[ Failed ]" << endl;
						  }
					  }
					  cout << "-------------------------" << endl;
					  break;
		}
		case('l') :
		{
					  int LChoice;
					  cout << "1: List unsorted data" << endl;
					  cout << "2: List data sorted by car plate number:" << endl;
					  cout << "3: List data sorted by user name:" << endl;
					  cout << "4: List data by indented list" << endl;
					  cout << "Please enter your choice: ";
					  cin >> LChoice;
					  cout << endl;
					  switch (LChoice)
					  {
					  case 1:
					  {
								cout << "List unsorted data" << endl;
								for (int i = 0; i < countData; i++)
									cout << "[ " << left << setw(7) << data[i].getPlate() << " | " << left << setw(16) << data[i].getName() << " | " << left << setw(9) << data[i].getBrand() << " ]"<<endl;
								break;
					  }
					  case 2:
						  cout << "By car plate number" << endl;
						  h.printTable();
						  cout << "-------------------------" << endl;
						  break;
					  case 3:
						  cout << "By user name" << endl;
						  cout << endl << "Sorted by car plate number(Unique Key Tree):" << endl;
						  treePtrPlate->inOrder(display);
						  cout << endl << "Sorted by user name(Secondary Key Tree):" << endl;
						  treePtrName->inOrder(display);
						  break;
					  case 4:
						  cout << "By indented list" << endl;
						  cout << "\n---------------------------------------------------------------------------" << endl;
						  cout << endl << "Sorted by car plate number:" << endl;
						  cout << "---------------------------------------------------------------------------" << endl;
						  treePtrPlate->indentedList(display);
						  cout << "\n---------------------------------------------------------------------------" << endl;
						  cout << endl << "Sorted by user name:" << endl;
						  cout << "---------------------------------------------------------------------------" << endl;
						  treePtrName->indentedList(display);
						  break;
					  default:
					  {
								 cout << "Please enter the valid choice:" << endl;
								 cout << "Backing to menu..." << endl;
					  }
					  }
					  break;
		}
		case('w') :
			cout << "-------------------------" << endl;
			cout << "Writing data to a file..." << endl;
			cout << "It will print base on the hash table sequence" << endl;
			h.output();
			cout << "-------------------------" << endl;
			break;
		case('t') :
		{

					  cout << "-------------------------" << endl;
					  cout << "Showing the statistics..." << endl;
					  h.stattistic();
					  cout << "-------------------------" << endl;
					  break;
		}
		case('u'):
		{
			if (!undoList.isEmpty()) {
				cout << endl << "Undo Delete Last Car...." << endl;
				customerData tempData;
				undoList.pop(tempData);
				data[countData] = tempData;

				h.add(data[countData], carPlateNum);
				treePtrPlate->insert(data[countData]);

				treePtrName->insert(data[countData]);
				countData++;
			}
			else cout << endl << "There is no more cars to undo delete" << endl;
			break;
		}
		default:
			if (tolower(choice) != 'q')
			{
				cout << "Please enter the valid key " << endl;
			}
		}
	} while (tolower(choice) != 'q');
}

// display function to pass to BST traverse functions
void display(customerData & anItem)
{
	cout << anItem;
}

void backUp(const char fileName[])
{
	ifstream fin;
	fin.open(fileName);
	string carPlateNum, userName, carBrand;
	if (!fin)
	{
		cerr << "error for opening " << fileName << endl;
		exit(111);
	}

	ofstream fout;
	const char fileName2[] = "BackUp.txt";
	fout.open(fileName2);
	if (!fout)
	{
		cerr << "Error to open " << fileName << "..." << endl;
		exit(1);
	}

	while (!(fin.eof()))
	{
		fin >> carPlateNum;
		fin >> carBrand;
		fin.ignore();
		getline(fin, userName);
		fout << carPlateNum << " " << carBrand << " " << userName << endl;
	}
	fout.close();
}
