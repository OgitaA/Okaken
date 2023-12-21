#include"Game_Manager.hpp"

void Game_Manager::update_menu() {

	if (0==menu_layer){

		update_menu_main();
	}
	else if(1 == menu_layer) {

		if (U"charm" == menu_scene) {
			update_menu_charm();
		}
		else if (U"item" == menu_scene) {
			update_menu_item();
		}
		else if (U"map" == menu_scene) {
			update_menu_map();
		}

	}
	
}

void Game_Manager::draw_menu()const {

	TextureAsset(U"menu_back").draw(0, 0);

	

	if (0 == menu_layer) {
		draw_menu_main();

		draw_UI();

		


	}
	else if (1 == menu_layer) {

		if (U"charm" == menu_scene) {
			draw_menu_charm();
		}
		else if (U"item" == menu_scene) {
			draw_menu_item();
		}
		else if (U"map" == menu_scene) {
			draw_menu_map();
		}

	}
}

void Game_Manager::update_menu_main() {

	menu_cur_main.update();

	int x = menu_cur_main.get_x();
	int y = menu_cur_main.get_y();

	if (KeyZ.down()) {

		if (0 == x) {

			if (0 == y) {
				go_menu_scene(1,U"charm");
			}
			else if (1 == y) {
				
			}
		}
		else if (1 == x) {

			if (0 == y) {
				go_menu_scene(1, U"item");
			}
			else if (1 == y) {

			}
		}
		else if (2 == x) {

			if (0 == y) {
				go_menu_scene(1, U"map");
			}
			else if (1 == y) {

			}
		}

	}

	//メニュー画面でる
	else if (KeyX.down()) {
		change_scene(U"game");
	}
}

void Game_Manager::draw_menu_main()const {

	TextureAsset(U"sign_menu").draw(550 + 2, 20);

	int stone_edge = 1920 - 905 - 50;

	TextureAsset(U"menu_stone").draw(stone_edge, 20);

	int maga_count = 0;

	for (auto& maga : status.get_have_magas()) {

		String image_name = U"maga_" + maga.name;
		TextureAsset(image_name).scaled(0.5).draw(stone_edge + 39 + (maga_count * (115)), 26);

		maga_count++;
	}

	int hollow_amount = 7 - maga_count;
	int hollow_count = 0;

	for (int i = 0; i < hollow_amount; i++) {

		TextureAsset(U"maga_hollow").scaled(0.5).draw(stone_edge + 39 + ((maga_count + hollow_count) * (115)), 26, ColorF(1, 0.5));

		hollow_count++;
	}





	int image_wide = 500;
	int blank = 100;
	int edge = (1920 - (image_wide * 3 + blank * 2)) / 2;

	//BIG_CUR
	{
		int x = menu_cur_main.get_x();
		TextureAsset(U"menu_big_cur").draw(edge + (image_wide + blank) * x - 10, 280 - 10);
	}

	for (int x = 0; x < 3; x++) {

		String image;

		if (0 == x) {
			image = U"menu_charm";
		}
		else if (1 == x) {
			image = U"menu_item";
		}
		else if (2 == x) {
			image = U"menu_map";
		}

		TextureAsset(image).draw(edge + (image_wide + blank) * x, 280);
	}



	int cur_x = menu_cur_main.get_x();

	const float fade = 0.2;

	if (0 == cur_x) {
		TextureAsset(U"menu_black").draw(edge + (image_wide + blank) * (1), 280, ColorF(1,fade));
		TextureAsset(U"menu_black").draw(edge + (image_wide + blank) * (2), 280, ColorF(1, fade));
	}
	else if (1 == cur_x) {
		TextureAsset(U"menu_black").draw(edge + (image_wide + blank) * (0), 280, ColorF(1, fade));
		TextureAsset(U"menu_black").draw(edge + (image_wide + blank) * (2), 280,ColorF(1,fade));
	}
	else if (2 == cur_x) {
		TextureAsset(U"menu_black").draw(edge + (image_wide + blank) * (0), 280,ColorF(1,fade));
		TextureAsset(U"menu_black").draw(edge + (image_wide + blank) * (1), 280, ColorF(1, fade));
	}

}



