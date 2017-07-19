#include "Cutter.h"
#include <iostream>

bool Cutter::m_findWeight(int toFind) const
{
	//search in array after identical integer
	for (int i = 0; i < this->m_size; i++)
	{
		if (this->m_values[i] == toFind)
			return true;
	}
	return false;
}

int Cutter::Cut(int elementPos, int into)
{
	//return 0 on success, 1 on array cap reached
	if (this->CheckArrayCapacity() == false)
		return 1;

	int rest = 0;

	rest = this->m_values[elementPos] - into;
	this->m_values[elementPos] = into;
	this->m_values[this->m_size++] = rest;
	this->m_nrOfCuts++;

	return 0;
}

int Cutter::Split(int element)
{
	if (this->CheckArrayCapacity() == false)
		return 1;

	int temp = 0;
	temp = this->m_values[element];
	temp /= 2;

	this->m_values[element] = temp;
	this->m_values[this->m_size++] = temp;
	this->m_nrOfCuts++;
	
	return 0;
}

PeakValues Cutter::FindHighAndLowValue() const
{
	PeakValues peaks = PeakValues();
	int avg = 0;

	//worst case O(n)
	for (int i = 0; i < this->m_size; i++)
	{
		if (peaks.highestVal < this->m_values[i] || peaks.highestVal == -1)
		{
			peaks.highestVal = this->m_values[i];
			peaks.highestPos = i;
		}
		if (peaks.lowestVal > this->m_values[i] || peaks.lowestVal == -1)
		{
			peaks.lowestVal = this->m_values[i];
			peaks.lowestPos = i;
		}
		avg += this->m_values[i];
	}

	//calculate avg and save, the answer will be rounded to integer, works as a guide
	//in the cut function
	peaks.average = avg / this->m_size;

	return peaks;
}

bool Cutter::RatioCheck(PeakValues peaks)
{
	bool result = false;
	int lowestUnique = -1;
	int nrOf = 0;
	for (int i = 0; i < this->m_size; i++)
	{
		//new Value is set
		if (this->m_values[i] > lowestUnique)
		{
			lowestUnique = this->m_values[i];
			nrOf = 1;
		}
		//same element is encountered
		else if (this->m_values[i] == lowestUnique)
			nrOf++;
	}

	//calculate the ratio
	float activeRatio = (float)peaks.lowestVal / (float)peaks.highestVal;
	this->m_activeRatio = activeRatio;

	if (this->m_T  < activeRatio + 0.0001 )
		result = true;
	
	return result;
}

void Cutter::ExpandArray()
{
	double* tempArr;
	tempArr = NULL;
	this->m_capacity += 100;

	tempArr = new double[this->m_capacity];
	for (int i = 0; i < this->m_size; i++)
		tempArr[i] = this->m_values[i];

	//release old memory, and apply new arr
	delete[] this->m_values;
	this->m_values = tempArr;
}

bool Cutter::CheckArrayCapacity()
{
	bool result = true;

	if (this->m_capacity == 500)
		result = false;
	else if (this->m_size == this->m_capacity)
		this->ExpandArray();

	return result;
}

void Cutter::m_ResetData()
{
	if (this->m_values != NULL)
	{
		delete[] this->m_values;
		this->m_values = NULL;
	}
	this->m_capacity = 10;
	this->m_size = 0;
	
	this->m_totalWeight = 0;
	this->m_T = 0;
	this->m_activeRatio = 0.0f;
	this->m_nrOfCuts = 0;
}

Cutter::Cutter()
{
	this->m_values = NULL;
	this->m_capacity = 0;
	this->m_size = 0;
	this->m_T = 0;
	this->m_nrOfCuts = 0;

	this->m_totalWeight = 0;
}

Cutter::~Cutter()
{
	//free allocated memory
	delete[] this->m_values;
}

int Cutter::Initialize(float T, int N)
{
	//return 1 if T or N are to large
	if (T > 1.0001f || T < 0.5)
	{
		return 1;
	}

	if (N > 1000 || N < 1)
	{
		return 1;
	}
	
	this->m_T = T;
	this->m_capacity = N; //let capacity be high to reduce chance of expanding
	this->m_size = 0;

	this->m_values = new double[this->m_capacity];
	return 0;
}

