#pragma once

#include "Simple2D/Simple2D.h"
#include "Simple2D/Simple2D_Sprite.h"
#include "Simple2D/Simple2D_Text.h"

#include <iostream>
#include <vector>
#include <string>
#include <memory>

namespace GUI {

	struct event {
		std::string source;
		int event_type, event_desc_1;
	};

	class GUI;

	class button {
	private:
		int pos_x, pos_y, width, height;
		bool clicked;
		Simple2D::Sprite sprite;
		std::string display_name;
		std::string internal_name;
		Simple2D::Colour regular_colour, clicked_colour;
	public:
		button(const Simple2D::Context& ctx, int pos_x, int pos_y, int height, const char* sprite_path, const std::string& internal_name, const Simple2D::Colour& regular_colour, const Simple2D::Colour& clicked_colour);

		button(Simple2D::Text_context& text_ctx, const Simple2D::Context& ctx, int pos_x, int pos_y, int height, const std::string& display_name, const std::string& internal_name, const Simple2D::Colour& regular_colour, const Simple2D::Colour& clicked_colour);

		button(Simple2D::Text_context& text_ctx, const Simple2D::Context& ctx, int pos_x, int pos_y, int height, const char* sprite_path, const std::string& display_name, const std::string& internal_name, const Simple2D::Colour& regular_colour, const Simple2D::Colour& clicked_colour);

		void draw_button(Simple2D::Text_context& text_ctx, const Simple2D::Context& ctx);
		void detect_button_click(Simple2D::Text_context& text_ctx, const Simple2D::Context& ctx, GUI& gui_parent, const Simple2D::mouse_button_e& mouse_button_event);

		int get_button_width() const;
	};

	class menu_bar {
	private:
		int pos_x, pos_y, width, height, button_row_length;
		Simple2D::Colour colour;
		std::vector<button> buttons;
		std::vector<int> button_end_pos;
		//std::vector<label> labels;
	public:
		menu_bar(int pos_x, int pos_y, int width, int height, const Simple2D::Colour& colour);

		void handle_mouse_click(Simple2D::Text_context& text_ctx, const Simple2D::Context& ctx, GUI& gui_parent, const Simple2D::mouse_button_e& mouse_button_event);

		void add_button(Simple2D::Text_context& text_ctx, const Simple2D::Context& ctx, const char* sprite_path, const std::string& display_name, const std::string& internal_name, const Simple2D::Colour& clicked_colour);
		void add_button(Simple2D::Text_context& text_ctx, const Simple2D::Context& ctx, const std::string& display_name, const std::string& internal_name, const Simple2D::Colour& clicked_colour);
		void add_button(const Simple2D::Context& ctx, const char* sprite_path, const std::string& internal_name, const Simple2D::Colour& clicked_colour);

		void draw_menu_bar(Simple2D::Text_context& text_ctx, const Simple2D::Context& ctx);
	};

	class GUI {
	private:
		std::vector<event> events;
		std::vector<std::unique_ptr<menu_bar>> menu_bars;
	public:
		GUI();

		void handle_mouse_click(Simple2D::Text_context& text_ctx, const Simple2D::Context& ctx, const Simple2D::mouse_button_e& mouse_button_event);

		event peek_event_stack();
		void push_event_stack(const event new_event);

		void add_menu_bar(menu_bar* new_menu_bar);

		void draw_gui(Simple2D::Text_context& text_ctx, const Simple2D::Context& ctx);
	};
}