#include <iostream>
#include <vector>
#include <cstring>
#include "src/LinkedList.h"

namespace hashTable {
	template<class T>
	struct node
	{
		int key;
		T data;
	};
}

template<class T>
class HashTable
{
private:

	static const int hashGroups = 10;
	LinkedList<hashTable::node<T>> table[hashGroups];
	
public:

	unsigned int itemCount;

	bool isEmpty() const
	{
		if (itemCount == 0) return true;
		return false;
	}

	int hashFunction(int key)
	{
		return key % hashGroups;
	}

	void insertItem(int key, T data)
	{
		itemCount++;
		int hashValue = hashFunction(key);
		LinkedList<hashTable::node<T>>& cell = table[hashValue];
		for (auto currPtr = cell.first; currPtr != nullptr; currPtr = currPtr->next)
		{
			if (currPtr->data.key == key)
			{
				currPtr->data.data = data;
				return;
			}
		}
		cell.add(hashTable::node<T>{key, data});
	}

	void removeItem(int key)
	{
		itemCount--;
		int hashValue = hashFunction(key);
		LinkedList<hashTable::node<T>>& cell = table[hashValue];
		int indx = 0;
		for (auto currPtr = cell.first; currPtr != nullptr; currPtr = currPtr->next)
		{
			if (currPtr->data.key == key)
			{
				cell.remove(indx);
				return;
			}
			indx++;
		}
	}

	T* searchTable(int key)
	{
		int hashValue = hashFunction(key);
		LinkedList<hashTable::node<T>>& cell = table[hashValue];
		for (auto currPtr = cell.first; currPtr != nullptr; currPtr = currPtr->next)
		{
			if (currPtr->data.key == key) return &currPtr->data.data;
		}
		return nullptr;
	}

	void printTable()
	{
		LinkedList<hashTable::node<T>>* cell;
		std::string output = "";
		for (int i = 0; i < hashGroups; i++)
		{
			output += std::to_string(i) + ": ";
			cell = &table[i];
			for (auto currPtr = cell->first; currPtr != nullptr; currPtr = currPtr->next)
			{
				output += currPtr->data.data + "; ";
			}
			output += "\n";
		}
		std::cout << output;
	}

	HashTable()
	{
		itemCount = 0;
	}

};

int main()
{
	HashTable<std::string> testMap;

	testMap.insertItem(0, "Hallo");
	testMap.insertItem(1, "I");
	testMap.insertItem(2, "Bims");

	testMap.insertItem(5, "A");
	testMap.insertItem(15, "B");
	testMap.insertItem(25, "C");

	testMap.printTable();
}