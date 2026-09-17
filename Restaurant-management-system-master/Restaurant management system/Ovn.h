#pragma once
#include "Order.h"
class Ovn :public Order
{
private:
	Scooter* assignedScooter;
	double Distance;
public:
	Ovn(int orderID, double s, double pr, double d);
	virtual OrderType GetType() const override;
	virtual double GetDistance() override;
	virtual Scooter* AssignedScooter() const override;
	virtual void setassignedscooter(Scooter* s);
};

