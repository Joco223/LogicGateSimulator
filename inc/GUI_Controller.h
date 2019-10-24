#pragma once

#include "Simple2D/Simple2D.h"
#include "Simple2D/Simple2D_Text.h"
#include "Simple2D/Simple2D_GUI.h"

#include "Chip.h"

#include <vector>
#include <string>

struct shadow_chip {
	int pos_x, pos_y;
	Simple2D::Sprite sprite;
	bool show;
};

class GUI_Controller {
private:
	int width, height, mouse_x, mouse_y;
	Simple2D::GUI::GUI gui;
	Simple2D::GUI::menu_bar main_bar;
	std::vector<std::pair<std::string, std::string>> chip_info; //internal name and sprite path
	shadow_chip selected_chip;
public:
	GUI_Controller(Simple2D::Context& ctx, int width, int height);

	void init_menu_bar(const Simple2D::Context& ctx, Simple2D::Text_context& text_ctx);
	void add_chips_button(const Simple2D::Context& ctx, const Chip& chip);

	void draw_gui(Simple2D::Context& ctx, Simple2D::Text_context& text_ctx);

	void handle_mouse_move(const Simple2D::mouse_motion_e& mouse_motion_event);
	void handle_mouse_click(const Simple2D::mouse_button_e& mouse_button_event);
	void handle_mouse_scroll(const Simple2D::mouse_wheel_e& mouse_wheel_event, int mouse_pos_x, int mouse_pos_y);
	void handle_events(Simple2D::Context& ctx);
};