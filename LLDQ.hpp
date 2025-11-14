#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>



template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T> list;

public:
    // Constructor
    LLDQ(): list() {}

    // Core Insertion Operations
    void pushFront(const T& item) override {
        list.addHead(item);
    }
    void pushBack(const T& item) override {
        list.addTail(item);
    }

    // Core Removal Operations
    T popFront() override {
        if (list.getCount() > 0) {
            Node<T>* res = list.getHead();
            list.removeHead();
            return res->data;
        }
        throw std::runtime_error("Out of range");
    }
    T popBack() override {
        if (list.getCount() > 0) {
            Node<T>* res = list.getTail();
            list.removeTail();
            return res->data;
        }
        throw std::runtime_error("Out of range");
    }

    // Element Accessors
    const T& front() const override {return list.getCount()> 0 ? list.getHead()->data: throw std::runtime_error("Out of range");}
    const T& back() const override {return list.getCount()> 0 ? list.getTail()->data : throw std::runtime_error("Out of range");}

    // Getter
    std::size_t getSize() const noexcept override {return static_cast<std::size_t>(list.getCount());}
    LinkedList<T> getList() {return list;}
};






