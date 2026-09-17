#include "ODG.h"

Odg::Odg(int orderID, int s, double pr, int seats, int dur, bool share)
    : Order(orderID, s),
    assignedTable(nullptr),
    numSeats(seats),
    duration(dur),
    canShare(share)
{
    this->price = pr; 
}
OrderType Odg::GetType() const
{
    return OrderType::ODG;
}
Table* Odg::AssignedTable() const
{
    return assignedTable;
}

void Odg::setAssignedTable(Table* t)
{
	assignedTable = t;
}

int Odg::GetSeats() const
{ 
    return numSeats; 
}
int Odg::getDuration() const 
{ 
    return duration;
}
bool Odg::getCanShare() const 
{ 
    return canShare;
}

double Odg::GetPriority() const
{
    return duration;
}

