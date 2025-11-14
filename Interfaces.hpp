#pragma once

#include <cstddef>
#include <stdexcept>


template <typename T>
class StackInterface {
    virtual void push(const T& item) =0;
    virtual T pop()= 0;
    virtual T peek() const = 0;
    virtual std::size_t getSize() const noexcept = 0;
public:
    virtual ~StackInterface() = default;

};


template <typename T>
class QueueInterface {
    virtual void enqueue(const T& item) = 0;

    // Deletion
    virtual T dequeue() = 0;

    // Access
    virtual T peek() const = 0;

    // Getter
    virtual std::size_t getSize() const noexcept  = 0;
public:
    virtual ~QueueInterface() = default;

};


template <typename T>
class DequeInterface {

public:
    virtual void pushFront(const T& item) = 0;
    virtual void pushBack(const T& item) = 0;

    // Core Removal Operations
    virtual T popFront() = 0;
    virtual T popBack() = 0;

    // Element Accessors
    const virtual T& front() const = 0;
    const virtual T& back() const = 0;

    // Getter
    virtual std::size_t getSize() const noexcept = 0;
public:
    virtual ~DequeInterface() = default;

};

