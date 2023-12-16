#include"Game_Manager.hpp"

void Game_Manager::update_edit() {

	if (U"edit_base" == edit_scene) {

		camera_edit.update();


		//カーソル位置
		edit_cur_x = int((Cursor::Pos().x + scroll_edit.x) / 72);
		edit_cur_y = int((Cursor::Pos().y + scroll_edit.y) / 72);

		//GUI
		click_edit = false;

		if (true == click_edit_over_scene) {

			if (!MouseL.pressed()) {
				click_edit_over_scene = false;
			}
			else {
				click_edit = true;
			}
		}

		


		//画面スクロール用スライダー
		use_slider_edit();

		//セレクトボックス
		use_select_box_edit();

		//簡易ボタン
		use_my_button();



		//GUIに触れていないなら
		if (false == click_edit) {

			switch (edit_type)
			{
			case Game_Manager::E_Block:
				edit_block();
				break;
			case Game_Manager::E_Enemy:
				edit_enemy();
				break;
			case Game_Manager::E_Tile:
				edit_tile();
				break;
			case Game_Manager::E_Deco:
				edit_deco();
				break;
			case Game_Manager::E_Event:
				edit_event();
				break;
			case Game_Manager::E_player:
				edit_player();
				break;
			default:
				break;
			}

		}

		//リセット
		if (KeyControl.pressed() and KeyC.pressed()) {
			tile_datas.clear();
			block_datas.clear();
			enemy_datas.clear();
			deco_datas.clear();
			event_datas.clear();
		}

		if (KeyControl.pressed() and KeyRight.down()) {

			move_area_data(1,0);
		}
		else if (KeyControl.pressed() and KeyDown.down()) {

			move_area_data(0,1);
		}
		else if (KeyControl.pressed() and KeyLeft.down()) {

			move_area_data(-1, 0);
		}
		else if (KeyControl.pressed() and KeyUp.down()) {

			move_area_data(0, -1);
		}

		camera_edit.jumpTo({ scroll_edit.x + 1920 / 2 ,scroll_edit.y + 1080 / 2 }, 1.0);
		//camera_edit.jumpTo({ scroll_edit.x,scroll_edit.y }, 1.0);

	}
	else if (U"edit_setting_event" == edit_scene) {

		bool back = false;

		back = detail_setter.update();

		bool empty = detail_setter.get_v_check_empty();

		//戻る
		if (true == back) {

			edit_scene = U"edit_base";
			click_edit_over_scene = true;


			for (auto& event_data : event_datas) {

				if (true == event_data.mark) {

					if (false == empty) {
						event_data.ID = detail_setter.get_v();
					}
					else if (true == empty) {

					}

					event_data.mark = false;
					break;
				}
			}

		}

	}
	else if (U"select_area" == edit_scene) {

		bool back = false;

		back = area_selecter.update();

		if (true==back) {

			edit_scene = U"edit_base";
			click_edit_over_scene = true;

			area = area_selecter.go_area();

			make_area_edit();
		}

	}
	else if (U"select_tool" == edit_scene) {

		bool back = false;

		back = tool_selecter.update();

		if (true == back) {

			edit_scene = U"edit_base";
			click_edit_over_scene = true;

			tool_edit = tool_selecter.get_tool();

		}
	}

	//セーブ
	if (KeyS.down()) {
		//optimize_edit();
		save_area_data();
		Print << U"saved";
	}

	//ロード
	if (KeyL.down()) {
		load_area_data();
		Print << U"loaded";
	}

}


