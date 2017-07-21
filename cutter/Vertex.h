#ifndef VERTEX_H
#define VERTEX_H

#include "SortedList.h"

class Vertex
{
public:
	SortedList* pieces;
	Vertex* parent;
	char color;
	int cuts;

	Vertex();
	virtual ~Vertex();

	void Init();
	void RemoveList();
};

#endif

