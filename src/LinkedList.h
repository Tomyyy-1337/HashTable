#include <iostream>
#include <string>

namespace linkedList {
	template<class T>
	struct node
	{
		node<T>* next;
		T data;
	};
}

template<class T>
class LinkedList
{
public:

	int size;
	linkedList::node<T>* first;
	linkedList::node<T>* last;

	LinkedList<T>()
	{
		size = 0;
		first = nullptr;
		last = nullptr;
	}

	bool contains(T data)
	{
		for (linkedList::node<T>* current = first; current != nullptr; current = current->next)
		{
			if (current->data == data) return true;
		}
		return false;
	}

	void replace(int indx, T data)
	{
		getNode(indx)->data = data;
	}

	void reverse()
	{
		if (size <= 1) return;

		this->last = first;

		linkedList::node<T>* last;
		linkedList::node<T>* current;
		linkedList::node<T>* next;

		last = first;
		current = first;
		next = current->next;

		current->next = nullptr;

		while (next != nullptr)
		{
			current = next;
			next = current->next;
			current->next = last;
			last = current;
		}
		first = current;
	}

	void add(T data)
	{
		size++;
		if (first == nullptr)
		{
			first = new linkedList::node<T>;
			first->data = data;
			first->next = nullptr;
			last = first;
		}
		else
		{
			linkedList::node<T>* tempNodePtr = new linkedList::node<T>;
			tempNodePtr->data = data;
			tempNodePtr->next = nullptr;
			last->next = tempNodePtr;
			last = tempNodePtr;
		}
	}

	T& getData(int index)
	{
		linkedList::node<T>* tempPtr = this->first;
		for (int i = 0; i < index; i++)
		{
			tempPtr = tempPtr->next;
		}
		return tempPtr->data;
	}

	void remove(int index, int numberOfElements = 1)
	{
		linkedList::node<T>* start;
		linkedList::node<T>* end;
		linkedList::node<T>* tmp;
		if (index == 0)
		{
			end = first;
			for (int i = 0; i < numberOfElements; i++)
			{
				tmp = end;
				end = end->next;
				delete tmp;
			}
			first = end;
		}
		else
		{
			start = getNode(index - 1);
			if (size == numberOfElements + index)
			{
				start->next = nullptr;
				last = start;
			}
			else
			{
				end = start->next;
				for (int i = 0; i < numberOfElements; i++)
				{
					tmp = end;
					end = end->next;
					delete tmp;
				}
				start->next = end;
			}
		}
		size -= numberOfElements;
	}

	void clear()
	{
		remove(0, size);
	}

	T& operator[](int index)
	{
		return getData(index);
	}

	void insert(int index, T data)
	{
		linkedList::node<T>* newNode = new linkedList::node<T>;
		if (index == 0)
		{
			newNode->next = first;
			newNode->data = data;
			first = newNode;
		}
		else
		{
			linkedList::node <T>* currentNode = getNode(index - 1);
			newNode->data = data;
			newNode->next = currentNode->next;
			currentNode->next = newNode;
		}
		if (index == size)
		{
			last = newNode;
		}

		size++;
	}

	linkedList::node<T>* getNode(int index)
	{
		linkedList::node<T>* tempPtr = first;
		for (int i = 0; i < index; i++)
		{
			tempPtr = tempPtr->next;
		}
		return tempPtr;
	}

	void print()
	{
		int indx = 0;
		for (linkedList::node<T>* tempPtr = first; tempPtr != nullptr; tempPtr = tempPtr->next)
		{
			std::cout << "Index: " << indx++ << ", Data: " << tempPtr->data << std::endl;
		}
		std::cout << "Die Liste hat " << size << " ELemente." << std::endl;
	}
};
