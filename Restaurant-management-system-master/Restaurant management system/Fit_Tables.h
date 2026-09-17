#pragma once
#include "PriQueue.h"
#include "Table.h"
class Fit_Tables :
    public priQueue<Table*>
{
public:

    // Remove one table that fits requiredSeats (smallest free-seat count among those that fit).
    bool getBest(int requiredSeats, Table*& bestTable) {
        priQueue<Table*> hold;
        Table* currenttable = nullptr;
        int pri = 0;
        while (dequeue(currenttable, pri)) {
            hold.enqueue(currenttable, pri);
        }
        bestTable = nullptr;
        Table* t = nullptr;
        int p = 0;
        priQueue<Table*> tmp;
        while (hold.dequeue(t, p)) {
            tmp.enqueue(t, p);
            if (t->getFreeseats() >= requiredSeats) {
                if (bestTable == nullptr || t->getFreeseats() < bestTable->getFreeseats()) {
                    bestTable = t;
                }
            }
        }
        while (tmp.dequeue(t, p)) {
            if (t != bestTable) {
                enqueue(t, p);
            }
        }
        return bestTable != nullptr;
    }
    void print()
    {
        if (head == nullptr)
        {
            std::cout << "None\n";
            return;
        }
        std::cout << getCount() << " Tables: ";
        int pri = 0;
        priNode<Table*>* ptr = head;
        while (ptr->getNext() != nullptr)
        {
            std::cout << "[" << ptr->getItem(pri)->getId() << ", "
                << ptr->getItem(pri)->getCapacity() << ", " << ptr->getItem(pri)->getFreeseats() << "], ";
            ptr = ptr->getNext();
        }
        std::cout << "[" << ptr->getItem(pri)->getId() << ", "
            << ptr->getItem(pri)->getCapacity() << ", " << ptr->getItem(pri)->getFreeseats() << "]\n";
    }
};