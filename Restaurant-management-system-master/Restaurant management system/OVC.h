#pragma once
#include "Order.h"
class Ovc:
	public Order

{
private:
	Scooter* assignedScooter;
	double distance;
public:
	Ovc(int orderID, int s, double pr , double dist);
	virtual Scooter* AssignedScooter() const;
	OrderType GetType() const;
	virtual double GetDistance();
	virtual void setassignedscooter(Scooter* s);
};


