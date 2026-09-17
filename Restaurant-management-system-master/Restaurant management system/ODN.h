#pragma once
#include "Order.h"

class Odn : public Order
{
private:
	Table* assignedTable;
	int numSeats;
	int duration;
	bool canShare;
public:
	Odn(int orderID, int s, double pr, int seats, int dur, bool share);
	virtual OrderType GetType() const override;
	virtual Table* AssignedTable() const override;
	virtual void setAssignedTable(Table* t) override;
	virtual int GetSeats() const override;
	virtual int getDuration() const override;
	virtual bool getCanShare() const override;
	virtual double GetPriority() const override;
};

	