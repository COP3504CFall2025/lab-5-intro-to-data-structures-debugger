#ifdef MAIN

#include "ABDQ.hpp"
#include "ABQ.hpp"
#include "ABS.hpp"
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include "LLDQ.hpp"
#include "LLQ.hpp"
#include "LLS.hpp"
#include <iostream>

/*
    - LEAVE THE IFDEF GUARDS TO KEEP YOUR MAIN WITHOUT CONFLICTING WITH GRADESCOPE!
    - Test your code in this main and run locally with the RunMain configuration in CLion, or
    through your own command line compilation. Make sure to add flag "-DMAIN" to your compilation so this
    main function can compile.

*/



 int main() {


     std::cout << "=== ABS<int> Stack Tests ===\n";

    // 1. Constructor tests
    ABS<int> s_default;
    std::cout << "Default stack size: " << s_default.getSize() << "\n"; // 0
    ABS<int> s_param(5);
    std::cout << "Param stack size: " << s_param.getSize() << "\n";   // 0

    // 2. Push tests
    s_default.push(10);
    std::cout << "After push 10, peek: " << s_default.peek() << "\n"; // 10
    s_default.push(20);
    s_default.push(30);
    std::cout << "Peek after 3 pushes: " << s_default.peek() << "\n"; // 30
    std::cout << "PrintForward: "; s_default.PrintForward();           // 10 20 30
    std::cout << "PrintReverse: "; s_default.PrintReverse();           // 30 20 10

    // Push enough to trigger resize
    for(int i = 40; i <= 100; i+=10) s_default.push(i);
    std::cout << "Size after pushes triggering resize: " << s_default.getSize() << "\n";
    std::cout << "Peek after resize pushes: " << s_default.peek() << "\n";

    // 3. Pop tests
    s_default.pop();
    std::cout << "Peek after one pop: " << s_default.peek() << "\n";
    while(s_default.getSize() > 0) s_default.pop();
    std::cout << "Size after popping all: " << s_default.getSize() << "\n";

    // 4. Peek edge
    try {
        s_default.peek(); // should handle empty stack
    } catch(...) { std::cout << "Peek on empty stack caught exception\n"; }

    std::cout << "\n=== ABQ<int> Queue Tests ===\n";

    // 1. Constructor tests
    ABQ<int> q_default;
    std::cout << "Default queue size: " << q_default.getSize() << "\n"; // 0
    ABQ<int> q_param(5);
    std::cout << "Param queue size: " << q_param.getSize() << "\n";   // 0

    // 2. Enqueue tests
    q_default.enqueue(10);
    std::cout << "Peek after enqueue 10: " << q_default.peek() << "\n"; // 10
    q_default.enqueue(20);
    q_default.enqueue(30);
    std::cout << "Peek after 3 enqueues: " << q_default.peek() << "\n"; // 10
    std::cout << "PrintForward: "; q_default.PrintForward();             // 10 20 30
    std::cout << "PrintReverse: "; q_default.PrintReverse();             // 30 20 10

    // Enqueue enough to trigger resize
    for(int i = 40; i <= 100; i+=10) q_default.enqueue(i);
    std::cout << "Size after enqueues triggering resize: " << q_default.getSize() << "\n";
    std::cout << "Peek after resize enqueues: " << q_default.peek() << "\n";

    // 3. Dequeue tests
    q_default.dequeue();
    std::cout << "Peek after one dequeue: " << q_default.peek() << "\n";
    while(q_default.getSize() > 0) q_default.dequeue();
    std::cout << "Size after dequeuing all: " << q_default.getSize() << "\n";

    // 4. Peek edge
    try {
        q_default.peek(); // should handle empty queue
    } catch(...) { std::cout << "Peek on empty queue caught exception\n"; }

    std::cout << "\nAll tests completed successfully.\n";



    //ABDQ<int>
     std::cout << "=== LinkedList<int> Tests ===\n";
    LinkedList<int> list;

    // AddHead and AddTail
    list.addHead(10);
    list.addTail(20);
    list.addHead(5);
    list.addTail(30);
    std::cout << "Forward: "; list.printForward();   // 5 10 20 30
    std::cout << "Reverse: "; list.printReverse();   // 30 20 10 5
    std::cout << "Count: " << list.getCount() << "\n"; // 4

    // RemoveHead and RemoveTail
    list.removeHead(); // removes 5
    list.removeTail(); // removes 30
    std::cout << "After removals Forward: "; list.printForward(); // 10 20
    std::cout << "Count: " << list.getCount() << "\n"; // 2

    // clear
    list.clear();
    std::cout << "After clear, Count: " << list.getCount() << "\n"; // 0
    std::cout << "Forward: "; list.printForward(); // nothing

    std::cout << "\n=== LLS<int> Stack Tests ===\n";
    LLS<int> stack;

    // Push
    stack.push(10);
    stack.push(20);
    stack.push(30);
    stack.push(40);
    stack.push(50);
    std::cout << "Forward: "; stack.getList().printForward(); // 50 40 30 20 10
    std::cout << "Reverse: "; stack.getList().printReverse(); // 10 20 30 40 50
    std::cout << "Size: " << stack.getSize() << "\n"; // 5

    // Peek
    std::cout << "Peek: " << stack.peek() << "\n"; // 50

    // Pop
    std::cout << "Popping all elements: ";
    while(stack.getSize() > 0) {
        std::cout << stack.pop() << " ";
    }
    std::cout << "\nSize after pops: " << stack.getSize() << "\n"; // 0

    // Edge peek
    try { stack.peek(); } catch(...) { std::cout << "Peek on empty stack caught exception\n"; }

    std::cout << "\n=== LLQ<int> Queue Tests ===\n";
    LLQ<int> queue;

    // Enqueue
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    queue.enqueue(40);
    queue.enqueue(50);
    std::cout << "Forward: "; queue.getList().printForward(); // 10 20 30 40 50
    std::cout << "Reverse: "; queue.getList().printReverse(); // 50 40 30 20 10
    std::cout << "Size: " << queue.getSize() << "\n"; // 5

    // Peek
    std::cout << "Peek: " << queue.peek() << "\n"; // 10

    // Dequeue
    std::cout << "Dequeuing all elements: ";
    while(queue.getSize() > 0) {
        std::cout << queue.dequeue() << " ";
    }
    std::cout << "\nSize after dequeues: " << queue.getSize() << "\n"; // 0

    try { queue.peek(); } catch(...) { std::cout << "Peek on empty queue caught exception\n"; }

    std::cout << "\n=== LLDQ<int> Deque Tests ===\n";
    LLDQ<int> deque;

    // pushFront / pushBack
    deque.pushFront(10);
    deque.pushBack(20);
    deque.pushFront(5);
    deque.pushBack(30);
    deque.pushFront(1);
    deque.pushBack(40);
    std::cout << "Forward: "; deque.getList().printForward(); // 1 5 10 20 30 40
    std::cout << "Reverse: "; deque.getList().printReverse(); // 40 30 20 10 5 1
    std::cout << "Size: " << deque.getSize() << "\n"; // 6

    // front / back
    std::cout << "Front: " << deque.front() << "\n"; // 1
    std::cout << "Back: " << deque.back() << "\n";   // 40

    // popFront / popBack
    std::cout << "Popping Front and Back: ";
    std::cout << deque.popFront() << " "; // 1
    std::cout << deque.popBack() << "\n"; // 40
    std::cout << "Forward after pops: "; deque.getList().printForward(); // 5 10 20 30
    std::cout << "Reverse after pops: "; deque.getList().printReverse(); // 30 20 10 5
    std::cout << "Size: " << deque.getSize() << "\n"; // 4

    // Stress test: multiple operations
    for(int i = 50; i <= 100; i+=10) {
        deque.pushBack(i);
        deque.pushFront(i-5);
    }
    std::cout << "Forward after stress test: "; deque.getList().printForward();
    std::cout << "Reverse after stress test: "; deque.getList().printReverse();
    std::cout << "Size: " << deque.getSize() << "\n";

    // Empty deque fully
    while(deque.getSize() > 0) {
        deque.popFront();
    }
    std::cout << "Size after emptying deque: " << deque.getSize() << "\n";

    std::cout << "\nAll linked-list tests completed successfully.\n";

    return 0;



}


#endif