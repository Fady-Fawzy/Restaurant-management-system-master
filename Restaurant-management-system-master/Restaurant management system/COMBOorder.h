#pragma once
#include "Order.h"
#include "LinkedQueue.h"
class COMBOorder :
    public Order
{
private:
    int ChefCount;
    int ScooterCount;
    int Distance;
	LinkedQueue<Chef*> AssignedChefs;
	LinkedQueue<Scooter*> AssignedScooters;
public:
    COMBOorder(int orderID = 0, int s = 0,int distance = 0);
    virtual int GetChefCount() const override;
    virtual int GetScooterCount() const override;
    virtual double GetDistance() override;
    virtual OrderType GetType() const override;
	virtual void setAssignedChef(Chef* c) override;
	virtual void setassignedscooter(Scooter* s) override;
	LinkedQueue<Chef*> getAssignedChefs() const { return AssignedChefs; }
	LinkedQueue<Scooter*> getAssignedScooters() const { return AssignedScooters; }
    void FreeBackScooters();
	void PrintCooking();
    void PrintInserv();
    void PrintChefs(std::ostream& os) const;
    void PrintScooters(std::ostream& os) const;
};