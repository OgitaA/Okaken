#include"Game_Manager.hpp"

void Game_Manager::initialize() {

	initialize_screen();
	initialize_data();
	initialize_editor();
	initialize_image();
	initialize_font();
	initialize_UI();
	initialize_event();
	initialize_music();
	initialize_shader();
	initialize_debug();
	

}

void Game_Manager::initialize_screen() {

	renderTexture = RenderTexture(1920, 1080);
}

void Game_Manager::initialize_data() {

	//Zone_Area_Data
	{
		set_zone_data(U"test_room");

		set_zone_data(U"first");
		set_zone_data(U"second");
		set_zone_data(U"third");
		set_zone_data(U"fourth");
		set_zone_data(U"fifth");
		set_zone_data(U"sixth");

		set_zone_data(U"under");

		set_area_data(U"test_room", 72 * 30, 72 * 30,U"test_room");


		set_area_data(U"first_1", 72 * 73 + 72 * 24, 1080, U"first");
		set_area_data(U"second_1", 72 * 73 + 72 * 24, 1080, U"second");
		set_area_data(U"third_1", 72 * 73 + 72 * 24, 1080, U"third");
		set_area_data(U"fourth_1", 72 * 73 + 72 * 24, 1080, U"fourth");
		set_area_data(U"fifth_1", 72 * 73 + 72 * 24, 1080, U"fifth");
		set_area_data(U"sixth_1", 72 * 73 + 72 * 24, 1080, U"sixth");


		set_area_data(U"first_toilet", 72 * 50, 1080, U"first");


		set_area_data(U"under_1", 72 * 50, 1080, U"under");
	}


	//Charm_Data
	{
		set_text_charm(U"test", U"テスト用のチャームのテキストです。");
		set_text_charm(U"金運上昇",U"金運UPのお守り。\n敵を倒したときに貰えるお金が、少し増える。");
		set_text_charm(U"安全祈願", U"安全祈願のお守り。\n受けるダメージが少し減る。");
		set_text_charm(U"諸刃の剣", U"安全祈願のお守り。\n受けるダメージが少し減る。");
		set_text_charm(U"歩行強化", U"安全祈願のお守り。\n受けるダメージが少し減る。");

	}

	//使わないデータ
	//Maga_Data
	{
		set_text_maga(U"緑の勾玉", U"緑色の勾玉。");

	}

	//使わないデータ
	//Weapon_Data
	{
		set_text_weapon(U"お祓い棒", U"邪気を払うお祓い棒");
		
	}

	//Item_Data
	{
		set_text_item(U"カギ",U"なにかのカギ");
		set_pos_item(U"カギ", 3, 1);

		set_text_item(U"おにぎり", U"");
	}

	//test
	get_item(U"カギ");




	//Area
	{
		

		area_selecter.set_zone(zone_datas);
		area_selecter.set_area(area_datas);
	}

	//Ev_List
	{
		set_ev(0, U"save_point");
		set_ev(1, U"talk");


	}

	//Shop
	{
		set_shop_goods(U"カギ",100,0,0);
		set_shop_goods(U"おにぎり", 150, 0, 1);
		set_shop_goods(U"カギ", 150, 0, 2);
		set_shop_goods(U"カギ", 150, 0, 3);
		set_shop_goods(U"カギ", 150, 0, 4);
		set_shop_goods(U"カギ", 150, 0, 5);

		set_shop_goods_text(U"カギ", U"職員室の前で拾ったぜ。\n何のカギなんだろうな？？");
		set_shop_goods_text(U"おにぎり", U"どっかの机の中に入っていたぜ。\nちょっと臭うぜ・・・");

		//商品の追加
		/*
		if (event_super.get_var(U"") == 1) {

		}*/

		//売れているものを削除
		shop_goods.remove_if([&](Shop_Goods goods) {


			for (auto& solds : status.get_shop_solds()) {
				if (solds == goods.name) {
					return true;
				}
			}

		return false;

			});

	}

}


