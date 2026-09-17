#pragma once
#include "Order.h"
class Ovg :
    public Order
{
private:
	Scooter* assignedScooter;
	double distance;
	double priority;
	int readyTime;
public:
	Ovg(int orderID, double s, double pr, double dist, double pri);
	virtual Scooter* AssignedScooter() const;
	OrderType GetType() const;
	virtual double GetDistance();
	virtual double GetPriority();
	virtual void setassignedscooter(Scooter* s);
};

