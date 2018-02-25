#pragma once
#include "Layer.h"
#include <array>

class CNNLayer :
	public Layer
{
public:
	CNNLayer();
	CNNLayer(std::array<unsigned int, 2> size, unsigned int filters = 1, unsigned int actMaps = 1,
				unsigned int padding = 0, unsigned int strides = 1);
	CNNLayer(unsigned int size_x, unsigned int size_y, unsigned int filters = 1, unsigned int actMaps = 1,
				unsigned int padding = 0, unsigned int strides = 1);
	CNNLayer(Layer *input_layer, std::array<unsigned int, 2> size, unsigned int filters = 1, unsigned int actMaps = 1,
				unsigned int padding = 0, unsigned int strides = 1);
	CNNLayer(Layer *input_layer);
	~CNNLayer();

	// dont allow copying and assignment
	CNNLayer(const CNNLayer&) = delete;
	void operator=(const CNNLayer&) = delete;

	// Getter - Setter
	std::array<unsigned int, 2> GetFilterSize() const { return filter_size; }
	void SetFilterSize(const std::array<unsigned int, 2> &size);
	void SetFilterSize(unsigned int x, unsigned int y);
	unsigned int GetFilters() const{ return filters; }
	void SetFilters(unsigned int filters);
	unsigned int GetStrides() const { return strides; }
	void SetStrides(unsigned int strides);
	unsigned int GetPadding() const { return padding; }
	void SetPadding(unsigned int padding);

private:
	std::array<unsigned int, 2> filter_size;
	unsigned int filters;
	unsigned int strides;
	unsigned int padding;
};

