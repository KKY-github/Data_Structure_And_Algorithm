#include <iostream>
using namespace std;

class Node {
public:
	int data;
	Node* prev;
	Node* next;

	Node(int value) {
		this->data = value;
		this->prev = nullptr;
		this->next = nullptr;
	}
};

class LinkedList {
private:
	Node* head;
	Node* tail;
public:
	LinkedList() {
		this->head = nullptr;
		this->tail = nullptr;
	}

	~LinkedList() {
		Node* p = this->head;
		Node* tmp = nullptr;

		while (p != nullptr) {
			tmp = p->next;
			delete p;
			p = tmp;
		}
		this->head = nullptr;
		this->tail = nullptr;
	}

	void push_Front(int value) {
		Node* node = new Node(value);
		Node* tmp = nullptr;
		// 비어있을 때
		if (this->head == nullptr) {
			this->head = node;
			node->prev = nullptr;
			this->tail = node;
			node->next = nullptr;
		}
		// 노드가 존재할 때
		else {
			tmp = this->head;
			this->head = node;
			node->prev = nullptr;
			node->next = tmp;
			node->next->prev = node;
		}
	}

	void push_Back(int value) {
		Node* node = new Node(value);
		Node* tmp = nullptr;
		// 비어 있을 때
		if (this->head == nullptr) {
			this->head = node;
			node->prev = nullptr;
			this->tail = node;
			node->next = nullptr;
		}
		// 노드가 존재할 때
		else {
			tmp = this->tail;
			this->tail = node;
			node->prev = tmp;
			node->prev->next = node;
		}
	}

	void remove(int value) {
		Node* target = this->head;
		Node* tmp = nullptr;

		while (target != nullptr) {
			if (target->data == value) {
				// 노드가 1개면
				if (target->next == nullptr && target->prev == nullptr) {
					delete target;
					this->head = nullptr;
					this->tail = nullptr;
				}
				// 맨 앞 노드면
				else if (target->prev == nullptr) {
					tmp = this->head;
					this->head = this->head->next;
					this->head->prev = nullptr;
					delete tmp;
				}
				// 맨 뒤 노드면
				else if (target->next == nullptr) {
					tmp = this->tail;
					this->tail = this->tail->prev;
					this->tail->next = nullptr;
					delete tmp;
				}
				// 중간 노드면
				else {
					target->prev->next = target->next;
					target->next->prev = target->prev;
					delete target;
				}
				return;
			}
			target = target->next;
		}
	}

	void printAll() {
		Node* p = this->head;

		if (p == nullptr) {
			cout << "Empty List";
			return;
		}

		while (p != nullptr) {
			cout << p->data << " ";
			p = p->next;
		}
		cout << '\n';
	}

	void printReverse() {
		Node* p = this->tail;
		
		if (p == nullptr) {
			cout << "Empty List";
			return;
		}

		while (p != nullptr) {
			cout << p->data << " ";
			p = p->prev;
		}
		cout << '\n';
	}
};

int main() {
	LinkedList list;

	list.printAll(); // empty
	list.printReverse(); // empty
	list.push_Front(10); // 10추가
	list.push_Back(20); // 20추가
	list.push_Back(30); // 30추가
	list.push_Back(40); // 40추가
	list.push_Back(50); // 50추가
	list.printAll();  // 10 20 30 40 50
	list.printReverse(); // 50 40 30 20 10 
	list.remove(10);  // 10 삭제
	list.remove(50); // 50 삭제
	list.remove(30); // 30 삭제
	list.printAll(); // 20 40
	list.printReverse(); // 40 20
}