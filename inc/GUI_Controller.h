#pragma once

#include "Simple2D/Simple2D.h"
#include "Simple2D/Simple2D_Text.h"
#include "Simple2D/Simple2D_GUI.h"

class GUI_Controller {
private:
	int width, height;
	Simple2D::GUI::GUI gui;
	Simple2D::GUI::menu_bar main_bar;
public:
	GUI_Controller(Simple2D::Context& ctx, int width, int height);

	void init_menu_bar(const Simple2D::Context& ctx, Simple2D::Text_context& text_ctx);

	void draw_gui(Simple2D::Context& ctx, Simple2D::Text_context& text_ctx);

	void handle_mouse_click(const Simple2D::mouse_button_e& mouse_button_event);
	void handle_mouse_scroll(const Simple2D::mouse_wheel_e& mouse_wheel_event, int mouse_pos_x, int mouse_pos_y);
	void handle_events();
};