#ifndef LinkedList_h
#define LinkedList_h

template <class T>

class LinkedList {
	private:
		typedef struct node {
			T data;
			node * next;
		}* nodePtr;
		nodePtr head;
		nodePtr curr;
		nodePtr tail;
	public:
		LinkedList() {
			head = NULL;
			curr = NULL;
			tail = NULL;
		}
		void behead();
		void push_back(T data);
		bool isempty();
		T *pop();
};

#endif
