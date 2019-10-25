#pragma once

#include <vector>
#include <iostream>

#include "Simple2D.h"

#include "Chip.h"

class Sandbox {
private:
	std::vector<Chip> objects;
public:
	Sandbox();

	void add_object(const Simple2D::Context& ctx, int pos_x, int pos_y, int angle, const std::string& name, const std::string& sprite_path);
	void draw(int offset_x, int offset_y, const Simple2D::Context& ctx);
};