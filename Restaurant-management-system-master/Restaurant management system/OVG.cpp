#include "OVG.h"

Ovg::Ovg(int orderID, double s, double pr, double dist, double pri)
    : Order(orderID, static_cast<int>(s)),
    assignedScooter(nullptr),
    distance(dist)
{
    this->price = pr; 
    this->priority = 10.0 * this->price - 5.0 * this->distance - 5.0 * s;
}

Scooter* Ovg::AssignedScooter() const 
{
    return assignedScooter;
}

OrderType Ovg::GetType() const
{
    return OrderType::OVG;
}

double Ovg::GetDistance()
{
    return distance;
}

double Ovg::GetPriority()
{
    return priority;
}

void Ovg::setassignedscooter(Scooter* s)
{
	assignedScooter = s;
}

