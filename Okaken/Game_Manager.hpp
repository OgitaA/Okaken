#pragma once

#include<Siv3D.hpp>

#include"Player.hpp"
#include"Block.hpp"
#include"Tile.hpp"
#include"Enemy.hpp"
#include"Item.hpp"
#include"Deco.hpp"
#include"Event.hpp"

#include"Bullet_Enemy.hpp"

#include"My_Effect.hpp"
#include"Circle_Effect.hpp"

//ブロックタイプ
#include"Block_Type.hpp"
#include"Needle.hpp"
#include"Slip_Block.hpp"
#include"Bound_Block.hpp"
#include"Break_Block.hpp"

//List
#include"Enemy_list.hpp"

//Stage_Data
#include"Stage_Data.hpp"

//Area
#include"Area_Data.hpp"
#include"Area_Map.hpp"

//Edit
#include"Editor_Grid.hpp"
#include"My_Slider.hpp"
#include"Select_Box.hpp"
#include"My_Button.hpp"
#include"Detail_Setter.hpp"
#include"Area_Selecter.hpp"
#include"Tool_Selecter.hpp"

//Status
#include"Status.hpp"
#include"Have_Charm.hpp"
#include"Equip_Charm.hpp"

//Action
#include"Stick.hpp"//お祓い棒クラス
#include"Jump_Effect.hpp"
#include"Dash_Effect.hpp"

//Menu
#include"Message_Box.hpp"

//Event
#include"Event_Super.hpp"
#include"Event_List.hpp"

//Cur
#include"Cur.hpp"

//Text
#include"Text_Data.hpp"

//Common
#include"Indent_Drawer.hpp"

//Shader
#include"White_Effect.hpp"

//Other
#include"Light_Bloom.hpp"


class Game_Manager {

public:

	Game_Manager();

	void initialize();

	void initialize_screen();
	void initialize_event();
	void initialize_editor();
	void initialize_image();
	void initialize_font();
	void initialize_shader();
	void initialize_UI();
	void initialize_data();
	void initialize_music();


	void initialize_debug();


	String update();
	void draw()const;


	//SDFFONT
	//const Font fontSDF_30{ FontMethod::SDF,30, Typeface::Bold };

	const Font fontSDF_40{ FontMethod::SDF,60,U"font/Murecho-Bold.ttf" };






private:

	float Delta_Time;
	float Game_Speed = 1;

	String scene = U"game";

	void update_game();
	void draw_game()const;


	void change_scene(String go_scene) {

		initialize_fade();

		fade_scene_type = U"scene";
		fade_scene_go_scene = go_scene;
	}



	void update_menu();
	void draw_menu()const;

	void update_event();
	void draw_event()const;
	bool lock_draw_game = false;


	Array<String> zone_datas;
	void set_zone_data(String set_name) {
		zone_datas.push_back(set_name);
	}

	String area;

	Array<Area_Data> area_datas;
	void set_area_data(String set_name,int set_w,int set_h,String set_zone) {
		area_datas.push_back(Area_Data(set_name, set_w, set_h, set_zone));
	}

	int area_wide = 0;
	int area_height = 0;

	void reset_area() {

		items.clear();
		bullet_enemys.clear();
		my_effects.clear();

		make_stage();
	}



	/*
	struct Retry_Point {
		float x;
		float y;
		String area;
	};*/

	//Array<Retry_Point> retry_points;

	String retry_area = U"";

	Vec2 scroll = { 0,0 };
	void control_scroll() {

		

		scroll = player.get_camera_target_pos();
		//scroll.x = int(player.get_camera_target_pos().x);
		//scroll.y = int(player.get_camera_target_pos().y);
		



		if ((scroll.x - 1920 / 2) < 0) {
			scroll.x = 1920 / 2;
		}
		if ((scroll.y - 1080 / 2) < 0) {
			scroll.y = 1080 / 2;
		}

		if ((scroll.x + 1920 / 2)>area_wide) {
			scroll.x = area_wide - 1920 / 2;
		}

		if ((scroll.y + 1080 / 2) > area_height) {
			scroll.y = area_height - 1080 / 2;
		}

	}



	Camera2D camera{ Vec2{1920 / 2,1080 / 2},1.0,CameraControl::None_ };

	RenderTexture renderTexture;

	void vs();
	void vs_player();
	void vs_player_plus_down(Block_Type);
	void vs_enemys();
	void vs_items();
	void vs_bullets();
	void vs_player_enemy();
	void vs_player_item();
	void vs_stick_enemy();
	void vs_stick_block();
	


	//Make
	void update_make_enemy();
	void make_enemy(String,int,int);
	void update_make_shot_enemy();
	void make_shot_enemy(int,int,int);
	void make_bullet_enemy(String, int, int,float,float,float);
	float search_angle_player(int, int);
	float convert_radian_to_angle(float);
	float convert_angle_to_radian(float);

	//Player
	Player player;
	void draw_player()const {

		//プレイヤーと点滅表示
		{

			const ScopedCustomShader2D shader{ psRed };

			cbRed->strength = player.get_red();

			Graphics2D::SetConstantBuffer(ShaderStage::Pixel, 1, cbRed);

			player.draw();
		}

		
	}


