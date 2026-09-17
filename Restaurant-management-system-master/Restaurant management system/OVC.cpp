#include "OVC.h"

Ovc::Ovc(int orderID, int s, double pr, double dist)
    : Order(orderID, s),
    assignedScooter(nullptr),
    distance(dist)
{
    this->price = pr; 
}

Scooter* Ovc::AssignedScooter() const 
{
    return assignedScooter;
}

OrderType Ovc::GetType() const
{
    return OrderType::OVC;
}

double Ovc::GetDistance()
{
    return distance;
}

void Ovc::setassignedscooter(Scooter* s)
{
	assignedScooter = s;
}

