#include"Game_Manager.hpp"

void Game_Manager::make_stage() {

	//Block

	blocks.clear();

	for (auto& block_data : block_datas) {

		int x = block_data.x;
		int y = block_data.y;
		int image_x = block_data.image_x;
		int image_y = block_data.image_y;

		String name = U"";

		for (auto& b_n : block_names) {

			if (b_n.x == image_x and b_n.y == image_y) {
				name = b_n.name;
				break;
			}
		}


		if (U"needle" == name) {
			blocks.push_back(std::make_unique<Needle>(name, x, y));
		}
		else if (U"slip" == name) {
			blocks.push_back(std::make_unique<Slip_Block>(name, x, y));
		}
		else if (U"bound" == name) {
			blocks.push_back(std::make_unique<Bound_Block>(name, x, y));
		}
		else if (U"break" == name) {
			blocks.push_back(std::make_unique<Break_Block>(name, x, y));
		}
		else {

			blocks.push_back(std::make_unique<Block>(name, x, y, image_x, image_y));

		}

		//blocks.push_back(std::make_unique<One_Way_Floor>(center_x + 300, y - 200));
		//blocks.push_back(std::make_unique<Move_Floor>(center_x - 500, y));
		//blocks.push_back(std::make_unique<Move_Floor>(center_x - 500, y - 600));

		//block_manager.plus_block(x, y, name);
	}

	//Enemy

	enemys.clear();





	for (auto& enemy_data : enemy_datas) {

		int x = enemy_data.x;
		int y = enemy_data.y;
		String name = enemy_data.name;

		make_enemy(name, x, y);

	}


	//Tile

	tiles.clear();

	for (auto& tile_data : tile_datas) {

		int x = tile_data.x;
		int y = tile_data.y;
		int image_x = tile_data.image_x;
		int image_y = tile_data.image_y;

		tiles.push_back(Tile(x, y, image_x, image_y));
	}


	//Deco

	decos.clear();

	for (auto& deco_data : deco_datas) {

		int x = deco_data.x;
		int y = deco_data.y;
		int image_x = deco_data.image_x;
		int image_y = deco_data.image_y;


		decos.push_back(Deco(x, y, image_x, image_y));
	}

	//Event

	events.clear();

	for (auto& event_data : event_datas) {

		int x = event_data.x;
		int y = event_data.y;
		int id = event_data.ID;
		int image_x = event_data.image_x;
		int image_y = event_data.image_y;

		events.push_back(Event(x, y, id, image_x, image_y));
	}

	int x_max = 0;
	int y_max = 0;

	for (auto& block : blocks) {

		int v_x = block->get_rect().x + 72;
		if (x_max < v_x) {
			x_max = v_x;
		}

		int v_y = block->get_rect().y + 72;
		if (y_max < v_y) {
			y_max = v_y;
		}

	}

	for (auto& tile : tiles) {

		int v_x = tile.get_rect().x + 72;
		if (x_max < v_x) {
			x_max = v_x;
		}

		int v_y = tile.get_rect().y + 72;
		if (y_max < v_y) {
			y_max = v_y;
		}

	}

	area_wide = x_max;
	area_height = y_max;

	bool no_data = true;



	for (auto& data : area_datas) {

		if (area == data.name) {
			area_wide = data.wide;
			area_height = data.height;

			no_data = false;


			break;
		}
	}

	if (true == no_data) {
		throw Error{ U"you_are_lost_in_null_area!!" };
	}

	items.clear();
	my_effects.clear();

	//エリアが画面より狭い場合、背景を黒にする。
	bool back_black = false;

	if (area_wide < 1920) {
		back_black = true;
	}

	if (false == back_black) {
		make_stage_back();
	}
	else {
		world_blue = false;
		back_base_name = U"black";
	}


	make_stage_plus();
}

void Game_Manager::make_stage_back() {

	//所属しているzoneを探す
	String zone = U"";

	for (auto& data : area_datas) {

		if (data.name == area) {
			zone = data.belong_zone;
			break;
		}
	}

	//通常の廊下
	back_base_name = U"normal";
	world_blue = false;


	bool is_zone = false;

	
	if (U"world_A" == zone) {
		is_zone = true;
	}
	else if (U"world_B" == zone) {
		is_zone = true;
	}
	else if (U"world_C" == zone) {
		is_zone = true;
	}
	else if (U"world_D" == zone) {
		is_zone = true;
	}
	else if (U"world_E" == zone) {
		is_zone = true;
	}
	else if (U"world_F" == zone) {
		is_zone = true;
	}
	else if (U"world_G" == zone) {
		is_zone = true;
	}
	else if (U"world_H" == zone) {
		is_zone = true;
	}

	if (true == is_zone) {

		back_base_name = U"world";
		world_blue = true;
	}
}

void Game_Manager::make_stage_plus() {

	special_objects.clear();

	if (U"world_A_1"==area) {

		special_objects.push_back(Special_Object(U"torii", 3, 5, U"red"));
		//special_objects.push_back(Special_Object(U"mirror", 71, 6, U"green"));

		special_objects.push_back(Special_Object(U"board_0", 13, 5, U"green"));
		special_objects.push_back(Special_Object(U"board_1", 23, 4, U"green"));
		special_objects.push_back(Special_Object(U"board_2", 40, 2, U"green"));
		special_objects.push_back(Special_Object(U"board_3", 49, 6, U"green"));

		special_objects.push_back(Special_Object(U"door", 71, 7, U"white"));



		//special_objects.push_back(Special_Object(U"board_2", 15, 8));
	}
	else if (U"world_A_2" == area) {

		

		special_objects.push_back(Special_Object(U"door", 3, 6, U"white"));


		special_objects.push_back(Special_Object(U"board_4", 11, 2, U"green"));

		special_objects.push_back(Special_Object(U"soul", 13, 7, U"green"));

		special_objects.push_back(Special_Object(U"board_5", 72, 2, U"green"));
		special_objects.push_back(Special_Object(U"board_5", 82, 2, U"green"));

		special_objects.push_back(Special_Object(U"mirror", 99, 5, U"green"));
	}
}