	//別のスクロールで描画(別のレンダーテクスチャを使うので)
	void draw_player_light()const {

		if (player.get_violet()>0) {


			{
				{
					auto t = camera.createTransformer();

					ScopedLightBloom target{ light_bloom };

					draw_player_violet();
				}

				light_bloom.draw(player.get_violet());

			}
		}
	}

	void draw_player_violet()const {

		{

			const ScopedCustomShader2D shader{ psViolet };

			cbViolet->strength = 1;

			Graphics2D::SetConstantBuffer(ShaderStage::Pixel, 1, cbViolet);

			player.draw();
		}
	}

	void draw_dash_effect_light()const {


		for (auto& effect : dash_effects) {

			{
				auto t = camera.createTransformer();

				ScopedLightBloom target{ light_bloom };

				{
					const ScopedCustomShader2D shader{ psViolet };

					cbViolet->strength = 1;

					Graphics2D::SetConstantBuffer(ShaderStage::Pixel, 1, cbViolet);

					effect.draw();
				}

			}

			light_bloom.draw(player.get_violet());
		}

	}

	void draw_jump_effect_light()const {

		for (auto& effect : jump_effects) {

			{
				auto t = camera.createTransformer();

				ScopedLightBloom target{ light_bloom };

				{
					const ScopedCustomShader2D shader{ psViolet };

					cbViolet->strength = 1;

					Graphics2D::SetConstantBuffer(ShaderStage::Pixel, 1, cbViolet);

					effect.draw();
				}

			}

			light_bloom.draw(player.get_violet());
		}
	}

	//使用しない
	void draw_dash_effect_violet()const {

		{
			
			const ScopedCustomShader2D shader{ psViolet };

			cbViolet->strength = 1;

			Graphics2D::SetConstantBuffer(ShaderStage::Pixel, 1, cbViolet);

			draw_dash_effects();

		
		}
	}

	LightBloom light_bloom;
	
	

	void damage_player(int v,String direction) {

		if (false == game_over_flag) {

			if (false == player.get_muteki()) {

				player.damage();

				if (direction != U"none") {
					player.set_knock_back(direction);
				}


				status.minus_life(1);
				status.minus_power(1);

				hp_white_lock_count = 0.5;
				damage_layer_count = 1.2;

				
			}
		}
	}

	void full_life_player() {
		status.full_life();
	}

	Array<Jump_Effect> jump_effects;

	void update_jump_effects(float d_time) {

		if (true==player.get_just_double()) {

			float x = player.get_rect().x + player.get_rect().w / 2;
			float y = player.get_rect().y + player.get_rect().h;

			jump_effects.push_back(Jump_Effect(x - 75, y));
		}

		for (auto& effect : jump_effects) {
			effect.update(d_time);
		}


		jump_effects.remove_if([&](Jump_Effect effect) {

			if (true == effect.get_delete()) {
				return true;
			}

		return false;

			});
	}

	void draw_jump_effects()const {

		for (auto& effect : jump_effects) {
			effect.draw();
		}
	}

	Array<Dash_Effect> dash_effects;

	void update_dash_effects(float d_time) {

		if (true == player.get_dash()) {

			float x = player.get_rect().x;
			float y = player.get_rect().y + player.get_rect().h / 2;

			if (player.get_dash_count() > player.get_dash_effect_count()*0.16) {

				//Print << U"count::" << player.get_dash_count();

				if (player.get_direction() == U"left") {

					dash_effects.push_back(Dash_Effect(x, y - 30, true));
				}
				else if (player.get_direction() == U"right") {

					dash_effects.push_back(Dash_Effect(x + (74 - 80), y - 30, false));
				}

				player.plus_dash_effect_count();
			}

			
		}

		for (auto& effect : dash_effects) {
			effect.update(d_time);
		}


		dash_effects.remove_if([&](Dash_Effect effect) {

			if (true == effect.get_delete()) {
				return true;
			}

		return false;

			});
	}

	void draw_dash_effects()const {

		for (auto& effect : dash_effects) {
			effect.draw();
		}
	}


	//Tile
	Array<Tile> tiles;
	void draw_tiles()const {

		//int center_x = player.get_rect().x + player.get_rect().w / 2;
		//int center_y = player.get_rect().y + player.get_rect().h / 2;

		int center_x = scroll.x;
		int center_y = scroll.y;

		int left_wall = center_x - 1920 / 2 - 200;
		int right_wall = center_x + 1920 / 2 + 200;
		int up_wall = center_y - 1080 / 2 - 200;
		int down_wall = center_y + 1080 / 2 + 200;


		for (auto& tile : tiles) {

			//x軸
			if (left_wall < tile.get_rect().x and tile.get_rect().x < right_wall) {

				//Y軸
				if (up_wall < tile.get_rect().y and tile.get_rect().y < down_wall) {

					tile.draw();
				}
			}
		}

		//Print << U"tile.size"<<tiles.size();

	}


