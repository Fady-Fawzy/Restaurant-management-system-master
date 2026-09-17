#pragma once
#include "Order.h"
class Ot :public Order
{
	private:
	double price;
	public:
	Ot(int orderID, int s, double pr);
	virtual OrderType GetType() const;
};

