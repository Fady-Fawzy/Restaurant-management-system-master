#pragma once
#include <iostream>
#include "Table.h"
#include "Scooter.h"
enum OrderType {
    ODG, 
    ODN, 
    OT,  
    OVN, 
    OVC, 
    OVG,
    COMBO
};
class Chef;
class Table;
class Scooter;
class Order {
protected:
    int id;                
    int RequestTime;
	int Cookstarttime;
    double cookduration;
    int FinishTime;
    int ServStart;
    double price;
    double size;
    Chef* assignedChef;

public:
    Order(int orderID = 0, int s = 0);
    int GetID() const;
    double GetPrice() const;
    double GetSize() const;
    virtual double GetDistance();
    void setPrice(double pr);
    void setSize(double s);
    Chef* AssignedChef() const;
    virtual Table* AssignedTable() const;
    virtual Scooter* AssignedScooter() const;
    int GetRequestTime() const;
    int GetFinishTime() const;
	int GetServStart() const;
    void setRequestTime(int time);
    void setFinishTime(int time);
    void setServStart(int time);
    virtual void setAssignedChef(Chef* c);
    virtual OrderType GetType() const = 0;
    virtual void setAssignedTable(Table* t);
    virtual bool getCanShare() const;
    virtual double GetPriority() const;
    virtual int GetSeats() const;
    virtual ~Order();
    virtual int getDuration() const;
    virtual void setassignedscooter(Scooter * s);
	void setCookstarttime(int t) { Cookstarttime = t; }
	int getCookstarttime() const { return Cookstarttime; }
	void setcookduration(int d) { cookduration = d; }
	double getcookduration() const { return cookduration; }
	virtual int GetChefCount() const { return 1; }
    virtual int GetScooterCount() const { return 1; }
};

std::ostream& operator<<(std::ostream& os, const Order* order);



