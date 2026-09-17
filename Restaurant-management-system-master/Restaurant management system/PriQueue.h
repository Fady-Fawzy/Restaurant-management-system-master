#pragma once
#include "PriNode.h"
#include <iostream>
#include <string>

template <typename T>
class priQueue
{
protected:
    priNode<T>* head;
public:
    priQueue() : head(nullptr) {}

    ~priQueue() {
        T tmp{};
        int p = 0;
        while (dequeue(tmp, p));
    }

    void enqueue(const T& data, int priority) {
        priNode<T>* newNode = new priNode<T>(data, priority);

        if (head == nullptr || priority > head->getPri()) {
            newNode->setNext(head);
            head = newNode;
            return;
        }

        priNode<T>* current = head;
        while (current->getNext() && priority <= current->getNext()->getPri()) {
            current = current->getNext();
        }
        newNode->setNext(current->getNext());
        current->setNext(newNode);
    }

    bool dequeue(T& topEntry, int& pri) {
        if (isEmpty()) {
            return false;
        }

        topEntry = head->getItem(pri);
        priNode<T>* temp = head;
        head = head->getNext();
        delete temp;
        return true;
    }

    bool peek(T& topEntry, int& pri) {
        if (isEmpty()) {
            return false;
        }

        topEntry = head->getItem(pri);
        return true;
    }

    bool isEmpty() const {
        return head == nullptr;
    }
    void print(string message = " ")
    {
        int pri;
        std::cout << getCount() << " " << message << ": ";
        if (!head) {
            std::cout << "None\n";
            return;
        }
        priNode<T>* ptr = head;
        while (ptr)
        {
            std::cout << ptr->getItem(pri);
            if (ptr->getNext())
                std::cout << ", ";
            ptr = ptr->getNext();
        }
        std::cout << "\n";
    }

    int getCount() const {
        if (head == nullptr) {
            return 0;
        }

        int count = 0;
        priNode<T>* ptr = head;

        while (ptr != nullptr) {
            count++;
            ptr = ptr->getNext();
        }
        return count;
    }
};
