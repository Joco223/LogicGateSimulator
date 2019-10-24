#include "Asset_loader.h"

Asset_loader::Asset_loader() {}

void Asset_loader::load_chips(Simple2D::Context& ctx, const std::string& chips_path, GUI_Controller& gui_controller) {
	for (const auto & entry : std::filesystem::directory_iterator(chips_path)) {
		std::string chip_name = std::filesystem::path(entry.path()).filename();
		chip_name = chip_name.substr(0, chip_name.find("."));
		Chip test_chip = Chip(ctx, 0, 0, chip_name, entry.path());
		gui_controller.add_chips_button(ctx, test_chip);
	}
}