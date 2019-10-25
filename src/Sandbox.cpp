#include "Sandbox.h"

Sandbox::Sandbox() {}

void Sandbox::add_object(const Simple2D::Context& ctx, int pos_x, int pos_y, int angle, const std::string& name, const std::string& sprite_path) {
	objects.emplace_back(Chip(ctx, pos_x, pos_y, name, sprite_path));
	objects[objects.size()-1].set_angle(angle);
}

void Sandbox::draw(int offset_x, int offset_y, const Simple2D::Context& ctx) {
	for(auto& i : objects) {
		i.draw(ctx, i.get_pos_x()+offset_x, i.get_pos_y()-offset_y);
	}
}