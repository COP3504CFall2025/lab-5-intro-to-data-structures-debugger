#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLQ : public QueueInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLQ(): list() {}

    // Insertion
    void enqueue(const T& item) override {
        list.addTail(item);
    }

    // Deletion
    T dequeue() override {
        if (list.getCount() > 0) {
        Node<T>* res = list.getHead();
        list.removeHead();
        return res->data;
        }
        throw std::runtime_error("Out of range");
    }

    // Access
    T peek() const override{return list.getCount() > 0 ? list.getHead()->data : throw std::runtime_error("Out of Range");}

    // Getter
    std::size_t getSize() const noexcept override {return static_cast<std::size_t>(list.getCount());}
    LinkedList<T> getList() {return list;}


};