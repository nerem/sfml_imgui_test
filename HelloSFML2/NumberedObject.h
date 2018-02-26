#pragma once

#include <cassert>
#include <iostream>

class NumberedObject
{
public:
	NumberedObject();
	NumberedObject(const NumberedObject&);
	void operator=(const NumberedObject&) = delete;

	unsigned long ID() const { return id; }

	static int count() { return anz; }
	
	static bool bTestMode;

	virtual ~NumberedObject();

private:
	static int anz;
	static unsigned long max;
	const unsigned long id;
};


