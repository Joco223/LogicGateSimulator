#pragma once

#include "Simple2D/Simple2D.h"
#include "Simple2D/Simple2D_Text.h"
#include "Simple2D/Simple2D_GUI.h"

#include "Chip.h"
#include "Sandbox.h"

#include <vector>
#include <string>
#include <memory>

struct shadow_object {
	int pos_x, pos_y, id, angle;
	bool show;
};

class GUI_Controller {
private:
	int width, height, mouse_x, mouse_y;
	Simple2D::GUI::GUI gui;
	Simple2D::GUI::menu_bar main_bar;
	std::vector<std::pair<int, std::string>> object_info; //Type and internal name (0 - chip, 1 - logic gate)
	shadow_object selected_object;
	std::vector<Simple2D::Sprite> object_sprites;

	std::vector<Chip> chip_copies;
public:
	GUI_Controller(Simple2D::Context& ctx, int width, int height);

	void init_menu_bar(const Simple2D::Context& ctx, Simple2D::Text_context& text_ctx);
	void add_chips_button(Simple2D::Context& ctx, int pos_x, int pos_y, const std::string& name, const std::string& sprite_path);
	void add_logic_gates_button(Simple2D::Context& ctx, int pos_x, int pos_y, const std::string& name, const std::string& sprite_path);

	void draw_gui(Simple2D::Context& ctx, Simple2D::Text_context& text_ctx);

	void handle_keyboard(const Simple2D::keyboard_e& keyboard_event);
	void handle_mouse_move(const Simple2D::mouse_motion_e& mouse_motion_event);
	void handle_mouse_click(int offset_x, int offset_y, const Simple2D::Context& ctx, const Simple2D::mouse_button_e& mouse_button_event, Sandbox& sandbox);
	void handle_mouse_scroll(const Simple2D::mouse_wheel_e& mouse_wheel_event, int mouse_pos_x, int mouse_pos_y);
	void handle_events(Simple2D::Context& ctx);
};