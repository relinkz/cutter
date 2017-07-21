#include "Vertex.h"



Vertex::Vertex()
{
	this->pieces = NULL;
	this->parent = NULL;
	this->color = 'w';
	this->cuts = 0;
}


Vertex::~Vertex()
{
	if (this->pieces != NULL)
	{
		this->pieces->FlushList();
	}
	delete this->pieces;
}

void Vertex::Init()
{
	this->pieces = new SortedList;
}

void Vertex::RemoveList()
{
	if (this->pieces != NULL)
	{
		this->pieces->FlushList();
		delete this->pieces;

		this->pieces = NULL;
	}
}
