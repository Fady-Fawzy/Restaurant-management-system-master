#include "Restaurant.h"
#include "Order.h"
#include "Chef.h"
#include "Action.h"
#include "RequestAction.h"
#include "CancelAction.h"
#include "UI.h"
#include "Scooter.h"
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>

namespace {

bool isOvType(OrderType t)
{
    return t == OVN || t == OVC || t == OVG || t == COMBO;
}

bool isOdType(OrderType t)
{
    return t == ODG || t == ODN;
}

} // namespace

Restaurant::Restaurant()
    : pUI(new UI())
{
	TimeStep = 0;
}



Restaurant::~Restaurant()
{
    Order* o = nullptr;
    int pri = 0;
    Chef* ch = nullptr;
    Table* tbl = nullptr;
    Scooter* sc = nullptr;
    Action* act = nullptr;

    while (PEND_ODG.dequeue(o)) {
        delete o;
    }
    while (PEND_ODN.dequeue(o)) {
        delete o;
    }
    while (PEND_OT.dequeue(o)) {
        delete o;
    }
    while (PEND_OVN.dequeue(o)) {
        delete o;
    }
    while (PEND_OVCL.dequeue(o)) {
        delete o;
    }
    while (PEND_OVG.dequeue(o, pri)) {
        delete o;
    }
    while (Cooking_Orders.dequeue(o, pri)) {
        delete o;
    }
    while (RDY_OT.dequeue(o)) {
        delete o;
    }
    while (RDY_OVL.dequeue(o)) {
        delete o;
    }
    while (RDY_OD.dequeue(o)) {
        delete o;
    }
    while (InServ_Orders.dequeue(o, pri)) {
        delete o;
    }
    while (Cancelled_Orders.dequeue(o)) {
        delete o;
    }
    while (Finished_Orders.pop(o)) {
        delete o;
    }

    while (Free_CS.dequeue(ch)) {
        delete ch;
    }
    while (Free_CN.dequeue(ch)) {
        delete ch;
    }

    while (Free_Tables.dequeue(tbl, pri)) {
        delete tbl;
    }
    while (Busy_Sharable.dequeue(tbl, pri)) {
        delete tbl;
    }
    while (Busy_No_Share.dequeue(tbl, pri)) {
        delete tbl;
    }

    while (Free_Scooters.dequeue(sc, pri)) {
        delete sc;
    }
    while (Back_Scooters.dequeue(sc, pri)) {
        delete sc;
    }
    while (Maint_Scooters.dequeue(sc)) {
        delete sc;
    }

    while (Actions.dequeue(act)) {
        delete act;
    }
    while (Pending_Rescue.dequeue(o)) {
        delete o;
    }
    delete pUI;
    pUI = nullptr;
}

void Restaurant::add_odg(Order* o)
{
    PEND_ODG.enqueue(o);
}

void Restaurant::add_odn(Order* o)
{
    PEND_ODN.enqueue(o);
}

void Restaurant::add_ot(Order* o)
{
    PEND_OT.enqueue(o);
}

void Restaurant::add_ovn(Order* o)
{
    PEND_OVN.enqueue(o);
}

void Restaurant::add_ovc(Order* o)
{
    PEND_OVCL.enqueue(o);
}

void Restaurant::add_ovg(Order* o, double priority)
{
    PEND_OVG.enqueue(o, static_cast<int>(priority));
}