void Game_Manager::initialize_editor() {

	//Editor

	{

		edit = true;

		scroll_edit = { 1920 / 2,1080 / 2 };

		edit_type = Edit_Type::E_Block;
		edit_mode = Edit_Mode::E_Pen;


		my_buttons.push_back(My_Button(U"save", 20, 1080 - 100 - 10, 150, 100));
		my_buttons.push_back(My_Button(U"load", 1920 - 20 - 150, 1080 - 100 - 10, 150, 100));
		my_buttons.push_back(My_Button(U"area", 20, 50, 150, 100));
		my_buttons.push_back(My_Button(U"start", 1920 - 20 - 150 - 150, 1080 - 100 - 10, 100, 100));
		my_buttons.push_back(My_Button(U"tool", 20, 50+130, 150, 100));



		block_name_edit = U"wood";
		enemy_name_edit = U"bake";
		tile_name_edit = U"gray_wall";
		deco_name_edit = U"poster";
		event_name_edit = U"save_point";


		{
			int x = 1920 / 2 - 1500 / 2;
			int adjust = 40;
			my_sliders.push_back(My_Slider(U"X", x, 1080 - 65, 1500 - adjust, 3000));
		}

		my_sliders.push_back(My_Slider(U"Y", 1920 - 65, 100, 800, 2000));


		select_boxs.push_back(Select_Box(U"block", 300, 50));
		select_boxs.push_back(Select_Box(U"enemy", 600, 50));
		select_boxs.push_back(Select_Box(U"tile", 900, 50));
		select_boxs.push_back(Select_Box(U"deco", 1200, 50));
		select_boxs.push_back(Select_Box(U"event", 1500, 50));

		for (auto& select_box : select_boxs) {

			if (U"block" == select_box.get_type()) {

				select_box.plus_data(U"wood");
				select_box.plus_data(U"carpet");
				select_box.plus_data(U"needle");
				select_box.plus_data(U"slip");
				select_box.plus_data(U"bound");
				select_box.plus_data(U"break");
				select_box.plus_data(U"cream_floor");
				select_box.plus_data(U"white_ceiling");

				select_box.plus_data(U"corridor_floor");
				select_box.plus_data(U"corridor_ceiling");

				select_box.plus_data(U"corridor_central_floor");

				select_box.plus_data(U"under_floor");



				select_box.plus_data(U"desk");

				
			}
			else if (U"enemy" == select_box.get_type()) {

				select_box.plus_data(U"bake");
				select_box.plus_data(U"kasa");
				select_box.plus_data(U"hitotume");
				select_box.plus_data(U"tyoutin");
			}
			else if (U"tile" == select_box.get_type()) {

				select_box.plus_data(U"gray_wall");
				select_box.plus_data(U"white_wall");

				select_box.plus_data(U"corridor_wall");

				select_box.plus_data(U"classroom_door");

				
			}
			else if (U"deco" == select_box.get_type()) {

				select_box.plus_data(U"poster");

				select_box.plus_data(U"classroom_door");
				select_box.plus_data(U"classroom_window");
				select_box.plus_data(U"classroom_window_plus");

				select_box.plus_data(U"toilet_boy");
				select_box.plus_data(U"toilet_girl");

				select_box.plus_data(U"stairs_up");
				select_box.plus_data(U"stairs_down");

				select_box.plus_data(U"number_1");
			}
			else if (U"event" == select_box.get_type()) {
				select_box.plus_data(U"save_point");
			}
		}

	}
}

