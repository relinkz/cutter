#include <iostream>
#include "Cutter.h"

int main()
{
	//present memoryleaks in visualstudio
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Cutter dummy = Cutter();
	int const SIZE = 20; //sets the capacity of the dynamic allocated array in cutter class
/*
	float tempT = 0.0;
	int nrOfInputs, veg = 0;
	bool badInput = false;

	//query the number of starting pieces
	std::cin >> tempT >> nrOfInputs;

	if (nrOfInputs > 1000)
	{
		return 1;
	}

	if (dummy.Initialize(tempT, SIZE) != 0)
		badInput = true;

	//Create the dynamic allocated array
	for (int i = 0; i < nrOfInputs && badInput == false; i++)
	{
		std::cin >> veg;
		if (dummy.CutweightAdd(veg) != 0)
			badInput = true;
	}

	if(badInput == false)
		dummy.Run();

	//print number on cuts
	std::cout << dummy.GetResult() << std::endl;
	//debug and view the cut array
	//std::cout << dummy.ToString() << std::endl;

	*/
	std::cout << dummy.TestRun() << std::endl;

	system("PAUSE");

	return 0;
}