void Game_Manager::update_menu_charm() {

	float d_time = Delta_Time;

	if (0 < menu_charm_cur_x_interval) {
		menu_charm_cur_x_interval -= d_time;
	}

	if (0 < menu_charm_cur_y_interval) {
		menu_charm_cur_y_interval -= d_time;
	}

	if (not KeyLeft.pressed() and not KeyRight.pressed()) {
		menu_charm_cur_x_interval = 0;
	}

	if (not KeyUp.pressed() and not KeyDown.pressed()) {
		menu_charm_cur_y_interval = 0;
	}

	float wait_time = 0.2;

	bool naname_guard = false;

	if (KeyLeft.pressed() or KeyRight.pressed()) {
		if (KeyUp.pressed() or KeyDown.pressed()) {
			naname_guard = true;
		}
	}

	if (false == naname_guard) {

		if (menu_charm_cur_x_interval <= 0) {

			bool key = false;

			if (KeyLeft.pressed()) {
				menu_charm_cur_x--;
				key = true;
			}
			else if (KeyRight.pressed()) {
				menu_charm_cur_x++;
				key = true;
			}

			if (true == key) {
				menu_charm_cur_x_interval = wait_time;
			}
		}

		if (menu_charm_cur_y_interval <= 0) {

			bool key = false;

			if (KeyUp.pressed()) {
				menu_charm_cur_y--;
				key = true;
			}
			else if (KeyDown.pressed()) {
				menu_charm_cur_y++;
				key = true;
			}

			if (true == key) {
				menu_charm_cur_y_interval = wait_time;
			}
		}

	}


	//切り替えし処理

	/*

	if (true == turn_x) {

		if (x < 0) {
			x = x_max;
		}

		if (x_max < x) {
			x = 0;
		}
	}

	if (true == turn_y) {

		if (y < 0) {
			y = y_max;
		}

		if (y_max < y) {
			y = 0;
		}
	}
    */

	//共通
	{
		if (menu_charm_cur_x < 0) {
			menu_charm_cur_x = 0;
		}
	}

	

	if (U"up" == charm_up_down) {

		if (menu_charm_cur_y < 0) {
			menu_charm_cur_y = 0;
		}

		if (1 <= menu_charm_cur_y) {
			charm_up_down = U"down";

			menu_charm_cur_x = 0;
			menu_charm_cur_y = 0;
		}

		
		if (3 <= menu_charm_cur_x) {
			menu_charm_cur_x = 2;
		}
	}
	else if (U"down" == charm_up_down) {

		if (3<=menu_charm_cur_y ) {
			menu_charm_cur_y = 2;
		}

		if (menu_charm_cur_y < 0) {
			charm_up_down = U"up";

			menu_charm_cur_x = 0;
			menu_charm_cur_y = 0;
		}

		if (8 <= menu_charm_cur_x) {
			menu_charm_cur_x = 7;
		}
	}

	//選択されているチャーム

	menu_charm_select = U"";

	if (U"up" == charm_up_down) {

		for (auto& charm : status.get_equip_charms()) {

			if (charm.x == menu_charm_cur_x) {
				menu_charm_select = charm.name;
				break;
			}
		}

		
	}
	else if (U"down" == charm_up_down) {



		for (auto& charm : status.get_have_charms()) {

			if (charm.x == menu_charm_cur_x and charm.y == menu_charm_cur_y) {
				menu_charm_select = charm.name;
			}
		}

		
	}

	if (KeyX.down()) {
		go_menu_scene(0, U"");
	}
	
}


