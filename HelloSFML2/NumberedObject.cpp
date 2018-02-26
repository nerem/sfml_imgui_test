#include "NumberedObject.h"

int NumberedObject::anz = 0;
unsigned long NumberedObject::max = 0L;
bool NumberedObject::bTestMode = true;

NumberedObject::NumberedObject()
	: id{++max} 
{
	++anz;
	if (bTestMode)
	{
		std::cout << "Object with ID " << id << " was generated. \n";
	}
}

NumberedObject::NumberedObject(const NumberedObject &X)
	: id{++max}
{
	++anz;
	if (bTestMode)
	{
		std::cout << "Object with ID " << id << "was generated from object with ID " << X.ID() << ".\n";
	}
}


NumberedObject::~NumberedObject()
{
	--anz;
	if (bTestMode)
	{
		std::cout << "Object with id " << id << " was deleted. \n";
		std::cout << anz << " objects remaining.\n";

		if (anz < 0)
		{
			std::cout << "ERROR! Deleted too many objects.\n";
		}
	}
	else
	{
		assert(count >= 0);
	}
}
