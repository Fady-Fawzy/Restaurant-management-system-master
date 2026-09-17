#pragma once
#include "Action.h"

class RequestAction : public Action
{
private:
    OrderType type;
    int timestep;
    double price;
    double size;
    double distance;
	bool shareable;
    int duration;
    int seats;
public:
    RequestAction(int ID, OrderType type, double size, int seats, double pr, double distance, bool share, int dur, int t)
        : Action(ID,t), type(type), size(size), seats(seats), price(pr), distance(distance), shareable(share), duration(dur)
    {
    }
    void Act(Restaurant* res);
    string orderTypeStr();
    int GetID() { return OrderID; }
};