	//Block
	Array<std::shared_ptr<Block>> blocks;
	void update_blocks(const float d_time) {
		for (auto& block : blocks) {
			block->update(d_time);
		}
	}
	void draw_blocks()const {


		//int center_x = player.get_rect().x + player.get_rect().w / 2;
		//int center_y = player.get_rect().y + player.get_rect().h / 2;

		int center_x = scroll.x;
		int center_y = scroll.y;

		int left_wall = center_x - 1920 / 2 - 200;
		int right_wall = center_x + 1920 / 2 + 200;
		int up_wall = center_y - 1080 / 2 - 200;
		int down_wall = center_y + 1080 / 2 + 200;

		for (auto& block : blocks) {

			//x軸
			if (left_wall < block->get_rect().x and block->get_rect().x < right_wall) {

				//Y軸
				if (up_wall < block->get_rect().y and block->get_rect().y < down_wall) {

					block->draw();
				}
			}
		}
	}


	//Enemy
	Array<std::shared_ptr<Enemy>> enemys;
	void update_enemys(const float d_time) {
		for (auto& enemy : enemys) {
			enemy->update(d_time, player);
		}
	}
	void draw_enemys()const {

		const ScopedCustomShader2D shader{ psWhite };

		for (auto& enemy : enemys) {

			cbWhite->strength = enemy->get_white() * 2;

			Graphics2D::SetConstantBuffer(ShaderStage::Pixel, 1, cbWhite);
			enemy->draw();
		}
	}
	void delete_enemy() {

		enemys.remove_if([&](const auto& enemy) {

			if (enemy->get_hp() <= 0) {

				
				float center_x = enemy->get_rect().x + enemy->get_rect().w / 2;
				float center_y = enemy->get_rect().y + enemy->get_rect().h / 2;

				int drop_heart = enemy->get_drop_heart();
				int drop_soul = enemy->get_drop_soul();

				int drop_coin_10 = enemy->get_drop_coin_10();
				int drop_coin_50 = enemy->get_drop_coin_50();
				int drop_coin_100 = enemy->get_drop_coin_100();
				int drop_coin_500 = enemy->get_drop_coin_500();

				make_items(drop_heart, drop_soul, drop_coin_10, drop_coin_50, drop_coin_100, drop_coin_500, center_x, center_y);

				circle_effects.push_back(Circle_Effect({ center_x,center_y }, 60, ColorF(0.93,0.5,0.93)));

				for (int i = 0; i < 5; i++) {
					circle_effects.push_back(Circle_Effect({ center_x,center_y }, 30, ColorF(0.93, 0.5, 0.93), float(72 * i) - 90));
				}


				return true;
			}

		    return false;
        });
	}

	//Deco
	Array<Deco> decos;
	Array<Deco> decos_2;
	void draw_decos()const {

		//int center_x = player.get_rect().x + player.get_rect().w / 2;
		//int center_y = player.get_rect().y + player.get_rect().h / 2;

		int center_x = scroll.x;
		int center_y = scroll.y;

		int left_wall = center_x - 1920 / 2 - 200;
		int right_wall = center_x + 1920 / 2 + 200;
		int up_wall = center_y - 1080 / 2 - 200;
		int down_wall = center_y + 1080 / 2 + 200;

		for (auto& deco : decos) {

			//x軸
			if (left_wall < deco.get_rect().x and deco.get_rect().x < right_wall) {

				//Y軸
				if (up_wall < deco.get_rect().y and deco.get_rect().y < down_wall) {

					deco.draw();
				}
			}
		}

		for (auto& deco : decos_2) {

			//x軸
			if (left_wall < deco.get_rect().x and deco.get_rect().x < right_wall) {

				//Y軸
				if (up_wall < deco.get_rect().y and deco.get_rect().y < down_wall) {

					deco.draw();
				}
			}
		}
	}


	//Item
	Array<Item> items;
	void update_items(const float d_time) {
		for (auto& item : items) {
			item.update(d_time);
		}
	}
	void draw_items()const {
		for (auto& item : items) {
			item.draw();
		}
	}

	void make_items(int heart,int soul,int coin_10,int coin_50,int coin_100,int coin_500,float center_x,float center_y) {

		String name = U"none";

		{
			

			if (heart >= 1) {
				name = U"heart";
			}
			else if (soul >= 1) {
				name = U"soul";
			}

			if (name != U"none") {

				items.push_back(Item(name, center_x, center_y));
			}
		}

		int en = 10;

		if (coin_10 >= 1) {

			

			bool left_on = true;

			//初期方向もランダム
			if (RandomBool()) {
				left_on = false;
			}

			for (int i = 0; i < coin_10; i++) {

				float ran_v = 10 + Random(135);

				name = U"coin";
				en = 10;

				if (true == left_on) {

					ran_v *= -1;

					left_on = false;
				}
				else {
					left_on = true;
				}

				items.push_back(Item(name, en, center_x, center_y, ran_v));
			}
		}
	}

	

	//Event
	Array<Event> events;
	void update_events(const float d_time) {
		for (auto& event : events) {
			event.update(d_time);
		}
	}
	void draw_events()const {
		for (auto& event : events) {
			event.draw();
		}
	}


