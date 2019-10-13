#include "GUI.h"

namespace GUI {

	button::button()
		:
		pos_x(0),
		pos_y(0),
		width(0),
		height(0),
		clicked(false) {}

	button::button(int pos_x_, int pos_y_, int height_, const std::string& internal_name_, const Simple2D::Colour& regular_colour_, const Simple2D::Colour& clicked_colour_)
		:
		pos_x(pos_x_),
		pos_y(pos_y_),
		width(0),
		height(height_),
		clicked(false),
		internal_name(internal_name_),
		regular_colour(regular_colour_),
		clicked_colour(clicked_colour_) {}

	void button::add_text(Simple2D::Text_context& text_ctx, const Simple2D::Context& ctx, const std::string& display_name) {
		int old_height = height;
		text_ctx.get_text_size(ctx, width, height, display_name, height/1.3333);
		height = old_height;
	}

	void button::add_sprite(const Simple2D::Context& ctx, const char* sprite_path) {
		sprite = Simple2D::Sprite(ctx, sprite_path);
		width = height;
	}

	void button::add_text_sprite(Simple2D::Text_context& text_ctx, const Simple2D::Context& ctx, const std::string& display_name_, const char* sprite_path) {
		int old_height = height;
		display_name = display_name_;
		sprite = Simple2D::Sprite(ctx, sprite_path);
		text_ctx.get_text_size(ctx, width, height, display_name, height/1.3333);
		width += 6 + height;
		height = old_height;
	}

	void button::set_clicked(const bool& new_clicked) {
		clicked = new_clicked;
	}

	bool button::get_clicked() {
		return clicked;
	}

	void button::draw_button(Simple2D::Text_context& text_ctx, const Simple2D::Context& ctx) {
		if(clicked) {
			ctx.draw_rect(pos_x-2, pos_y, width+3, height, clicked_colour - 10, true);
			ctx.draw_rect(pos_x, pos_y, width, height, clicked_colour, true);
		}else{
			ctx.draw_rect(pos_x-2, pos_y, width+3, height, regular_colour - 10, true);
			ctx.draw_rect(pos_x, pos_y, width, height, regular_colour, true);
		}
		int total_size = 0;

		if(sprite.get_sprite_width() > 0) {
			sprite.draw(ctx, pos_x+2, pos_y+2, height-4, height-4);
			total_size += height;
		}

		if(display_name.length() > 0) {
			if(clicked) {
				text_ctx.draw_text(ctx, pos_x+total_size, pos_y+2, display_name, height/1.33333, regular_colour);
			}else{
				text_ctx.draw_text(ctx, pos_x+total_size, pos_y+2, display_name, height/1.33333);
			}	
		}
	}

	void button::detect_button_click(GUI& gui_parent, const Simple2D::mouse_button_e& mouse_button_event) {	
		event new_event;
		new_event.source = internal_name;
		new_event.event_type = mouse_button_event.state;
		new_event.event_desc_1 = mouse_button_event.button;
		bool was_clicked = false;
		if(mouse_button_event.x > pos_x && mouse_button_event.x < pos_x+width) {
			if(mouse_button_event.y > pos_y && mouse_button_event.y < pos_y+height) {
				was_clicked = true;
				new_event.event_desc_bool = true;
				gui_parent.push_event_stack(new_event);
			}
		}
		if(!was_clicked && clicked) {
			new_event.event_desc_bool = false;
			gui_parent.push_event_stack(new_event);
		}
	}

	int button::get_button_width() const {
		return width;
	}

	int button::get_pos_x() const {
		return pos_x;
	}

	int button::get_pos_y() const {
		return pos_y;
	}

	tile_button::tile_button()
		:
		pos_x(0),
		pos_y(0),
		width(0),
		height(0),
		clicked(false) {}

	tile_button::tile_button(const Simple2D::Context& ctx, int pos_x_, int pos_y_, int width_, int height_, const char* sprite_path, const std::string& display_name_, const std::string& internal_name_, const Simple2D::Colour& regular_colour_, const Simple2D::Colour& clicked_colour_) 
		:
		pos_x(pos_x_),
		pos_y(pos_y_),
		width(width_),
		height(height_),
		clicked(false),
		display_name(display_name_),
		internal_name(internal_name_),
		regular_colour(regular_colour_),
		clicked_colour(clicked_colour_) {
			sprite.load_sprite(ctx, sprite_path);
		}