void Restaurant::overwait_order()
{
	Ready_OV tempQueue;
	while (!RDY_OVL.isEmpty())
    {
        Order* (o) = nullptr;
        RDY_OVL.dequeue(o);
        if(o->GetType() == OVG && TimeStep - (o->getcookduration() + o->getCookstarttime()) > Tthreshold)
        {
            overwait.enqueue(o, TimeStep - o->GetRequestTime());
        }
        else
        {
            tempQueue.enqueue(o);
        }
    }
    while (!tempQueue.isEmpty())
    {
        Order* o = nullptr;
        tempQueue.dequeue(o);
        RDY_OVL.enqueue(o);
    }
}
void Restaurant::AddAction(Action* pAction)
{
    Actions.enqueue(pAction);
}
void Restaurant::LoadActions(string& filename)
{
    int CScount, CNCount, CSspeed, CNspeed, ScooterCount, ScooterSpeed, MainOrds, MainDur, TotalTables, TableCount, TableCap, Tth, TotalActions;
    std::ifstream InputFile(filename);
    InputFile >> CNCount >> CScount >> CNspeed >> CSspeed >> ScooterCount >> ScooterSpeed >> MainOrds >> MainDur >> TotalTables;
    for(int i = 0; i < CScount; i++)
    {
        Chef* c = new Chef(i + 1, 'S', CSspeed);
        Free_CS.enqueue(c);
	}
    for(int i = 0; i < CNCount; i++)
    {
        Chef* c = new Chef(CScount + i + 1, 'N', CNspeed);
        Free_CN.enqueue(c);
	}
    int TableSum = 0;
    while (TableSum < TotalTables)
    {
		InputFile >> TableCount >> TableCap;
        for (int i = 0; i < TableCount; i++)
        {
           Table* t = new Table(TableSum + i + 1, TableCap);
		   Free_Tables.enqueue(t,t->getCapacity());
        }
		TableSum += TableCount;
    }
    for(int i = 0; i < ScooterCount; i++)
    {
        Scooter* s = new Scooter(i + 1, ScooterSpeed, MainOrds, MainDur);
        Free_Scooters.enqueue(s, s->GetSpeed());
	}
	InputFile >> Tth;
    Tthreshold = Tth;
	InputFile >> TotalActions;
    for (int i = 0; i < TotalActions; i++)
    {
        char ActionType;
        InputFile >> ActionType;
        if (ActionType == 'Q')
        {
            std::string OrderType;
            InputFile >> OrderType;
            int Tq, ID, size, price;
            InputFile>> Tq >> ID >> size >> price;
            if (OrderType == "ODG" || OrderType == "ODN")
            {
                int Seats, Duration;
                bool shareable;
                char share;
				InputFile >> Seats >> Duration >> share;
                if(share == 'Y')
                {
                    shareable = true;
                }
                else
                {
                    shareable = false;
				}
                if (OrderType == "ODG")
                {
                    Action* act = new RequestAction(ID, ODG, size, Seats, price,0, shareable, Duration, Tq);
                    AddAction(act);
                }
                else
                {
                    Action* act = new RequestAction(ID, ODN, size, Seats, price, 0, shareable, Duration, Tq);
                    AddAction(act);
                }
            }
            else if (OrderType == "OVC" || OrderType == "OVN" || OrderType == "OVG")
            {
                int Distance;
				InputFile >> Distance;
                if(OrderType == "OVC")
                {
                    Action* act = new RequestAction(ID, OVC, size, 0, price, Distance, false, 0, Tq);
                    AddAction(act);
                }
                else if (OrderType == "OVN")
                {
                    Action* act = new RequestAction(ID, OVN, size, 0, price, Distance, false, 0, Tq);
                    AddAction(act);
                }
                else
                {
                    Action* act = new RequestAction(ID, OVG, size, 0, price, Distance, false, 0, Tq);
                    AddAction(act);
				}
            }
            else if (OrderType == "OT")
            {
                Action* act = new RequestAction(ID, OT, size, 0, price, 0, false, 0, Tq);
                AddAction(act);
            }
            else if (OrderType == "COMBO")
            {
                int Distance;
                InputFile >> Distance;
                Action* act = new RequestAction(ID, COMBO, size, 0, price, Distance, false, 0, Tq);
                AddAction(act);
            }
        }
        else if(ActionType == 'X')
        {
            int Tcancel, ID;
            InputFile >> Tcancel >> ID;
            Action* act = new CancelAction(ID, Tcancel);
            AddAction(act);
		}
    }
}
void Restaurant::Request()
{
    Action* temp = nullptr;
    LinkedQueue<Action*> tempQueue;
    while (Actions.dequeue(temp))
    {
        if (dynamic_cast<RequestAction*>(temp))
        {
            if (TimeStep >= temp->GetTime())
            {
                temp->Act(this);
                delete temp;
            }
            else
            {
                tempQueue.enqueue(temp);
            }
        }
        else
        {
            tempQueue.enqueue(temp);
        }
    }
    while (tempQueue.dequeue(temp))
    {
        Actions.enqueue(temp);
    }
}
void Restaurant::Cancel()
{
    Action* temp = nullptr;
    LinkedQueue<Action*> tempQueue;
    while (Actions.dequeue(temp))
    {
        if (dynamic_cast<CancelAction*>(temp))
        {
            if (TimeStep >= temp->GetTime())
            {
                temp->Act(this);
                delete temp;
            }
            else
            {
                tempQueue.enqueue(temp);
            }
        }
        else
        {
            tempQueue.enqueue(temp);
        }
    }
    while (tempQueue.dequeue(temp))
    {
        Actions.enqueue(temp);
    }
}
void Restaurant::CheckScooters()
{
    Scooter* tempScooter = nullptr;
    int pri = 0;
    priQueue<Scooter*> tempQueue;

    while (!Back_Scooters.isEmpty())
    {
        Back_Scooters.dequeue(tempScooter, pri);

        if (TimeStep >= pri + tempScooter->GetDileveryDuration())
        {
            tempScooter->SetDeliveryDuration(0);

            // Added the check for broken scooters returning to base
            if (tempScooter->getIsReturningBroken() || tempScooter->getNoOfDeliveries() >= tempScooter->GetMainOrds())
            {
                Maint_Scooters.enqueue(tempScooter);
                tempScooter->SetMaintStartStep(TimeStep);
                tempScooter->addBusyTime(tempScooter->GetMainDur());

                // Reset the broken state since it is now in maintenance
                tempScooter->setIsReturningBroken(false);
                tempScooter->resetDeliveries();
            }
            else
            {
                Free_Scooters.enqueue(tempScooter, tempScooter->getDistance());
            }
        }
        else
        {
            tempQueue.enqueue(tempScooter, pri);
        }
    }
    while (tempQueue.dequeue(tempScooter, pri))
    {
        Back_Scooters.enqueue(tempScooter, pri);
    }
    LinkedQueue<Scooter*> tempMaintQueue;
    while (!Maint_Scooters.isEmpty())
    {
        Maint_Scooters.dequeue(tempScooter);

        if (TimeStep >= tempScooter->GetMaintStartStep() + tempScooter->GetMainDur())
        {
            Free_Scooters.enqueue(tempScooter, tempScooter->getDistance());
        }
        else
        {
            tempMaintQueue.enqueue(tempScooter);
        }
    }

    while (tempMaintQueue.dequeue(tempScooter))
    {
        Maint_Scooters.enqueue(tempScooter);
        /* tempScooter->addBusyTime(tempScooter->GetMainDur());*/
    }
}
void Restaurant::RunSimulation() {
    string Inputfilename, Outputfilename;
    int mode;
    cout << "Enter input filename: ";
    cin >> Inputfilename;
    LoadActions(Inputfilename);
	cout << "Enter output filename: ";
    cin >> Outputfilename;
    cout << "Choose mode: 1 for Interactive, 2 for Silent: ";
    cin >> mode;
    while (!Actions.isEmpty() ||
        !PEND_ODG.isEmpty() ||
        !PEND_ODN.isEmpty() ||  
        !PEND_OT.isEmpty() ||   
        !PEND_OVN.isEmpty() ||  
        !PEND_OVCL.isEmpty() || 
		!PEND_OVG.isEmpty() ||
		!PEND_COMBO.isEmpty() ||
        !Cooking_Orders.isEmpty() ||
        !RDY_OD.isEmpty() ||    
        !InServ_Orders.isEmpty()|| 
        !PEND_OVG.isEmpty() ||
        !RDY_OT.isEmpty() ||
        !RDY_OVL.isEmpty()||
		!RDY_COMBO.isEmpty() ||
        !Back_Scooters.isEmpty()||
        !Pending_Rescue.isEmpty() ||
        !Maint_Scooters.isEmpty()|| !overwait.isEmpty())
    {
        

        if (TimeStep == 571)
        {
            int x = 0;
        }
        if (!Actions.isEmpty()) Request();
        if (!Actions.isEmpty())  Cancel();
        AssignChef();
        move_from_cooking_to_ready();
        AssignTable();       // table
		overwait_order();      // over-waiting OV orders
        AssignRescueScooter(); // rescue scooters
        AssignScooter();     // scooters
        
        FinalizeTakeaway();  // takeaway

        CheckFinishedDeliveryOrders(); // delivery
        CheckFinishedDineInOrders();   // dine-in

        CheckScooters();
        if (mode == 1) {
            pUI->PrintState(TimeStep,
                PEND_ODG,
                PEND_ODN,
                PEND_OT,
                PEND_OVN,
                PEND_OVCL,
                PEND_OVG,
                Free_CS,
                Free_CN,
                Cooking_Orders,
                RDY_OT,
                RDY_OVL,
                RDY_OD,
                InServ_Orders,
                Cancelled_Orders,
                Finished_Orders,
                Free_Scooters,
                Back_Scooters,
                Maint_Scooters,
                Free_Tables,
                Busy_Sharable,
                Busy_No_Share,
                Actions,
                PEND_COMBO,
                RDY_COMBO,
                Pending_Rescue);
            cout << "Press any key to go to next timestep: ";
            system("Pause");
        }
        TimeStep++;
    }
    TimeStep--;
	cout << "Simulation finished. Generating output file..." << endl;
	GenerateOutputFile(Outputfilename);
	cout << "Output file generated successfully." << endl;
}
bool Restaurant::CancelOVC(int targetID)
{
    Order* tempOrd = nullptr;
    PEND_OVCL.cancelorder(targetID, tempOrd);
    if (tempOrd) {
        Cancelled_Orders.enqueue(tempOrd);
        return true;
    }
    Cooking_Orders.cancelorder(targetID, tempOrd);
    if (tempOrd) {
        Cancelled_Orders.enqueue(tempOrd);
        Chef* ch = tempOrd->AssignedChef();
        if (ch != nullptr) {
            if (ch->getType() == 'S') {
                Free_CS.enqueue(ch);
            } else {
                Free_CN.enqueue(ch);
            }
			ch->addBusyTime(TimeStep - tempOrd->getCookstarttime());
            ch->addBusyTime(-1*(tempOrd->getcookduration()));
            tempOrd->setAssignedChef(nullptr);
        }
        return true;
    }
    RDY_OVL.cancelorder(targetID, tempOrd);
    if (tempOrd) {
        Cancelled_Orders.enqueue(tempOrd);
        return true;
    }
    return false;
}

