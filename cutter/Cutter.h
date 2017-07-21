#ifndef CUTTER_H
#define CUTTER_H


#include <queue>
#include "SortedList.h"
#include <string>
#include <sstream>
#include <iostream>
#include "Vertex.h"

struct TestResult
{
	int nrOfCuts[10];
	int myAnswer[10];
	bool failedRuntime[10];

	TestResult()
	{
		for (int i = 0; i < 10; i++)
		{
			nrOfCuts[i] = 0;
			myAnswer[i] = 0;
			failedRuntime[i] = false;
		}
	}
};

//struct Node
//{
//	SortedList* pieces;
//	char color;
//	Node* parent;
//
//	Node() 
//	{
//		this->color = 'w';
//		this->parent = NULL;
//		this->pieces = new SortedList;
//	}
//	void InsertTo(int a)
//	{
//		this->pieces->Insert(a);
//	}
//};

class Cutter
{
private:
	std::queue<Vertex*> m_queque;
	int m_bestCut;
	float m_T;

	void m_DiscoverNodes(Vertex* v);
	bool m_OverDelta(Vertex* v) const;
public:
	Cutter();
	Cutter(float T, Vertex* start);
	virtual ~Cutter();

	bool Run();
};

#endif
