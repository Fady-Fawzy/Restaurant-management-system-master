#include "Table.h"

Table::Table(int id, int capacity)
{
	this->id = id;
	this->capacity = capacity;
	freeseats = capacity;
}

int Table::getId() const
{
	return id;
}

int Table::getCapacity() const
{
	return capacity;
}

int Table::getFreeseats() const
{
	return freeseats;
}

void Table::reserveSeats(int numSeats)
{
	freeseats = freeseats - numSeats;
}

void Table::freeSeats(int numSeats)
{
	freeseats = freeseats + numSeats;
}

ostream& Table::operator<<(ostream& os)
{
	os << "Table ID: " << id << ", Capacity: " << capacity << ", Free Seats: " << freeseats;
	return os;
}
