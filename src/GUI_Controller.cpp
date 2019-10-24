#include "GUI_Controller.h"

GUI_Controller::GUI_Controller(Simple2D::Context& ctx, int width_, int height_) : width(width_), height(height_), mouse_x(0), mouse_y(0) {
	gui = Simple2D::GUI::GUI(ctx, width, height);
	main_bar = Simple2D::GUI::menu_bar(0, height*0.97, width, height-height*0.97, {20, 20, 20, 255});
	gui.add_menu_bar(&main_bar);
	selected_chip = {0, 0, Simple2D::Sprite(), false};
}

void GUI_Controller::init_menu_bar(const Simple2D::Context& ctx, Simple2D::Text_context& text_ctx) {
	//Buttons
	main_bar.add_button_sprite(ctx, "assets/wire_icon.png", "wire_button", {200, 200, 200, 255});
	main_bar.add_button_text_sprite(text_ctx, ctx, "assets/chips/Chip 1.png", "Chips", "chip_button", {200, 200, 200, 255});

	//Chips menu
	main_bar.add_pop_up_window(ctx, 10, 550, 350, 20, {20, 20, 20, 255}, {15, 15, 15, 100}, "Chips", "chips_pop_up_window", "chip_button");
}

void GUI_Controller::add_chips_button(const Simple2D::Context& ctx, const Chip& chip) {
	main_bar.add_pop_up_window_button(ctx, chip.get_sprite_path().c_str(), chip.get_name(), chip.get_internal_name(), {20, 20, 20, 255}, {200, 200, 200, 255}, "chips_pop_up_window");
	chip_info.push_back({chip.get_internal_name(), chip.get_sprite_path()});
}

void GUI_Controller::draw_gui(Simple2D::Context& ctx, Simple2D::Text_context& text_ctx) {
	if(selected_chip.show) {
		selected_chip.sprite.draw(ctx, mouse_x-selected_chip.sprite.get_sprite_width()/2, mouse_y-selected_chip.sprite.get_sprite_height()/2, selected_chip.sprite.get_sprite_width(), selected_chip.sprite.get_sprite_height());
	}

	gui.draw_gui(text_ctx, ctx);
}

void GUI_Controller::handle_mouse_move(const Simple2D::mouse_motion_e& mouse_motion_event) {
	mouse_x = mouse_motion_event.x;
	mouse_y = mouse_motion_event.y;
}

void GUI_Controller::handle_mouse_click(const Simple2D::mouse_button_e& mouse_button_event) {
	gui.handle_mouse_click(mouse_button_event);
	selected_chip.show = false;
}

void GUI_Controller::handle_mouse_scroll(const Simple2D::mouse_wheel_e& mouse_wheel_event, int mouse_pos_x, int mouse_pos_y) {
	main_bar.check_pop_up_tile_scroll("chips_pop_up_window", mouse_wheel_event, mouse_pos_x, mouse_pos_y);
}

void GUI_Controller::handle_events(Simple2D::Context& ctx) {
	Simple2D::GUI::event gui_event = gui.peek_event_stack();
	while(gui_event.event_type != -1) {
		if(gui_event.source == "wire_button") {
			if(gui_event.event_type == Simple2D::MOUSE_DOWN && gui_event.event_desc_bool) {
				main_bar.set_button_state("wire_button", !main_bar.get_button_state("wire_button"));
				main_bar.set_button_state("chip_button", false);
			}
		}else if(gui_event.source == "chip_button") {
			if(gui_event.event_type == Simple2D::MOUSE_DOWN && gui_event.event_desc_bool) {
				main_bar.set_button_state("wire_button", false);
				main_bar.set_button_state("chip_button", !main_bar.get_button_state("chip_button"));
				main_bar.set_pop_up_window_direction("chips_pop_up_window", !main_bar.get_pop_up_window_direction("chips_pop_up_window"));
			}
		}

		for(auto& i : chip_info) {
			if(gui_event.source == i.first) {
				if(gui_event.event_type == Simple2D::MOUSE_DOWN) {
					if(gui_event.event_desc_1 == Simple2D::MOUSE_LEFT) {
						main_bar.set_pop_up_tile_button_state("chips_pop_up_window", i.first, true);
					}
				}else{
					main_bar.set_pop_up_tile_button_state("chips_pop_up_window", i.first, false);
					selected_chip = {mouse_x, mouse_y, Simple2D::Sprite(ctx, i.second.c_str()), true};
					selected_chip.sprite.set_alpha(150);
					main_bar.set_pop_up_window_direction("chips_pop_up_window", !main_bar.get_pop_up_window_direction("chips_pop_up_window"));
					main_bar.set_button_state("chip_button", false);
				}
			}
		}

		gui_event = gui.peek_event_stack();
	}
}