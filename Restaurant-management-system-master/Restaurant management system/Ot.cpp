#include "Ot.h"

Ot::Ot(int orderID, int s, double pr)
    : Order(orderID, s)
{
    this->price = pr; 
    this->RequestTime = 0;
    this->FinishTime = 0;
    this->assignedChef = nullptr;
}

OrderType Ot::GetType() const
{
    return OrderType::OT;
}