#include "GUI_Controller.h"

GUI_Controller::GUI_Controller(Simple2D::Context& ctx, int width_, int height_) : width(width_), height(height_), mouse_x(0), mouse_y(0) {
	gui = Simple2D::GUI::GUI(ctx, width, height);
	main_bar = Simple2D::GUI::menu_bar(0, height*0.97, width, height-height*0.97, {20, 20, 20, 255});
	gui.add_menu_bar(&main_bar);
	selected_object = {0, 0, 0, 0, false};
}

void GUI_Controller::init_menu_bar(const Simple2D::Context& ctx, Simple2D::Text_context& text_ctx) {
	//Buttons
	main_bar.add_button_sprite(ctx, "assets/wire_icon.png", "wire_button", {200, 200, 200, 255});
	main_bar.add_button_text(text_ctx, ctx, "Chips", "chip_button", {200, 200, 200, 255});
	main_bar.add_button_text(text_ctx, ctx, "Logic Gates", "logic_gates_button", {200, 200, 200, 255});

	//Chips menu
	main_bar.add_pop_up_window(ctx, 10, 550, 350, 20, {20, 20, 20, 255}, {15, 15, 15, 100}, "Chips", "chips_window", "chip_button");

	//Logic gates menu
	main_bar.add_pop_up_window(ctx, 10, 550, 350, 20, {20, 20, 20, 255}, {15, 15, 15, 100}, "Logic Gates", "logic_gates_window", "logic_gates_button");
}

void GUI_Controller::add_chips_button(Simple2D::Context& ctx, int pos_x, int pos_y, const std::string& name, const std::string& sprite_path) {
	main_bar.add_pop_up_window_button(ctx, sprite_path.c_str(), name, name, {20, 20, 20, 255}, {200, 200, 200, 255}, "chips_window");
	object_info.push_back({0, name});
	object_sprites.push_back(Simple2D::Sprite(ctx, sprite_path.c_str()));
	chip_copies.emplace_back(Chip(ctx, 0, 0, name, sprite_path));
}

void GUI_Controller::add_logic_gates_button(Simple2D::Context& ctx, int pos_x, int pos_y, const std::string& name, const std::string& sprite_path) {
	main_bar.add_pop_up_window_button(ctx, sprite_path.c_str(), name, name, {20, 20, 20, 255}, {200, 200, 200, 255}, "logic_gates_window");
	object_info.push_back({1, name});
	object_sprites.push_back(Simple2D::Sprite(ctx, sprite_path.c_str()));
	chip_copies.emplace_back(Chip(ctx, 0, 0, name, sprite_path));
}

void GUI_Controller::draw_gui(Simple2D::Context& ctx, Simple2D::Text_context& text_ctx) {
	if(selected_object.show) {
		object_sprites[selected_object.id].draw_rotated(ctx, mouse_x-object_sprites[selected_object.id].get_sprite_width()/2, mouse_y-object_sprites[selected_object.id].get_sprite_height()/2, object_sprites[selected_object.id].get_sprite_width(), object_sprites[selected_object.id].get_sprite_height(), selected_object.angle);
	}

	gui.draw_gui(text_ctx, ctx);
}

void GUI_Controller::handle_keyboard(const Simple2D::keyboard_e& keyboard_event) {
	if(selected_object.show) {
		if(keyboard_event.key_code == Simple2D::KEY_R && keyboard_event.state == Simple2D::KEY_DOWN) {
			selected_object.angle += 90;
		}
	}
}

void GUI_Controller::handle_mouse_move(const Simple2D::mouse_motion_e& mouse_motion_event) {
	mouse_x = mouse_motion_event.x;
	mouse_y = mouse_motion_event.y;
}

