#define SDL_MAIN_HANDLED

#include "Simple2D.h"
#include "Simple2D_Sprite.h"
#include "Simple2D_Text.h"

#include "Sandbox.h"
#include "Camera.h"
#include "GUI.h"

#include <iostream>
#include <string>
#include <optional>
#include <functional>

constexpr int width                      = 1600;
constexpr int height                     = 900;
constexpr Simple2D::Colour window_colour = {50, 50, 50, 255};

int main() {

	Simple2D::Context ctx(width, height, "LGS");
	ctx.set_window_colour(window_colour);
	ctx.set_blending_mode(Simple2D::S2D_BLENDING_ALPHA);
	ctx.set_aa_mode(Simple2D::S2D_AA_NEAREST);

	Simple2D::Text_context text_ctx("assets/Cascadia.ttf");

	Sandbox sandbox(20, 20);
	Camera camera = Camera();
	int rel_x = 0;
	int rel_y = 0;
	int curr_mouse_x = 0;
	int curr_mouse_y = 0;

	GUI::GUI gui(ctx, width, height);
	GUI::menu_bar main_bar = GUI::menu_bar(0, height*0.97, width, height-height*0.97, {20, 20, 20, 255});
	gui.add_menu_bar(&main_bar);
	main_bar.add_button_sprite(ctx, "assets/wire_icon.png", "wire_button", {200, 200, 200, 255});
	main_bar.add_button_text_sprite(text_ctx, ctx, "assets/chip_icon.png", "Chips", "chip_button", {200, 200, 200, 255});
	main_bar.add_pop_up_window(ctx, 10, 550, 350, 20, {20, 20, 20, 255}, {15, 15, 15, 100}, "Chips", "chips_pop_up_window", "chip_button");
	main_bar.add_pop_up_window_button(ctx, "assets/chip_icon.png", "Test chip 1", "test_chip1", {20, 20, 20, 255}, {200, 200, 200, 255}, "chips_pop_up_window");
	main_bar.add_pop_up_window_button(ctx, "assets/chip2_icon.png", "Test chip 2", "test_chip2", {20, 20, 20, 255}, {200, 200, 200, 255}, "chips_pop_up_window");
	main_bar.add_pop_up_window_button(ctx, "assets/chip4_icon.png", "Test chip 3", "test_chip3", {20, 20, 20, 255}, {200, 200, 200, 255}, "chips_pop_up_window");
	main_bar.add_pop_up_window_button(ctx, "assets/chip3_icon.png", "Test chip 4", "test_chip4", {20, 20, 20, 255}, {200, 200, 200, 255}, "chips_pop_up_window");
	main_bar.add_pop_up_window_button(ctx, "assets/chip_icon.png", "Test chip 5", "test_chip5", {20, 20, 20, 255}, {200, 200, 200, 255}, "chips_pop_up_window");
	main_bar.add_pop_up_window_button(ctx, "assets/chip_icon.png", "Test chip 6", "test_chip6", {20, 20, 20, 255}, {200, 200, 200, 255}, "chips_pop_up_window");
	main_bar.add_pop_up_window_button(ctx, "assets/chip_icon.png", "Test chip 7", "test_chip7", {20, 20, 20, 255}, {200, 200, 200, 255}, "chips_pop_up_window");
	main_bar.add_pop_up_window_button(ctx, "assets/chip4_icon.png", "Test chip 8", "test_chip8", {20, 20, 20, 255}, {200, 200, 200, 255}, "chips_pop_up_window");
	main_bar.add_pop_up_window_button(ctx, "assets/chip3_icon.png", "Test chip 9", "test_chip9", {20, 20, 20, 255}, {200, 200, 200, 255}, "chips_pop_up_window");
	main_bar.add_pop_up_window_button(ctx, "assets/chip4_icon.png", "Test chip 10", "test_chip10", {20, 20, 20, 255}, {200, 200, 200, 255}, "chips_pop_up_window");

	while(!ctx.check_exit()) {
		ctx.clear();

		rel_x = 0;
		rel_y = 0;
		std::optional<Simple2D::mouse_motion_e> mouse_motion_event = ctx.check_mouse_motion();
		while(mouse_motion_event) {
			rel_x += mouse_motion_event->rel_x;
			rel_y += mouse_motion_event->rel_y;
			curr_mouse_x = mouse_motion_event->x;
			curr_mouse_y = mouse_motion_event->y;
			mouse_motion_event = ctx.check_mouse_motion();
		}

		std::optional<Simple2D::mouse_button_e> mouse_button_event = ctx.check_mouse_button();
		if(mouse_button_event) {
			camera.update_position(*mouse_button_event);
			gui.handle_mouse_click(*mouse_button_event);
		}

		std::optional<Simple2D::mouse_wheel_e> mouse_wheel_event = ctx.check_mouse_wheel();
		if(mouse_wheel_event) {
			main_bar.check_pop_up_tile_scroll("chips_pop_up_window", *mouse_wheel_event, curr_mouse_x, curr_mouse_y);
		}

		camera.move_camera(rel_x, rel_y);

		sandbox.draw_grid(camera.get_pos_x(), camera.get_pos_y(), ctx);

		gui.draw_gui(text_ctx, ctx);

		GUI::event gui_event = gui.peek_event_stack();
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

		ctx.draw();
	}

	return 0;
}
