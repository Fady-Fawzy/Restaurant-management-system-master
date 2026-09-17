#pragma once
#include <iostream>

class Scooter
{
private:
	int ID;
	int NoOfDeliveries;
	int distance;
	int speed;
	int mainOrd;
	int mainDur;
	int DileverDuration;
	int maintStartStep;
	int TotalBusyTime;
	bool willFail;
	int breakdownDistance;
	int breakdownTimeStep;
	bool isReturningBroken;

public:
	Scooter(int id, int s, int MO, int MD) : ID(id), NoOfDeliveries(0), distance(0), speed(s), mainOrd(MO), mainDur(MD), TotalBusyTime(0), willFail(false), breakdownDistance(0), breakdownTimeStep(0), isReturningBroken(false) {}

	int getID() const { return ID; }
	int getNoOfDeliveries() const { return NoOfDeliveries; }
	int getDistance() const { return distance; }
	double getSpeed() const { return speed; }
	void deliver(int dist) {
		NoOfDeliveries++;
		distance += dist;
	}
	int GetSpeed() { return speed; }
	int GetMainOrds() { return mainOrd; }
	void SetDeliveryDuration(int t) { DileverDuration = t; }
	int GetDileveryDuration() const { return DileverDuration; }
	void SetMaintStartStep(int t) { maintStartStep = t; }
	int GetMaintStartStep() const { return maintStartStep; }
	int GetMainDur() const { return mainDur; }
	int GetTotalBusyTime() const { return TotalBusyTime; }
	void addBusyTime(int busyTime) { TotalBusyTime += busyTime; }

	void setWillFail(bool fail) { willFail = fail; }
	bool getWillFail() const { return willFail; }
	void setBreakdownDistance(int dist) { breakdownDistance = dist; }
	int getBreakdownDistance() const { return breakdownDistance; }
	void setBreakdownTimeStep(int ts) { breakdownTimeStep = ts; }
	int getBreakdownTimeStep() const { return breakdownTimeStep; }
	void setIsReturningBroken(bool broken) { isReturningBroken = broken; }
	bool getIsReturningBroken() const { return isReturningBroken; }
	void resetDeliveries() { NoOfDeliveries = 0; }
};

std::ostream& operator<<(std::ostream& os, const Scooter* s);