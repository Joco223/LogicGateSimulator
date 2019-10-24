#pragma once

#include "GUI_Controller.h"
#include "Chip.h"

#include "Simple2D/Simple2D.h"
#include "Simple2D/Simple2D_Sprite.h"
#include "Simple2D/Simple2D_GUI.h"

#include <vector>
#include <string>
#include <filesystem>
#include <algorithm>

class Asset_loader {
private:
	std::vector<Chip> chips;
public:
	Asset_loader();

	void load_chips(Simple2D::Context& ctx, const std::string& chips_path, GUI_Controller& gui_controller);
};