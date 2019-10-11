#define SDL_MAIN_HANDLED

#include "Simple2D/Simple2D.h"
#include "Simple2D/Simple2D_Sprite.h"
#include "Simple2D/Simple2D_Text.h"

#include "Sandbox.h"
#include "Camera.h"
#include "GUI.h"

#include <iostream>
#include <string>
#include <optional>
#include <functional>

constexpr int width                      = 1280;
constexpr int height                     = 720;
constexpr Simple2D::Colour window_colour = {50, 50, 50, 255};

int main() {

	Simple2D::Context ctx(width, height, "LGS");
	ctx.set_window_colour(window_colour);
	ctx.set_vsync(true);
	ctx.set_blending_mode(Simple2D::S2D_BLENDING_ALPHA);
	ctx.set_aa_mode(Simple2D::S2D_AA_NEAREST);

	Simple2D::Text_context text_ctx("Cascadia.ttf");

	Sandbox sandbox(20, 20);
	Camera camera = Camera();
	int rel_x = 0;
	int rel_y = 0;

	GUI::GUI gui;
	GUI::menu_bar main_bar = GUI::menu_bar(0, height*0.97, width, height-height*0.97, {20, 20, 20, 255});
	gui.add_menu_bar(&main_bar);
	main_bar.add_button_sprite(ctx, "wire_icon.png", "wire_button", {200, 200, 200, 255});
	main_bar.add_button_text_sprite(text_ctx, ctx, "chip_icon.png", "Chips", "chip_button", {200, 200, 200, 255});

	while(!ctx.check_exit()) {
		ctx.clear();

		std::optional<Simple2D::mouse_motion_e> mouse_motion_event = ctx.check_mouse_motion();
		if(mouse_motion_event) {
			rel_x = mouse_motion_event->rel_x;
			rel_y = mouse_motion_event->rel_y;
		}

		std::optional<Simple2D::mouse_button_e> mouse_button_event = ctx.check_mouse_button();
		if(mouse_button_event) {
			camera.update_position(*mouse_button_event);
			gui.handle_mouse_click(text_ctx, ctx, *mouse_button_event);
		}

		camera.move_camera(rel_x, rel_y);
		rel_x = 0;
		rel_y = 0;

		sandbox.draw_grid(camera.get_pos_x(), camera.get_pos_y(), ctx);

		gui.draw_gui(text_ctx, ctx);

		GUI::event gui_event = gui.peek_event_stack();
		while(gui_event.event_type != -1) {
			if(gui_event.source == "wire_button") {
				if(gui_event.event_type == Simple2D::MOUSE_DOWN) {
					std::cout << "Wire button was pressed with button: " << gui_event.event_desc_1 << '\n';
				}else{
					std::cout << "Wire button was released with button: " << gui_event.event_desc_1 << '\n';
				}
			}else if(gui_event.source == "chip_button") {
				if(gui_event.event_type == Simple2D::MOUSE_DOWN) {
					std::cout << "Chip button was pressed with button: " << gui_event.event_desc_1 << '\n';
				}else{
					std::cout << "Chip button was released with button: " << gui_event.event_desc_1 << '\n';
				}
			}
			gui_event = gui.peek_event_stack();
		}

		ctx.draw();
	}

	return 0;
}
