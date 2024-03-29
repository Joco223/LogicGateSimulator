#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <memory>

#include "Simple2D.h"

namespace Simple2D {

	extern void error_out(const std::string& error);
	
	class Sprite {
	private:
		int width, height, blending_mode;
		std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture;

		SDL_BlendMode get_blending_mode_internal();
	public:
		Sprite();
		Sprite(const Context& ctx, int width, int height, int blending_mode);
		Sprite(const Context& ctx, const char* texture_file);

		void load_sprite(const Context& ctx,  const char* texture_file);
		int get_sprite_width();
		int get_sprite_height();

		void set_blending_mode(int new_blending_mode);
		int  get_blending_mode();

		SDL_Texture* get_texture();

		void set_alpha(unsigned char new_alpha);

		void draw(const Context& ctx, int x, int y, int size_x, int size_y);
		void draw_rotated(const Context& ctx, int x, int y, int size_x, int size_y, double angle);
	};
}