#include "Order.h"
#include "COMBOorder.h"
Order::Order(int orderID, int s) {
    id = orderID;
    size = s;
    RequestTime = 0;
    FinishTime = 0;
    assignedChef = nullptr;
}
int Order::GetID() const {
    return id;
}
void Order::setAssignedChef(Chef* c) {
    assignedChef = c;
}
double Order::GetPrice() const {
    return price;
}
double Order::GetSize() const {
    return size;
}
double Order::GetDistance()
{
    return 0;
}
void Order::setPrice(double pr) {
    price = pr;
}
void Order::setSize(double s) {
    size = s;
}
Chef* Order::AssignedChef() const {
    return assignedChef;
}
Table* Order::AssignedTable() const
{
    return nullptr;
}
int Order::GetRequestTime() const {
    return RequestTime;
}
int Order::GetFinishTime() const {
    return FinishTime;
}
int Order::GetServStart() const
{
	return ServStart;
}
void Order::setRequestTime(int time) {
    RequestTime = time;
}
void Order::setFinishTime(int time) {
    FinishTime = time;
}
void Order::setServStart(int time)
{
	ServStart = time;
}
void Order::setAssignedTable(Table* t)
{

}
bool Order::getCanShare() const
{
    return false;
}
double Order::GetPriority() const
{
    return 0.0;
}
Scooter* Order::AssignedScooter() const
{
    return nullptr;
}
Order::~Order() {

}
int Order::getDuration() const
{
    return 0;
}
void Order::setassignedscooter(Scooter* s)
{
}
int Order::GetSeats() const
{
    return 0;
}
std::ostream& operator<<(std::ostream& os, const Order* order) {
    if(order->GetType() == COMBO)
    {
        const COMBOorder* combo = dynamic_cast<const COMBOorder*>(order);
        if (!((combo->getAssignedScooters()).isEmpty()))
        {
            os << "[" << order->GetID() << ", ";
            combo->PrintScooters(os);
            os << "]";
        }
        else
        {
            os << order->GetID();
        }
        return os;
	}
    if (order->AssignedTable() != nullptr) {
        os <<"["<< order->GetID()<<","<< " T" << order->AssignedTable()->getId()<<"]";
        return os;
    }
    if (order->AssignedScooter() != nullptr) {
        os << "[" << order->GetID() << "," << " S" << order->AssignedScooter()->getID() << "]";
        return os;
    }
    os << order->GetID();
    return os;
}