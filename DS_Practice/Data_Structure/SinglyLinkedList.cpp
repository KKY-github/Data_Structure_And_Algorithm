#include <iostream>
using namespace std;

// Node 클래스 만들기
class Node {
public:
	int data;
	Node* next;

	Node(int value) {
		this->data = value;
		this->next = nullptr;
	}
};

// 관리자 역할
class LinkedList {
private:
	Node* head;
	Node* tail;

public:
	// 포인터에 쓰레기값 들어가는 것을 방지
	LinkedList() {
		this->head = nullptr;
		this->tail = nullptr;
	}

	// 동적 할당 해제하는 역할(전체 삭제)
	~LinkedList() {
		this->clear();
	}

	void push_Front(int value) {
		Node* node = new Node(value);

		// head가 이미 다른 노드를 가리키고 있다면 node->next가 가리키도록 한다.
		node->next = this->head;
		// head는 새로 만들어진 node를 가리키도록 한다. 이때 노드는 위에서 원래 맨 앞에 있던 노드를 가리키는 상태!
		this->head = node;

		// tail이 아무것도 안 가리키면 노드가 하나만 있는거니까 tail이 새로 만든 노드를 가리키게 한다.
		if (this->tail== nullptr) {
			this->tail = node;
		}
	}

	void push_Back(int value) {
		Node* node = new Node(value);

		// 리스트가 비어 있을 때
		if (this->head == nullptr) {
			this->head = node;
			this->tail = node;
		}
		// 이미 존재 할 때 tail이 가리키는 노드의 next를 새로 만든 노드를 가리키게 하고 tail을 새로 만든 노드로 최신화함.
		else {
			this->tail->next = node;
			this->tail = node;
		}
	}

	// 특정 노드 삭제
	void remove(int value) {
		Node* prev = this->head;
		Node* target = nullptr;
		Node* tmp = nullptr;

		// 리스트가 비어있을 때
		if (this->head == nullptr) {
			cout << "Empty List";
			return;
		}

		// 맨 앞 노드 삭제
		if (this->head->data == value) {
			tmp = this->head->next;
			delete this->head;
			if (tmp == nullptr) {
				this->head = nullptr;
				this->tail = nullptr;
			}
			else {
				this->head = tmp;
			}
			return;
		}

		// 맨 뒤 또는 중간 노드 삭제
		while (prev->next != nullptr) {
			if (prev->next->data == value) {
				target = prev->next;
				tmp = target->next;
				prev->next = tmp;

				// 마지막 노드라는 뜻
				if (tmp == nullptr) {
					this->tail = prev;
				}

				delete target;
				return;
			}
			prev = prev->next;
		}
	}

	void clear() {
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

	// 전체 순회 출력
	void printAll() {
		Node* p = this->head;

		// 존재하지 않으면
		if (p == nullptr) {
			cout << "List Empty";
			return;
		}

		// 노드가 존재하면
		while (p != nullptr) {
			cout << p->data << " ";
			p = p->next;
		}
	}
};

int main(void) {
	LinkedList list;
	list.push_Front(10);
	list.push_Back(20);
	list.push_Back(30);
	list.printAll();
	list.remove(20);
	list.printAll();

	list.clear();
	list.printAll();

	return 0;
}