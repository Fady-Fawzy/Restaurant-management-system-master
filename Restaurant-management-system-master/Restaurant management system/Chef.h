#pragma once
#include <iostream>

class Chef
{
private:
	int ID;
	char type;
	int speed;
	int totalbusytime;
public:
	Chef(int id, char t, int s) : ID(id), type(t), speed(s), totalbusytime(0) {}
	int getID() const { return ID; }
	char getType() const { return type; }
	int GetSpeed() const { return speed; }
	int getTotalBusyTime() const { return totalbusytime; }
	void addBusyTime(int busyTime) { totalbusytime += busyTime; }
	void setTotalBusyTime(int busyTime) { totalbusytime = busyTime; }
};

std::ostream& operator<<(std::ostream& os, const Chef* c);
