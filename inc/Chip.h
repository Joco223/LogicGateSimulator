#pragma once

#include "Simple2D/Simple2D.h"
#include "Simple2D/Simple2D_Sprite.h"

#include <vector>
#include <string>
#include <functional>

struct chip_connector {
	int pos_x, pos_y;
	bool state = 0;
};

class Chip {
private:
	int pos_x, pos_y, width, height;
	std::string name, internal_name;
	Simple2D::Sprite sprite;
	std::vector<chip_connector> input_connectors;
	std::vector<chip_connector> output_connectors;
	std::string sprite_path;
public:
	Chip();
	Chip(const Simple2D::Context& ctx, int pos_x, int pos_y, const std::string& name, const std::string& sprite_path);

	void add_input_connector(int pos_x, int pos_y);
	void add_output_connector(int pos_x, int pos_y);

	void set_input_connector(int index, const bool& new_state);
	bool get_input_connector(int index) const;

	void set_output_connector(int index, const bool& new_state);
	bool get_output_connector(int index) const;

	std::string get_sprite_path() const;
	std::string get_name() const;
	std::string get_internal_name() const;

	void set_sprite_alpha(unsigned char new_alpha);

	void draw(const Simple2D::Context& ctx);
};