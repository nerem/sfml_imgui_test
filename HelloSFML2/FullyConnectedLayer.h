#pragma once
#include "Layer.h"
#include <array>
class FullyConnectedLayer :
	public Layer
{
public:
	FullyConnectedLayer();
	~FullyConnectedLayer();

private:
	std::array<unsigned int, 2> size;
};

