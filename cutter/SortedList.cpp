#include "SortedList.h"


SortedList::SortedList()
{
	this->m_start = NULL;
	this->m_end = NULL;
	this->m_nrOfElements = 0;
}

SortedList::~SortedList()
{
	this->FlushList();
}

bool SortedList::Insert(int element)
{
	bool result = false;
	Node* walker = NULL;
	Node* prev = this->m_start;
	Node* toAdd = new Node(element);

	walker = this->m_start;
	if (walker == NULL)
	{
		this->m_start = toAdd;
		this->m_end = toAdd;
		result = true;
	}
	else
	{
		while (walker!= NULL && result == false)
		{
			if (walker->value > element)
			{
				if (walker->next == NULL)
				{
					//is this the last element
					walker->next = toAdd;
					this->m_end = toAdd;
					result = true;
				}
				else
				{
					//continue
					prev = walker;
					walker = walker->next;
				}
			}
			else
			{
				if (prev == walker)
				{
					//only one element in list
					toAdd->next = walker;
					this->m_start = toAdd;
					result = true;
				}
				else
				{
					//standard
					prev->next = toAdd;
					toAdd->next = walker;
					result = true;
				}
			}
		}
		
	}

	if(result == true)
		this->m_nrOfElements++;
	return result;
}

int SortedList::GetFirst() const
{
	return this->m_start->value;
}

int SortedList::GetLast() const
{
	return this->m_end->value;
}

int SortedList::GetNrOfElements() const
{
	return this->m_nrOfElements;
}

int SortedList::RemoveFirst()
{
	int val = 0;
	Node* toRemove = this->m_start;
	this->m_start = toRemove->next;

	val = toRemove->value;
	delete toRemove;

	this->m_nrOfElements--;
	return val;
}

int SortedList::RemoveLast()
{
	//cost like hell!
	Node* walker = this->m_start;
	int val = 0;

	if (this->m_nrOfElements == 1)
	{
		val = walker->value;
		delete walker;
		this->m_start = NULL;
		this->m_end = NULL;
	}
	else
	{
		while (walker->next->next != NULL)
			walker = walker->next;
		//the next last node are now stored in walker

		val = this->m_end->value;
		delete this->m_end;
		this->m_end = walker;
		this->m_end->next = NULL;
	}

	this->m_nrOfElements--;
	return val;
}

void SortedList::FlushList()
{
	Node* walker = NULL;
	Node* ereaser = NULL;

	walker = this->m_start;
	while (walker != NULL)
	{
		ereaser = walker;
		walker = walker->next;
		delete ereaser;
	}
	this->m_start = NULL;
	this->m_end = NULL;

	this->m_nrOfElements = 0;
}

std::string SortedList::PrintAll() const
{
	std::stringstream toString;
	Node* walker = this->m_start;

	while (walker != NULL)
	{
		toString << walker->value << std::endl;
		walker = walker->next;
	}

	return toString.str();
}
