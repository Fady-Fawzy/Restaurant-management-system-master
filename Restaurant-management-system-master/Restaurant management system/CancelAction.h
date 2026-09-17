#pragma once
#include "Action.h"
class CancelAction : public Action
{
public:
    CancelAction(int ID, int t) : Action(ID, t) {}
    void Act(Restaurant* res);
	int GetID() { return OrderID; }
};