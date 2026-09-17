#pragma once
#include "Order.h"
#include "Restaurant.h"
class Action
{
protected:
	int OrderID;
	int time;
public:
	Action(int ID, int t)
	{
		OrderID = ID;
		time = t;
	}
	virtual void Act(Restaurant* res) = 0;
	int GetTime() { return time; }
	friend std::ostream& operator<<(std::ostream& out, Action* action);
};
