#include <LinkedList.h>

LinkedList::LinkedList() {
	LinkedList::head = NULL;
	LinkedList::tail = NULL;
	LinkedList::curr = NULL;
}

/*
void behead() {
	LinkedList::curr = LinkedList::curr->next;
	LinkedList::head = LinkedList::curr;
}

void LinkedList::push_back(T data) {
	LinkedList::nodePtr n = new node;
	n->data = data;
	n->next = LinkedList::head;
	if(LinkedList::head == NULL) {
		LinkedList::head = n;
		LinkedList::tail = n;
		LinkedList::curr = n;
	} else {
		LinkedList::head = n;
		LinkedList::curr = n;
	}
}

bool LinkedList::isempty() {
	if(LinkedList::head == NULL) {
		return true;
	} else {
		return false;
	}
}

T *LinkedList::pop() {
	if(LinkedList::head == NULL) {
		return NULL;
	} else {
		T * data = &LinkedList::curr->data;
		behead();
		return data;
	}
}
*/
