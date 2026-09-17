#pragma once
#include <iostream>
#include "LinkedQueue.h"
#include "ArrayStack.h"
#include "PriQueue.h"
#include "Cook_Ords.h"
#include "PEND_OVC.h"
#include "Ready_OV.h"
#include "Fit_Tables.h"
#include "Order.h"
#include "Chef.h"
#include "Scooter.h"
#include "Table.h"
#include "Action.h"

class UI
{
public:
    UI();
    ~UI();

    void PrintState(
        int timestep,

        LinkedQueue<Order*>& PEND_ODG,
        LinkedQueue<Order*>& PEND_ODN,
        LinkedQueue<Order*>& PEND_OT,
        LinkedQueue<Order*>& PEND_OVN,
        PEND_OVC& PEND_OVC,
        priQueue<Order*>& PEND_OVG,

        LinkedQueue<Chef*>& Free_CS,
        LinkedQueue<Chef*>& Free_CN,

        Cook_Ords& Cooking_Orders,

        LinkedQueue<Order*>& RDY_OT,
        Ready_OV& RDY_OV,
        LinkedQueue<Order*>& RDY_OD,

        priQueue<Order*>& InServ_Orders,

        LinkedQueue<Order*>& Cancelled_Orders,
        ArrayStack<Order*>& Finished_Orders,

        priQueue<Scooter*>& Free_Scooters,
        priQueue<Scooter*>& Back_Scooters,
        LinkedQueue<Scooter*>& Maint_Scooters,

        Fit_Tables& Free_Tables,
        Fit_Tables& Busy_Sharable,
        Fit_Tables& Busy_No_Share,
        LinkedQueue<Action*> Actions,
        LinkedQueue<Order*> PEND_COMBO,
		LinkedQueue<Order*>& RDY_COMBO,
        LinkedQueue<Order*>& Pending_Rescue
    );
};
