#pragma once
#include <iostream>
using namespace std;
class Table
{
private:
	int id;
	int capacity;
	int freeseats;
public:
	Table(int id, int capacity);
	int getId() const;
	int getCapacity() const;
	int getFreeseats() const;
	//void setFreeseats(int freeseats);
	void reserveSeats(int numSeats);
	void freeSeats(int numSeats);
	ostream& operator<<(ostream& os);
};