	void tile_button::set_clicked(const bool new_state) {
		clicked = new_state;
	}

	bool tile_button::get_clicked() const {
		return clicked;
	}

	void tile_button::draw_button(Simple2D::Text_context& text_ctx, const Simple2D::Context& ctx) {
		if(clicked)	{
			ctx.draw_rect(pos_x, pos_y, width, height, clicked_colour+10, true);
			ctx.draw_rect(pos_x+2, pos_y+2, width-4, height-4, clicked_colour, true);
		}else{
			ctx.draw_rect(pos_x, pos_y, width, height, regular_colour+10, true);
			ctx.draw_rect(pos_x+2, pos_y+2, width-4, height-4, regular_colour, true);
		}

		int text_width = 0;
		int text_height = 0;
		text_ctx.get_text_size(ctx, text_width, text_height, display_name, (height/6)/1.333);

		text_ctx.draw_text(ctx, pos_x+(width/2)-text_width/2, (pos_y+height)-text_height-4, display_name, (height/6)/1.333);

		int sprite_height = 4*height/6;
		float ratio = (float)sprite.get_sprite_width()/(float)sprite.get_sprite_height();
		int sprite_width = ratio*sprite_height;
		if(sprite_width > width-4) {
			sprite_width /= (float)sprite_width/(float)(width-4);
			sprite_height /= (float)sprite_width/(float)(width-4); 
		}
		sprite.draw(ctx, pos_x+(width/2)-(sprite_width/2), pos_y+height/12, sprite_width, sprite_height);
	}

	void tile_button::detect_button_click(GUI& gui_parent, const Simple2D::mouse_button_e& mouse_button_event) {
		event new_event;
		new_event.source = internal_name;
		new_event.event_type = mouse_button_event.state;
		new_event.event_desc_1 = mouse_button_event.button;
		bool was_clicked = false;
		if(mouse_button_event.x > pos_x && mouse_button_event.x < pos_x+width) {
			if(mouse_button_event.y > pos_y && mouse_button_event.y < pos_y+height) {
				was_clicked = true;
				new_event.event_desc_bool = true;
				gui_parent.push_event_stack(new_event);
			}
		}
		if(!was_clicked && clicked) {
			new_event.event_desc_bool = false;
			gui_parent.push_event_stack(new_event);
		}
	}

	pop_up_window::pop_up_window()
		:
		pos_x(0),
		pos_y(0),
		scaled_pos_x(0),
		scaled_width(0),
		width(0),
		height(0),
		animation_step(0),
		direction(false),
		extended(false) {}

	pop_up_window::pop_up_window(const Simple2D::Context& ctx, int pos_x_, int pos_y_, int scaled_pos_x_, int scaled_width_, int width_, int height_, const Simple2D::Colour& colour_, const Simple2D::Colour& background_colour_, const std::string& title_, const std::string& internal_name_)
		:
		pos_x(pos_x_),
		pos_y(pos_y_),
		scaled_pos_x(scaled_pos_x_),
		scaled_width(scaled_width_),
		width(width_),
		height(height_),
		animation_step(0),
		direction(false),
		extended(false),
		colour(colour_),
		background_colour(background_colour_),
		title(title_),
		internal_name(internal_name_) {};

	bool pop_up_window::get_direction() const {
		return direction;
	}

	void pop_up_window::set_direction(bool new_direction) {
		direction = new_direction;
	}

	bool pop_up_window::get_state() const {
		return extended;
	}

	void pop_up_window::draw_scale_up(Simple2D::Text_context& text_ctx, const Simple2D::Context& ctx) {
		int start_x = pos_x-((pos_x-scaled_pos_x)/20)*animation_step;
		int new_width = width+((scaled_width-width)/20)*animation_step;
		int start_y = pos_y-((pos_y-height)/20)*animation_step;
		int new_height = pos_y-start_y;

		ctx.draw_rect(start_x, start_y, new_width, new_height*0.05, colour, true);
		ctx.draw_rect(start_x, start_y+new_height*0.05, new_width, new_height*0.95, background_colour, true);

		text_ctx.draw_text(ctx, start_x+2, start_y+2, title, (new_height*0.05)/1.3333);
		
		if(animation_step < 21) {
			animation_step++;
		}else{
			for(auto& i : buttons) {
				i.second.draw_button(text_ctx, ctx);
			}
			extended = true;
		}
	}

