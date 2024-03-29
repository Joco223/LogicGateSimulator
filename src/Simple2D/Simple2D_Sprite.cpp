#include "Simple2D_Sprite.h"

namespace Simple2D {
	Sprite::Sprite()
	:
	width(0),
	height(0),
	blending_mode(1),
	texture(nullptr, SDL_DestroyTexture) {}

	Sprite::Sprite(const Context& ctx, int width_, int height_, int blending_mode_)
	:
	width(width_),
	height(height_),
	blending_mode(blending_mode_),
	texture(nullptr, SDL_DestroyTexture) {
		texture.reset(SDL_CreateTexture(ctx.get_renderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height));
		SDL_SetTextureBlendMode(texture.get(), get_blending_mode_internal());
	}
	
	Sprite::Sprite(const Context& ctx, const char* texture_file) : texture(nullptr, SDL_DestroyTexture) {
		texture.reset(IMG_LoadTexture(ctx.get_renderer(), texture_file));
		if(texture.get() == nullptr) error_out("Unable to load texture.");
		if(SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height) < 0) error_out("Unable to load texture info.");
		if(SDL_SetTextureBlendMode(texture.get(), SDL_BLENDMODE_BLEND) < 0) error_out("Unable to set texture blending mode.");
	}

	SDL_BlendMode Sprite::get_blending_mode_internal() {
		switch(blending_mode) {
			case 0: return SDL_BLENDMODE_NONE;
			case 1: return SDL_BLENDMODE_BLEND;
			case 2: return SDL_BLENDMODE_ADD;
			case 3: return SDL_BLENDMODE_MOD;
			default: error_out("Invalid blending mode " + std::to_string(blending_mode));
		}
		return SDL_BLENDMODE_NONE;
	}

	void Sprite::load_sprite(const Context& ctx, const char* texture_file) {
		texture.reset();
		texture.reset(IMG_LoadTexture(ctx.get_renderer(), texture_file));
		if(texture.get() == nullptr) error_out("Unable to load texture.");
		if(SDL_QueryTexture(texture.get(), nullptr, nullptr, &width, &height) < 0) error_out("Unable to load texture info.");
		if(SDL_SetTextureBlendMode(texture.get(), get_blending_mode_internal()) < 0) error_out("Unable to set texture blending mode.");
	}

	int Sprite::get_sprite_height() {
		return height;
	}

	int Sprite::get_sprite_width() {
		return width;
	}

	void Sprite::set_blending_mode(int new_blending_mode) {
		if(new_blending_mode != 0 && new_blending_mode != 1 && new_blending_mode != 2 && new_blending_mode != 3) error_out("Invalid blending mode " + std::to_string(new_blending_mode));
		blending_mode = new_blending_mode;
		if(SDL_SetTextureBlendMode(texture.get(), get_blending_mode_internal()) < 0) error_out("Unable to set texture blending mode.");
	}

	int Sprite::get_blending_mode() {
		return blending_mode;
	}

	SDL_Texture* Sprite::get_texture() {
		return texture.get();
	}

	void Sprite::set_alpha(unsigned char new_alpha) {
		SDL_SetTextureAlphaMod(texture.get(), new_alpha);
	}

	void Sprite::draw(const Context& ctx, int x, int y, int size_x, int size_y) {
		SDL_Rect destination = {x, y, size_x, size_y};
		if(SDL_RenderCopy(ctx.get_renderer(), texture.get(), nullptr, &destination) < 0) error_out("Unable to render sprite.");
	}

	void Sprite::draw_rotated(const Context& ctx, int x, int y, int size_x, int size_y, double angle) {
		SDL_Rect destination = {x, y, size_x, size_y};
		SDL_Point rotation_center = {size_x/2, size_y/2};
		if(SDL_RenderCopyEx(ctx.get_renderer(), texture.get(), nullptr, &destination, angle, &rotation_center, SDL_FLIP_NONE) < 0) error_out("Unable to render sprite.");
	}
}