#include"Game_Manager.hpp"

void Game_Manager::update_event_state() {

	/*
	if (KeyU.down()) {
		event_super.set_var(U"display_5", 1);
	}*/

	for (auto& event : events) {

		int ID = event.get_ID();

		if (3==ID) {

			if (event_super.get_var(U"display_5") == 1) {

				event.set_image_x(1);
				event.set_image_y(0);
			}
		}
		else if (100 == ID) {

			if (event_super.get_var(U"got_stick") == 1) {

				event.set_image_x(0);
				event.set_image_y(0);
			}
		}

	}
}
