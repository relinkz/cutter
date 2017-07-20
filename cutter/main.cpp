#include <iostream>
#include "Cutter.h"

int main()
{
	//present memoryleaks in visualstudio
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	Cutter dummy = Cutter();
	int const SIZE = 20; //sets the capacity of the dynamic allocated array in cutter class

	float tempT = 0.0;
	int nrOfInputs, veg = 0;

	//query the number of starting pieces
	std::cin >> tempT >> nrOfInputs;

	if (nrOfInputs > 1000)
	{
		return 1;
	}

	//Create the dynamic allocated array
	for (int i = 0; i < nrOfInputs; i++)
	{
		std::cin >> veg;
		if (veg < 1000000)
		{
			if (dummy.AddVegetable(veg) == false)
				return 0; //nrOfelement exeeded in list, n < 500
		}
	}
	dummy.SetT(tempT);

	if (dummy.Run() != 0)
		return 0; // runtime error

	//print number on cuts
	std::cout << dummy.GetResult() << std::endl;

	system("PAUSE");

	return 0;
}