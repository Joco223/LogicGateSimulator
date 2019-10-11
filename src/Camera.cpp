#include "Camera.h"

Camera::Camera() 
	: 
	pos_x(0), 
	pos_y(0),
	middle_click_pressed(false) {}

int Camera::get_pos_x() const {
	return pos_x;
}

int Camera::get_pos_y() const {
	return pos_y;
}

void Camera::update_position(const Simple2D::mouse_button_e& mouse_button_event) {
	if(mouse_button_event.state == Simple2D::MOUSE_DOWN && mouse_button_event.button == Simple2D::MOUSE_MIDDLE) {
		middle_click_pressed = true;
	}else{
		middle_click_pressed = false;
	}
}

void Camera::move_camera(int rel_x, int rel_y) {
	if(middle_click_pressed) {
		pos_x += rel_x;
		pos_y += rel_y;
	}
}