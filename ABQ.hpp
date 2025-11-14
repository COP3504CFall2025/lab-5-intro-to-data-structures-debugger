#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;
using namespace std;

template<typename T>
class ABQ : public QueueInterface<T>{

    size_t capacity_;
    size_t curr_size_;
    size_t front_;
    size_t back_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;

public:
    // Constructors + Big 5
    ABQ(): capacity_(1),curr_size_(0),front_(0), back_(0), array_(new T[1]){}
    explicit ABQ(const size_t capacity): capacity_(capacity), curr_size_(0),front_(0), back_(0), array_(new T[capacity]) {}
    ABQ(const ABQ& other): capacity_(other.capacity_), curr_size_(other.curr_size), front_(other.front_), back_(other.back_), array_(new T[other.capacity_]) {
        for (int i = 0; i< other.capacity_; i++) {
            array_[i] = other.array_[i];
        }
    }
    ABQ<T>& operator=(const ABQ& rhs) {
        if (this == &rhs) {return *this;}
        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        front_ = rhs.front_;
        back_ = rhs.back_;
        delete[] array_;
        T* copy = new T[rhs.capacity_];
        for (int i = 0;  i<rhs.capacity_; i++) {
            copy[i] = rhs.array_[i];
        }
        array_ = copy;
        return *this;
    }
    ABQ(ABQ&& other) noexcept: capacity_(other.capacity), curr_size_(other.curr_size_), front_(other.front_), back_(other.back_), array_(other.array_) {
        other.capacity_ = 0;
        other.curr_size_ = 0;
        other.front_ = 0;
        other.back_ =0;
        delete other.array_;
    }
    ABQ<T>& operator=(ABQ&& rhs) noexcept {
        if (this == &rhs) {return *this;}
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

    ~ABQ() noexcept override {
        capacity_ = 0;
        curr_size_ = 0;
        front_ = 0;
        back_ = 0;
        delete[] array_;
    }

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override {return curr_size_;}
    [[nodiscard]] size_t getMaxCapacity() const noexcept {return capacity_;}
    [[nodiscard]] T* getData() const noexcept {return array_;}

    // Insertion
    void enqueue(const T& data) override {
        curr_size_ ++;


        if (curr_size_ > capacity_) {
            capacity_ *= scale_factor_;
            T* copy = new T[capacity_];
            std::size_t start = front_;
            for (std::size_t i = 0; i<curr_size_-1; i++) {
                copy[i] = array_[start];
                start = start < curr_size_-2 ? start +1 :0;
            }
            back_ = curr_size_-1;
            front_ = 0;
            delete[] array_;
            array_ = copy;


        }
        else if (curr_size_ == 1) {

            back_ = 0;
        }
        else {
            back_ = back_ < capacity_-1 ? back_+1: 0;
        }

        array_[back_]= data;

    }

    // Access
    T peek() const override {
        return curr_size_ > 0 ? array_[front_]: throw std::runtime_error("Out of range");
    }

    // Deletion
    T dequeue() override {
        T res = array_[front_];
        if (curr_size_ > 0) {
            curr_size_ --;
            front_ = front_ < capacity_-1 ? front_+1 : 0;

            ShrinkIfNeeded();
            return res;
        }
        throw std::runtime_error("Out of range.");
    }
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
            delete[] array_;
            array_ = copy;
        }
        if (curr_size_ == 0) {
            T* copy = new T[4];
            capacity_ = 4;
            front_ = back_ = 0;
            delete[] array_;
            array_ = copy;
        }
    }

        void PrintForward() {
            cout << "[";
            std::size_t start = front_;
            T value = array_[start];
            while (start !=  back_) {
                cout << value << ", ";
                start  = start < capacity_ -1 ? start+1 : 0;
                value = array_[start];
            }
            if (curr_size_ > 0){cout << array_[back_] << "]" << endl;}
            else {cout << "[]" << endl;}


        }
        void PrintReverse() {
            cout << "[";
            std::size_t start = back_;
            T value = array_[start];
            while (start !=  front_) {
                cout << value << ", ";
                start  = start > 0 ? start-1 : capacity_-1;
                value = array_[start];
            }
            if (curr_size_ > 0){cout << array_[front_] << "]" << endl;}
            else {cout << "[]" << endl;}


        }


};
