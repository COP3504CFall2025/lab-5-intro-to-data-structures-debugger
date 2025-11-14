#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    size_t front_;
    size_t back_;
    static constexpr size_t scale_factor_ = 2;
public:
    // Big 5 + Parameterized Constructor
    ABS(): capacity_(1), curr_size_(0), array_(new T[1]), front_(0), back_(0) {}
    explicit ABS(const size_t capacity): capacity_(capacity), curr_size_(0), array_(new T[capacity]), front_(0), back_(0) {}
    ABS(const ABS& other):  capacity_(other.capacity_), curr_size_(other.curr_size), array_(new T[other.capacity_]), front_(other.front_), back_(other.back_) {
        for (int i = 0; i< other.capacity_; i++) {
            array_[i] = other.array_[i];
        }
    }
    ABS<T>& operator=(const ABS& rhs) {
        if (this == &rhs) {return *this;}
        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        front_ = rhs.front_;
        back_ = rhs.back_;
        delete array_;
        T* copy = new T[rhs.capacity_];
        for (int i = 0;  i<rhs.capacity_; i++) {
            copy[i] = rhs.array_[i];
        }
        array_ = copy;
        return *this;
    }
    ABS(ABS&& other) noexcept: capacity_(other.capacity), curr_size_(other.curr_size_), front_(other.front_), back_(other.back_), array_(other.array_) {
        other.capacity_ = 0;
        other.curr_size_ = 0;
        other.front_ = 0;
        other.back_ =0;
        delete other.array_;
    }
    ABS<T>& operator=(ABS&& rhs) noexcept {
        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        front_ = rhs.front_;
        back_ = rhs.back_;
        array_ = rhs.array_;
        delete rhs.array_;
        rhs.capacity_  = 0;
        rhs.curr_size_  = 0;
        rhs.front_ = 0;
        rhs.back_  = 0;
        rhs.array_ = 0;
        return *this;
    }
    ~ABS() noexcept override {
        capacity_ = 0;
        curr_size_ = 0;
        front_ = 0;
        back_ = 0;
        delete array_;
    }

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override {return curr_size_;}

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept {return capacity_;}

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept {return array_;}

    // Push item onto the stack
    void push(const T& data)  override {
        curr_size_ ++;


        if (curr_size_ > capacity_) {
            capacity_ *= scale_factor_;
            T* copy = new T[capacity_];
            std::size_t start = front_;
            for (std::size_t i = 0; i<curr_size_-1; i++) {
                copy[i] = array_[start];
                start = start < curr_size_-2 ? start +1 :0;
            }
            back_ = curr_size_-2;
            front_ = capacity_ -1;
            delete array_;
            array_ = copy;


        }
        else if (curr_size_ == 1) {

            front_ = 0;
        }
        else {
            front_ = front_ > 0 ? front_-1: capacity_-1;
        }

        array_[front_]= data;

    }

    T peek() const override {
        return curr_size_ > 0 ? array_[back_]: throw std::runtime_error("Out of range");

    }

    T pop() override{
        T res = array_[back_];
        if (curr_size_ > 0) {
            curr_size_ --;
            back_ = back_ > 0? back_-1 : capacity_;

            ShrinkIfNeeded();
            return res;
        }
        throw std::runtime_error("Out of range.");

    };

    void ShrinkIfNeeded() {
        if (curr_size_ < capacity_/2) {

            T* copy = new T[capacity_/2];
            std::size_t start = front_;
            for (std::size_t i = 0; i < curr_size_; i++) {
                copy[i] = array_[start];
                start = start < capacity_ -1 ? start +1 : 0;
            }
            front_ = 0;
            back_ = curr_size_-1;
            capacity_ /= 2;
            delete array_;
            array_ = copy;
        }
        if (curr_size_ == 0) {
            T* copy = new T[4];
            capacity_ = 4;
            front_ = back_ = 0;
            delete array_;
            array_ = copy;
        }

    }
    void PrintForward() {
        std::cout << "[";
        std::size_t start = front_;
        T value = array_[start];
        while (start !=  back_) {
            std::cout << value << ", ";
            start  = start < capacity_ -1 ? start+1 : 0;
            value = array_[start];
        }
        if (curr_size_ > 0){std::cout << array_[back_] << "]" << std::endl;}
        else {std::cout << "[]" << std::endl;}


    }

    void PrintReverse() {
        std::cout << "[";
        std::size_t start = back_;
        T value = array_[start];
        while (start !=  front_) {
            std::cout << value << ", ";
            start  = start > 0 ? start-1 : capacity_-1;
            value = array_[start];
        }
        if (curr_size_ > 0){std::cout << array_[front_] << "]" << std::endl;}
        else {std::cout << "[]" << std::endl;}


    }


};
