#include "Sandbox.h"

Sandbox::Sandbox(int x, int y) 
	:
	size_x(x),
	size_y(y) {}

void Sandbox::draw_grid(int offset_x, int offset_y, const Simple2D::Context& ctx) const {
	for(int i = 0; i < size_x+1; i++) {
		ctx.draw_line(i*32 + offset_x, 0 + offset_y, i*32 + offset_x, size_y*32 + offset_y, {10, 10, 10, 255});
	}

	for(int i = 0; i < size_y+1; i++) {
		ctx.draw_line(0 + offset_x, i*32 + offset_y, size_x*32 + offset_x, i*32 + offset_y, {10, 10, 10, 255});
	}
}