void Game_Manager::draw_menu_charm()const {

	TextureAsset(U"sign_charm").draw(150, 20);

	int edge_x = 150;
	int edge_y = 450;

	int charm_w = 172;
	int charm_w_blank = 20;

	int charm_h = 244;
	int charm_h_blank = 20;


	//Have

	int charm_have_w = charm_w * 0.7;
	int charm_have_h = charm_h * 0.7;

	int charm_have_w_blank = 10;
	int charm_have_h_blank = 30;



	//カーソル描画
	{
		int display_x = 0;
		int display_y = 0;
		if (U"up" == charm_up_down) {

			display_x = edge_x + 150 * menu_charm_cur_x + 10;
			display_y = 200;

			TextureAsset(U"menu_charm_cur").scaled(0.9).draw(display_x, display_y);
		}
		else if (U"down" == charm_up_down) {

			display_x = edge_x + (menu_charm_cur_x * charm_have_w) + (menu_charm_cur_x * charm_have_w_blank);
			display_y = edge_y + (menu_charm_cur_y * charm_have_h) + (menu_charm_cur_y * charm_have_h_blank)+20;

			TextureAsset(U"menu_charm_cur").scaled(0.7).draw(display_x, display_y);
		}

		

	}



	//Equip_Charm

	Array<Equip_Charm>equip_charm = status.get_equip_charms();

	for (auto& charm : equip_charm) {

		String image_name = U"charm_" + charm.name;
		int display_x = edge_x + 150 * charm.x + 10;
		int display_y = 200;
		TextureAsset(image_name).scaled(0.9).draw(display_x, display_y);
	}

	//Have_Charm

	Array<Have_Charm> have_charms = status.get_have_charms();

	for (auto& charm : have_charms) {


		String image_name = U"charm_" + charm.name;
		int x = charm.x;
		int y = charm.y;

		int blank_x = x;
		int blank_y = y;
	

	


		int display_x = edge_x + (x * charm_have_w) + (blank_x * charm_have_w_blank);
		int display_y = edge_y + (y * charm_have_h) + (blank_y*charm_have_h_blank)+20;

		//Print << U"x::" << display_x;
		//Print << U"y::" << display_y;

		TextureAsset(image_name).scaled(0.7).draw(display_x, display_y);

		
	}

	//説明用・大表示

	int big_center_x = 1550;

	for (auto& text : text_charms) {

		if (text.get_name() == menu_charm_select) {

			FontAsset(U"BIZ_60")(menu_charm_select).drawAt(big_center_x, 150);

			String big_image_name = U"charm_" + menu_charm_select;
			TextureAsset(big_image_name).drawAt(big_center_x, 350);

			String my_text = text.get_text();
			indent_drawer.draw(FontAsset(U"BIZ_30"), my_text, 400, big_center_x - 400 / 2, 520, Palette::White, 0);


		}
	}



	/*

	//テスト用
	{
		int display_x = 0;
		int display_y = 0;
		if (U"up" == up_down) {

			display_x = edge_x + 150 * menu_charm_cur_x;
			display_y = 200;
		}
		else if (U"down" == up_down) {

			display_x = edge_x + (menu_charm_cur_x * charm_w) + (menu_charm_cur_x * charm_w_blank);
			display_y = edge_y + (menu_charm_cur_y * charm_h) + (menu_charm_cur_y * charm_h_blank);
		}

		TextureAsset(U"menu_cur").draw(display_x, display_y);
		//TextureAsset(U"charm_money_up").draw(display_x, display_y);
	}

	*/
}