void Game_Manager::initialize_image() {

	//Image

	//自動読み込み
	for (auto& box : select_boxs) {

		if (U"block" == box.get_type()) {

			for (auto& block : box.get_data_names()) {

				String name = block;
				String adress = U"image/block/" + name + U".png";

				String block_name = U"block_" + name;

				TextureAsset::Register(block_name, adress);
				TextureAsset::Load(block_name);
			}
		}

		if (U"tile" == box.get_type()) {

			for (auto& tile : box.get_data_names()) {

				String name = tile;
				String adress = U"image/tile/" + name + U".png";

				String tile_name = U"tile_" + name;

				TextureAsset::Register(tile_name, adress);
				TextureAsset::Load(tile_name);
			}
		}

		/*
		if (U"deco" == box.get_type()) {

			for (auto& deco : box.get_data_names()) {

				String name = deco;
				String adress = U"image/deco/" + name + U".png";

				String deco_name = U"deco_" + name;

				TextureAsset::Register(deco_name, adress);
				TextureAsset::Load(deco_name);
			}
		}*/
	}

	//Tile
	TextureAsset::Register(U"block_tile", U"image/block/tile.png");
	TextureAsset::Load(U"block_tile");

	//Tile
	TextureAsset::Register(U"tile_tile", U"image/tile/tile.png");
	TextureAsset::Load(U"tile_tile");

	//Deco
	TextureAsset::Register(U"deco_tile", U"image/deco/tile.png");
	TextureAsset::Load(U"deco_tile");

	//Deco
	TextureAsset::Register(U"event_tile", U"image/event/tile.png");
	TextureAsset::Load(U"event_tile");

	/*

	TextureAsset::Register(U"block_cream", U"image/block/cream.png");
	TextureAsset::Load(U"block_cream");


	TextureAsset::Register(U"block_wood", U"image/block/wood.png");
	TextureAsset::Load(U"block_wood");

	TextureAsset::Register(U"block_carpet", U"image/block/carpet.png");
	TextureAsset::Load(U"block_carpet");

	TextureAsset::Register(U"block_needle", U"image/block/needle.png");
	TextureAsset::Load(U"block_needle");

	TextureAsset::Register(U"block_slip", U"image/block/slip.png");
	TextureAsset::Load(U"block_slip");

	TextureAsset::Register(U"block_bound", U"image/block/bound.png");
	TextureAsset::Load(U"block_bound");
*/

   /*
   TextureAsset::Register(U"tile_gray_wall", U"image/tile/gray_wall.png");
   TextureAsset::Load(U"tile_gray_wall");
   */


	//Player
	TextureAsset::Register(U"player_wait", U"image/player/player/wait.png");
	TextureAsset::Load(U"player_wait");

	TextureAsset::Register(U"player_attack_0", U"image/player/player/attack_0.png");
	TextureAsset::Load(U"player_attack_0");

	TextureAsset::Register(U"player_attack_1", U"image/player/player/attack_1.png");
	TextureAsset::Load(U"player_attack_1");

	TextureAsset::Register(U"player_attack_2", U"image/player/player/attack_2.png");
	TextureAsset::Load(U"player_attack_2");

	TextureAsset::Register(U"player_attack_3", U"image/player/player/attack_3.png");
	TextureAsset::Load(U"player_attack_3");

	//player_under

	TextureAsset::Register(U"player_under_wait", U"image/player/player/under_wait.png");
	TextureAsset::Load(U"player_under_wait");

	TextureAsset::Register(U"player_under_jump", U"image/player/player/under_jump.png");
	TextureAsset::Load(U"player_under_jump");

	TextureAsset::Register(U"player_under_walk_1", U"image/player/player/under_walk_1.png");
	TextureAsset::Load(U"player_under_walk_1");

	TextureAsset::Register(U"player_under_walk_2", U"image/player/player/under_walk_2.png");
	TextureAsset::Load(U"player_under_walk_2");

	TextureAsset::Register(U"player_under_walk_3", U"image/player/player/under_wait.png");
	TextureAsset::Load(U"player_under_walk_3");

	TextureAsset::Register(U"player_under_walk_4", U"image/player/player/under_walk_4.png");
	TextureAsset::Load(U"player_under_walk_4");

	TextureAsset::Register(U"player_under_walk_5", U"image/player/player/under_walk_5.png");
	TextureAsset::Load(U"player_under_walk_5");


	//jump_effect

	TextureAsset::Register(U"player_jump_effect_0", U"image/player/jump/0.png");
	TextureAsset::Load(U"player_jump_effect_0");

	TextureAsset::Register(U"player_jump_effect_1", U"image/player/jump/1.png");
	TextureAsset::Load(U"player_jump_effect_1");

	TextureAsset::Register(U"player_jump_effect_2", U"image/player/jump/2.png");
	TextureAsset::Load(U"player_jump_effect_2");

	TextureAsset::Register(U"player_jump_effect_3", U"image/player/jump/3.png");
	TextureAsset::Load(U"player_jump_effect_3");

	TextureAsset::Register(U"player_jump_effect_4", U"image/player/jump/4.png");
	TextureAsset::Load(U"player_jump_effect_4");


	TextureAsset::Register(U"player_dash_effect_0", U"image/player/dash/0.png");
	TextureAsset::Load(U"player_dash_effect_0");

	TextureAsset::Register(U"player_dash_effect_1", U"image/player/dash/1.png");
	TextureAsset::Load(U"player_dash_effect_1");

	TextureAsset::Register(U"player_dash_effect_2", U"image/player/dash/2.png");
	TextureAsset::Load(U"player_dash_effect_2");

	TextureAsset::Register(U"player_dash_effect_3", U"image/player/dash/3.png");
	TextureAsset::Load(U"player_dash_effect_3");




	TextureAsset::Register(U"enemy_slime", U"image/enemy/slime.png");
	TextureAsset::Load(U"enemy_slime");

	TextureAsset::Register(U"enemy_bake", U"image/enemy/bake.png");
	TextureAsset::Load(U"enemy_bake");

	TextureAsset::Register(U"enemy_kasa", U"image/enemy/kasa.png");
	TextureAsset::Load(U"enemy_kasa");

	

	TextureAsset::Register(U"deco_poster", U"image/deco/poster.png");
	TextureAsset::Load(U"deco_poster");

	TextureAsset::Register(U"event_save_point", U"image/event/save_point.png");
	TextureAsset::Load(U"event_save_point");

	//Stick(お祓い棒)

	TextureAsset::Register(U"stick_wait", U"image/player/stick/object_wait.png");
	TextureAsset::Load(U"stick_wait");

	TextureAsset::Register(U"stick_0", U"image/player/stick/object_0.png");
	TextureAsset::Load(U"stick_0");

	TextureAsset::Register(U"stick_1", U"image/player/stick/object_1.png");
	TextureAsset::Load(U"stick_1");

	TextureAsset::Register(U"stick_2", U"image/player/stick/object_2.png");
	TextureAsset::Load(U"stick_2");

	TextureAsset::Register(U"stick_3", U"image/player/stick/object_3.png");
	TextureAsset::Load(U"stick_3");

	//attack

	TextureAsset::Register(U"attack_0", U"image/player/stick/attack_0.png");
	TextureAsset::Load(U"attack_0");

	TextureAsset::Register(U"attack_1", U"image/player/stick/attack_1.png");
	TextureAsset::Load(U"attack_1");

	TextureAsset::Register(U"attack_2", U"image/player/stick/attack_2.png");
	TextureAsset::Load(U"attack_2");

	TextureAsset::Register(U"attack_3", U"image/player/stick/attack_3.png");
	TextureAsset::Load(U"attack_3");

	/*
	TextureAsset::Register(U"stick_right", U"image/player/stick/right.png");
	TextureAsset::Load(U"stick_right");
*/

	TextureAsset::Register(U"item_heart", U"image/item/heart.png");
	TextureAsset::Load(U"item_heart");

	TextureAsset::Register(U"item_soul", U"image/item/soul.png");
	TextureAsset::Load(U"item_soul");

	TextureAsset::Register(U"effect_soul_big", U"image/effect/soul_big.png");
	TextureAsset::Load(U"effect_soul_big");

	TextureAsset::Register(U"item_coin_10", U"image/item/coin_10.png");
	TextureAsset::Load(U"item_coin_10");

	TextureAsset::Register(U"charm_test", U"image/charm/test.png");
	TextureAsset::Load(U"charm_test");


	//Bullet
	TextureAsset::Register(U"bullet_enemy_fire", U"image/bullet_enemy/fire.png");
	TextureAsset::Load(U"bullet_enemy_fire");

	//Menu

	TextureAsset::Register(U"menu_back", U"image/menu/back.png");
	TextureAsset::Load(U"menu_back");

	TextureAsset::Register(U"menu_cur", U"image/menu/cur.png");
	TextureAsset::Load(U"menu_cur");

	TextureAsset::Register(U"menu_charm", U"image/menu/charm.png");
	TextureAsset::Load(U"menu_charm");

	TextureAsset::Register(U"menu_item", U"image/menu/item.png");
	TextureAsset::Load(U"menu_item");

	TextureAsset::Register(U"menu_map", U"image/menu/map.png");
	TextureAsset::Load(U"menu_map");

	TextureAsset::Register(U"menu_big_cur", U"image/menu/big_cur.png");
	TextureAsset::Load(U"menu_big_cur");

	TextureAsset::Register(U"menu_charm_cur", U"image/menu/charm_cur.png");
	TextureAsset::Load(U"menu_charm_cur");


	//UI
	TextureAsset::Register(U"life_bar_frame", U"image/ui/life_bar_frame.png");
	TextureAsset::Load(U"life_bar_frame");

	TextureAsset::Register(U"life_bar_red", U"image/ui/life_bar_red.png");
	TextureAsset::Load(U"life_bar_red");

	TextureAsset::Register(U"life_bar_white", U"image/ui/life_bar_white.png");
	TextureAsset::Load(U"life_bar_white");

	TextureAsset::Register(U"life_bar_bottom", U"image/ui/life_bar_bottom.png");
	TextureAsset::Load(U"life_bar_bottom");

	TextureAsset::Register(U"power_soul_empty", U"image/ui/power_soul_empty.png");
	TextureAsset::Load(U"power_soul_empty");

	TextureAsset::Register(U"power_soul", U"image/ui/power_soul.png");
	TextureAsset::Load(U"power_soul");

	TextureAsset::Register(U"damage_layer", U"image/ui/damage_layer.png");
	TextureAsset::Load(U"damage_layer");




	TextureAsset::Register(U"my_life", U"image/ui/my_life.png");
	TextureAsset::Load(U"my_life");

	TextureAsset::Register(U"purse", U"image/ui/purse.png");
	TextureAsset::Load(U"purse");

	TextureAsset::Register(U"black", U"image/ui/black.png");
	TextureAsset::Load(U"black");

	TextureAsset::Register(U"map_all", U"image/map/map_all.png");
	TextureAsset::Load(U"map_all");

	//Event
	TextureAsset::Register(U"message_box", U"image/event/message_box.png");
	TextureAsset::Load(U"message_box");

	TextureAsset::Register(U"transparent", U"image/transparent.png");
	TextureAsset::Load(U"transparent");

	TextureAsset::Register(U"event_blue_box", U"image/event/blue_box.png");
	TextureAsset::Load(U"event_blue_box");





	TextureAsset::Register(U"face_sakura", U"image/event/face_sakura.png");
	TextureAsset::Load(U"face_sakura");

	/*
	TextureAsset::Register(U"charm_金運上昇", U"image/charm/金運上昇.png");
	TextureAsset::Load(U"charm_金運上昇");
	TextureAsset::Register(U"charm_安全祈願", U"image/charm/安全祈願.png");
	TextureAsset::Load(U"charm_安全祈願");
	TextureAsset::Register(U"charm_歩行強化", U"image/charm/.png");
	TextureAsset::Load(U"charm_安全祈願");
    */

	//Menu

	for (auto& text : text_charms) {

		String name = U"charm_" + text.get_name();
		String adress = U"image/charm/" + text.get_name() + U".png";

		TextureAsset::Register(name, adress);
		TextureAsset::Load(name);
	}

	
	for (auto& text : text_magas) {

		String name = U"maga_" + text.get_name();
		String adress = U"image/maga/" + text.get_name() + U".png";

		TextureAsset::Register(name, adress);
		TextureAsset::Load(name);
	}

	for (auto& text : text_weapons) {

		String name = U"weapon_" + text.get_name();
		String adress = U"image/weapon/" + text.get_name() + U".png";

		//Print << U"name::" << name;
		//Print << U"adress::" << adress;
		TextureAsset::Register(name, adress);
		TextureAsset::Load(name);
	}

	for (auto& text : text_items) {

		String name = U"item_" + text.get_name();
		String adress = U"image/item/" + text.get_name() + U".png";

		TextureAsset::Register(name, adress);
		TextureAsset::Load(name);
	}


	//Menu


	TextureAsset::Register(U"sign_menu", U"image/menu/sign_menu.png");
	TextureAsset::Load(U"sign_menu");

	TextureAsset::Register(U"sign_charm", U"image/menu/sign_charm.png");
	TextureAsset::Load(U"sign_charm");

	TextureAsset::Register(U"sign_item", U"image/menu/sign_item.png");
	TextureAsset::Load(U"sign_item");


	TextureAsset::Register(U"sign_shop", U"image/menu/sign_shop.png");
	TextureAsset::Load(U"sign_shop");




	TextureAsset::Register(U"menu_black", U"image/menu/black.png");
	TextureAsset::Load(U"menu_black");

	
	TextureAsset::Register(U"menu_stone", U"image/menu/stone.png");
	TextureAsset::Load(U"menu_stone");

	TextureAsset::Register(U"bg_my_room", U"image/bg/my_room.png");
	TextureAsset::Load(U"bg_my_room");

	TextureAsset::Register(U"maga_green", U"image/maga/green.png");
	TextureAsset::Load(U"maga_green");

	TextureAsset::Register(U"maga_hollow", U"image/maga/hollow.png");
	TextureAsset::Load(U"maga_hollow");

	TextureAsset::Register(U"maga_hollow", U"image/maga/hollow.png");
	TextureAsset::Load(U"maga_hollow");


	TextureAsset::Register(U"shop_box", U"image/ui/shop_box.png");
	TextureAsset::Load(U"shop_box");

	TextureAsset::Register(U"shop_cur", U"image/ui/shop_cur.png");
	TextureAsset::Load(U"shop_cur");

	TextureAsset::Register(U"shop_top", U"image/ui/shop_top.png");
	TextureAsset::Load(U"shop_top");

	TextureAsset::Register(U"shop_under", U"image/ui/shop_under.png");
	TextureAsset::Load(U"shop_under");

	/*
	TextureAsset::Register(U"item_カギ", U"image/item/カギ.png");
	TextureAsset::Load(U"item_カギ");

	TextureAsset::Register(U"weapon_お祓い棒", U"image/weapon/お祓い棒.png");
	TextureAsset::Load(U"weapon_お祓い棒");

	TextureAsset::Register(U"maga_緑の勾玉", U"image/maga/緑の勾玉.png");
	TextureAsset::Load(U"maga_緑の勾玉");

*/
}


