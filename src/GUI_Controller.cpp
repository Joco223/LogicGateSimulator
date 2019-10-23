#include "GUI_Controller.h"

GUI_Controller::GUI_Controller(Simple2D::Context& ctx, int width_, int height_) : width(width_), height(height_) {
	gui = Simple2D::GUI::GUI(ctx, width, height);
	main_bar = Simple2D::GUI::menu_bar(0, height*0.97, width, height-height*0.97, {20, 20, 20, 255});
	gui.add_menu_bar(&main_bar);
}

void GUI_Controller::init_menu_bar(const Simple2D::Context& ctx, Simple2D::Text_context& text_ctx) {
	//Buttons
	main_bar.add_button_sprite(ctx, "assets/wire_icon.png", "wire_button", {200, 200, 200, 255});
	main_bar.add_button_text_sprite(text_ctx, ctx, "assets/chip_icon.png", "Chips", "chip_button", {200, 200, 200, 255});

	//Chips menu
	main_bar.add_pop_up_window(ctx, 10, 550, 350, 20, {20, 20, 20, 255}, {15, 15, 15, 100}, "Chips", "chips_pop_up_window", "chip_button");
	main_bar.add_pop_up_window_button(ctx, "assets/chip_icon.png",  "Test chip 1",  "test_chip1",  {20, 20, 20, 255}, {200, 200, 200, 255}, "chips_pop_up_window");
	main_bar.add_pop_up_window_button(ctx, "assets/chip2_icon.png", "Test chip 2",  "test_chip2",  {20, 20, 20, 255}, {200, 200, 200, 255}, "chips_pop_up_window");
	main_bar.add_pop_up_window_button(ctx, "assets/chip4_icon.png", "Test chip 3",  "test_chip3",  {20, 20, 20, 255}, {200, 200, 200, 255}, "chips_pop_up_window");
	main_bar.add_pop_up_window_button(ctx, "assets/chip3_icon.png", "Test chip 4",  "test_chip4",  {20, 20, 20, 255}, {200, 200, 200, 255}, "chips_pop_up_window");
	main_bar.add_pop_up_window_button(ctx, "assets/chip_icon.png",  "Test chip 5",  "test_chip5",  {20, 20, 20, 255}, {200, 200, 200, 255}, "chips_pop_up_window");
	main_bar.add_pop_up_window_button(ctx, "assets/chip_icon.png",  "Test chip 6",  "test_chip6",  {20, 20, 20, 255}, {200, 200, 200, 255}, "chips_pop_up_window");
	main_bar.add_pop_up_window_button(ctx, "assets/chip_icon.png",  "Test chip 7",  "test_chip7",  {20, 20, 20, 255}, {200, 200, 200, 255}, "chips_pop_up_window");
	main_bar.add_pop_up_window_button(ctx, "assets/chip4_icon.png", "Test chip 8",  "test_chip8",  {20, 20, 20, 255}, {200, 200, 200, 255}, "chips_pop_up_window");
	main_bar.add_pop_up_window_button(ctx, "assets/chip3_icon.png", "Test chip 9",  "test_chip9",  {20, 20, 20, 255}, {200, 200, 200, 255}, "chips_pop_up_window");
	main_bar.add_pop_up_window_button(ctx, "assets/chip4_icon.png", "Test chip 10", "test_chip10", {20, 20, 20, 255}, {200, 200, 200, 255}, "chips_pop_up_window");
}

void GUI_Controller::draw_gui(Simple2D::Context& ctx, Simple2D::Text_context& text_ctx) {
	gui.draw_gui(text_ctx, ctx);
}

void GUI_Controller::handle_mouse_click(const Simple2D::mouse_button_e& mouse_button_event) {
	gui.handle_mouse_click(mouse_button_event);
}

void GUI_Controller::handle_mouse_scroll(const Simple2D::mouse_wheel_e& mouse_wheel_event, int mouse_pos_x, int mouse_pos_y) {
	main_bar.check_pop_up_tile_scroll("chips_pop_up_window", mouse_wheel_event, mouse_pos_x, mouse_pos_y);
}

void GUI_Controller::handle_events() {
	Simple2D::GUI::event gui_event = gui.peek_event_stack();
	while(gui_event.event_type != -1) {
		if(gui_event.source == "wire_button") {
			if(gui_event.event_type == Simple2D::MOUSE_DOWN && gui_event.event_desc_bool) {
				main_bar.set_button_state("wire_button", !main_bar.get_button_state("wire_button"));
			}
		}else if(gui_event.source == "chip_button") {
			if(gui_event.event_type == Simple2D::MOUSE_DOWN && gui_event.event_desc_bool) {
				main_bar.set_button_state("chip_button", !main_bar.get_button_state("chip_button"));
				main_bar.set_pop_up_window_direction("chips_pop_up_window", !main_bar.get_pop_up_window_direction("chips_pop_up_window"));
			}
		}
		gui_event = gui.peek_event_stack();
	}
}