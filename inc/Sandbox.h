#pragma once

#include <vector>
#include <iostream>

#include "Simple2D/Simple2D.h"

class Sandbox {
private:
	int size_x, size_y;
	//std::vector<tile> tiles;
public:
	Sandbox(int x, int y);

	void draw_grid(int offset_x, int offset_y, const Simple2D::Context& ctx) const;
};