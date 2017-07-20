#ifndef CUTTER_H
#define CUTTER_H

#include "SortedList.h"
//#include <string>
//#include <sstream>

/*
This class does the calculations to solve the algorithm, it holds a dynamic allocated array
of ints (m_values) that is expandable should the temporary limit be exceeded, with the function 
ExpandArray()
*/

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

class Cutter
{
private:
	SortedList m_sl;
	int m_nrOfCuts;
	float m_T;
public:
	Cutter();
	virtual ~Cutter();

	void SetT(const float &T);
	bool AddVegetable(const int &weight);

	int Run();
	std::string TestRun();

	int GetResult() const;
};

#endif
