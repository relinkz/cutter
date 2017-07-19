#ifndef SORTEDLIST_H
#define SORTEDLIST_H

#include <string>
#include <sstream>

class SortedList
{
private:
	struct Node
	{
		int value;
		Node* next;

		Node(int element) 
		{ 
			value = element;
			next = NULL;
		}
		Node()
		{
			value = 0;
			next = NULL;
		}
	};
	Node* m_start;
	Node* m_end;
	int m_nrOfElements;

public:
	SortedList();
	virtual ~SortedList();

	bool Insert(int element);
	int GetFirst() const;
	int GetLast() const;
	int GetNrOfElements() const;

	int RemoveFirst();
	int RemoveLast();
	
	std::string PrintAll() const;
};

#endif