void Game_Manager::update_menu_item() {

	float d_time = Delta_Time;

	if (0 < menu_item_cur_x_interval) {
		menu_item_cur_x_interval -= d_time;
	}

	if (0 < menu_item_cur_y_interval) {
		menu_item_cur_y_interval -= d_time;
	}

	if (not KeyLeft.pressed() and not KeyRight.pressed()) {
		menu_item_cur_x_interval = 0;
	}

	if (not KeyUp.pressed() and not KeyDown.pressed()) {
		menu_item_cur_y_interval = 0;
	}

	float wait_time = 0.2;

	bool naname_guard = false;

	if (KeyLeft.pressed() or KeyRight.pressed()) {
		if (KeyUp.pressed() or KeyDown.pressed()) {
			naname_guard = true;
		}
	}

	if (false == naname_guard) {

		if (menu_item_cur_x_interval <= 0) {

			bool key = false;

			if (KeyLeft.pressed()) {
				menu_item_cur_x--;
				key = true;
			}
			else if (KeyRight.pressed()) {
				menu_item_cur_x++;
				key = true;
			}

			if (true == key) {
				menu_item_cur_x_interval = wait_time;
			}
		}

		if (menu_item_cur_y_interval <= 0) {

			bool key = false;

			if (KeyUp.pressed()) {
				menu_item_cur_y--;
				key = true;
			}
			else if (KeyDown.pressed()) {
				menu_item_cur_y++;
				key = true;
			}

			if (true == key) {
				menu_item_cur_y_interval = wait_time;
			}
		}

	}


	//切り替えし処理

	/*

	if (true == turn_x) {

		if (x < 0) {
			x = x_max;
		}

		if (x_max < x) {
			x = 0;
		}
	}

	if (true == turn_y) {

		if (y < 0) {
			y = y_max;
		}

		if (y_max < y) {
			y = 0;
		}
	}
	*/

	//共通
	{
		if (menu_item_cur_x < 0) {
			menu_item_cur_x = 0;
		}
	}

	/*

	if (U"up" == item_up_down) {

		if (menu_item_cur_y < 0) {
			menu_item_cur_y = 0;
		}

		if (1 <= menu_item_cur_y) {
			item_up_down = U"middle";

			menu_item_cur_x = 0;
			menu_item_cur_y = 0;
		}


		if (8 <= menu_item_cur_x) {
			menu_item_cur_x = 7;
		}
	}
	else if (U"middle" == item_up_down) {

		if (menu_item_cur_y < 0) {
			item_up_down = U"up";

			menu_item_cur_x = 0;
			menu_item_cur_y = 0;
		}
		else if (1 <= menu_item_cur_y) {
			item_up_down = U"down";

			menu_item_cur_x = 0;
			menu_item_cur_y = 0;
		}


		if (8 <= menu_item_cur_x) {
			menu_item_cur_x = 7;
		}

	}
	else if (U"down" == item_up_down) {

		if (3 <= menu_item_cur_y) {
			menu_item_cur_y = 2;
		}

		if (menu_item_cur_y < 0) {
			item_up_down = U"middle";

			menu_item_cur_x = 0;
			menu_item_cur_y = 0;
		}

		if (8 <= menu_item_cur_x) {
			menu_item_cur_x = 7;
		}
	}*/

	//Item用
	if (8 <= menu_item_cur_x) {
		menu_item_cur_x = 7;
	}

	if (4 <= menu_item_cur_y) {
		menu_item_cur_y = 3;
	}

	
	//選択されているチャーム

	menu_maga_select = U"";
	menu_weapon_select = U"";
	menu_item_select = U"";

	/*

	if (U"up" == item_up_down) {

		for (auto& maga : status.get_have_magas()) {

			if (maga.x == menu_item_cur_x) {
				menu_maga_select = maga.name;
				break;
			}
		}


	}
	else if (U"middle" == item_up_down) {

		for (auto& weapon : status.get_have_weapons()) {

			if (weapon.x == menu_item_cur_x) {
				menu_weapon_select = weapon.name;
				break;
			}

		}



	}
	else if (U"down" == item_up_down) {

		for (auto& item : status.get_have_items()) {

			if (item.x == menu_item_cur_x and item.y==menu_item_cur_y) {
				menu_item_select = item.name;
				break;
			}

		}


	}*/

	//Item
	for (auto& item : status.get_have_items()) {

		if (item.x == menu_item_cur_x and item.y == menu_item_cur_y) {
			menu_item_select = item.name;
			break;
		}

	}

	if (KeyX.down()) {
		go_menu_scene(0, U"");
	}


	
}

