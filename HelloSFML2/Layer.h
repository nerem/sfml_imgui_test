#pragma once
#include <array>
#include <string>

class Layer
{
public:
	Layer();
	Layer(const Layer&) = delete;
	void operator=(const Layer&) = delete;
	virtual ~Layer();

	const Layer* GetOutputLayer() const { return output; }
	const Layer* GetInputLayer() const { return input; }

	void SetInputLayer(Layer* input);
	void SetOutputLayer(Layer* output);

	const std::string& GetName() const { return layer_name; }
	void SetName(const std::string& name);

protected:
	// input and output layer
	Layer *input = nullptr;
	Layer *output = nullptr;

	// how many activation maps does this layer have
	unsigned int activation_maps;
	// current data size
	std::array<unsigned int, 2> size;

	std::string layer_name;
};