int Cutter::CutweightAdd(int weightSize)
{
	//return 1 if weightSize already exist in array
	//return 2 if array exceed capacity
	//return 3 if above 10^6
	if (m_findWeight(weightSize) == true)
		return 1;
	if (this->m_size == this->m_capacity && this->m_capacity != 500)
		this->ExpandArray();
	else if (this->m_size == this->m_capacity && this->m_capacity == 500)
		return 2;
	if (weightSize > 1000000)
	{
		return 3;
	}

	this->m_values[this->m_size++] = weightSize;
	this->m_totalWeight += weightSize;

	return 0;
}

int Cutter::Insert(int weight)
{
	//return 1 if weightSize already exist in array
	//return 2 if array exceed capacity
	//return 3 if above 10^6
	int temp = 0;

	if (m_findWeight(weight) == true)
		return 1;
	if (this->m_size == this->m_capacity && this->m_capacity != 500)
		this->ExpandArray();
	else if (this->m_size == this->m_capacity && this->m_capacity == 500)
		return 2;

	for (int i = 0; i < this->m_size; i++)
	{
		if (this->m_values[i] > weight)
		{
			//push all elements back
		}
	}

	return 0;
}

int Cutter::Run()
{
	PeakValues peaks;
	peaks = this->FindHighAndLowValue();

	//while ratioValue is not satisfied
	while (this->RatioCheck(peaks) == false && this->m_nrOfCuts < 500 )
	{
		//higher prio to split values higher than twice the lowest
		if (peaks.highestVal > (peaks.lowestVal * 2) && (peaks.highestVal % 2) ==0)
		{
			if (this->Split(peaks.highestPos))
				return 1;
		}
		//else cut an equal large piece of the highest value to the lowest and add a rest in array
		else if (this->Cut(peaks.highestPos, peaks.lowestVal) == 1)
			return 1;
	}
	return 0;
}

int Cutter::Run2()
{
	float deltaT = (float)this->m_sl.GetLast() / (float)this->m_sl.GetFirst();
	while(deltaT < this->m_T && this->m_sl.GetNrOfElements() < 500)
	{
		int higestVeg = this->m_sl.RemoveFirst();
		int lowestVeg = this->m_sl.GetLast();

		int w1 = 0;
		int w2 = 0;

		//goal is to make this piece lower then the next highest but above the lowest
		
		//if the veg to be cut become less then the recent lowest
		//if the highest is a multiple of the lowest 
		if (higestVeg % lowestVeg == 0)
		{
			while (higestVeg != 0)
			{
				/*
				ToDo
				this shit is not bulletproof yet, failes 2nd test

				 */
				w1 = higestVeg - lowestVeg;
				w2 = higestVeg - lowestVeg;

				this->m_sl.Insert(w1);
				this->m_sl.Insert(w2);

				higestVeg -= lowestVeg * 2;
				this->m_nrOfCuts++;
			}
		}
		//there is no solution with the parts we have now to satisfy the
		//condition, we need to decrease the lowest veg piece
		else
		{

			//find the lowest cut piece that they share
			int closestCutVal = higestVeg % lowestVeg;

			//cut the largest piece to this value
			this->m_sl.Insert(higestVeg - closestCutVal);

			//add remaining
			this->m_sl.Insert(closestCutVal);

			//add to nrofcuts
			this->m_nrOfCuts++;
		}
		deltaT = (float)this->m_sl.GetLast() / (float)this->m_sl.GetFirst();
	}
	
	return 0;
}