	//Bullet_Enemy
	Array<Bullet_Enemy> bullet_enemys;
	void update_bullet_enemys(const float d_time) {
		for (auto& bullet : bullet_enemys) {
			bullet.update(d_time);
		}
	}
	void draw_bullet_enemys()const {
		for (auto& bullet : bullet_enemys) {
			bullet.draw();
		}
	}



	//My_Effect
	Array<My_Effect> my_effects;
	void update_my_effects(const float d_time) {
		for (auto& my_effect : my_effects) {
			my_effect.update(d_time);
		}
	}
	void draw_my_effects()const {
		for (auto& my_effect : my_effects) {
			my_effect.draw();
		}
	}
	void delete_my_effects() {

		my_effects.remove_if([&](My_Effect my_effect) {

			if (my_effect.get_delete()) {
				return true;
			}

		return false;

			});
	}

	Array<My_Effect> soul_bigs;
	void update_soul_bigs(const float d_time) {
		for (auto& soul_big : soul_bigs) {
			soul_big.update(d_time);
		}
	}
	void draw_soul_bigs()const {
		for (auto& soul_big : soul_bigs) {
			soul_big.draw();
		}
	}
	void delete_soul_bigs() {

		soul_bigs.remove_if([&](My_Effect soul_big) {

			if (soul_big.get_delete()) {
				return true;
			}

		return false;

			});
	}

	Array<Circle_Effect> circle_effects;
	void update_circle_effects(const float d_time) {
		for (auto& effect : circle_effects) {
			effect.update(d_time);
		}
	}
	void draw_circle_effects()const {
		for (auto& effect : circle_effects) {
			effect.draw();
		}
	}
	void delete_circle_effects() {

		circle_effects.remove_if([&](Circle_Effect effect) {

			if (effect.get_delete()) {
				return true;
			}

		return false;

			});
	}

	//Change
	
	void change_edit() {
		bool v = edit;
		v ? edit = false : edit = true;
	}

	//Make_Stage
	struct Block_Name {
		int x = 0;
		int y = 0;
		String name = U"";
	};
	Array<Block_Name> block_names;
	