void Game_Manager::initialize_font() {

	const String preloadText = U"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";


	FontAsset::Load(U"MyFont", preloadText);

	FontAsset::Register(U"BIZ_60", 60, U"font/BIZUDGothic-Regular.ttf");
	FontAsset::Load(U"BIZ_60", preloadText);

	FontAsset::Register(U"BIZ_50", 50, U"font/BIZUDGothic-Regular.ttf");
	FontAsset::Load(U"BIZ_50", preloadText);

	FontAsset::Register(U"BIZ_45", 45, U"font/BIZUDGothic-Regular.ttf");
	FontAsset::Load(U"BIZ_45", preloadText);

	FontAsset::Register(U"BIZ_40", 40, U"font/BIZUDGothic-Regular.ttf");
	FontAsset::Load(U"BIZ_40", preloadText);

	FontAsset::Register(U"BIZ_30", 30, U"font/BIZUDGothic-Regular.ttf");
	FontAsset::Load(U"BIZ_30", preloadText);

	FontAsset::Register(U"Mur_50", 50, U"font/Murecho-Bold.ttf");
	FontAsset::Load(U"Mur_50", preloadText);
}

void Game_Manager::initialize_shader() {

	//Shader
	psWhite = HLSL{ U"shader/white.hlsl", U"PS" };
	if (not psWhite)
	{
		throw Error{ U"Failed to load a shader file" };
	}

	psRed = HLSL{ U"shader/red.hlsl", U"PS" };
	if (not psRed)
	{
		throw Error{ U"Failed to load a shader file" };
	}

	psViolet = HLSL{ U"shader/violet.hlsl", U"PS" };
	if (not psViolet)
	{
		throw Error{ U"Failed to load a shader file" };
	}
}

