#include "COMBOorder.h"
#include "Chef.h"
COMBOorder::COMBOorder(int orderID, int s,int distance)
{
	id = orderID;
	size = s;
	Distance = distance;
	if (size > 20)
		ChefCount = 4;
	else
		ChefCount = size / 6;
	if (size < 10)
		ScooterCount = 2;
	else
		ScooterCount = size / 6;

}

int COMBOorder::GetChefCount() const
{
	return ChefCount;
}

int COMBOorder::GetScooterCount() const
{
	return ScooterCount;
}

double COMBOorder::GetDistance()
{
	return Distance;
}

OrderType COMBOorder::GetType() const
{
	return COMBO;
}

void COMBOorder::setAssignedChef(Chef* c)
{
	AssignedChefs.enqueue(c);
}

void COMBOorder::setassignedscooter(Scooter* s)
{
	AssignedScooters.enqueue(s);
}

void COMBOorder::FreeBackScooters()
{
	Scooter* s = nullptr;
	while (AssignedScooters.dequeue(s));
}

void COMBOorder::PrintCooking()
{
	Chef* c = nullptr;
	cout << "[ " << id << ", ";
	LinkedQueue<Chef*> tempChefs = AssignedChefs;
	while(AssignedChefs.dequeue(c))
	{
		cout << c->getID();
		if (AssignedChefs.peek(c))
		{
			cout << ", ";
		}
	}
	cout << "]";
	while(tempChefs.dequeue(c))
	{
		AssignedChefs.enqueue(c);
	}
}

void COMBOorder::PrintInserv()
{
}

void COMBOorder::PrintChefs(std::ostream& os) const
{
	Chef* c = nullptr;
	LinkedQueue<Chef*> temp = AssignedChefs;
	while (temp.dequeue(c))
	{
		os << c->getID() << ", ";
	}
}
void COMBOorder::PrintScooters(std::ostream& os) const
{
	Scooter* s = nullptr;
	LinkedQueue<Scooter*> temp = AssignedScooters;
	while (temp.dequeue(s))
	{
		os <<"S"<< s->getID();
		if (temp.peek(s))
			os << ", ";
	}
}