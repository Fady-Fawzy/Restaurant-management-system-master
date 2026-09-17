#pragma once
#include "LinkedQueue.h"
#include "StackADT.h"
#include "ArrayStack.h"
#include "PriQueue.h"
#include "Cook_Ords.h"
#include "Fit_Tables.h"
#include "PEND_OVC.h"
#include "Ready_OV.h"
#include "COMBOorder.h"
#include <fstream>
class UI;
class Order;
class Chef;
class Table;
class Scooter;
class Action;
class Restaurant
{
private:
    UI* pUI;

    LinkedQueue<Action*> Actions;
    LinkedQueue<Order*> PEND_ODG;
    LinkedQueue<Order*> PEND_ODN;
    LinkedQueue<Order*> PEND_OT;
    LinkedQueue<Order*> PEND_OVN;
    PEND_OVC PEND_OVCL;
    priQueue<Order*> PEND_OVG;
    LinkedQueue<Chef*> Free_CS;
    LinkedQueue<Chef*> Free_CN;

    Fit_Tables Free_Tables;
    Fit_Tables Busy_Sharable;
    Fit_Tables Busy_No_Share;

    LinkedQueue<Order*> Cancelled_Orders;
    ArrayStack<Order*> Finished_Orders;
    Cook_Ords Cooking_Orders;
    LinkedQueue<Order*> RDY_OT;
    Ready_OV RDY_OVL;
    LinkedQueue<Order*> RDY_OD;
    priQueue<Order*> InServ_Orders;
    priQueue<Scooter*> Free_Scooters;
    priQueue<Scooter*> Back_Scooters;
    LinkedQueue<Scooter*> Maint_Scooters;
    LinkedQueue<Order*> RDY_COMBO;
    LinkedQueue<Order*> PEND_COMBO;
    LinkedQueue<Order*> Pending_Rescue;
    priQueue<Order*> overwait;
    int TimeStep;
    int Tthreshold;
    Order* get_the_related_pending_order_to_the_time_step();
public:
    Restaurant();
    ~Restaurant();

    void add_odg(Order* o);
    void add_odn(Order* o);
    void add_ot(Order* o);
    void add_ovn(Order* o);
    void add_ovc(Order* o);
    void add_ovg(Order* o, double priority);
	void overwait_order();
    void AddAction(Action* pAction);
    void RunSimulation();
    bool CancelOVC(int id);
    void LoadActions(string& filename);
    void Request();
    void Cancel();
    void CheckScooters();
    void AssignTable();
    void CheckFinishedDeliveryOrders();
    void CheckFinishedDineInOrders();
    void AssignScooter();
    void AssignRescueScooter();
    void FinalizeTakeaway();
    void AssignChef();
    void move_from_cooking_to_ready();
    void GenerateOutputFile(string& filename);
    void add_combo(Order* o);
};