void Game_Manager::initialize_UI() {

	//Cur
	menu_cur_main.set_x_max(2);
	menu_cur_main.set_y_max(0);
	menu_cur_main.set_off_turn_x();
	menu_cur_main.set_off_turn_y();

	shop_cur.set_x_max(5);
	shop_cur.set_y_max(2);
	shop_cur.set_off_turn_x();
	shop_cur.set_off_turn_y();
}

//イベントの変数を準備
void Game_Manager::initialize_event() {

	event_super.plus_var(U"display_5", 0);
}

void Game_Manager::initialize_music() {

	

	//AudioAsset::Register(bgm[0], Audio::Stream, U"music/bgm/日光浴.ogg", Loop::Yes);

	set_bgm(U"日光浴");
	set_se(U"お祓い棒");



	//AudioAsset::Load(bgm[0]);


	// アセットの登録
	//AudioAsset::Register(U"BGM", U"example/test.mp3");
	//AudioAsset::Register(U"Sound", GMInstrument::Piano1, PianoKey::A4, 0.5s);
}

void Game_Manager::initialize_debug() {

	status.plus_equip_charm(U"金運上昇");
	status.plus_equip_charm(U"諸刃の剣");
	status.plus_equip_charm(U"安全祈願");

	for (int i = 0; i < 5; i++) {
		status.plus_maga(U"green");
	}

	status.test();

	status.plus_money(500);

}
