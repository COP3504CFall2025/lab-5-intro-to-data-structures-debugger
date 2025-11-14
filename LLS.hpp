#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLS(): list() {}

    // Insertion
    void push(const T& item) override {
        list.addHead(item);
    }

    // Deletion
    T pop() override {
        if (list.getCount() > 0) {
            Node<T>* res = list.getHead();
            list.removeHead();
            return res->data;
        }
        throw std::runtime_error("Out of range.");
    }

    // Access
    T peek() const override {
        return list.getCount() > 0 ? list.getHead()->data: throw std::runtime_error("Out of range");}


    //Getters
    std::size_t getSize() const noexcept override {return list.getCount(); ;}
    LinkedList<T> getList() {return list;}
};