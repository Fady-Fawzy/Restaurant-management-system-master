#pragma once
#include "LinkedQueue.h"
#include "Order.h"
class Ready_OV :
    public LinkedQueue<Order*>
{
public:
    void cancelorder(int id, Order*& cancelledOrder)
    {
        LinkedQueue<Order*> tempQueue;
        Order* currentOrder = nullptr;
        bool found = false;
        while (dequeue(currentOrder))
        {
            if (currentOrder->GetID() == id)
            {
                cancelledOrder = currentOrder;
                found = true;
            }
            else
            {
                tempQueue.enqueue(currentOrder);
            }
        }
        while (tempQueue.dequeue(currentOrder)) {
            enqueue(currentOrder);
        }
    }

    void print()
    {
        if (frontPtr == nullptr)
        {
            std::cout << "None\n";
            return;
        }
        std::cout << getCount() << " Ready OV: " ;
        Node<Order*>* ptr = frontPtr;
        while (ptr->getNext() != nullptr)
        {
            std::cout << ptr->getItem()->GetID() << ",";
            ptr = ptr->getNext();
        }
        std::cout << ptr->getItem()->GetID() << endl;
    }
};