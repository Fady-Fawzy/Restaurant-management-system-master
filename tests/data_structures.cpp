#include <cassert>
#include <iostream>
#include <string>
#include "LinkedQueue.h"
#include "PriQueue.h"
#include "ArrayStack.h"

struct Lifetime {
    inline static int live = 0;
    int value = 0;
    Lifetime() { ++live; }
    Lifetime(const Lifetime& other) : value(other.value) { ++live; }
    Lifetime& operator=(const Lifetime&) = default;
    ~Lifetime() { --live; }
};

int main() {
    {
        LinkedQueue<Lifetime> queue;
        Lifetime input, output;
        const int baseline = Lifetime::live;
        queue.enqueue(input);
        assert(Lifetime::live == baseline + 1);
        assert(queue.dequeue(output));
        assert(Lifetime::live == baseline); // catches the original leaked node
    }
    assert(Lifetime::live == 0);
    {
        LinkedQueue<int> queue;
        int value = -1;
        assert(!queue.dequeue(value));
        queue.enqueue(10); queue.enqueue(20);
        LinkedQueue<int> copy(queue);
        assert(queue.peek(value) && value == 10);
        assert(queue.dequeue(value) && value == 10);
        assert(queue.dequeue(value) && value == 20);
        assert(queue.isEmpty());
        queue.enqueue(30);
        assert(queue.dequeue(value) && value == 30);
        assert(copy.dequeue(value) && value == 10);
        assert(copy.dequeue(value) && value == 20);
    }
    {
        priQueue<int> queue;
        int value = -1, priority = -1;
        queue.enqueue(1, 3); queue.enqueue(2, 7); queue.enqueue(3, 7);
        assert(queue.dequeue(value, priority) && value == 2 && priority == 7);
        assert(queue.dequeue(value, priority) && value == 3 && priority == 7);
        assert(queue.dequeue(value, priority) && value == 1 && priority == 3);
        assert(!queue.dequeue(value, priority));
    }
    {
        ArrayStack<int> stack;
        int value = -1;
        assert(!stack.pop(value));
        assert(stack.push(1)); assert(stack.push(2));
        assert(stack.peek(value) && value == 2);
        assert(stack.pop(value) && value == 2);
        assert(stack.pop(value) && value == 1);
        assert(stack.isEmpty());
    }
    std::cout << "FIFO, copy, reuse, lifetime, priority, and stack checks passed\n";
}
