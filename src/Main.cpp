#define SDL_MAIN_HANDLED

#include "Simple2D.h"
#include "Simple2D_Sprite.h"
#include "Simple2D_Text.h"

#include "Sandbox.h"
#include "Camera.h"
#include "GUI_Controller.h"
#include "Chip.h"
#include "Asset_loader.h"

#include <iostream>
#include <string>
#include <optional>
#include <functional>

constexpr int width                      = 1600;
constexpr int height                     = 900;
constexpr Simple2D::Colour window_colour = {50, 50, 50, 255};

void placeholder() {}

int main() {

	Simple2D::Context ctx(width, height, "LGS");
	ctx.set_window_colour(window_colour);
	ctx.set_blending_mode(Simple2D::S2D_BLENDING_ALPHA);
	ctx.set_aa_mode(Simple2D::S2D_AA_LINEAR);

	Simple2D::Text_context text_ctx("assets/Cascadia.ttf");

	Sandbox sandbox;

	GUI_Controller gui_controller = GUI_Controller(ctx, width, height);

	gui_controller.init_menu_bar(ctx, text_ctx);

	Asset_loader asset_loader;
	asset_loader.load_chips(ctx, "assets/chips/", gui_controller);
	asset_loader.load_logic_gates(ctx, "assets/logic_gates/", gui_controller);

	Camera camera = Camera();
	int rel_x = 0;
	int rel_y = 0;
	int curr_mouse_x = 0;
	int curr_mouse_y = 0;

	while(!ctx.check_exit()) {
		ctx.clear();

		rel_x = 0;
		rel_y = 0;
		std::optional<Simple2D::mouse_motion_e> mouse_motion_event = ctx.check_mouse_motion();
		while(mouse_motion_event) {
			rel_x += mouse_motion_event->rel_x;
			rel_y -= mouse_motion_event->rel_y;
			curr_mouse_x = mouse_motion_event->x;
			curr_mouse_y = mouse_motion_event->y;
			gui_controller.handle_mouse_move(*mouse_motion_event);
			mouse_motion_event = ctx.check_mouse_motion();
		}

		std::optional<Simple2D::mouse_button_e> mouse_button_event = ctx.check_mouse_button();
		if(mouse_button_event) {
			camera.update_position(*mouse_button_event);
			gui_controller.handle_mouse_click(camera.get_pos_x(), camera.get_pos_y(), ctx, *mouse_button_event, sandbox);
		}

		std::optional<Simple2D::mouse_wheel_e> mouse_wheel_event = ctx.check_mouse_wheel();
		if(mouse_wheel_event) {
			gui_controller.handle_mouse_scroll(*mouse_wheel_event, curr_mouse_x, curr_mouse_y);
		}

		std::optional<Simple2D::keyboard_e> keyboard_event = ctx.check_keyboard();
		while(keyboard_event) {
			gui_controller.handle_keyboard(*keyboard_event);
			keyboard_event = ctx.check_keyboard();
		}

		gui_controller.handle_events(ctx);

		camera.move_camera(rel_x, rel_y);

		sandbox.draw(camera.get_pos_x(), camera.get_pos_y(), ctx);

		gui_controller.draw_gui(ctx, text_ctx);

		ctx.draw();
	}

	return 0;
}
