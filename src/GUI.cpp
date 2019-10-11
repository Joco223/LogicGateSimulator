#include "GUI.h"

namespace GUI {

	button::button(const Simple2D::Context& ctx, int pos_x_, int pos_y_, int height_, const char* sprite_path, const std::string& internal_name_, const Simple2D::Colour& regular_colour_, const Simple2D::Colour& clicked_colour_)
		:
		pos_x(pos_x_),
		pos_y(pos_y_),
		width(0),
		height(height_),
		clicked(false),
		internal_name(internal_name_),
		regular_colour(regular_colour_),
		clicked_colour(clicked_colour_) {
			sprite = Simple2D::Sprite(ctx, sprite_path);
			width = 4 + height;
		}

	button::button(Simple2D::Text_context& text_ctx, const Simple2D::Context& ctx, int pos_x_, int pos_y_, int height_, const std::string& display_name_, const std::string& internal_name_, const Simple2D::Colour& regular_colour_, const Simple2D::Colour& clicked_colour_)
		:
		pos_x(pos_x_),
		pos_y(pos_y_),
		width(0),
		height(height_),
		clicked(false),
		display_name(display_name_),
		internal_name(internal_name_),
		regular_colour(regular_colour_),
		clicked_colour(clicked_colour_) {
			text_ctx.get_text_size(ctx, width, height, display_name, height_/1.3333);
			height = height_;
		}

	button::button(Simple2D::Text_context& text_ctx, const Simple2D::Context& ctx, int pos_x_, int pos_y_, int height_, const char* sprite_path, const std::string& display_name_, const std::string& internal_name_, const Simple2D::Colour& regular_colour_, const Simple2D::Colour& clicked_colour_)
		:
		pos_x(pos_x_),
		pos_y(pos_y_),
		width(0),
		height(height_),
		clicked(false),
		display_name(display_name_),
		internal_name(internal_name_),
		regular_colour(regular_colour_),
		clicked_colour(clicked_colour_) {
			sprite = Simple2D::Sprite(ctx, sprite_path);
			text_ctx.get_text_size(ctx, width, height, display_name, height_/1.3333);
			height = height_;
		}

	void button::draw_button(Simple2D::Text_context& text_ctx, const Simple2D::Context& ctx) {
		if(clicked) {
			ctx.draw_rect(pos_x, pos_y, width, height, clicked_colour, true);
		}else{
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

	void button::detect_button_click(Simple2D::Text_context& text_ctx, const Simple2D::Context& ctx, GUI& gui_parent, const Simple2D::mouse_button_e& mouse_button_event) {
		event new_event;
		new_event.source = internal_name;
		new_event.event_type = mouse_button_event.state;
		new_event.event_desc_1 = mouse_button_event.button;
		if(mouse_button_event.x > pos_x && mouse_button_event.x < pos_x+width) {
			if(mouse_button_event.y > pos_y && mouse_button_event.y < pos_y+height) {
				if(mouse_button_event.state == Simple2D::MOUSE_UP && clicked)
					gui_parent.push_event_stack(new_event);

				if(mouse_button_event.state == Simple2D::MOUSE_DOWN && !clicked)
					gui_parent.push_event_stack(new_event);
				
				if(mouse_button_event.state == Simple2D::MOUSE_DOWN) {
					clicked = true;
				}else{
					clicked = false;
				}
			}else{
				if(mouse_button_event.state == Simple2D::MOUSE_UP && clicked)
					gui_parent.push_event_stack(new_event);
				clicked = false;
			}
		}else{
			if(mouse_button_event.state == Simple2D::MOUSE_UP && clicked)
				gui_parent.push_event_stack(new_event);
			clicked = false;
		}
		draw_button(text_ctx, ctx);
	}

	int button::get_button_width() const {
		return width;
	}

	menu_bar::menu_bar(int pos_x_, int pos_y_, int width_, int height_, const Simple2D::Colour& colour_)
		:
		pos_x(pos_x_),
		pos_y(pos_y_),
		width(width_),
		height(height_),
		button_row_length(5),
		colour(colour_) {}

	void menu_bar::handle_mouse_click(Simple2D::Text_context& text_ctx, const Simple2D::Context& ctx, GUI& gui_parent, const Simple2D::mouse_button_e& mouse_button_event) {
		for(auto& i : buttons) {
			i.detect_button_click(text_ctx, ctx, gui_parent, mouse_button_event);
		}
	}

	void menu_bar::add_button(Simple2D::Text_context& text_ctx, const Simple2D::Context& ctx, const char* sprite_path, const std::string& display_name, const std::string& internal_name, const Simple2D::Colour& clicked_colour) {
		buttons.push_back(button(text_ctx, ctx, button_row_length, pos_y, height, sprite_path, display_name, internal_name, colour, clicked_colour));
		button_row_length += buttons[buttons.size()-1].get_button_width() + 3;
		button_end_pos.push_back(button_row_length-2);
	}

	void menu_bar::add_button(Simple2D::Text_context& text_ctx, const Simple2D::Context& ctx, const std::string& display_name, const std::string& internal_name, const Simple2D::Colour& clicked_colour) {
		buttons.push_back(button(text_ctx, ctx, button_row_length, pos_y, height, display_name, internal_name, colour, clicked_colour));
		button_row_length += buttons[buttons.size()-1].get_button_width() + 3;
		button_end_pos.push_back(button_row_length-2);
	}

	void menu_bar::add_button(const Simple2D::Context& ctx, const char* sprite_path, const std::string& internal_name, const Simple2D::Colour& clicked_colour) {
		buttons.push_back(button(ctx, button_row_length, pos_y, height, sprite_path, internal_name, colour, clicked_colour));
		button_row_length += buttons[buttons.size()-1].get_button_width() + 3;
		button_end_pos.push_back(button_row_length-2);
	}

	void menu_bar::draw_menu_bar(Simple2D::Text_context& text_ctx, const Simple2D::Context& ctx) {
		ctx.draw_rect(pos_x, pos_y, width, height, colour, true);

		int index = 0;
		for(auto& i : buttons) {
			i.draw_button(text_ctx, ctx);
			ctx.draw_line(button_end_pos[index], pos_y + height/5, button_end_pos[index], pos_y + 4*height/5, {255, 255, 255, 255});
			index++;
		}
	}

	GUI::GUI() {}

	void GUI::handle_mouse_click(Simple2D::Text_context& text_ctx, const Simple2D::Context& ctx, const Simple2D::mouse_button_e& mouse_button_event) {
		for(unsigned int i = 0; i < menu_bars.size(); i++) {
			menu_bars[i].get()->handle_mouse_click(text_ctx, ctx, *this, mouse_button_event);
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