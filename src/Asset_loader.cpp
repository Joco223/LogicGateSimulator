#include "Asset_loader.h"

Asset_loader::Asset_loader() {}

void Asset_loader::load_chips(Simple2D::Context& ctx, const std::string& chips_path, GUI_Controller& gui_controller) {
	for (const auto & entry : std::filesystem::directory_iterator(chips_path)) {
		std::string chip_name = std::filesystem::path(entry.path()).filename();
		chip_name = chip_name.substr(0, chip_name.find("."));
		gui_controller.add_chips_button(ctx, 0, 0, chip_name, entry.path());
	}
}

void Asset_loader::load_logic_gates(Simple2D::Context& ctx, const std::string& logic_gates_path, GUI_Controller& gui_controller) {
	for (const auto & entry : std::filesystem::directory_iterator(logic_gates_path)) {
		std::string chip_name = std::filesystem::path(entry.path()).filename();
		chip_name = chip_name.substr(0, chip_name.find("."));
		gui_controller.add_logic_gates_button(ctx, 0, 0, chip_name, entry.path());
	}
}