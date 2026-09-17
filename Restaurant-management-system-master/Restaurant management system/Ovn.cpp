#include "Ovn.h"

Ovn::Ovn(int orderID, double s, double pr, double d)
    : Order(orderID, static_cast<int>(s)),
    assignedScooter(nullptr),
    Distance(d)
{
    this->price = pr; 
    this->RequestTime = 0;
    this->FinishTime = 0;
    this->assignedChef = nullptr;
}

OrderType Ovn::GetType() const
{
    return OrderType::OVN;
}

double Ovn::GetDistance()
{
    return Distance;
}

Scooter* Ovn::AssignedScooter() const 
{
    return assignedScooter;
}

void Ovn::setassignedscooter(Scooter* s)
{
    assignedScooter = s;
}