void Game_Manager::draw_menu_item()const {

	TextureAsset(U"sign_item").draw(150, 20);

	int edge_x = 150;
	int edge_y = 250;

	int charm_w = 250;
	int charm_w_blank = 20;

	int charm_h = 250;
	int charm_h_blank = 20;


	//Have

	int charm_have_w = charm_w * 0.7;
	int charm_have_h = charm_h * 0.7;

	int charm_have_w_blank = 30;
	int charm_have_h_blank = 30;

	/*

	//Maga

	int maga_count = 0;

	for (auto& maga : status.get_have_magas()) {

		String image_name = U"maga_" + maga.name;
		TextureAsset(image_name).scaled(0.7).draw(edge_x + (maga_count * 160), edge_y);
		maga_count++;
	}

    */

	/*

	int weapon_count = 0;

	//Weapon
	for (auto& weapon : status.get_have_weapons()) {

		String image_name = U"weapon_" + weapon.name;
		TextureAsset(image_name).scaled(0.7).draw(edge_x + (weapon_count * 160), edge_y + 300);
		weapon_count++;
	}

	 */

	//Item
	for (auto& item : status.get_have_items()) {


		String image_name = U"item_" + item.name;
		int x = item.x;
		int y = item.y;

		int blank_x = x;
		int blank_y = y;





		int display_x = edge_x + (x * charm_have_w) + (blank_x * charm_have_w_blank);
		int display_y = edge_y + (y * charm_have_h) + (blank_y * charm_have_h_blank);

		//Print << U"x::" << display_x;
		//Print << U"y::" << display_y;

		TextureAsset(image_name).scaled(0.7).draw(display_x, display_y);


	}

	//Weapon
	for (auto& item : status.get_have_weapons()) {


		String image_name = U"weapon_" + item.name;
		int x = item.x;
		int y = item.y;

		int blank_x = x;
		int blank_y = y;





		int display_x = edge_x + (x * charm_have_w) + (blank_x * charm_have_w_blank);
		int display_y = edge_y + (y * charm_have_h) + (blank_y * charm_have_h_blank);

		//Print << U"x::" << display_x;
		//Print << U"y::" << display_y;

		TextureAsset(image_name).scaled(0.7).draw(display_x, display_y);


	}

	//Print << U"=================================";

	//説明用・大表示

	int big_center_x = 1550;

	String display_name = U"";
	String big_image_name = U"";
	String big_image_text = U"";


	/*

	if (U"up" == item_up_down) {

		display_name = menu_maga_select;
		big_image_name = U"maga_" + menu_maga_select;

		for (auto& text : text_magas) {

			if (text.get_name()==menu_maga_select) {
				big_image_text = text.get_text();
			}
		}
	}
	else if (U"middle"==item_up_down) {

		display_name = menu_weapon_select;
		big_image_name = U"weapon_" + menu_weapon_select;

		for (auto& text : text_weapons) {

			if (text.get_name() == menu_weapon_select) {
				big_image_text = text.get_text();
			}
		}
	}
	else if (U"down" == item_up_down) {

		display_name = menu_item_select;
		big_image_name = U"item_" + menu_item_select;

		for (auto& text : text_items) {

			if (text.get_name() == menu_item_select) {
				big_image_text = text.get_text();
			}
		}
	}*/


	display_name = menu_item_select;
	big_image_name = U"item_" + menu_item_select;

	for (auto& text : text_items) {

		if (text.get_name() == menu_item_select) {
			big_image_text = text.get_text();
		}
	}


	if (display_name != U"" and big_image_name != U"" and big_image_text != U"") {

		FontAsset(U"BIZ_60")(display_name).drawAt(big_center_x, 150);
		TextureAsset(big_image_name).drawAt(big_center_x, 350);
		indent_drawer.draw(FontAsset(U"BIZ_30"), big_image_text, 400, big_center_x - 400 / 2, 520, Palette::White, 0);

	}

	
}

void Game_Manager::update_menu_map() {

	if (0 == menu_map_scene) {

	}
	else if (1 == menu_map_scene) {


	}

	if (KeyX.down()) {
		go_menu_scene(0, U"");
	}
}

void Game_Manager::draw_menu_map()const {

	if (0 == menu_map_scene) {
		TextureAsset(U"map_all").draw(0,0);
	}
	else if (1 == menu_map_scene) {

	}
}