void Game_Manager::draw_edit()const {

	{
		auto t = camera_edit.createTransformer();

		for (auto& tile_data : tile_datas) {
			tile_data.draw();
		}

		for (auto& block_data : block_datas) {
			block_data.draw();
		}

		for (auto& enemy_data : enemy_datas) {
			enemy_data.draw();
		}

		for (auto& deco_data : deco_datas) {
			deco_data.draw();
		}

		for (auto& event_data : event_datas) {
			event_data.draw();

			//情報表示
			int ID=event_data.ID;
			String name = U"";
			int x = event_data.x*72 + 74 / 2;
			int y = event_data.y*72 - 30;


			for (auto& event_list : event_lists) {

				if (event_list.ID == ID) {
					name=event_list.name;
				}
			}

			FontAsset(U"BIZ_30")(name).drawAt(x, y);
		}


		{
			Rect p_rect(player_data.x, player_data.y, 72, 72);
			p_rect.draw(Palette::Red);
		}

	}

	{
	

			for (auto& my_slider : my_sliders) {
				my_slider.draw();
			}


			for (auto& select_box : select_boxs) {
				select_box.draw();
			}

			for (auto& my_button : my_buttons) {
				my_button.draw();
			}

		

		{
			String display = U"x:" + Format(scroll_edit.x) + U"  y:" + Format(scroll_edit.y);
			FontAsset(U"BIZ_30")(display).draw(300, 10, Palette::White);
		}

		{

			int x = (scroll_edit.x + Cursor::Pos().x) / 72;
			int y = (scroll_edit.y + Cursor::Pos().y) / 72;
			String display = U"x:" + Format(x) + U"  y:" + Format(y);
			FontAsset(U"BIZ_30")(display).draw(300 + 300, 10, Palette::White);
		}
	}
	

	if (U"edit_setting_event" == edit_scene) {

		Rect black_rect(0,0,1920,1080);
		black_rect.draw(ColorF(0, 0, 0, 0.8));

		detail_setter.draw();

		int select_number = 99999999;

		if (detail_setter.get_v_check_empty() == false) {
			select_number = detail_setter.get_v();
		}

		{
			int x = 200;
			int y = 300;
			int count = 0;

			for (auto& ev_list : event_lists) {
	
				String text = Format(ev_list.ID) + U":" + Format(ev_list.name);

				if (select_number != ev_list.ID) {

					FontAsset(U"BIZ_30")(text).draw(x, y + (count * 50));
				}
				else {
					FontAsset(U"BIZ_30")(text).draw(x, y + (count * 50), Palette::Yellow);
				}

				count++;
			}
		}
	}
	else if (U"select_area" == edit_scene) {

		Rect black_rect(0, 0, 1920, 1080);
		black_rect.draw(ColorF(0, 0, 0, 0.8));

		area_selecter.draw();
	}
	else if (U"select_tool" == edit_scene) {

		tool_selecter.draw();
	}


	//共通情報
	{

		FontAsset(U"BIZ_30")(area).draw(15, 10, Palette::White);

		

	}
}

void Game_Manager::edit_block() {
	
	switch (edit_mode)
	{
	case Game_Manager::E_Pen:
		plus_block();
		erase_block();
		break;
	case Game_Manager::E_Eraser:
		break;
	default:
		break;
	}
}

void Game_Manager::edit_enemy() {

	switch (edit_mode)
	{
	case Game_Manager::E_Pen:
		plus_enemy();
		erase_enemy();
		break;
	case Game_Manager::E_Eraser:
		break;
	default:
		break;
	}
}

void Game_Manager::edit_tile() {

	switch (edit_mode)
	{
	case Game_Manager::E_Pen:
		plus_tile();
		erase_tile();
		break;
	case Game_Manager::E_Eraser:
		break;
	default:
		break;
	}
}

void Game_Manager::edit_deco() {

	switch (edit_mode)
	{
	case Game_Manager::E_Pen:
		plus_deco();
		erase_deco();
		break;
	case Game_Manager::E_Eraser:
		break;
	default:
		break;
	}
}

void Game_Manager::edit_event() {

	switch (edit_mode)
	{
	case Game_Manager::E_Pen:
		plus_event();
		erase_event();
		break;
	case Game_Manager::E_Eraser:
		break;
	default:
		break;
	}
}

void Game_Manager::edit_player() {

	if (MouseL.down()) {
		player_data.x = edit_cur_x * 72;
		player_data.y = edit_cur_y * 72;
	}
}

