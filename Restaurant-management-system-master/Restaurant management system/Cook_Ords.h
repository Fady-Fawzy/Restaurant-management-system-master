#pragma once
#include "Order.h"
#include "PriQueue.h"
#include "Chef.h"
#include "COMBOorder.h"
class Cook_Ords : public priQueue <Order*>
{
public:
    bool cancelorder(int id, Order*& cancelledOrder) {
        priQueue<Order*> tempQueue;
        Order* currentorder = nullptr;
        int pri = 0;
        bool found = false;
        while (dequeue(currentorder, pri))
        {
            if (currentorder->GetID() == id)
            {
                cancelledOrder = currentorder;
                found = true;
            }
            else
            {
                tempQueue.enqueue(currentorder, pri);
            }
        }
        while (tempQueue.dequeue(currentorder, pri)) {
            enqueue(currentorder, pri);
        }
        return found;
    }
    void print()
    {
        if (head == nullptr)
        {
            std::cout << "None\n";
            return;
        }
        std::cout << getCount() << " Cooking Orders: ";
        int pri = 0;
        priNode<Order*>* ptr = head;
        while (ptr->getNext() != nullptr)
        {
            if (ptr->getItem(pri)->GetType() != COMBO)
            {
                std::cout << "[ " << ptr->getItem(pri)->GetID() << ", "
                    << ptr->getItem(pri)->AssignedChef()->getID() << "], ";
            }
            else
            {
                COMBOorder* comb = dynamic_cast<COMBOorder*> (ptr->getItem(pri));
                comb->PrintCooking();
            }
            ptr = ptr->getNext();
        }
        if (ptr->getItem(pri)->GetType() == COMBO)
        {

            COMBOorder* comb = dynamic_cast<COMBOorder*> (ptr->getItem(pri));
            comb->PrintCooking();
            std::cout << endl;
        }
        else
        {
            std::cout << "[ " << ptr->getItem(pri)->GetID() << ", "
                << ptr->getItem(pri)->AssignedChef()->getID() << "]\n";
        }
    }
};