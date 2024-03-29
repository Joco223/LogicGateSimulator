#pragma once

#include "Simple2D.h"
#include "Simple2D_Sprite.h"
#include "Simple2D_Text.h"

#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>

namespace Simple2D {

	namespace GUI {
		
		struct event {
			std::string source;
			int event_type, event_desc_1;
			bool event_desc_bool;
		};

		class GUI;

		class button {
		private:
			float pos_x, pos_y, width, height;
			bool clicked;
			Simple2D::Sprite sprite;
			std::string display_name;
			std::string internal_name;
			Simple2D::Colour regular_colour, clicked_colour;
		public:
			button();
			button(float pos_x, float pos_y, float height, const std::string& internal_name, const Simple2D::Colour& regular_colour, const Simple2D::Colour& clicked_colour);

			void add_text(Simple2D::Text_context& text_ctx, const Simple2D::Context& ctx, const std::string& display_name);
			void add_sprite(const Simple2D::Context& ctx, const char* sprite_path);
			void add_text_sprite(Simple2D::Text_context& text_ctx, const Simple2D::Context& ctx, const std::string& display_name, const char* sprite_path);

			void set_clicked(const bool& new_clicked);
			bool get_clicked();

			void draw_button(Simple2D::Text_context& text_ctx, const Simple2D::Context& ctx);
			void detect_button_click(GUI& gui_parent, const Simple2D::mouse_button_e& mouse_button_event);

			float get_button_width() const;
			float get_pos_x() const;
			float get_pos_y() const;
		};

		class tile_button {
		private:
			float pos_x, pos_y, width, height;
			bool clicked;
			Simple2D::Sprite sprite;
			std::string display_name;
			std::string internal_name;
			Simple2D::Colour regular_colour, clicked_colour;
		public:
			tile_button();
			tile_button(const Simple2D::Context& ctx, float pos_x, float pos_y, float width, float height, const char* sprite_path, const std::string& display_name, const std::string& internal_name, const Simple2D::Colour& regular_colour, const Simple2D::Colour& clicked_colour);

			void set_clicked(const bool new_state);
			bool get_clicked() const;

			void draw_button(Simple2D::Text_context& text_ctx, const Simple2D::Context& ctx, int offset_y);
			void detect_button_click(GUI& gui_parent, const Simple2D::mouse_button_e& mouse_button_event);
		};

		struct window_structure {
			float pos_x, pos_y, width, height;
			int bar_height, window_height, text_size;
		};

		class pop_up_window {
		private:
			float pos_x, pos_y, scaled_pos_x, scaled_width, width, height;
			int animation_step, old_animation_step, animation_time, current_scroll;
			std::vector<window_structure> animation_steps;
			bool direction, extended; //Direction, true - expand, false - contract
			Simple2D::Colour colour, background_colour;
			std::string title, internal_name;
			std::unordered_map<std::string, tile_button> buttons;
		public:
			pop_up_window();
			pop_up_window(const Simple2D::Context& ctx, float pos_x, float pos_y, float scaled_pos_x, float scaled_width, float width, float height, int animation_time, const Simple2D::Colour& colour, const Simple2D::Colour& background_colour, const std::string& title, const std::string& internal_name);

			bool get_direction() const;
			void set_direction(bool);

			bool get_state() const;

			void draw_scale_up(Simple2D::Text_context& text_ctx, const Simple2D::Context& ctx);
			void draw_scale_down(Simple2D::Text_context& text_ctx, const Simple2D::Context& ctx);
			void draw_mask(const Simple2D::Context& ctx);

			void add_tile_button(const Simple2D::Context& ctx, const char* sprite_path, const std::string& display_name, const std::string& internal_name, const Simple2D::Colour& regular_colour_, const Simple2D::Colour& clicked_colour_);

			void detect_button_click(GUI& gui_parent, const Simple2D::mouse_button_e& mouse_button_event);
			void detect_mouse_scroll(const Simple2D::mouse_wheel_e& mouse_wheel_event, int mouse_pos_x, int mouse_pos_y);

			void set_tile_button_state(const std::string& internal_name, const bool new_state);
			bool get_tile_button_state(const std::string& internal_name);
		};

		class menu_bar {
		private:
			float pos_x, pos_y, width, height, button_row_length;
			Simple2D::Colour colour;
			std::unordered_map<std::string, button> buttons;
			std::unordered_map<std::string, pop_up_window> pop_up_windows;
		public:
			menu_bar();
			menu_bar(float pos_x, float pos_y, float width, float height, const Simple2D::Colour& colour);

			void handle_mouse_click(GUI& gui_parent, const Simple2D::mouse_button_e& mouse_button_event);

			void add_button_text_sprite(Simple2D::Text_context& text_ctx, const Simple2D::Context& ctx, const char* sprite_path, const std::string& display_name, const std::string& internal_name, const Simple2D::Colour& clicked_colour);
			void add_button_text(Simple2D::Text_context& text_ctx, const Simple2D::Context& ctx, const std::string& display_name, const std::string& internal_name, const Simple2D::Colour& clicked_colour);
			void add_button_sprite(const Simple2D::Context& ctx, const char* sprite_path, const std::string& internal_name, const Simple2D::Colour& clicked_colour);

			void set_button_state(const std::string& internal_name, const bool& new_state);
			bool get_button_state(const std::string& internal_name);

			void add_pop_up_window(const Simple2D::Context& ctx, float end_pos_x, float width, float height, int animation_time, const Simple2D::Colour& colour, const Simple2D::Colour& background_colour, const std::string& title, const std::string& internal_name, const std::string& bound_button_internal_name);
			
			void set_pop_up_window_direction(const std::string& internal_name, bool new_direction);
			bool get_pop_up_window_direction(const std::string& internal_name);

			void add_pop_up_window_button(const Simple2D::Context& ctx, const char* sprite_path, const std::string& display_name, const std::string& internal_name, const Simple2D::Colour& regular_colour_, const Simple2D::Colour& clicked_colour_, const std::string& window_internal_name);

			void set_pop_up_tile_button_state(const std::string& window_internal_name, const std::string& button_internal_name, const bool new_state);
			bool get_pop_up_tile_button_state(const std::string& window_internal_name, const std::string& button_internal_name);

			void check_pop_up_tile_scroll(const std::string& window_internal_name, const Simple2D::mouse_wheel_e& mouse_wheel_event, int mouse_pos_x, int mouse_pos_y);

			void draw_menu_bar(Simple2D::Text_context& text_ctx, const Simple2D::Context& ctx);
			void draw_menu_bar_mask(const Simple2D::Context& ctx);
		};

		class GUI {
		private:
			int width, height;
			std::vector<event> events;
			std::vector<std::unique_ptr<menu_bar>> menu_bars;
			Simple2D::Sprite gui_texture;
			Simple2D::Sprite gui_mask;
			Simple2D::Colour original_window_colour;
		public:
			GUI();
			GUI(Simple2D::Context& ctx, int width, int height);

			void handle_mouse_click(const Simple2D::mouse_button_e& mouse_button_event);

			event peek_event_stack();
			void push_event_stack(const event new_event);

			void add_menu_bar(menu_bar* new_menu_bar);

			void draw_gui(Simple2D::Text_context& text_ctx, Simple2D::Context& ctx);
		};
	}
}