void Game_Manager::plus_block() {

	if (U"pen" == tool_edit) {

		if (MouseL.pressed()) {//ペン

			//描画の座標
			int write_x = edit_cur_x;


			//tileの一枚絵の座標
			int make_x = block_image_x;


			for (int w = 0; w < block_image_w; w++) {

				//描画の座標
				int write_y = edit_cur_y;

				//tileの一枚絵の座標
				int make_y = block_image_y;

				for (int h = 0; h < block_image_h; h++) {

					bool exist = false;

					for (auto& block_data : block_datas) {

						int x = block_data.x;
						int y = block_data.y;

						if (write_x == x and write_y == y) {

							//すでにある
							exist = true;

							//deco_data.name = deco_name_edit;

							block_data.image_x = make_x;
							block_data.image_y = make_y;
						}
					}

					if (false == exist) {//まだない

						//deco_datas.push_back(Deco_Data(edit_cur_x, edit_cur_y, deco_name_edit));
						block_datas.push_back(Block_Data(write_x, write_y, make_x, make_y));

					}

					make_y++;
					write_y++;
				}

				make_x++;
				write_x++;
			}
		}

		
	}
	else if (U"bucket" == tool_edit) {

		if (0 == bucket_edit_scene) {

			if (MouseL.down()) {

				bucket_edit_start_x = edit_cur_x;
				bucket_edit_start_y = edit_cur_y;
				bucket_edit_scene++;
			}
		}
		else if (1 == bucket_edit_scene) {

			if (MouseL.up()) {

				int start_x = bucket_edit_start_x;
				int start_y = bucket_edit_start_y;
				int end_x = edit_cur_x;
				int end_y = edit_cur_y;

				tile_datas.remove_if([&](Tile_Data(tile_data)) {

					if (start_x <= tile_data.x and tile_data.x <= end_x) {
						if (start_y <= tile_data.y and tile_data.y <= end_y) {
							return true;
						}
					}

				return false;

					});

				int w = abs(end_x - start_x) + 1;
				int h = abs(end_y - start_y) + 1;

				for (int x = 0; x < w; x++) {
					for (int y = 0; y < h; y++) {

						//	tile_datas.push_back(Tile_Data(start_x + x, start_y + y, tile_name_edit));
					}
				}

				bucket_edit_scene = 0;


			}
		}

	}
}



void Game_Manager::erase_block() {

	

	if (MouseR.pressed()) {//消しゴム

		block_datas.remove_if([&](Block_Data block_data) {

			if (edit_cur_x == block_data.x and edit_cur_y == block_data.y) {
				return true;
			}



		    return false;


		});

	}
}

void Game_Manager::plus_enemy() {

	
	if (MouseL.pressed()) {//ペン

		bool exist = false;

		for (auto& enemy_data : enemy_datas) {

			int x = enemy_data.x;
			int y = enemy_data.y;

			if (edit_cur_x == x and edit_cur_y == y) {

				//すでにある
				exist = true;

				enemy_data.name = enemy_name_edit;
			}
		}

		if (false == exist) {//まだない

			enemy_datas.push_back(Enemy_Data(edit_cur_x, edit_cur_y, enemy_name_edit));
		}
	}
}

void Game_Manager::erase_enemy() {

	if (MouseR.pressed()) {//消しゴム

		enemy_datas.remove_if([&](Enemy_Data enemy_data) {

			if (edit_cur_x == enemy_data.x and edit_cur_y == enemy_data.y) {
				return true;
			}



		return false;


		});

	}
}

