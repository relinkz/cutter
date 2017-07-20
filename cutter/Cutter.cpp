#include "Cutter.h"

Cutter::Cutter()
{
	this->m_T = 0;
	this->m_nrOfCuts = 0;
}

Cutter::~Cutter()
{
}

void Cutter::SetT(const float &T)
{
	this->m_T = T;
}

bool Cutter::AddVegetable(const int & weight)
{
	bool result = true;
	if (this->m_sl.Insert(weight) == false)
		result = false;
	return result;
}

int Cutter::Run()
{
	float deltaT = (float)this->m_sl.GetLast() / (float)this->m_sl.GetFirst();
	while(deltaT < this->m_T && this->m_nrOfCuts < 500)
	{
		int higestVeg = this->m_sl.RemoveFirst();
		int lowestVeg = this->m_sl.GetLast();

		int w1 = 0;
		int w2 = 0;

		//goal is to make this piece lower then the next highest but above the lowest
		
		//if the veg to be cut become less then the recent lowest
		//if the highest is a multiple of the lowest 
		
		//rounded down
		if ((higestVeg / 2) >= lowestVeg)
		{
			w1 = (higestVeg / 2);
			w2 = w1;

			//add one more to offset the non symmetrical cut
			if (higestVeg % 2 == 1)
				w2++;

			this->m_sl.Insert(w1);
			this->m_sl.Insert(w2);
			this->m_nrOfCuts++;
		}

		else if (higestVeg % lowestVeg == 0)
		{
			//unsure about this while loop
			w1 = higestVeg - lowestVeg;
			w2 = higestVeg - lowestVeg;

			this->m_sl.Insert(w1);
			this->m_sl.Insert(w2);

			this->m_nrOfCuts++;
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

	//test 1
	this->m_T = 0.99;

	if (this->m_sl.Insert(2000) == false)
		result.failedRuntime[0] = true;
	else if (this->m_sl.Insert(3000) == false)
		result.failedRuntime[0] = true;
	else if (this->m_sl.Insert(4000) == false)
		result.failedRuntime[0] = true;
	else if (this->Run() != 0)
		result.failedRuntime[0] = true;

	result.nrOfCuts[0] = this->m_nrOfCuts;
	result.myAnswer[0] = 6;

	this->m_sl.FlushList();
	this->m_nrOfCuts = 0;

	//test 2
	this->m_T = 0.80;

	if (this->m_sl.Insert(1000) == false)
		result.failedRuntime[1] = true;
	else if (this->m_sl.Insert(1400) == false)
		result.failedRuntime[1] = true;
	else if (this->Run() != 0)
		result.failedRuntime[1] = true;


	result.nrOfCuts[1] = this->m_nrOfCuts;
	result.myAnswer[1] = 3;

	this->m_sl.FlushList();
	this->m_nrOfCuts = 0;

	//test 3
	this->m_T = 0.5001;

	if (this->m_sl.Insert(99999) == false)
		result.failedRuntime[2] = true;
	else if (this->m_sl.Insert(44444) == false)
		result.failedRuntime[2] = true;
	else if (this->Run() != 0)
		result.failedRuntime[2] = true;


	result.nrOfCuts[2] = this->m_nrOfCuts;
	result.myAnswer[2] = 1;

	this->m_sl.FlushList();
	this->m_nrOfCuts = 0;
	
	//test 4
	this->m_T = 0.99;

	if (this->m_sl.Insert(1) == false)
		result.failedRuntime[3] = true;
	else if (this->m_sl.Insert(99999) == false)
		result.failedRuntime[3] = true;
	else if (this->Run() != 0)
		result.failedRuntime[3] = true;


	result.nrOfCuts[3] = this->m_nrOfCuts;
	result.myAnswer[3] = 99999;

	this->m_sl.FlushList();
	this->m_nrOfCuts = 0;


	/*
	Print test results
	*/
	for (int i = 0; i < 4; i++)
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
}

int Cutter::GetResult() const
{
	return this->m_nrOfCuts;
}