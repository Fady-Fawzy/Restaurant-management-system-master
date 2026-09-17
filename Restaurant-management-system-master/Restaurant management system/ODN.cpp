#include "ODN.h"

Odn::Odn(int orderID, int s, double pr, int seats, int dur, bool share)
    : Order(orderID, s),
    assignedTable(nullptr),
    numSeats(seats),
    duration(dur),
    canShare(share)
{
    this->price = pr; 
}
OrderType Odn::GetType() const
{
    return OrderType::ODN;
}
Table* Odn::AssignedTable() const
{
    return assignedTable;
}

void Odn::setAssignedTable(Table* t)
{
	assignedTable = t;
}

int Odn::GetSeats() const
{
    return numSeats;
}

int Odn::getDuration() const
{
    return duration;
}
bool Odn::getCanShare() const
{
    return canShare;
}

double Odn::GetPriority() const
{
    return duration;
}