std::string Cutter::TestRun()
{
	TestResult result = TestResult();
	std::stringstream toString;

	//this->m_T = 0.99;

	//this->m_sl.Insert(2000);
	//this->m_sl.Insert(3000);
	//this->m_sl.Insert(4000);
	//this->Run2();

	this->m_T = 0.80;

	this->m_sl.Insert(1000);
	this->m_sl.Insert(1400);
	this->Run2();



	toString << this->m_sl.PrintAll() << std::endl;
	toString << "cuts: " << this->m_nrOfCuts << std::endl;

	return toString.str();

	


	/*
	//test 1
	if (this->Initialize(0.99f, 10) != 0)
		result.failedRuntime[0] = true;
	else if (this->CutweightAdd(2000) != 0)
		result.failedRuntime[0] = true;
	else if (this->CutweightAdd(3000) != 0)
		result.failedRuntime[0] = true;
	else if (this->CutweightAdd(4000) != 0)
		result.failedRuntime[0] = true;
	else if (this->Run() != 0)
		result.failedRuntime[0] = true;

	result.nrOfCuts[0] = this->m_nrOfCuts;
	result.myAnswer[0] = 6;

	this->m_ResetData();


	
	//test 2
	if (this->Initialize(0.80f, 10) != 0)
		result.failedRuntime[1] = true;
	else if (this->CutweightAdd(1000) != 0)
		result.failedRuntime[1] = true;
	else if (this->CutweightAdd(1400) != 0)
		result.failedRuntime[1] = true;
	else if (this->Run() != 0)
		result.failedRuntime[1] = true;

	result.nrOfCuts[1] = this->m_nrOfCuts;
	result.myAnswer[1] = 3;

	this->m_ResetData();

	//test 3
	if (this->Initialize(0.50001f, 10) != 0)
		result.failedRuntime[2] = true;
	else if (this->CutweightAdd(999999) != 0)
		result.failedRuntime[2] = true;
	else if (this->CutweightAdd(444444) != 0)
		result.failedRuntime[2] = true;
	else if (this->Run() != 0)
		result.failedRuntime[2] = true;

	result.nrOfCuts[2] = this->m_nrOfCuts;
	result.myAnswer[2] = 1;

	this->m_ResetData();

	//test 4
	if (this->Initialize(0.99f, 10) != 0)
		result.failedRuntime[3] = true;
	else if (this->CutweightAdd(1) != 0)
		result.failedRuntime[3] = true;
	else if (this->CutweightAdd(999999) != 0)
		result.failedRuntime[3] = true;
	else if (this->Run() != 0)
		result.failedRuntime[3] = true;

	result.nrOfCuts[3] = this->m_nrOfCuts;
	result.myAnswer[3] = 99999;

	this->m_ResetData();

	//test 5
	if (this->Initialize(0.75f, 10) != 0)
		result.failedRuntime[4] = true;
	else if (this->CutweightAdd(25) != 0)
		result.failedRuntime[4] = true;
	else if (this->CutweightAdd(12) != 0)
		result.failedRuntime[4] = true;
	else if (this->CutweightAdd(35) != 0)
		result.failedRuntime[4] = true;
	else if (this->CutweightAdd(10) != 0)
		result.failedRuntime[4] = true;
	else if (this->CutweightAdd(40) != 0)
		result.failedRuntime[4] = true;
	else if (this->Run() != 0)
		result.failedRuntime[4] = true;

	result.nrOfCuts[4] = this->m_nrOfCuts;
	result.myAnswer[4] = 6;

	this->m_ResetData();

	//test 4
	if (this->Initialize(0.5f, 10) != 0)
		result.failedRuntime[5] = true;
	else if (this->CutweightAdd(20) != 0)
		result.failedRuntime[5] = true;
	else if (this->CutweightAdd(10) != 0)
		result.failedRuntime[5] = true;
	else if (this->CutweightAdd(30) != 0)
		result.failedRuntime[5] = true;
	else if (this->Run() != 0)
		result.failedRuntime[5] = true;

	result.nrOfCuts[5] = this->m_nrOfCuts;
	result.myAnswer[5] = 1;

	this->m_ResetData();

	for (int i = 0; i < 6; i++)
	{
		if (result.myAnswer[i] >= result.nrOfCuts[i] && result.failedRuntime[i] == false)
		{
			toString << "Test " << i + 1 << " SUCCESS" << std::endl;
			toString << "Result: " << result.nrOfCuts[i] << " myAnsw: " << result.myAnswer[i] << std::endl;
		}
		else
		{
			toString << "Test " << i + 1 << " FAILED" << std::endl;
			toString << "cuts: " << result.nrOfCuts[i] << std::endl;
			toString << "myAns: " << result.myAnswer[i] << std::endl;
			toString << "failed Runtime : " << ((result.failedRuntime[i] == true) ? "YES" : "NO") << std::endl;
		}
		
	}

	return toString.str();
	*/
}

int Cutter::GetResult() const
{
	return this->m_nrOfCuts;
}

std::string Cutter::ToString() const
{
	std::stringstream toReturn;

	for (int i = 0; i < this->m_size; i++)
	{
		toReturn << "[" << i << "] : " << this->m_values[i] << std::endl;;
	}
	toReturn << "total weight: " << this->m_totalWeight << std::endl;
	toReturn << "Active Ratio: " << this->m_activeRatio << std::endl;
	toReturn << "Nr of cuts so far: " << this->m_nrOfCuts << std::endl;


	return toReturn.str();
}