void GUI_Controller::handle_mouse_click(int offset_x, int offset_y, const Simple2D::Context& ctx, const Simple2D::mouse_button_e& mouse_button_event, Sandbox& sandbox) {
	gui.handle_mouse_click(mouse_button_event);
	if(selected_object.show) {
		sandbox.add_object(ctx, mouse_button_event.x-offset_x-chip_copies[selected_object.id].get_sprite_width()/2, mouse_button_event.y+offset_y-chip_copies[selected_object.id].get_sprite_height()/2, selected_object.angle, chip_copies[selected_object.id].get_name(), chip_copies[selected_object.id].get_sprite_path());
	}
	selected_object.show = false;
}

void GUI_Controller::handle_mouse_scroll(const Simple2D::mouse_wheel_e& mouse_wheel_event, int mouse_pos_x, int mouse_pos_y) {
	main_bar.check_pop_up_tile_scroll("chips_window", mouse_wheel_event, mouse_pos_x, mouse_pos_y);
}

void GUI_Controller::handle_events(Simple2D::Context& ctx) {
	Simple2D::GUI::event gui_event = gui.peek_event_stack();
	while(gui_event.event_type != -1) {
		if(gui_event.source == "wire_button") {
			if(gui_event.event_type == Simple2D::MOUSE_DOWN && gui_event.event_desc_bool) {
				main_bar.set_button_state("wire_button", !main_bar.get_button_state("wire_button"));

				main_bar.set_button_state("logic_gates_button", false);
				main_bar.set_pop_up_window_direction("logic_gates_window", false);

				main_bar.set_button_state("chip_button", false);
				main_bar.set_pop_up_window_direction("chips_window", false);
			}
		}else if(gui_event.source == "chip_button") {
			if(gui_event.event_type == Simple2D::MOUSE_DOWN && gui_event.event_desc_bool) {
				main_bar.set_button_state("logic_gates_button", false);
				main_bar.set_pop_up_window_direction("logic_gates_window", false);

				main_bar.set_button_state("wire_button", false);

				main_bar.set_button_state("chip_button", !main_bar.get_button_state("chip_button"));
				main_bar.set_pop_up_window_direction("chips_window", !main_bar.get_pop_up_window_direction("chips_window"));
			}
		}else if(gui_event.source == "logic_gates_button") {
			if(gui_event.event_type == Simple2D::MOUSE_DOWN && gui_event.event_desc_bool) {
				main_bar.set_button_state("chip_button", false);
				main_bar.set_pop_up_window_direction("chips_window", false);

				main_bar.set_button_state("wire_button", false);
				main_bar.set_button_state("logic_gates_button", !main_bar.get_button_state("logic_gates_button"));
				main_bar.set_pop_up_window_direction("logic_gates_window", !main_bar.get_pop_up_window_direction("logic_gates_window"));
			}
		}

		int object_index = 0;
		for(auto& i : object_info) {
			if(gui_event.source == i.second) {
				if(gui_event.event_type == Simple2D::MOUSE_DOWN) {
					if(gui_event.event_desc_1 == Simple2D::MOUSE_LEFT) {
						if(i.first == 0) {
							main_bar.set_pop_up_tile_button_state("chips_window", i.second, true);
						}else{
							main_bar.set_pop_up_tile_button_state("logic_gates_window", i.second, true);
						}
						
					}
				}else{
					selected_object = {mouse_x, mouse_y, object_index, 0, true};
					object_sprites[object_index].set_alpha(150);

					if(i.first == 0) {
						main_bar.set_pop_up_tile_button_state("chips_window", i.second, false);
						main_bar.set_pop_up_window_direction("chips_window", !main_bar.get_pop_up_window_direction("chips_window"));
						main_bar.set_button_state("chip_button", false);
					}else{
						main_bar.set_pop_up_tile_button_state("logic_gates_window", i.second, false);
						main_bar.set_pop_up_window_direction("logic_gates_window", !main_bar.get_pop_up_window_direction("logic_gates_window"));
						main_bar.set_button_state("logic_gates_button", false);
					}
				}
			}
			object_index++;
		}

		gui_event = gui.peek_event_stack();
	}
}