#include "Cutter.h"

Cutter::Cutter()
{
	this->m_bestCut = INFINITY;
	this->m_T = 0;
}

void Cutter::m_DiscoverNodes(Vertex* v)
{
	//we know that we must cut the greatest piece
	int toCut = v->pieces->GetFirst();
	int w1, w2 = 0;
	int toLoop = toCut / 2;

	//find and store all possible ways to cut this piece
	for (int i = 1; i < toLoop + 1; i++)
	{
		w1 = toCut - i;
		w2 = toCut - w1;

		Vertex* toAdd = new Vertex();
		toAdd->pieces = v->pieces->CopyList();
		
		toAdd->pieces->Insert(w1);
		toAdd->pieces->Insert(w2);
		//traversed in graph, one cut was used to get to this node
		toAdd->cuts = v->cuts + 1;

		//sliced this one up
		toAdd->pieces->RemoveFirst();

		//change color to gray, we have visited this node
		toAdd->color = 'g';


		//std::cout << toAdd->pieces->PrintAll();
		//std::cout << "cuts " << toAdd->cuts << std::endl;

		//system("pause");

		//queue it up
		this->m_queque.push(toAdd);
	}
}

bool Cutter::m_OverDelta(Vertex* v) const
{
	bool result = false;
	float nodeT = 0;
	//get the lowest value
	nodeT = (float)v->pieces->GetLast();
	//devide with the highest value, to get the dT
	nodeT /= (float)v->pieces->GetFirst();

	if (this->m_T < nodeT)
		result = true;
	return result;
}

Cutter::Cutter(float T, Vertex* start)
{
	this->m_T = T;
	this->m_queque.push(start);
}

Cutter::~Cutter()
{
	Vertex* toDestroy = NULL;

	while (this->m_queque.empty() != true)
	{
		toDestroy = this->m_queque.front();
		//delete toDestroy;
		this->m_queque.pop();
	}
}

bool Cutter::Run()
{
	Vertex* activeNode = NULL;
	

	while (this->m_queque.empty() != true)
	{
		activeNode = this->m_queque.front();
		if (this->m_OverDelta(activeNode) == false)
		{
			//discover new nodes
			this->m_DiscoverNodes(activeNode);
		}
		else
		{
			this->m_bestCut = activeNode->cuts;
			std::cout << "OVER " << this->m_bestCut << std::endl;
			system("PAUSE");
			//I do not need to traverse here, since goal is reached
		}
		delete activeNode;
		this->m_queque.pop();
	}

	
	//std::cout << this->m_queque.front()->pieces->PrintAll() << std::endl;

	return true;
}