void Restaurant::AssignTable() {
    while (true) {
        Order* order = nullptr;
        if (!RDY_OD.peek(order)) {
            break;
        }
        int requiredSeats = order->GetSeats();
        Table* bestTable = nullptr;
        if (order->getCanShare())
        {
            if (Busy_Sharable.getBest(requiredSeats, bestTable)) {
                RDY_OD.dequeue(order);
                bestTable->reserveSeats(requiredSeats);
                order->setAssignedTable(bestTable);
                order->setServStart(TimeStep);
                order->setFinishTime(TimeStep + order->getDuration());
                InServ_Orders.enqueue(order, -order->GetPriority());
            }
            else if (Free_Tables.getBest(requiredSeats, bestTable)) {
                RDY_OD.dequeue(order);
                order->setAssignedTable(bestTable);
                bestTable->reserveSeats(requiredSeats);
                order->setServStart(TimeStep);
                order->setFinishTime(TimeStep + order->getDuration());
                InServ_Orders.enqueue(order, -order->GetPriority());
                Busy_Sharable.enqueue(bestTable, bestTable->getFreeseats());
            }
            else
            {
                break;
            }
        }
        else if (!order->getCanShare())
        {
            if (Free_Tables.getBest(requiredSeats, bestTable)) {
                RDY_OD.dequeue(order);
                order->setAssignedTable(bestTable);
                bestTable->reserveSeats(requiredSeats);
                order->setServStart(TimeStep);
                order->setFinishTime(TimeStep + order->getDuration());
                InServ_Orders.enqueue(order, -order->GetPriority());
                Busy_No_Share.enqueue(bestTable, bestTable->getFreeseats());
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
}
void Restaurant::CheckFinishedDeliveryOrders()
{
    priQueue <Order*> tempqueue;
    while (!InServ_Orders.isEmpty())
    {
        int pri = 0;
        Order* o = nullptr;
        InServ_Orders.dequeue(o, pri);

        bool needsRescue = false;
        if (isOvType(o->GetType()) && o->GetType() != COMBO)
        {
            Scooter* sc = o->AssignedScooter();
            if (sc && sc->getWillFail() && TimeStep >= sc->getBreakdownTimeStep())
            {
                needsRescue = true;
            }
        }

        if (needsRescue)
        {
            Pending_Rescue.enqueue(o);
        }
        else if (TimeStep >= o->GetFinishTime() && isOvType(o->GetType()))
        {
            if (o->GetType() == COMBO)
            {
                Finished_Orders.push(o);
                Scooter* TempScooter = nullptr;
                COMBOorder* Comb = dynamic_cast<COMBOorder*>(o);
                LinkedQueue<Scooter*> assignedScooters = Comb->getAssignedScooters();
                while (assignedScooters.dequeue(TempScooter))
                {
                    Back_Scooters.enqueue(TempScooter, o->GetFinishTime());
                }
                Comb->FreeBackScooters();
            }
            else {
                Finished_Orders.push(o);
                Scooter* sc = o->AssignedScooter();
                o->setassignedscooter(nullptr);
                Back_Scooters.enqueue(sc, o->GetFinishTime());
            }
        }
        else
        {
            tempqueue.enqueue(o, pri);
        }
    }

    Order* temporder = nullptr;
    int p = 0;
    while (tempqueue.dequeue(temporder, p))
    {
        InServ_Orders.enqueue(temporder, p);
    }
}

void Restaurant::CheckFinishedDineInOrders()
{
    priQueue <Order*> tempqueue1;
    while (!InServ_Orders.isEmpty())
    {
        int pri = 0;
        Order* o = nullptr;
        bool x = InServ_Orders.dequeue(o, pri);
        if (TimeStep >= o->GetFinishTime()&&isOdType(o->GetType()))
        {
            bool temp = Finished_Orders.push(o);
            Table* t = o->AssignedTable();
            t->freeSeats(o->GetSeats()); 
            if (t->getFreeseats() == t->getCapacity() || !o->getCanShare()) 
            {
				t->freeSeats(t->getCapacity() - t->getFreeseats());
                Free_Tables.enqueue(t, t->getFreeseats());
				priQueue<Table*> tempqueue2;
				Table* t2 = nullptr;
                int p = 0;
                while (Busy_Sharable.dequeue(t2, p))
                {
                    if (t2 != t)
                    {
                        tempqueue2.enqueue(t2, p);
                    }
				}
                while (tempqueue2.dequeue(t2, p))
                {
                    Busy_Sharable.enqueue(t2, p);
				}
                while (Busy_No_Share.dequeue(t2, p))
                {
                    if (t2 != t)
                    {
                        tempqueue2.enqueue(t2, p);
                    }
				}
                while (tempqueue2.dequeue(t2, p))
                {
                    Busy_No_Share.enqueue(t2, p);
                }

			}
            else if (t->getFreeseats() < t->getCapacity() && o -> getCanShare())
            {
				priQueue<Table*> tempqueue3;
                int pr = 0;
				Table* t3 = nullptr;
                while (Busy_Sharable.dequeue(t3, pr))
                {
                        tempqueue3.enqueue(t3, pr);
                }
                while (tempqueue3.dequeue(t3, pr))
                {
                    Busy_Sharable.enqueue(t3, t3->getFreeseats());
				}
            }
            o->setAssignedTable(nullptr);
        }
        else
        {
            tempqueue1.enqueue(o, pri);
        }
    }
    Order* temporder = nullptr;
    int p = 0;
    while (tempqueue1.dequeue(temporder, p))
    {
        InServ_Orders.enqueue(temporder, p);
    }
}

void Restaurant::AssignScooter() {
    LinkedQueue<Order*> RdyTemp;
    LinkedQueue<Order*> ComboTemp;
    Order* temp;
    while (true) {
        Order* order = nullptr;
        Scooter* scooter = nullptr;
        int pri = 0;
        if (!RDY_OVL.peek(order) && !RDY_COMBO.peek(order) &&!overwait.peek(order, pri))
        {
            break;
        }
        if (overwait.peek(order, pri))
        {
            if (Free_Scooters.dequeue(scooter, pri)) {
                overwait.dequeue(order, pri);
                order->setassignedscooter(scooter);
                order->setServStart(TimeStep);
                int deliveryTime = ceil((double)order->GetDistance() / scooter->getSpeed());
                order->setFinishTime(TimeStep + deliveryTime);
                scooter->deliver(order->GetDistance());
                InServ_Orders.enqueue(order, -order->GetPriority());
                scooter->SetDeliveryDuration(deliveryTime);
                scooter->addBusyTime(deliveryTime * 2);

                scooter->setWillFail(false);
                if (rand() % 100 < 3)
                {
                    scooter->setWillFail(true);
                    int dist = (int)order->GetDistance();
                    int bDist = (dist > 1) ? (1 + rand() % (dist - 1)) : 1;
                    scooter->setBreakdownDistance(bDist);
                    int bTime = ceil((double)bDist / scooter->getSpeed());
                    scooter->setBreakdownTimeStep(TimeStep + bTime);
                }
            }
            else
            {
                break;
            }
        }

        else if (RDY_COMBO.peek(order))
        {
            if (Free_Scooters.getCount() >= order->GetScooterCount())
            {
                RDY_COMBO.dequeue(order);
                order->setServStart(TimeStep);
                Scooter* tempScooter = nullptr;
                int deliveryTime = 0;
                for (int i = 0; i < order->GetScooterCount(); i++)
                {
                    Free_Scooters.dequeue(tempScooter, pri);
                    deliveryTime = ceil((double)order->GetDistance() / tempScooter->getSpeed());
                    order->setassignedscooter(tempScooter);
                    tempScooter->deliver(order->GetDistance());
                    tempScooter->SetDeliveryDuration(deliveryTime);
                    tempScooter->addBusyTime(deliveryTime * 2);
                    tempScooter->setWillFail(false);
                }
                order->setFinishTime(TimeStep + deliveryTime);
                InServ_Orders.enqueue(order, -order->GetPriority());
            }
            else
            {
                RDY_COMBO.dequeue(order);
				ComboTemp.enqueue(order);
            }
        }
        else if (RDY_OVL.peek(order))
        {
            if (Free_Scooters.dequeue(scooter, pri)) {
                RDY_OVL.dequeue(order);
                order->setassignedscooter(scooter);
                order->setServStart(TimeStep);
                int deliveryTime = ceil((double)order->GetDistance() / scooter->getSpeed());
                order->setFinishTime(TimeStep + deliveryTime);
                scooter->deliver(order->GetDistance());
                InServ_Orders.enqueue(order, -order->GetPriority());
                scooter->SetDeliveryDuration(deliveryTime);
                scooter->addBusyTime(deliveryTime * 2);

                scooter->setWillFail(false);
                if (rand() % 100 < 3)
                {
                    scooter->setWillFail(true);
                    int dist = (int)order->GetDistance();
                    int bDist = (dist > 1) ? (1 + rand() % (dist - 1)) : 1;
                    scooter->setBreakdownDistance(bDist);
                    int bTime = ceil((double)bDist / scooter->getSpeed());
                    scooter->setBreakdownTimeStep(TimeStep + bTime);
                }
            }
            else
            {
                break;
            }
        }
        else
        {
            break;
        }
    }
    while(ComboTemp.dequeue(temp))
    {
        RDY_COMBO.enqueue(temp);
	}
    while (RdyTemp.dequeue(temp))
    {
        RDY_OVL.enqueue(temp);
    }
}
void Restaurant::FinalizeTakeaway() {
    Order* order = nullptr;

    if (!RDY_OT.peek(order))
        return;
    if (TimeStep >= order->GetServStart() + 1) {
        RDY_OT.dequeue(order);
        order->setFinishTime(TimeStep + 1);
        order->setServStart(TimeStep + 1);
        Finished_Orders.push(order);
    }
}

void Restaurant::AssignChef()
{
    while (true)
    {
        Order* order_tobe_assigned = get_the_related_pending_order_to_the_time_step();

        if (!order_tobe_assigned)
            break;

        bool chefAssigned = false;

        if (order_tobe_assigned->GetType() == ODG)
        {
            Chef* specialChef = nullptr;
            if (Free_CS.dequeue(specialChef))
            {
                if (PEND_ODG.dequeue(order_tobe_assigned))
                {
                    order_tobe_assigned->setAssignedChef(specialChef);
                    int cookTime = ceil((double)order_tobe_assigned->GetSize() / specialChef->GetSpeed());
                    order_tobe_assigned->setCookstarttime(TimeStep);
                    order_tobe_assigned->setcookduration(cookTime);
                    Cooking_Orders.enqueue(order_tobe_assigned, order_tobe_assigned->getcookduration());
					specialChef->addBusyTime(cookTime);
                    chefAssigned = true;
                }
            }
        }
        else if (order_tobe_assigned->GetType() == ODN)
        {
            Chef* normalChef = nullptr;
            if (Free_CN.dequeue(normalChef))
            {
                if (PEND_ODN.dequeue(order_tobe_assigned))
                {
                    order_tobe_assigned->setAssignedChef(normalChef);
                    int cookTime = ceil((double)order_tobe_assigned->GetSize() / normalChef->GetSpeed());
                    order_tobe_assigned->setCookstarttime(TimeStep);
                    order_tobe_assigned->setcookduration(cookTime);
                    Cooking_Orders.enqueue(order_tobe_assigned, order_tobe_assigned->getcookduration());
					normalChef->addBusyTime(cookTime);
                    chefAssigned = true;
                }
            }
            else if (Free_CS.dequeue(normalChef))
            {
                if (PEND_ODN.dequeue(order_tobe_assigned))
                {
                    order_tobe_assigned->setAssignedChef(normalChef);
                    int cookTime = ceil((double)order_tobe_assigned->GetSize() / normalChef->GetSpeed());
                    order_tobe_assigned->setCookstarttime(TimeStep);
                    order_tobe_assigned->setcookduration(cookTime);
                    Cooking_Orders.enqueue(order_tobe_assigned, order_tobe_assigned->getcookduration());
					normalChef->addBusyTime(cookTime);
                    chefAssigned = true;
                }
            }
        }
        else if (order_tobe_assigned->GetType() == OT)
        {
            Chef* anyChef = nullptr;
            if (Free_CN.dequeue(anyChef))
            {
                if (PEND_OT.dequeue(order_tobe_assigned))
                {
                    order_tobe_assigned->setAssignedChef(anyChef);
                    int cookTime = ceil((double)order_tobe_assigned->GetSize() / anyChef->GetSpeed());
                    order_tobe_assigned->setCookstarttime(TimeStep);
                    order_tobe_assigned->setcookduration(cookTime);
                    Cooking_Orders.enqueue(order_tobe_assigned, order_tobe_assigned->getcookduration());
					anyChef->addBusyTime(cookTime);
                    chefAssigned = true;
                }
            }
        }
        else if (order_tobe_assigned->GetType() == OVG)
        {
            Chef* specialChef = nullptr;
            int temppri = 0;
            if (Free_CS.dequeue(specialChef))
            {
                if (PEND_OVG.dequeue(order_tobe_assigned, temppri))
                {
                    order_tobe_assigned->setAssignedChef(specialChef);
                    int cookTime = ceil((double)order_tobe_assigned->GetSize() / specialChef->GetSpeed());
                    order_tobe_assigned->setCookstarttime(TimeStep);
                    order_tobe_assigned->setcookduration(cookTime);
                    Cooking_Orders.enqueue(order_tobe_assigned, order_tobe_assigned->getcookduration());
					specialChef->addBusyTime(cookTime);
                    chefAssigned = true;
                }
            }
        }
        else if (order_tobe_assigned->GetType() == OVC)
        {
            Chef* anyChef = nullptr;
            if (Free_CN.dequeue(anyChef))
            {
                if (PEND_OVCL.dequeue(order_tobe_assigned))
                {
                    order_tobe_assigned->setAssignedChef(anyChef);
                    int cookTime = ceil((double)order_tobe_assigned->GetSize() / anyChef->GetSpeed());
                    order_tobe_assigned->setCookstarttime(TimeStep);
                    order_tobe_assigned->setcookduration(cookTime);
                    Cooking_Orders.enqueue(order_tobe_assigned, order_tobe_assigned->getcookduration());
					anyChef->addBusyTime(cookTime);
                    chefAssigned = true;
                }
            }
            else if (Free_CS.dequeue(anyChef))
            {
                if (PEND_OVCL.dequeue(order_tobe_assigned))
                {
                    order_tobe_assigned->setAssignedChef(anyChef);
                    int cookTime = ceil((double)order_tobe_assigned->GetSize() / anyChef->GetSpeed());
                    order_tobe_assigned->setCookstarttime(TimeStep);
                    order_tobe_assigned->setcookduration(cookTime);
                    Cooking_Orders.enqueue(order_tobe_assigned, order_tobe_assigned->getcookduration());
					anyChef->addBusyTime(cookTime);
                    chefAssigned = true;
                }
            }
        }
        else if (order_tobe_assigned->GetType() == OVN)
        {
            Chef* anyChef = nullptr;
            if (Free_CN.dequeue(anyChef))
            {
                if (PEND_OVN.dequeue(order_tobe_assigned))
                {
                    order_tobe_assigned->setAssignedChef(anyChef);
                    int cookTime = ceil((double)order_tobe_assigned->GetSize() / anyChef->GetSpeed());
                    order_tobe_assigned->setCookstarttime(TimeStep);
                    order_tobe_assigned->setcookduration(cookTime);
                    Cooking_Orders.enqueue(order_tobe_assigned, order_tobe_assigned->getcookduration());
                    anyChef->addBusyTime(cookTime);
                    chefAssigned = true;
                }
            }
        }
        else if (order_tobe_assigned->GetType() == COMBO)
        {
            Chef* anyChef = nullptr;
            if (Free_CS.getCount() + Free_CN.getCount() >= order_tobe_assigned->GetChefCount() && Free_CS.dequeue(anyChef))
            {
                if (PEND_COMBO.dequeue(order_tobe_assigned))
                {
					LinkedQueue<Chef*> assignedChefs;
                    int ChefCounter = 0;
                    int totalSpeed = 0;
					order_tobe_assigned->setAssignedChef(anyChef);
					assignedChefs.enqueue(anyChef);
					totalSpeed += anyChef->GetSpeed();
                    ChefCounter++;
                    for (int i = 0; i < order_tobe_assigned->GetChefCount() - 1; i++)
                    {
                        if (Free_CN.dequeue(anyChef))
                        {
                            order_tobe_assigned->setAssignedChef(anyChef);
                            ChefCounter++;
							totalSpeed += anyChef->GetSpeed();
							assignedChefs.enqueue(anyChef);
                        }
                        else if (Free_CS.dequeue(anyChef))
                        {
                            order_tobe_assigned->setAssignedChef(anyChef);
                            ChefCounter++;
							totalSpeed += anyChef->GetSpeed();
							assignedChefs.dequeue(anyChef);
                        }
                        while (assignedChefs.dequeue(anyChef))
                        {
                            anyChef->addBusyTime(ceil((double)order_tobe_assigned->GetSize() / totalSpeed));
                        }
                    }
					order_tobe_assigned->setCookstarttime(TimeStep);
					order_tobe_assigned->setcookduration(ceil((double)order_tobe_assigned->GetSize() / totalSpeed));
                    Cooking_Orders.enqueue(order_tobe_assigned, order_tobe_assigned->getcookduration());
					chefAssigned = true;
                }
            }
        }
        if (!chefAssigned)
        {
            break;
        }
    }
}

void Restaurant::move_from_cooking_to_ready()
{
	Order* cookedOrder = nullptr;
    int pri = 0;
	priQueue<Order*> tempQueue;
    while (Cooking_Orders.dequeue(cookedOrder, pri))
    {
        if (TimeStep >= cookedOrder->getCookstarttime() + cookedOrder->getcookduration())
        {
            if (cookedOrder->GetType() == ODG || cookedOrder->GetType() == ODN)
            {
                RDY_OD.enqueue(cookedOrder);
				Chef* ch = cookedOrder->AssignedChef();
				ch->getType() == 'S' ? Free_CS.enqueue(ch) : Free_CN.enqueue(ch);
				cookedOrder->setAssignedChef(nullptr);
            }
            else if (cookedOrder->GetType() == OT)
            {
                RDY_OT.enqueue(cookedOrder);
                Chef* ch = cookedOrder->AssignedChef();
                ch->getType() == 'S' ? Free_CS.enqueue(ch) : Free_CN.enqueue(ch);
                cookedOrder->setAssignedChef(nullptr);
            }
            else if (cookedOrder->GetType() == OVC || cookedOrder->GetType() == OVN)
            {
                RDY_OVL.enqueue(cookedOrder);
                Chef* ch = cookedOrder->AssignedChef();
                ch->getType() == 'S' ? Free_CS.enqueue(ch) : Free_CN.enqueue(ch);
                cookedOrder->setAssignedChef(nullptr);
            }
            else if (cookedOrder->GetType() == OVG)
            {
                RDY_OVL.enqueue(cookedOrder);
                Chef* ch = cookedOrder->AssignedChef();
                ch->getType() == 'S' ? Free_CS.enqueue(ch) : Free_CN.enqueue(ch);
                cookedOrder->setAssignedChef(nullptr);
            }
            else if (cookedOrder->GetType() == COMBO)
            {
                RDY_COMBO.enqueue(cookedOrder);
                Chef* ch = nullptr;
				COMBOorder* comb = dynamic_cast<COMBOorder*>(cookedOrder);
				LinkedQueue<Chef*> assignedChefs = comb->getAssignedChefs();
                while(assignedChefs.dequeue(ch))
                {
                    ch->getType() == 'S' ? Free_CS.enqueue(ch) : Free_CN.enqueue(ch);
				}
                cookedOrder->setAssignedChef(nullptr);
            }
        }
        else
        {
            tempQueue.enqueue(cookedOrder, pri);
        }
	}
	while (!tempQueue.isEmpty())
	{
		tempQueue.dequeue(cookedOrder, pri);
		Cooking_Orders.enqueue(cookedOrder, pri);
	}
}

void Restaurant::GenerateOutputFile(string& filename)
{
    std::ofstream outputFile(filename);
    outputFile << " TF\tID\tTQ\tTA\tTR\tTS\tTi\tTC\tTw\tTserv" << endl;
    Order* order = nullptr;
    int ODNcount = 0, ODGcount = 0, OTcount = 0, OVNcount = 0, OVCcount = 0, OVGcount = 0, COMBOcount = 0;
    int TiSum = 0, TcSum = 0, TwSum = 0, TservSum = 0;

    while (Finished_Orders.pop(order))
    {
        outputFile << order->GetFinishTime() << "\t" << order->GetID() << "\t" << order->GetRequestTime() << "\t" << order->getCookstarttime()
            << "\t" << order->getcookduration() + order->getCookstarttime() << "\t" << order->GetServStart() << "\t" <<
            order->getCookstarttime() - order->GetRequestTime() + order->GetServStart() - (order->getcookduration() + order->getCookstarttime()) //T idle
            << "\t" << order->getcookduration() << "\t"
            //T idle + T cook
            << order->getCookstarttime() - order->GetRequestTime() + order->GetServStart() - (order->getcookduration() + order->getCookstarttime()) + order->getcookduration()
            << "\t" << order->GetFinishTime() - order->GetServStart() << endl; // Service duration

        switch (order->GetType())
        {
        case ODN:
            ODNcount++;
            break;
        case ODG:
            ODGcount++;
            break;
        case OT:
            OTcount++;
            break;
        case OVN:
            OVNcount++;
            break;
        case OVC:
            OVCcount++;
            break;
        case OVG:
            OVGcount++;
            break;
        case COMBO:
            COMBOcount++;
			break;
        }

        TiSum += order->getCookstarttime() - order->GetRequestTime() + order->GetServStart() - (order->getcookduration() + order->getCookstarttime());
        TcSum += order->getcookduration();
        TwSum += order->getCookstarttime() - order->GetRequestTime() + order->GetServStart() - (order->getcookduration() + order->getCookstarttime()) + order->getcookduration();
        TservSum += order->GetFinishTime() - order->GetServStart();
    }

    int finishedOrders = ODNcount + ODGcount + OTcount + OVNcount + OVCcount + OVGcount + COMBOcount;
    int CancelledOrders = Cancelled_Orders.getCount();

    outputFile << "Total Orders: " << finishedOrders + CancelledOrders << endl;
    outputFile << "ODN: " << ODNcount << endl;
    outputFile << "ODG: " << ODGcount << endl;
    outputFile << "OT: " << OTcount << endl;
    outputFile << "OVN: " << OVNcount << endl;
    outputFile << "OVC: " << OVCcount + CancelledOrders << endl;
    outputFile << "OVG: " << OVGcount << endl;
	outputFile << "COMBO: " << COMBOcount << endl;

    // Calculate Scooters Utilization
    int totalScooterBusyTime = 0;
    int totalScooters = 0;
    Scooter* sc = nullptr;
    int scPri = 0;
    priQueue<Scooter*> tempFree, tempBack;
    LinkedQueue<Scooter*> tempMaint;

    while (Free_Scooters.dequeue(sc, scPri)) {
        totalScooterBusyTime += sc->GetTotalBusyTime();
        totalScooters++;
        tempFree.enqueue(sc, scPri);
    }
    while (tempFree.dequeue(sc, scPri)) Free_Scooters.enqueue(sc, scPri);

    //while (Back_Scooters.dequeue(sc, scPri)) {
    //    totalScooterBusyTime += sc->GetTotalBusyTime();
    //    totalScooters++;
    //    tempBack.enqueue(sc, scPri);
    //}
    //while (tempBack.dequeue(sc, scPri)) Back_Scooters.enqueue(sc, scPri);

    //while (Maint_Scooters.dequeue(sc)) {
    //    totalScooterBusyTime += sc->GetTotalBusyTime();
    //    totalScooters++;
    //    tempMaint.enqueue(sc);
    //}
    //while (tempMaint.dequeue(sc)) Maint_Scooters.enqueue(sc);

    double scootersUtilization = 0.0;
    if (TimeStep > 0 && totalScooters > 0) {
        scootersUtilization = ((double)totalScooterBusyTime / (TimeStep * totalScooters)) * 100.0;
    }

    // Calculate Chefs Utilization
    int totalChefBusyTime = 0;
    int specialChefsCount = 0;
    int normalChefsCount = 0;
    Chef* ch = nullptr;
    LinkedQueue<Chef*> tempCS, tempCN;

    while (Free_CS.dequeue(ch)) {
        totalChefBusyTime += ch->getTotalBusyTime();
        specialChefsCount++;
        tempCS.enqueue(ch);
    }
    while (tempCS.dequeue(ch)) Free_CS.enqueue(ch);


    while (Free_CN.dequeue(ch)) {
        totalChefBusyTime += ch->getTotalBusyTime();
        normalChefsCount++;
        tempCN.enqueue(ch);
    }
    while (tempCN.dequeue(ch)) Free_CN.enqueue(ch);

    int totalChefs = specialChefsCount + normalChefsCount;
    double chefsUtilization = 0.0;
    if (TimeStep > 0 && totalChefs > 0) {
        chefsUtilization = ((double)totalChefBusyTime / (TimeStep * totalChefs)) * 100.0;
    }

    outputFile << "Number of special chefs: " << specialChefsCount << endl;
    outputFile << "Number of normal chefs: " << normalChefsCount << endl;
    outputFile << "Number of scooters: " << totalScooters << endl;

    if (finishedOrders + CancelledOrders > 0) {
        outputFile << "Percentage of finished orders: " << (double)finishedOrders / (finishedOrders + CancelledOrders) * 100 << "%" << endl;
        outputFile << "Percentage of cancelled orders: " << (double)CancelledOrders / (finishedOrders + CancelledOrders) * 100 << "%" << endl;
    }
    else {
        outputFile << "Percentage of finished orders: 0%" << endl;
        outputFile << "Percentage of cancelled orders: 0%" << endl;
    }

    if (finishedOrders > 0) {
        outputFile << "Ti average: " << (float)TiSum / finishedOrders << endl;
        outputFile << "Tc average: " << (float)TcSum / finishedOrders << endl;
        outputFile << "Tw average: " << (float)TwSum / finishedOrders << endl;
        outputFile << "Tserv average: " << (float)TservSum / finishedOrders << endl;
    }
    else {
        outputFile << "Ti average: 0\nTc average: 0\nTw average: 0\nTserv average: 0" << endl;
    }

    outputFile << "Scooters utilization %: " << scootersUtilization << "%" << endl;
    outputFile << "Chefs utilization %: " << chefsUtilization << "%" << endl;
}
void Restaurant::add_combo(Order* o)
{
	PEND_COMBO.enqueue(o);
}
Order* Restaurant::get_the_related_pending_order_to_the_time_step()
{
	Order* bestorder = nullptr;
	Order* temporder = nullptr;
    int besttimestep = -1;
	int ovgpri = 0;
    if (!PEND_COMBO.isEmpty())
    {
        PEND_COMBO.peek(temporder);
        if (temporder->GetRequestTime() <= TimeStep)
        {
            bestorder = temporder;
            besttimestep = temporder->GetRequestTime();
            return temporder;
        }
    }
    if (!PEND_ODG.isEmpty())
    {
        PEND_ODG.peek(temporder);
        if (temporder->GetRequestTime() <= TimeStep)
        {
			bestorder = temporder;
			besttimestep = temporder->GetRequestTime();
        }
    }
    if (!PEND_ODN.isEmpty())
    {
        PEND_ODN.peek(temporder);
        if (temporder->GetRequestTime() <= TimeStep&&bestorder&&temporder->GetRequestTime() < besttimestep)
        {
			bestorder = temporder;
			besttimestep = temporder->GetRequestTime();
        }
        else if (temporder->GetRequestTime() <= TimeStep && !bestorder)
        {
            bestorder = temporder;
            besttimestep = temporder->GetRequestTime();
        }
    }
    if (!PEND_OT.isEmpty())
    {
        PEND_OT.peek(temporder);
        if (temporder->GetRequestTime() <= TimeStep&&bestorder&&temporder->GetRequestTime() < besttimestep)
		{
            bestorder = temporder;
            besttimestep = temporder->GetRequestTime();
        }
        else if (temporder->GetRequestTime() <= TimeStep && !bestorder)
        {
            bestorder = temporder;
            besttimestep = temporder->GetRequestTime();
        }
    }
    if (!PEND_OVG.isEmpty())
    {
        PEND_OVG.peek(temporder, ovgpri);
        if (temporder->GetRequestTime() <= TimeStep && bestorder && temporder->GetRequestTime() < besttimestep)
        {
            bestorder = temporder;
            besttimestep = temporder->GetRequestTime();
        }
        else if (temporder->GetRequestTime() <= TimeStep && !bestorder)
        {
            bestorder = temporder;
            besttimestep = temporder->GetRequestTime();
        }
    }
    if (!PEND_OVN.isEmpty())
    {
        PEND_OVN.peek(temporder);
        if (temporder->GetRequestTime() <= TimeStep&&bestorder&&temporder->GetRequestTime() < besttimestep)
        {
            bestorder = temporder;
            besttimestep = temporder->GetRequestTime();
        }
        else if (temporder->GetRequestTime() <= TimeStep && !bestorder)
        {
            bestorder = temporder;
            besttimestep = temporder->GetRequestTime();
        }
    }
    if (!PEND_OVCL.isEmpty())
    {
        PEND_OVCL.peek(temporder);
        if (temporder->GetRequestTime() <= TimeStep&&bestorder&&temporder->GetRequestTime() < besttimestep)
        {
            bestorder = temporder;
            besttimestep = temporder->GetRequestTime();
        }
        else if (temporder->GetRequestTime() <= TimeStep && !bestorder)
        {
            bestorder = temporder;
            besttimestep = temporder->GetRequestTime();
        }
    }
		return bestorder;
}

void Restaurant::AssignRescueScooter() {
    Order* order = nullptr;
    Scooter* rescueScooter = nullptr;
    int pri = 0;

    while (Pending_Rescue.peek(order)) {
        if (Free_Scooters.dequeue(rescueScooter, pri)) {
            Pending_Rescue.dequeue(order);

            Scooter* brokenScooter = order->AssignedScooter();
            int bDist = brokenScooter->getBreakdownDistance();
            int reachTime = ceil((double)bDist / rescueScooter->getSpeed());
            int remainTime = ceil((double)(order->GetDistance() - bDist) / rescueScooter->getSpeed());
            int totalDeliveryTime = reachTime + remainTime;
            order->setFinishTime(TimeStep + totalDeliveryTime);
            order->setassignedscooter(rescueScooter);
            rescueScooter->setWillFail(false);
            rescueScooter->deliver(order->GetDistance());
            rescueScooter->SetDeliveryDuration(totalDeliveryTime);
            rescueScooter->addBusyTime(totalDeliveryTime * 2);
            InServ_Orders.enqueue(order, -order->GetPriority());
            int brokenReturnTime = ceil((double)bDist / brokenScooter->getSpeed());
            brokenScooter->setIsReturningBroken(true);
            brokenScooter->setWillFail(false);
            brokenScooter->SetDeliveryDuration(brokenReturnTime);
            Back_Scooters.enqueue(brokenScooter, TimeStep + reachTime);
        }
        else {
            break;
        }
    }
}