void Game_Manager::plus_tile() {



	if (U"pen" == tool_edit) {

		if (MouseL.pressed()) {//ペン

			//描画の座標
			int write_x = edit_cur_x;


			//tileの一枚絵の座標
			int make_x = tile_image_x;


			for (int w = 0; w < tile_image_w; w++) {

				//描画の座標
				int write_y = edit_cur_y;

				//tileの一枚絵の座標
				int make_y = tile_image_y;

				for (int h = 0; h < tile_image_h; h++) {

					bool exist = false;

					for (auto& tile_data : tile_datas) {

						int x = tile_data.x;
						int y = tile_data.y;

						if (write_x == x and write_y == y) {

							//すでにある
							exist = true;

							//deco_data.name = deco_name_edit;

							tile_data.image_x = make_x;
							tile_data.image_y = make_y;
						}
					}

					if (false == exist) {//まだない

						//deco_datas.push_back(Deco_Data(edit_cur_x, edit_cur_y, deco_name_edit));
						tile_datas.push_back(Tile_Data(write_x, write_y, make_x, make_y));

					}

					make_y++;
					write_y++;
				}

				make_x++;
				write_x++;
			}
		}

		
	}
	else if (U"bucket" == tool_edit) {

		if (0 == bucket_edit_scene) {

			if (MouseL.down()) {

				bucket_edit_start_x = edit_cur_x;
				bucket_edit_start_y = edit_cur_y;
				bucket_edit_scene++;
			}
		}
		else if (1 == bucket_edit_scene) {

			if (MouseL.up()) {

				int start_x = bucket_edit_start_x;
				int start_y = bucket_edit_start_y;
				int end_x = edit_cur_x;
				int end_y = edit_cur_y;

				tile_datas.remove_if([&](Tile_Data(tile_data)) {

					if (start_x <= tile_data.x and tile_data.x <= end_x) {
						if (start_y <= tile_data.y and tile_data.y <= end_y) {
							return true;
						}
					}

				return false;

					});

				int w = abs(end_x - start_x) + 1;
				int h = abs(end_y - start_y) + 1;

				for (int x = 0; x < w; x++) {
					for (int y = 0; y < h; y++) {

					//	tile_datas.push_back(Tile_Data(start_x + x, start_y + y, tile_name_edit));
					}
				}

				bucket_edit_scene = 0;


			}
		}

	}

}

void Game_Manager::erase_tile() {

	if (MouseR.pressed()) {//消しゴム

		tile_datas.remove_if([&](Tile_Data tile_data) {

			if (edit_cur_x == tile_data.x and edit_cur_y == tile_data.y) {
				return true;
			}



		return false;


		});

	}
}

void Game_Manager::plus_deco() {

	if (MouseL.pressed()) {//ペン

		//描画の座標
		int write_x = edit_cur_x;
		

		//tileの一枚絵の座標
		int make_x = deco_image_x;
		

		for (int w = 0; w < deco_image_w; w++) {

			//描画の座標
			int write_y = edit_cur_y;

			//tileの一枚絵の座標
			int make_y = deco_image_y;

			for (int h = 0; h < deco_image_h; h++) {

				bool exist = false;

				for (auto& deco_data : deco_datas) {

					int x = deco_data.x;
					int y = deco_data.y;

					if (write_x == x and write_y == y) {

						//すでにある
						exist = true;

						//deco_data.name = deco_name_edit;

						deco_data.image_x = make_x;
						deco_data.image_y = make_y;
					}
				}

				if (false == exist) {//まだない

					//deco_datas.push_back(Deco_Data(edit_cur_x, edit_cur_y, deco_name_edit));
					deco_datas.push_back(Deco_Data(write_x, write_y, make_x, make_y));

				}

				make_y++;
				write_y++;
			}

			make_x++;
			write_x++;
		}
	}
}

void Game_Manager::erase_deco() {

	if (MouseR.pressed()) {//消しゴム

		deco_datas.remove_if([&](Deco_Data deco_data) {

			if (edit_cur_x == deco_data.x and edit_cur_y == deco_data.y) {
				return true;
			}



		return false;


		});

	}
}

void Game_Manager::plus_event() {

	if (MouseL.down()) {//ペン

		bool exist = false;

		for (auto& event_data : event_datas) {

			int x = event_data.x;
			int y = event_data.y;

			if (edit_cur_x == x and edit_cur_y == y) {

				//すでにある
				exist = true;

				//event_data.name = event_name_edit;
				edit_scene = U"edit_setting_event";

				set_detail_v = event_data.ID;

				detail_setter.set_v(set_detail_v);

				//set_detail_index = event_data.;

				event_data.mark = true;

				break;
			}
		}

		if (false == exist) {//まだない

			//event_datas.push_back(Event_Data(edit_cur_x, edit_cur_y, event_name_edit));
			event_datas.push_back(Event_Data(edit_cur_x, edit_cur_y, event_image_x, event_image_y));
		}
	}
}

