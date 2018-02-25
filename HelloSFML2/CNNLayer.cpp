#include "CNNLayer.h"



CNNLayer::CNNLayer()
{
	padding = 0;
	strides = 1;
	filter_size[0] = 1;
	filter_size[1] = 1;
	filters = 1;
	activation_maps = 1;
}

CNNLayer::CNNLayer(std::array<unsigned int, 2> size, unsigned int filters, unsigned int actMaps, unsigned int padding, unsigned int strides)
	: filter_size(size),
	filters(filters),
	padding(padding),
	strides(strides)
{
	activation_maps = actMaps;
}


CNNLayer::CNNLayer(unsigned int size_x, unsigned int size_y, unsigned int filters, unsigned int actMaps, unsigned int padding, unsigned int strides)
	: filters(filters),
	padding(padding),
	strides(strides)
{
	filter_size[0] = size_x;
	filter_size[1] = size_y;
	activation_maps = actMaps;
}

CNNLayer::CNNLayer(Layer *input_layer, std::array<unsigned int, 2> size, unsigned int filters, unsigned int actMaps, unsigned int padding, unsigned int strides)
{
	input = input_layer;
	CNNLayer(size, filters, actMaps, padding, strides);
}

CNNLayer::CNNLayer(Layer * input_layer)
{
	input = input_layer;
}

CNNLayer::~CNNLayer()
{
}

void CNNLayer::SetFilterSize(const std::array<unsigned int, 2>& size)
{
	filter_size = size;
}

void CNNLayer::SetFilterSize(unsigned int x, unsigned int y)
{
	filter_size[0] = x;
	filter_size[1] = y;
}

void CNNLayer::SetFilters(unsigned int filters)
{
	filters = filters;
}

void CNNLayer::SetStrides(unsigned int strides)
{
	strides = strides;
}

void CNNLayer::SetPadding(unsigned int padding)
{
	padding = padding;
}
