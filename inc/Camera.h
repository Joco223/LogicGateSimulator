#pragma once

#include <iostream>

#include "Simple2D/Simple2D.h"

class Camera {
private:
	int pos_x, pos_y;
	bool middle_click_pressed;
public:
	Camera();

	int get_pos_x() const;
	int get_pos_y() const;

	void update_position(const Simple2D::mouse_button_e& mouse_button_event);
	void move_camera(int rel_x, int rel_y);
};