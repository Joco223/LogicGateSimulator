#include "Chip.h"

Chip::Chip() 
	:
	pos_x(0), 
	pos_y(0),
	width(0),
	height(0)
	{}


Chip::Chip(const Simple2D::Context& ctx, int pos_x_, int pos_y_, const std::string& name_, const std::string& sprite_path_)
	:
	pos_x(pos_x_),
	pos_y(pos_y),
	name(name_),
	internal_name(name_),
	sprite_path(sprite_path_) {
		sprite.load_sprite(ctx, sprite_path.c_str());
		width = sprite.get_sprite_width();
		height = sprite.get_sprite_height();
	}

void Chip::add_input_connector(int pos_x, int pos_y) {
	input_connectors.push_back({pos_x, pos_y, false});
}

void Chip::add_output_connector(int pos_x, int pos_y) {
	output_connectors.push_back({pos_x, pos_y, false});
}

void Chip::set_input_connector(int index, const bool& new_state) {
	input_connectors[index].state = new_state;
}

bool Chip::get_input_connector(int index) const {
	return input_connectors[index].state;
}

void Chip::set_output_connector(int index, const bool& new_state) {
	output_connectors[index].state = new_state;
}

bool Chip::get_output_connector(int index) const {
	return output_connectors[index].state;
}

std::string Chip::get_sprite_path() const {
	return sprite_path;
}

std::string Chip::get_name() const {
	return name;
}

std::string Chip::get_internal_name() const {
	return internal_name;
}

void Chip::set_sprite_alpha(unsigned char new_alpha) {
	sprite.set_alpha(new_alpha);
}

void Chip::draw(const Simple2D::Context& ctx) {
	sprite.draw(ctx, pos_x, pos_y, width, height);
}