	void make_stage() {

		//Block

		blocks.clear();

		for (auto& block_data : block_datas) {

			int x = block_data.x;
			int y = block_data.y;
			int image_x = block_data.image_x;
			int image_y = block_data.image_y;
		
			String name = U"";

			for (auto& b_n : block_names) {

				if (b_n.x == image_x and b_n.y==image_y) {
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

				blocks.push_back(std::make_unique<Block>(name,x, y, image_x, image_y));

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

			tiles.push_back(Tile(x, y,image_x,image_y));
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

			events.push_back(Event(x,y,id,image_x,image_y));
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
		
	}

	//Action
	Stick stick;

	

	void attack() {

		if (KeyX.down() and false == player.get_action_lock() and false==game_over_flag and player.get_attack()) {

			String direction = player.get_direction();
			float x = 0;
			float y = 0;

			/*
			if (direction == U"left") {
				x = player.get_rect().x;
			}
			else if (direction == U"right") {
				x = player.get_rect().x + player.get_rect().w;
			}*/

			x = player.get_rect().x + player.get_rect().w / 2;

			y = player.get_rect().y;

			stick.make_attack(direction, x, y);


			player.set_attack_cool_time();
		}

		if (stick.get_exist()) {

			float x = 0;
			float y = 0;

			x = player.get_rect().x + player.get_rect().w / 2;

			y = player.get_rect().y;

			stick.set_pos(x,y);


			//プレイヤーの描画用

			player.set_state(U"attack");

			int page = stick.get_page();
			player.set_attack_page(page);

		}
	}

	//Text_Data

	Array<Text_Charm> text_charms;
	void set_text_charm(String set_name, String set_text) {
		text_charms.push_back(Text_Charm(set_name, set_text));
	}

	
	Array<Text_Maga> text_magas;
	void set_text_maga(String set_name, String set_text) {
		text_magas.push_back(Text_Maga(set_name, set_text));
	}

	Array<Text_Weapon> text_weapons;
	void set_text_weapon(String set_name, String set_text) {
		text_weapons.push_back(Text_Weapon(set_name, set_text));
	}

	Array<Text_Item> text_items;
	void set_text_item(String set_name, String set_text) {
		text_items.push_back(Text_Item(set_name, set_text));
	}




	//Common
	Indent_Drawer indent_drawer;









	//Edit

	String edit_scene = U"edit_base";


	//Function
	void update_edit();
	void draw_edit()const;

	void save_area_data();
	void load_area_data();

	void make_area_edit() {

		block_datas.clear();
		enemy_datas.clear();
		event_datas.clear();
		deco_datas.clear();
		tile_datas.clear();
        //item_datas.clear();

		load_area_data();
		make_stage();

		//スライダー調整

		int wide = 0;
		int height = 0;

		for (auto& area_data : area_datas) {

			if (area_data.name == area) {
				wide = area_data.wide;
				height = area_data.height;
				break;
			}
		}


		for (auto& slider : my_sliders) {

			if (slider.get_type() == U"X") {
				slider.set_v(wide);
			}
			if (slider.get_type() == U"Y") {
				slider.set_v(height);
			}
		}
	}

	//Function_Sub

	void edit_block();
	void edit_enemy();
	void edit_tile();
	void edit_deco();
	void edit_event();
	void edit_player();


	void plus_block();
	void erase_block();

	void plus_enemy();
	void erase_enemy();

	void plus_tile();
	void erase_tile();

	void plus_deco();
	void erase_deco();

	void plus_event();
	void erase_event();

	//最適化する
	void optimize_edit();


	//Var

	bool edit = false;

	//Stage_Data

	Array<Block_Data> block_datas;
	Array<Enemy_Data> enemy_datas;
	Array<Tile_Data> tile_datas;
	Array<Deco_Data> deco_datas;
	Array<Event_Data> event_datas;

	Player_Data player_data;

	


	Camera2D camera_edit{ Vec2{1920 / 2,1080 / 2},1.0,CameraControl::None_ };


	Editor_Grid editor_grid;

	Vec2 scroll_edit;

	//クリック判定
	bool click_edit = false;

	//クリック判定シーンマタギ用
	bool click_edit_over_scene = false;
	
	//Edit_Type
	enum Edit_Type {
		E_Block,
		E_Enemy,
		E_Tile,
		E_Deco,
		E_Event,
		E_player

	};

	Edit_Type edit_type;

	enum Edit_Mode {
		E_Pen,
		E_Eraser
	};

	Edit_Mode edit_mode;


	//Edit各種情報

	String block_name_edit;
	String enemy_name_edit;
	String tile_name_edit;
	String deco_name_edit;
	String event_name_edit;

	int block_image_x = 0;
	int block_image_y = 0;
	int block_image_w = 1;
	int block_image_h = 1;

	int tile_image_x = 0;
	int tile_image_y = 0;
	int tile_image_w = 1;
	int tile_image_h = 1;

	int deco_image_x = 0;
	int deco_image_y = 0;
	int deco_image_w = 1;
	int deco_image_h = 1;

	int event_image_x = 0;
	int event_image_y = 0;
	int event_image_w = 1;
	int event_image_h = 1;

	int edit_cur_x;
	int edit_cur_y;


	//エディタ用のGUI


	//スライダー
	double slider_x = 0;
	double slider_y = 0;
	int slider_x_wide = 0;
	int slider_y_height = 0;

	void use_slider_edit();
	void use_select_box_edit();
	void use_my_button();

	//スライダー
	Array<My_Slider> my_sliders;

	//セレクトボックス
	Array<Select_Box> select_boxs;

	//マイボタン
	Array<My_Button> my_buttons;

	//ディテール設定
	Detail_Setter detail_setter;

	int set_detail_v = -1;
	int set_detail_index = 0;


	//Editor用エリア選択
	Area_Selecter area_selecter;

	//Editor用ツール選択
	Tool_Selecter tool_selecter;
	String tool_edit = U"pen";

	//Editor_Bucket
	int bucket_edit_scene = 0;
	int bucket_edit_start_x;
	int bucket_edit_start_y;

	//マップデータいじるよう(使う時だけ)
	void move_area_data(int plus_x,int plus_y) {

		Array<Tile_Data> temp_tiles;
		temp_tiles = tile_datas;

		Array<Block_Data> temp_blocks;
		temp_blocks = block_datas;

		Array<Deco_Data> temp_decos;
		temp_decos = deco_datas;

		tile_datas.clear();

		for (auto& tile : temp_tiles) {
			tile.x += plus_x;
			tile.y += plus_y;
		}

		tile_datas = temp_tiles;


		block_datas.clear();

		for (auto& block : temp_blocks) {
			block.x += plus_x;
			block.y += plus_y;
		}

		block_datas = temp_blocks;


		deco_datas.clear();

		for (auto& deco : temp_decos) {
			deco.x += plus_x;
			deco.y += plus_y;
		}

		deco_datas = temp_decos;



	}



	//Menu
	Status status;

	void plus_will_money(int v) {

		will_money += v;

		if (0 == will_money_scene) {
			will_money_scene = 1;
		}
	}

	void minus_will_money(int v) {

		will_money_minus += v;

		if (0 == will_money_scene) {
			will_money_scene = 3;
			
		}
	}


	//UI処理

	int will_money_scene = 0;

	
	int will_money_base = 0;//初期値
	int will_money = 0;//加算分
	int will_money_goal = 0;//結果

	int will_money_split = 0;

	float will_money_count = 0;

	//UI処理お金減らす

	int will_money_minus = 0;//減算分

	float purse_display_count = 0;




	void update_UI() {

		float d_time = Delta_Time;

		bool process = false;

		const float keep_count = 4;

		//お金の処理なし
		if (0 == will_money_scene) {

		}
		//開始処理(増加)
		else if (1 == will_money_scene) {

			//実行中
			process = true;

			//財布の描画カウント維持
			purse_display_count = keep_count;

			//初期値を取得
			will_money_base = status.get_money();

			//増加結果を計算
			will_money_goal = will_money_base + will_money;


			//１回当たりの増加量を計算
			//will_money_split = will_money / 60 / 3;

			//カウンターをリセット
			will_money_count = 0;

			will_money_scene++;
		}
		//増加処理
		else if (2 == will_money_scene) {

			//実行中
			process = true;

			//財布の描画カウント維持
			purse_display_count = keep_count;


			//更新(お金が処理中に増加した場合にも対応)
			//増加結果を再計算
			will_money_goal = will_money_base + will_money;

			//Print << U"will_money_goal::" << will_money_goal;

			//カウンター増加
			will_money_count += d_time;

			if (will_money_count >= float(1 / 60)) {

				int v = 1;

				status.plus_money(v);
				will_money_count = 0;
			}

			//目標値まで増加した(終了処理)
			if (status.get_money() >= will_money_goal) {

				status.set_money(will_money_goal);

				will_money_scene = 0;
				will_money = 0;
				will_money_goal = 0;
			}

		}


		//開始処理(減少)
		else if (3 == will_money_scene) {

			//実行中
			process = true;

			//財布の描画カウント維持
			purse_display_count = keep_count;

			//初期値を取得
			will_money_base = status.get_money();

			//減少結果を計算
			will_money_goal = will_money_base - will_money_minus;

			//バグ除け
			if (will_money_goal < 0) {
				throw Error{U"your_money_is_under_0_from_Game_Manager.hpp"};
			}

			//１回当たりの増加量を計算
			//will_money_split = will_money / 60 / 3;

			//カウンターをリセット
			will_money_count = 0;

			will_money_scene++;

			Print << U"pass";
		}
		else if (4 == will_money_scene) {

			//実行中
			process = true;

			//財布の描画カウント維持
			purse_display_count = keep_count;


			//更新(お金が処理中に増加した場合にも対応)
			//増加結果を再計算
			will_money_goal = will_money_base - will_money_minus;

			//バグ除け
			if (will_money_goal < 0) {
				Error{ U"your_money_is_under_0_from_Game_Manager.hpp" };
			}

			//Print << U"will_money_goal::" << will_money_goal;

			//カウンター増加
			will_money_count += d_time;

			if (will_money_count >= float(1 / 60)) {

				int v = 1;

				status.minus_money(v);
				will_money_count = 0;
			}

			//目標値まで減少した(終了処理)
			if (status.get_money() <= will_money_goal) {

				status.set_money(will_money_goal);

				will_money_scene = 0;
				will_money_minus = 0;
				will_money_goal = 0;
			}
		}




		//実行していないとき
		if (purse_display_count > 0) {
			purse_display_count -= d_time;
		}



		//hp_white_var

		bool hp_white_lock = false;

		if (hp_white_lock_count > 0) {

			hp_white_lock_count -= d_time;
			hp_white_lock = true;
		}

		if (false == hp_white_lock) {

			float v = 450 * status.get_life() / status.get_life_max();

			//多い場合減らしていく
			if (v < hp_white_v) {
				hp_white_v -= d_time * 150;
			}

			//微調整(減りすぎた場合そろえる)
			if (hp_white_v < v) {
				hp_white_v = v;
			}

		}


		if (damage_layer_count > 0) {
			damage_layer_count -= d_time;

			//スローモーション
			if (damage_layer_count > 1) {

				Game_Speed = 0.7;
			}


			if (damage_layer_count < 0) {
				damage_layer_count = 0;
			}
		}
		else {
			Game_Speed = 1;
		}


	}


	void draw_UI()const {

		if (flash_UI_count > 0) {

		}




		TextureAsset(U"life_bar_bottom").draw(50, 20);
		TextureAsset(U"life_bar_white")(0, 0, hp_white_v, 60).draw(50, 20);


		float v = 450 * status.get_life() / status.get_life_max();

		if (v > 450) {
			v = 450;
		}

		TextureAsset(U"life_bar_red")(0, 0, v, 60).draw(50, 20);
		TextureAsset(U"life_bar_frame").draw(50, 20);

		/*
		{
			int x = 50;
			int blank_x = 100;

			int y = 50;


			for (int i = 0; i < status.get_life(); i++) {
				TextureAsset(U"my_life").draw(x + blank_x * i, y);
			}

		}*/

		//TextureAsset(U"purse").draw(50,100);

		for (int i = 0; i < status.get_power_max(); i++) {
			TextureAsset(U"power_soul_empty").draw(50 + (i * 70), 90);
		}

		for (int i = 0; i < status.get_power(); i++) {
			TextureAsset(U"power_soul").draw(50 + (i * 70), 90);
		}


		//FontAsset(U"BIZ_45")(status.get_money()).draw(150, 100,Palette::White);

		/*
		if (purse_display_count > 0) {
			TextureAsset(U"purse").draw(100, 100);
			FontAsset(U"BIZ_30")(status.get_money()).draw(150,100,Palette::Black);
		}*/

		float fade = purse_display_count;

		//Print << U"fade::"<<fade;

		if (U"menu" == scene or ev_shop) {
			fade = 1;
		}

			TextureAsset(U"purse").draw(70, 175, ColorF(1, fade));

			const double outlineScale = 0.5;
			const ColorF outlineColor = ColorF(0, 0, 0, fade);

			//fontSDF_40(status.get_money()).draw(TextStyle::Outline(outlineScale, outlineColor), 70+100, 160+2,ColorF(1,fade));
			fontSDF_40(status.get_money()).draw(TextStyle::Outline(outlineScale, outlineColor), 70 + 100, 160 + 2, ColorF(1, 1, 1, fade));
		


		for (auto& soul_big : soul_bigs) {
			soul_big.draw();
		}

		
		if (damage_layer_count > 0) {

			float v = damage_layer_count;

			TextureAsset(U"damage_layer").draw(0, 0, ColorF(1, v));


		
		}
		else {
			
		}

	}

	float hp_white_v = 0;
	float hp_white_lock_count = 0;

	float damage_layer_count = 0;

	//使わないかも
	float flash_UI_count = 0;
	bool flash_UI = false;
	int flash_UI_next = 2.5;



	//先に配置を決めておく

	struct Pos_Charm {

		Pos_Charm(String set_name,int set_x,int set_y) {

			name = set_name;
			x = set_x;
			y = set_y;
		}

		String name;
		int x;
		int y;
	};
	Array<Pos_Charm> pos_charms;
	void set_pos_charm(String set_name,int set_x,int set_y) {
		pos_charms.push_back(Pos_Charm(set_name, set_x, set_y));
	}

	struct Pos_Item {

		Pos_Item(String set_name, int set_x, int set_y) {
			name = set_name;
			x = set_x;
			y = set_y;
		}

		String name;
		int x;
		int y;
	};
	Array<Pos_Item> pos_items;
	void set_pos_item(String set_name, int set_x, int set_y) {
		pos_items.push_back(Pos_Item(set_name, set_x, set_y));
	}

	void get_charm(String set_name) {

		int x = 0;
		int y = 0;

		for (auto& data : pos_charms) {

			if (data.name == set_name) {
				x = data.x;
				y = data.y;
			}
		}

		status.plus_have_charm(set_name, x, y);
	}

	void get_item(String set_name) {

		int x = 0;
		int y = 0;

		for (auto& data : pos_items) {

			if (data.name == set_name) {
				x = data.x;
				y = data.y;
			}
		}


		status.plus_have_item(set_name, x, y);
	}

	







	//Event

	Event_Super event_super;

	Message_Box message_box;
	bool message_box_on = false;
	void start_message() { message_box_on = true; }
	void end_message() { message_box_on = false; }
	void mes(String v) { message_box.set_text(v); message_box.set_face(U""); }
	void mes(String face, String v) { message_box.set_face(face); message_box.set_text(v); }

	Array<Event_List> event_lists;
	void set_ev(int set_ID, String set_name) {
		event_lists.push_back(Event_List(set_ID, set_name));
	}







	int event_ID = 0;

	int ev_scene = 0;

	String ev_bg = U"";

	void start_event() {

		bool auto_start = false;

		for (auto& event : events) {
		
		}

		if (false == auto_start) {

			if (KeyUp.down()) {

				for (auto& event : events) {

					if (player.get_rect().intersects(event.get_rect())) {

						scene = U"event";

						event_ID = event.get_ID();

						//初期化
						ev_scene = 0;
					}
				}
			}
		}
	}


	void update_event_main();

	//状況に合わせて自動でイベントの画像や状態を更新
	void update_event_state_main() {

		for (auto& event : events) {
			update_event_state();
		}
	}

	void update_event_state();



	void z() {

		if (KeyZ.down()) {
			ev_scene++;
		}
	}

	void z(int v) {

		if (KeyZ.down()) {
			ev_scene = v;
		}
	}

	void end() {

		ev_scene = 0;

		message_box_on = false;

		scene = U"game";

		player.set_speed_x_zero();

		ev_shop = false;
	}

	void next() { ev_scene++; }
	void next(int v) { ev_scene = v; }

	void go_area(String go_name,int x,int y) {

		initialize_fade();
		fade_scene_type = U"area";
		fade_scene_go_area = go_name;
		fade_scene_go_area_pos = { x*72,y*72 };
	}

	void set_bg(String set_bg) {
		ev_bg = set_bg;
	}


	//Event関数

	void ev_save_point();

	

	void ev_up_first();
	void ev_up_second();
	void ev_up_third();
	void ev_up_fourth();
	void ev_up_fifth();
	void ev_up_sixth();

	void ev_down_first();
	void ev_down_second();
	void ev_down_third();
	void ev_down_fourth();
	void ev_down_fifth();
	void ev_down_sixth();

	void ev_enter_first_toilet();
	void ev_exit_first_toilet();

	

	void ev_talk_test();


	void ev_story_1();









	//Menu
	void start_menu() {

		if (false == game_over_flag and false==player.get_action_lock()) {

			if (U"game" == scene) {
				if (KeyM.down()) {
					//scene = U"menu";
					change_scene(U"menu");
				}
			}
		}
	}
	void end_menu() {

		if (KeyM.down() or KeyX.down()) {
			scene = U"game";
		}
	}

	String menu_scene = U"charm";

	int menu_layer = 0;

	void update_show_quick_map() {

		show_quick_map = false;

		if (false == game_over_flag and false == player.get_action_lock()) {

			if (KeyShift.pressed()) {
				show_quick_map = true;
			}
		}
	}

	void draw_show_quick_map()const {

		if (true == show_quick_map) {

			Rect black(0, 0, 1920, 1080);

			float size = 0.8;

			int adjust_x = 1920 * (1-size) / 2;
			int adjust_y = 1080 * (1-size) / 2;

			black.draw(ColorF(0,0,0, 0.6));

			TextureAsset(U"map_all").scaled(size).draw(0 + adjust_x, 0 + adjust_y);
		}
	}

	bool show_quick_map = false;


	void go_menu_scene(int go_layer,String go_plus_scene) {
		initialize_fade();
		fade_scene_type = U"scene";
		fade_scene_go_scene = U"menu";
		fade_go_scene_plus_layer = go_layer;
		fade_go_scene_plus_scene = go_plus_scene;
	}

	
	void update_menu_main();
	void draw_menu_main()const;

	void update_menu_charm();
	void draw_menu_charm()const;

	void update_menu_item();
	void draw_menu_item()const;

	void update_menu_map();
	void draw_menu_map()const;

	Cur menu_cur_main;
	

	int menu_charm_cur_x = 0;
	int menu_charm_cur_y = 0;
	float menu_charm_cur_x_interval = 0;
	float menu_charm_cur_y_interval = 0;

	String charm_up_down = U"up";

	String menu_charm_select = U"";



	int menu_item_cur_x = 0;
	int menu_item_cur_y = 0;
	float menu_item_cur_x_interval = 0;
	float menu_item_cur_y_interval = 0;


	String item_up_down = U"up";

	String menu_maga_select = U"";
	String menu_weapon_select = U"";
	String menu_item_select = U"";


	Cur menu_cur_item;



	int menu_map_scene = 0;


	

	//Fade_Manager

	void update_fade();
	void draw_fade()const;

	void initialize_fade();


	bool fade_scene_on = false;

	int fade_scene = 0;
	float fade_scene_alpha = 0;
	float fade_scene_count = 0;


	String fade_scene_type = U"";

	String fade_scene_go_scene = U"";

	String fade_scene_go_area = U"";
	Vec2 fade_scene_go_area_pos = { 0,0 };

	
	int fade_go_scene_plus_layer = 0;
	String fade_go_scene_plus_scene = U"";


	//Shader

	PixelShader psWhite;
	mutable ConstantBuffer<WhiteEffectConstants> cbWhite;

	PixelShader psRed;
	mutable ConstantBuffer<WhiteEffectConstants> cbRed;

	PixelShader psViolet;
	mutable ConstantBuffer<WhiteEffectConstants> cbViolet;

	//GameOver
	bool game_over_flag = false;
	float game_over_count = 0;
	int game_over_scene = 0;

	void check_game_over() {
		if (status.get_life() <= 0) {

			game_over_flag = true;

			player.set_game_over_flag(true);
		}
	}

	void update_game_over(float d_time) {

		if (true == game_over_flag) {
			
			game_over_count += d_time;

			if (0 == game_over_scene) {

				if (game_over_count > 3) {

					initialize_fade();

					//fade_scene_type = U"area";
					//fade_scene_go_area = go_name;
					//fade_scene_go_area_pos = { x * 72,y * 72 };
				}
			}
			else if (1 == game_over_scene) {

			}
			else if (2 == game_over_scene) {

			}
		}
	}

	







	//Music


	Array<String> bgm_list;

	Array<String> se_wills;

	struct Se_Lock {

		Se_Lock(String set_name) {
			name = set_name;
		}

		String name = U"";
		float count = 0;
	};

	Array<Se_Lock> se_locks;





	void set_bgm(String set_name) {

		bgm_list.push_back(set_name);


		String adress = U"bgm/" + set_name + U".ogg";
		AudioAsset::Register(set_name, Audio::Stream,adress, Loop::Yes);

	}

	void set_se(String set_name) {

		se_locks.push_back(Se_Lock(set_name));

		String adress = U"music/se/" + set_name + U".mp3";
		AudioAsset::Register(set_name, adress);

	}



	int bgm_volume = 5;
	int se_volume = 5;



	void play_se(String);
	void update_se_main();
	void play_se_main();

	
	void play_bgm(String);

	void stop_bgm();

	void change_bgm_volume();
	void change_se_volume();

	void start_bgm(String);


	//Shop

	bool ev_shop = false;

	void ev_update_shop();
	void ev_draw_shop()const;

	Cur shop_cur;

	String shop_select = U"";
	int shop_price = 0;

	int shop_scene = 0;

	int shop_cur_yes_no = 0;

	float shop_bought_count = 0;

	struct Shop_Goods {

		Shop_Goods(String set_name,int set_price,int set_x,int set_y) {
			name = set_name;
			price = set_price;
			x = set_x;
			y = set_y;
		}

		String name;
		int price = 0;
		int x = 0;
		int y = 0;

		String text = U"";
	};

	Array<Shop_Goods> shop_goods;

	void set_shop_goods(String set_name,int set_price,int set_x,int set_y) {

		shop_goods.push_back(Shop_Goods(set_name, set_price, set_x, set_y));
	}

	void set_shop_goods_text(String name,String set_text) {

		for (auto& goods : shop_goods) {
			if (name == goods.name) {
				goods.text = set_text;
				break;
			}
		}
	}


};
