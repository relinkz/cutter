#ifndef CUTTER_H
#define CUTTER_H

#include <string>
#include <sstream>

/*
This class does the calculations to solve the algorithm, it holds a dynamic allocated array
of ints (m_values) that is expandable should the temporary limit be exceeded, with the function 
ExpandArray()
*/

struct PeakValues
{
	int highestVal;
	int highestPos;

	int lowestVal;
	int lowestPos;

	float activeT;
	int average;

	PeakValues() 
	{
		highestVal = -1;
		highestPos = -1;

		lowestVal = -1;
		lowestPos = -1;

		activeT = -1;
		average = -1;
	}
};

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
	double* m_values;
	int m_capacity;
	int m_size;

	double m_totalWeight;
	float m_T;
	float m_activeRatio;
	int m_nrOfCuts;

	bool m_findWeight(int toFind) const;
	int Cut(int element, int into);		//return the rest product
	int Split(int element);
	PeakValues FindHighAndLowValue() const; //return position of the highest value in arr
	bool RatioCheck(PeakValues peaks);
	void ExpandArray();
	bool CheckArrayCapacity();

	void m_ResetData();

public:
	Cutter();
	virtual ~Cutter();

	//return 1 if T or N are to large
	int Initialize(float T, int N);

	int CutweightAdd(int weightSize);
	int Insert(int weight);

	int Run();
	std::string TestRun();

	int GetResult() const;
	
	

	std::string ToString() const;
};

#endif
