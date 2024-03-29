#include "Simple2D.h"

namespace Simple2D {

	void error_out(const std::string& error) {
		std::cout << "ERROR: " << SDL_GetError() << " - " << error << '\n';
		std::exit(0);
	}

	Context::Context(int window_width, int window_height, const char* window_name_)
	: current_time(0),
		width(window_width),
		height(window_height),
		blending_mode(0),
		aa_mode(0),
		fps_cap(60),
		frame_delay(0),
		rendering_scale(1),
		vsync(false),
		window_colour({0, 0, 0, 255}),
		window_name(window_name_),
		window(nullptr, SDL_DestroyWindow),
		renderer(nullptr, SDL_DestroyRenderer) {

		window.reset(SDL_CreateWindow(window_name_, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_SHOWN));
		if(window.get() == nullptr) error_out("Unable to create the window.");

		renderer.reset(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE));
		if(renderer.get() == nullptr) error_out("Unable to create a renderer.");

		if(SDL_RenderSetScale(renderer.get(), rendering_scale, rendering_scale) < 0) error_out("Unable to set renderer scale.");

		if(SDL_SetRenderDrawBlendMode(renderer.get(), SDL_BLENDMODE_NONE) < 0) error_out("Unable to set renderer blending mode.");

		if(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, std::to_string(aa_mode).c_str()) < 0) error_out("Unable to set renderer AA mode.");

		frame_delay = 1000 / fps_cap;
	}

	SDL_BlendMode Context::get_blending_mode_internal() {
		switch(blending_mode) {
			case 0: return SDL_BLENDMODE_NONE;
			case 1: return SDL_BLENDMODE_BLEND;
			case 2: return SDL_BLENDMODE_ADD;
			case 3: return SDL_BLENDMODE_MOD;
			default: error_out("Invalid window blending mode " + std::to_string(blending_mode));
		}
		return SDL_BLENDMODE_NONE;
	}

	void Context::clear() {
		if(SDL_RenderClear(renderer.get()) < 0) error_out("Unable to clean the window.");
	}

	void Context::draw() const {
		if(SDL_SetRenderDrawColor(renderer.get(), window_colour.red, window_colour.green, window_colour.blue, window_colour.alpha) < 0) error_out("Unable to render to the window.");
		SDL_RenderPresent(renderer.get());
		
		int frame_time = SDL_GetTicks() - current_time;

		if(frame_delay > frame_time) {
			SDL_Delay(frame_delay - frame_time);
		}
	}

	void Context::flush() const {
		if(SDL_RenderFlush(renderer.get()) < 0) error_out("Unable to flush the renderer.");
	}

	std::optional<keyboard_e> Context::check_keyboard() {
		SDL_PumpEvents();
		if(SDL_PeepEvents(&event, 1, SDL_PEEKEVENT, SDL_KEYDOWN, SDL_KEYUP) > 0) {
			keyboard_e new_event;
			new_event.state = event.key.state;
			new_event.key_code = event.key.keysym.sym;
			new_event.mod = event.key.keysym.mod;
			new_event.character = (unsigned char)event.key.keysym.sym;
			SDL_PeepEvents(&event, 1, SDL_GETEVENT, SDL_KEYDOWN, SDL_KEYUP);
			return new_event;
		}
		return {};
	}

	std::optional<mouse_motion_e> Context::check_mouse_motion() {
		SDL_PumpEvents();
		if(SDL_PeepEvents(&event, 1, SDL_PEEKEVENT, SDL_MOUSEMOTION, SDL_MOUSEMOTION) > 0) {
			mouse_motion_e new_event;
			new_event.x = event.motion.x;
			new_event.y = event.motion.y;
			new_event.rel_x = event.motion.xrel;
			new_event.rel_y = event.motion.yrel;
			SDL_PeepEvents(&event, 1, SDL_GETEVENT, SDL_MOUSEMOTION, SDL_MOUSEMOTION);
			return new_event;
		}
		return {};
	}

	std::optional<mouse_button_e> Context::check_mouse_button() {
		SDL_PumpEvents();
		if(SDL_PeepEvents(&event, 1, SDL_PEEKEVENT, SDL_MOUSEBUTTONDOWN, SDL_MOUSEBUTTONUP) > 0) {
			mouse_button_e new_event;
			new_event.x = event.button.x;
			new_event.y = event.button.y;
			new_event.state = event.button.state;
			new_event.clicks = event.button.clicks;
			new_event.button = event.button.button;
			SDL_PeepEvents(&event, 1, SDL_GETEVENT, SDL_MOUSEBUTTONDOWN, SDL_MOUSEBUTTONUP);
			return new_event;
		}
		return {};
	}

	std::optional<mouse_wheel_e> Context::check_mouse_wheel() {
		SDL_PumpEvents();
		if(SDL_PeepEvents(&event, 1, SDL_PEEKEVENT, SDL_MOUSEWHEEL, SDL_MOUSEWHEEL) > 0) {
			mouse_wheel_e new_event;
			new_event.x = event.wheel.x;
			new_event.y = event.wheel.y;
			SDL_PeepEvents(&event, 1, SDL_GETEVENT, SDL_MOUSEWHEEL, SDL_MOUSEWHEEL);
			return new_event;
		}
		return {};
	}

	bool Context::check_exit() {
		current_time = SDL_GetTicks();
		SDL_PumpEvents();
		if(SDL_PeepEvents(&event, 1, SDL_PEEKEVENT, SDL_QUIT, SDL_QUIT) > 0) {
			SDL_PeepEvents(&event, 1, SDL_GETEVENT, SDL_QUIT, SDL_QUIT);
			return true;
		}
		return false;
	}

	void Context::clean_events() {
		while(SDL_PeepEvents(&event, 1, SDL_PEEKEVENT, SDL_KEYDOWN, SDL_KEYUP) == 0 &&
					SDL_PeepEvents(&event, 1, SDL_PEEKEVENT, SDL_MOUSEMOTION, SDL_MOUSEMOTION) == 0 &&
					SDL_PeepEvents(&event, 1, SDL_PEEKEVENT, SDL_MOUSEBUTTONDOWN, SDL_MOUSEBUTTONUP) == 0 &&
					SDL_PeepEvents(&event, 1, SDL_PEEKEVENT, SDL_MOUSEWHEEL, SDL_MOUSEWHEEL) == 0 &&
					SDL_PeepEvents(&event, 1, SDL_PEEKEVENT, SDL_QUIT, SDL_QUIT) == 0) {
						SDL_PollEvent(&event);
					}
	}

	void Context::set_window_colour(Colour new_window_colour) {
		window_colour = new_window_colour;
		if(SDL_SetRenderDrawColor(renderer.get(), window_colour.red, window_colour.green, window_colour.blue, window_colour.alpha) < 0) error_out("Unable to set window colour.");
	}

	Colour Context::get_window_colour() {
		return window_colour;
	}

	void Context::set_vsync(bool vsync_mode) {
		renderer.reset();
		if(vsync_mode) {
			renderer.reset(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_TARGETTEXTURE));
		}else{
			renderer.reset(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE));
		}
		if(renderer.get() == nullptr) error_out("Unable to create renderer.");
		vsync = vsync_mode;
	}

	bool Context::get_vsync() const {
		return vsync;
	}

	void Context::set_scale(float new_scale) {
		rendering_scale = new_scale;
		if(SDL_RenderSetScale(renderer.get(), rendering_scale, rendering_scale) < 0) error_out("Unable to set renderer scale.");
		if(SDL_SetRenderDrawBlendMode(renderer.get(), get_blending_mode_internal()) < 0) error_out("Unable to set renderer blending mode.");
	}

	float Context::get_scale() const {
		return rendering_scale;
	}

	void Context::set_blending_mode(int new_blending_mode) {
		if(new_blending_mode != 0 && new_blending_mode != 1 && new_blending_mode != 2 && new_blending_mode != 3) std::cout << "ERROR: Ivalid blending mode " << new_blending_mode << '\n';
		blending_mode = new_blending_mode;
		if(SDL_SetRenderDrawBlendMode(renderer.get(), get_blending_mode_internal()) < 0) error_out("Unable to set renderer blending mode.");
	}

	int Context::get_blending_mode() const {
		return blending_mode;
	}

	void Context::set_aa_mode(int new_aa_mode) {
		if(new_aa_mode != 0 && new_aa_mode != 1 && new_aa_mode != 2) error_out("Invalid AA mode " + std::to_string(new_aa_mode));
		aa_mode = new_aa_mode;
		if(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, std::to_string(aa_mode).c_str()) < 0) error_out("Unable to set renderer AA mode.");
	}

	int Context::get_aa_mode() const {
		return aa_mode;
	}

	void Context::set_fps_cap(int new_fps_cap) {
		if(new_fps_cap == 0) {std::cerr << "ERROR, can't set FPS cap to 0.\n"; return;}
		fps_cap = new_fps_cap;
		frame_delay = 1000 / fps_cap;
	}

	int Context::get_fps_cap() const {
		return fps_cap;
	}

	Uint32 Context::get_current_time() const {
		return current_time;
	}

	SDL_Renderer* Context::get_renderer() const {
		return renderer.get();
	}

	void Context::set_render_target(SDL_Texture* target_texture) const {
		if(SDL_SetRenderTarget(renderer.get(), target_texture) < 0) error_out("Unable to set render target.");
	}

	void Context::draw_rect(float x, float y, float w, float h, Colour c, bool filled) const {
		if(SDL_SetRenderDrawColor(renderer.get(), c.red, c.green, c.blue, c.alpha) < 0) error_out("Unable to set renderer draw colour.");
		SDL_FRect rect = {x, y, w, h};
		if(filled) {
			if(SDL_RenderFillRectF(renderer.get(), &rect) < 0) error_out("Unable to draw filled rectangle.");
		}else{
			if(SDL_RenderDrawRectF(renderer.get(), &rect) < 0) error_out("Unable to draw rectangle.");
		}
	}

	void Context::draw_line(float x1, float y1, float x2, float y2, Colour c) const {
		if(SDL_SetRenderDrawColor(renderer.get(), c.red, c.green, c.blue, c.alpha) < 0) error_out("Unable to set renderer draw colour.");
		if(SDL_RenderDrawLineF(renderer.get(), x1, y1, x2, y2) < 0) error_out("Unable to draw line.");
	}

	void Context::draw_square_line(float x1, float y1, float x2, float y2, Colour c) const {
		if(SDL_SetRenderDrawColor(renderer.get(), c.red, c.green, c.blue, c.alpha) < 0) error_out("Unable to set renderer draw colour.");

		if(x2 > x1) {
			if(SDL_RenderDrawLineF(renderer.get(), x1, y1, x1+(abs(x1-x2))/2, y1) < 0) error_out("Unable to draw line.");
			if(SDL_RenderDrawLineF(renderer.get(), x1+(abs(x1-x2))/2, y1, x1+(abs(x1-x2))/2, y2) < 0) error_out("Unable to draw line.");
			if(SDL_RenderDrawLineF(renderer.get(), x1+(abs(x1-x2))/2, y2, x2, y2) < 0) error_out("Unable to draw line.");
		}else{
			if(SDL_RenderDrawLineF(renderer.get(), x1, y1, x1-(abs(x1-x2))/2, y1) < 0) error_out("Unable to draw line.");
			if(SDL_RenderDrawLineF(renderer.get(), x1-(abs(x1-x2))/2, y1, x1-(abs(x1-x2))/2, y2) < 0) error_out("Unable to draw line.");
			if(SDL_RenderDrawLineF(renderer.get(), x1-(abs(x1-x2))/2, y2, x2, y2) < 0) error_out("Unable to draw line.");
		}
	}

	void Context::draw_circle(float x1, float y1, int radius, Colour c) const {
		if(SDL_SetRenderDrawColor(renderer.get(), c.red, c.green, c.blue, c.alpha) < 0) error_out("Unable to set renderer draw colour.");

		int x = radius-1;
		int y = 0;
		int dx = 1;
		int dy = 1;
		int err = dx - (radius << 1);

		while (x >= y) {
			if(SDL_RenderDrawPointF(renderer.get(), x1 + x, y1 + y) < 0) error_out("Unable to draw a point.");
			if(SDL_RenderDrawPointF(renderer.get(), x1 + y, y1 + x) < 0) error_out("Unable to draw a point.");
			if(SDL_RenderDrawPointF(renderer.get(), x1 - y, y1 + x) < 0) error_out("Unable to draw a point.");
			if(SDL_RenderDrawPointF(renderer.get(), x1 - x, y1 + y) < 0) error_out("Unable to draw a point.");
			if(SDL_RenderDrawPointF(renderer.get(), x1 - x, y1 - y) < 0) error_out("Unable to draw a point.");
			if(SDL_RenderDrawPointF(renderer.get(), x1 - y, y1 - x) < 0) error_out("Unable to draw a point.");
			if(SDL_RenderDrawPointF(renderer.get(), x1 + y, y1 - x) < 0) error_out("Unable to draw a point.");
			if(SDL_RenderDrawPointF(renderer.get(), x1 + x, y1 - y) < 0) error_out("Unable to draw a point.");

			if(err <= 0) {
				y++;
				err += dy;
				dy += 2;
			}

			if(err > 0) {
				x--;
				dx += 2;
				err += dx - (radius << 1);
			}
		}
	}
}