	void pop_up_window::draw_scale_down(Simple2D::Text_context& text_ctx, const Simple2D::Context& ctx) {
		int start_x = pos_x-((pos_x-scaled_pos_x)/20)*animation_step;
		int new_width = width+((scaled_width-width)/20)*animation_step;
		int start_y = pos_y-((pos_y-height)/20)*animation_step;
		int new_height = pos_y-start_y;

		ctx.draw_rect(start_x, start_y, new_width, new_height*0.05, colour, true);
		ctx.draw_rect(start_x, start_y+new_height*0.05, new_width, new_height*0.95, background_colour, true);

		text_ctx.draw_text(ctx, start_x+2, start_y+2, title, (new_height*0.05)/1.3333);
		
		if(animation_step > 0) {
			animation_step--;
		}else{
			extended = false;
		}
	}

	void pop_up_window::add_tile_button(const Simple2D::Context& ctx, const char* sprite_path, const std::string& display_name, const std::string& internal_name, const Simple2D::Colour& regular_colour_, const Simple2D::Colour& clicked_colour_) {
		int start_x = pos_x-((pos_x-scaled_pos_x)/20)*20 + (buttons.size() % 3) * ceil((scaled_width-20)/3);
		int start_y = pos_y-((pos_y-height)/20)*20;
		int new_height = pos_y-start_y;
		start_y += ceil(buttons.size() / 3) * ceil(new_height/3);
		buttons.emplace(std::make_pair(internal_name, tile_button(ctx, start_x, start_y+1, ((scaled_width-20)/3), (new_height/3), sprite_path, display_name, internal_name, regular_colour_, clicked_colour_)));
	}

	void pop_up_window::detect_button_click(GUI& gui_parent, const Simple2D::mouse_button_e& mouse_button_event) {
		if(extended) {
			for(auto& i : buttons) {
				i.second.detect_button_click(gui_parent, mouse_button_event);
			}
		}
	}

	void pop_up_window::set_tile_button_state(const std::string& internal_name, const bool new_state) {
		buttons[internal_name].set_clicked(new_state);
	}

	bool pop_up_window::get_tile_button_state(const std::string& internal_name) {
		return buttons[internal_name].get_clicked();
	}

	menu_bar::menu_bar(int pos_x_, int pos_y_, int width_, int height_, const Simple2D::Colour& colour_)
		:
		pos_x(pos_x_),
		pos_y(pos_y_),
		width(width_),
		height(height_),
		button_row_length(5),
		colour(colour_) {}

	void menu_bar::handle_mouse_click(GUI& gui_parent, const Simple2D::mouse_button_e& mouse_button_event) {
		for(auto& i : pop_up_windows) {
			i.second.detect_button_click(gui_parent, mouse_button_event);
		}

		for(auto& i : buttons) {
			i.second.detect_button_click(gui_parent, mouse_button_event);
		}
	}

	void menu_bar::add_button_text_sprite(Simple2D::Text_context& text_ctx, const Simple2D::Context& ctx, const char* sprite_path, const std::string& display_name, const std::string& internal_name, const Simple2D::Colour& clicked_colour) {
		buttons.emplace(std::make_pair(internal_name, button(button_row_length, pos_y, height, internal_name, colour, clicked_colour)));
		buttons[internal_name].add_text_sprite(text_ctx, ctx, display_name, sprite_path);
		button_row_length += buttons[internal_name].get_button_width() + 3;
	}

	void menu_bar::add_button_text(Simple2D::Text_context& text_ctx, const Simple2D::Context& ctx, const std::string& display_name, const std::string& internal_name, const Simple2D::Colour& clicked_colour) {
		buttons.emplace(std::make_pair(internal_name, button(button_row_length, pos_y, height, internal_name, colour, clicked_colour)));
		buttons[internal_name].add_text(text_ctx, ctx, display_name);
		button_row_length += buttons[internal_name].get_button_width() + 3;
	}

