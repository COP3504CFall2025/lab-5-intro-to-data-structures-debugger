#pragma once
#include <iostream>
#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;
public:
    // Big 5
    ABDQ(): data_(new T[4]), capacity_(4), size_(0), front_(0), back_(0){}
    explicit ABDQ(std::size_t capacity): data_(new T[capacity]), capacity_(capacity), size_(0), front_(0), back_(0){}
    ABDQ(const ABDQ& other): data_(new T[other.capacity_]), capacity_(other.capacity_), size_(other.size_), front_(other.front_), back_(other.back_) {

        for (std::size_t i = 0; i < capacity_; i++) {
            data_[i] = other.data_[i];
        }

    }

    ABDQ(ABDQ&& other) noexcept: data_(other.data_), capacity_(other.capacity_), size_(other.size_), front_(other.front_), back_(other.back_) {
        other.data_ = nullptr;
        other.capacity_ = 0;
        other.size_ = 0;
        other.front_ = 0;
        other.back_ = 0;
    }
    ABDQ<T>& operator=(const ABDQ& other) {
        if (this == &other) {return *this;}
        delete data_;
        T* copy = new T[other.capacity_];
        for (std::size_t i = 0; i< capacity_; i++) {copy[i] = other.data_[i];}
        data_ = copy;
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        return *this;
    }
    ABDQ<T>& operator=(ABDQ&& other) noexcept {
        if (this == &other) {return *this;}
        data_ = other.data_;
        capacity_ = other.capacity_;
        front_ = other.front_;
        back_ = other.back_;
        size_ = other.size_;
        other.data_= nullptr;
        other.capacity_ = 0;
        other.front_ = 0;
        other.back_ = 0;
        other.size_ = 0;
        return *this;
    }
    ~ABDQ() override {
        delete[] data_;
        capacity_ = 0;
        size_ = 0;
        front_ = 0;
        back_ = 0;
    }



    // Insertion
    void pushFront(const T& item) override {

        size_ ++;


        if (size_ > capacity_) {
            capacity_ *= SCALE_FACTOR;
            T* copy = new T[capacity_];
            std::size_t start = front_;
            for (std::size_t i = 0; i<size_-1; i++) {
                copy[i] = data_[start];
                start = start < size_-2 ? start +1 :0;
            }
            front_ = capacity_-1;
            back_ = size_ - 2;
            delete data_;
            data_ = copy;
        }
        /*
          for (std::size_t i = 0; i <front_; i++) {
              copy[i] = data_[i];
          }
          for (std::size_t i = front_+1; i<size_+1; i++ ) {copy[i] =data_[i-1];}
          delete data_;
          data_ = copy;
          */


    else if (size_ == 1) {

        front_ = 0;
    }
    else {
        front_ = front_ > 0 ? front_-1: capacity_ -1;
    }
    data_[front_]= item;
}
    void pushBack(const T& item) override {


        size_ ++;


        if (size_ > capacity_) {
            capacity_ *= SCALE_FACTOR;
            T* copy = new T[capacity_];
            std::size_t start = front_;
            for (std::size_t i = 0; i<size_-1; i++) {
                copy[i] = data_[start];
                start = start < size_-2 ? start +1 :0;
            }
            back_ = size_-1;
            front_ = 0;
            delete data_;
            data_ = copy;

            /*
            for (std::size_t i = 0; i <back_; i++) {
                copy[i] = data_[i];
            }
            for (std::size_t i = back_+1; i<size_+1; i++) {copy[i] =data_[i-1];}
            delete data_;
            data_ = copy;
            front_++;
            */

        }
        else if (size_ == 1) {

            back_ = 0;
        }
        else {
            back_ = back_ < capacity_-1 ? back_+1: 0;
        }

        data_[back_]= item;
    }

    // Deletion
    T popFront() override {
        T res = data_[front_];
        if (size_ > 0) {
            size_ --;
            front_ = front_ < capacity_-1 ? front_+1 : 0;

            ShrinkIfNeeded();
            return res;
        }
        throw std::out_of_range("Out of range.");


    }
    T popBack() override {
        T res = data_[back_];
        if (size_ > 0 ) {
            size_ --;
            back_ = back_ > 0 ? back_ - 1: capacity_ -1;

            ShrinkIfNeeded();
            return res;
        }

        throw std::out_of_range("Out of range.");

    }

    // Access
    const T& front() const override {
        if ( front_ > size_) {
            throw std::out_of_range("Out of range.");
        }
        return data_[front_];
    }
    const T& back() const override {
        if ( back_ > size_) {
            throw std::out_of_range("Out of range.");
        }
        return data_[back_];
    }

    // Getters
    std::size_t getSize() const noexcept override {return size_;}

    void PrintForward() {
        std::cout << "[";
        std::size_t start = front_;
        T value = data_[start];
        while (start !=  back_) {
            std::cout << value << ", ";
            start  = start < capacity_ -1 ? start+1 : 0;
            value = data_[start];
        }
        if (size_ > 0){std::cout << data_[back_] << "]" << std::endl;}
        else {std::cout << "[]" << std::endl;}


    }

    void PrintReverse() {
        std::cout << "[";
        std::size_t start = back_;
        T value = data_[start];
        while (start !=  front_) {
            std::cout << value << ", ";
            start  = start > 0 ? start -1: capacity_- 1;
            value = data_[start];
        }
        if (size_ > 0){std::cout << data_[front_] << "]" << std::endl;}
        else {std::cout << "[]" << std::endl;}
    }

    size_t getFront() {return front_;}
    size_t getBack() {return back_;}
    void ShrinkIfNeeded() {
        if (size_ < capacity_/2) {

            T* copy = new T[capacity_/2];
            std::size_t start = front_;
            for (std::size_t i = 0; i < size_; i++) {
                copy[i] = data_[start];
                start = start < capacity_ -1 ? start +1 : 0;
            }
            front_ = 0;
            back_ = size_-1;
            capacity_ /= 2;
            delete data_;
            data_ = copy;
        }
        if (size_ == 0) {
            T* copy = new T[4];
            capacity_ = 4;
            front_ = back_ = 0;
            delete data_;
            data_ = copy;
        }

    }

};
