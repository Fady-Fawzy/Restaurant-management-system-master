#include"Action.h"
#include "RequestAction.h"
#include "CancelAction.h"
#include <iostream>
std::ostream& operator<<(std::ostream& out, Action* action)
{
    if (dynamic_cast<RequestAction*>(action) != NULL)
    {
        RequestAction* ReqAction = dynamic_cast<RequestAction*>(action);
        return out << '[' << ReqAction->orderTypeStr() << ", " << (ReqAction)->GetTime() << ", " << ReqAction->GetID() << ']';
    }
    else if (dynamic_cast<CancelAction*>(action) != NULL)
    {
        CancelAction* CancelledAction = dynamic_cast<CancelAction*>(action);
        return out << "(X, " << (CancelledAction)->GetTime() << ", " << (CancelledAction)->GetID() << ')';
    }
}