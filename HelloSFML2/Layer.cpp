#include "Layer.h"



Layer::Layer()
{
}


Layer::~Layer()
{
}

void Layer::SetInputLayer(Layer *input)
{
	this->input = input;
}

void Layer::SetOutputLayer(Layer *output)
{
	this->output = output;
}

void Layer::SetName(const std::string & name)
{
	layer_name = name;
}