void Game_Manager::erase_event() {

	if (MouseR.pressed()) {//消しゴム

		event_datas.remove_if([&](Event_Data event_data) {

			if (edit_cur_x == event_data.x and edit_cur_y == event_data.y) {
				return true;
			}



		return false;


		});

	}
}




void Game_Manager::use_slider_edit() {

	for (auto& slider : my_sliders) {

		int v = slider.update();

		if (U"X" == slider.get_type()) {
			scroll_edit.x = v;
		}
		else if (U"Y" == slider.get_type()) {
			scroll_edit.y = v;
		}

		if (true==slider.get_click()) {
			click_edit = true;
		}
	}

	
	
}

void Game_Manager::use_select_box_edit() {

	for (auto& select_box : select_boxs) {

		select_box.update();


		if (select_box.get_click()) {

			click_edit = true;
		}

		if (select_box.get_just_click()) {//操作した

			click_edit = true;

			if (U"block" == select_box.get_type()) {

				block_name_edit = select_box.get_name();
				edit_type = Edit_Type::E_Block;

				block_image_x = select_box.get_select_x();
				block_image_y = select_box.get_select_y();
				block_image_w = select_box.get_select_w();
				block_image_h = select_box.get_select_h();
			}
			else if (U"enemy" == select_box.get_type()) {

				enemy_name_edit = select_box.get_name();
				edit_type = Edit_Type::E_Enemy;
			}
			else if (U"tile" == select_box.get_type()) {

				//tile_name_edit = select_box.get_name();

				tile_image_x = select_box.get_select_x();
				tile_image_y = select_box.get_select_y();
				tile_image_w = select_box.get_select_w();
				tile_image_h = select_box.get_select_h();

				edit_type = Edit_Type::E_Tile;
			}
			else if (U"deco" == select_box.get_type()) {

				//deco_name_edit = select_box.get_name();

				deco_image_x = select_box.get_select_x();
				deco_image_y = select_box.get_select_y();
				deco_image_w = select_box.get_select_w();
				deco_image_h = select_box.get_select_h();

				edit_type = Edit_Type::E_Deco;
			}
			else if (U"event" == select_box.get_type()) {

			    event_image_x = select_box.get_select_x();
				event_image_y = select_box.get_select_y();
				event_image_w = select_box.get_select_w();
				event_image_h = select_box.get_select_h();

				//deco_name_edit = select_box.get_name();
				edit_type = Edit_Type::E_Event;
			}
		}

		
		

		{

			switch (edit_type)
			{
			case Game_Manager::E_Block:

				if (U"block" == select_box.get_type()) {
					select_box.set_select();
				}

				break;
			case Game_Manager::E_Enemy:

				if (U"enemy" == select_box.get_type()) {
					select_box.set_select();
				}

				break;
			case Game_Manager::E_Tile:

				if (U"tile" == select_box.get_type()) {
					select_box.set_select();
				}
				break;
			case Game_Manager::E_Deco:

				if (U"deco" == select_box.get_type()) {
					select_box.set_select();
				}
				break;
			case Game_Manager::E_Event:

				if (U"event" == select_box.get_type()) {
					select_box.set_select();
				}
				break;
			default:
				break;
			}

		}
	}
}

void Game_Manager::use_my_button() {

	for (auto& my_button : my_buttons) {

		my_button.update();

		if (my_button.get_click()) {

			click_edit = true;

			String name = my_button.get_name();

			if (U"save"==name) {
				//optimize_edit();
				save_area_data();
				Print << U"save";
			}
			else if (U"load" == name) {
				load_area_data();
				Print << U"load";
			}
			else if (U"area" == name) {
				edit_scene = U"select_area";
				area_selecter.set_area_first(area);
			}
			else if (U"start" == name) {
				edit_type = Edit_Type::E_player;
			}
			else if (U"tool"==name) {
				edit_scene = U"select_tool";
			}
		}

		if (my_button.get_press()) {
			click_edit = true;
		}
	}
}

void Game_Manager::optimize_edit() {



	tile_datas.remove_if([&](Tile_Data tile) {

		for (auto& block_data : block_datas) {
			int x = block_data.x;
			int y = block_data.y;
			if (x == tile.x and y == tile.y) {

				return true;
			}
		}

	    return false;

	});

	
}
