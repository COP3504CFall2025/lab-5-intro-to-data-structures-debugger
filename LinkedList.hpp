#pragma once
#include <iostream>
using namespace std;

template <typename T>
struct Node{
	T data;
	Node<T>* next;
	Node<T>* prev;
		

};

template <typename T>
class LinkedList {
	

	// Stores pointers to first and last nodes and count
	Node<T>* head;
	Node<T>* tail;
	unsigned int count;
public:
	// Behaviors
	void printForward() const {
		Node<T>* loc = head;
		for (unsigned int i = 0 ; i< count; i++) {
			std::cout << loc->data;
			loc = loc->next;
		}
		std::cout << std::endl;
	}
	void printReverse() const {
		Node<T>* loc = tail;
		for (unsigned int i = count ; i > 0 ; i--) {
			std::cout << loc->data;
			loc = loc->prev;
		}
		std::cout << "\n";
	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const {return count;}
	Node<T>* getHead() {return head;}
	const Node<T>* getHead() const {return head;}
	Node<T>* getTail() {return tail;}
	const Node<T>* getTail() const {return tail;}


	// Insertion
 	void addHead(const T& data) {
		Node<T>* nNode = new Node<T>();
		nNode->data = data;
		nNode->next = head;
		nNode->prev = nullptr;

		if (head != nullptr) {
			 head->prev = nNode;
		}
		if (tail == nullptr) {
			tail = nNode;
		}
		head = nNode;
		count++;

	}
	void addTail(const T& data) {
		Node<T>* nNode = new Node<T>();
		nNode->data = data;
		nNode->next = nullptr;
		nNode->prev = tail;


		if (tail != nullptr) {
			tail->next= nNode;
		}
		if ( head == nullptr) {
			head  =  nNode;
		}
		tail = nNode;
		count++;

	}

	// Removal
	bool removeHead() {
		if (head == nullptr) {return false;}
		if (head->next == nullptr) {
			delete head;
			return true;
		}
		Node<T>* temp = head;
		head = head->next;
		temp = nullptr;
		head->prev = nullptr;
		count --;

		return true;
	}
	bool removeTail() {
		if (tail == nullptr) {return false;}
		if (tail-> prev == nullptr) {
			delete tail;
			return true;
		}
		Node<T>* temp = tail;
		tail = tail -> prev;
		temp = nullptr;
		tail-> next = nullptr;
		count --;
		return true;
	}
	void Clear() {
		if (head != nullptr) {
			Node<T>* cur = this->tail;
			for (unsigned int i = count; i > 0; i--) {
				Node<T>* temp = cur;
				cur = cur->prev;
				delete temp;
				count -- ;

			}
		}
		head = nullptr;
		tail = nullptr;
	}

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept{
		if (this == &other) {return *this;}
		delete this->head;
		delete this->tail;
		this->head = other.head;
		this->tail= other.tail;
		this->count = other.count;
		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
		return *this;


	}
	LinkedList<T>& operator=(const LinkedList<T>& rhs) {
		if (this == &rhs) {return *this;}
		this->Clear();
		Node<T>* cur = rhs.head;
		if (cur) {
			addHead(cur->data);
			for (unsigned int i = 1; i<rhs.count; i++ ) {
				cur = cur -> next;
				addTail(cur->data);
			}
		}
		this->count = rhs.count;

		return *this;
		
	}

	// Construction/Destruction
	LinkedList(): head(nullptr), tail(nullptr), count(0) {}
	LinkedList(const LinkedList<T>& list) {
		Node<T>* cur = list.head;
		head = nullptr;
		tail = nullptr;
		if (cur) {
			addHead(cur->data);
			for (unsigned int i = 1; i<list.count; i++ ) {
				cur = cur -> next;
				addTail(cur->data);
			}
		}
		this->count = list.count;


	}
	LinkedList(LinkedList<T>&& other) noexcept: head(other.head), tail(other.tail), count(other.count) {
		other.head = nullptr;
		other.tail = nullptr;
		other.count = 0;
	}
	~LinkedList() {Clear();}


};