	void menu_bar::add_button_sprite(const Simple2D::Context& ctx, const char* sprite_path, const std::string& internal_name, const Simple2D::Colour& clicked_colour) {
		buttons.emplace(std::make_pair(internal_name, button(button_row_length, pos_y, height, internal_name, colour, clicked_colour)));
		buttons[internal_name].add_sprite(ctx, sprite_path);
		button_row_length += buttons[internal_name].get_button_width() + 3;
	}

	void menu_bar::set_button_state(const std::string& internal_name, const bool& new_state) {
		buttons[internal_name].set_clicked(new_state);
	}

	bool menu_bar::get_button_state(const std::string& internal_name) {
		return buttons[internal_name].get_clicked();
	}

	void menu_bar::add_pop_up_window(const Simple2D::Context& ctx, int end_pos_x, int width, int height, const Simple2D::Colour& colour, const Simple2D::Colour& background_colour, const std::string& title, const std::string& internal_name, const std::string& bound_button_internal_name) {
		pop_up_windows.emplace(std::make_pair(internal_name, pop_up_window(ctx, buttons[bound_button_internal_name].get_pos_x(), buttons[bound_button_internal_name].get_pos_y(), end_pos_x, width, buttons[bound_button_internal_name].get_button_width(), height, colour, background_colour, title, internal_name)));
	}

	void menu_bar::set_pop_up_window_direction(const std::string& internal_name, bool new_direction) {
		pop_up_windows[internal_name].set_direction(new_direction);
	}

	bool menu_bar::get_pop_up_window_direction(const std::string& internal_name) {
		return pop_up_windows[internal_name].get_direction();
	}

	void menu_bar::add_pop_up_window_button(const Simple2D::Context& ctx, const char* sprite_path, const std::string& display_name, const std::string& internal_name, const Simple2D::Colour& regular_colour_, const Simple2D::Colour& clicked_colour_, const std::string& window_internal_name) {
		pop_up_windows[window_internal_name].add_tile_button(ctx, sprite_path, display_name, internal_name, regular_colour_, clicked_colour_);
	}

	void menu_bar::set_pop_up_tile_button_state(const std::string& window_internal_name, const std::string& button_internal_name, const bool new_state) {
		pop_up_windows[window_internal_name].set_tile_button_state(button_internal_name, new_state);
	}
	
	bool menu_bar::get_pop_up_tile_button_state(const std::string& window_internal_name, const std::string& button_internal_name) {
		return pop_up_windows[window_internal_name].get_tile_button_state(button_internal_name);
	}

	void menu_bar::draw_menu_bar(Simple2D::Text_context& text_ctx, const Simple2D::Context& ctx) {
		for(auto& i : pop_up_windows) {
			if(i.second.get_direction()) {
				i.second.draw_scale_up(text_ctx, ctx);
			}else{
				i.second.draw_scale_down(text_ctx, ctx);
			}
		}

		ctx.draw_rect(pos_x, pos_y, width, height, colour, true);

		for(auto& i : buttons) {
			i.second.draw_button(text_ctx, ctx);
		}
	}

	GUI::GUI() {}

	void GUI::handle_mouse_click(const Simple2D::mouse_button_e& mouse_button_event) {
		for(unsigned int i = 0; i < menu_bars.size(); i++) {
			menu_bars[i].get()->handle_mouse_click(*this, mouse_button_event);
		}
	}

	event GUI::peek_event_stack() {
		if(events.size() > 0) {
			event tmp = events[events.size()-1];
			events.pop_back();
			return tmp;
		}else{
			return {"", -1, 0};
		}
	}

	void GUI::push_event_stack(const event new_event) {
		events.push_back(new_event);
	}

	void GUI::add_menu_bar(menu_bar* new_menu_bar) {
		menu_bars.push_back(std::unique_ptr<menu_bar>(new_menu_bar));
	}

	void GUI::draw_gui(Simple2D::Text_context& text_ctx, const Simple2D::Context& ctx) {
		for(unsigned int i = 0; i < menu_bars.size(); i++) {
			menu_bars[i].get()->draw_menu_bar(text_ctx, ctx);
		}
	}

}