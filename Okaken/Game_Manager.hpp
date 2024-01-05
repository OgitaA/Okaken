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
#include"Bound_Block.hpp"
#include"Break_Block.hpp"
#include"Needle.hpp"
#include"Slip_Block.hpp"



//List
#include"Enemy_list.hpp"

//Stage_Data
#include"Stage_Data.hpp"

//Area
#include"Area_Data.hpp"
#include"Area_Map.hpp"

//Edit
#include"My_GUI.hpp"
#include"Parts.hpp"


//Status
#include"Status.hpp"


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

	void load_first_data();
	void load_save_data();

	bool once_bgm = false;


	void initialize_debug();

	void register_tiles(const String& name,const FilePathView path, const Size& regionSize, int32 xCount, int32 yCount);

	void update();
	void draw()const;


	//SDFFONT
	//const Font fontSDF_30{ FontMethod::SDF,30, Typeface::Bold };

	const Font fontSDF_40{ FontMethod::SDF,60,U"font/Murecho-Bold.ttf" };






private:

	bool develop = false;

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

	void change_scene_and_bgm(String go_scene,String set_bgm) {

		initialize_fade();

		fade_scene_type = U"scene";
		fade_scene_go_scene = go_scene;

		fade_scene_bgm = set_bgm;
	}

	void change_scene_and_bgm_and_se(String go_scene, String set_bgm,String set_se) {

		initialize_fade();

		fade_scene_type = U"scene";
		fade_scene_go_scene = go_scene;

		fade_scene_bgm = set_bgm;
		fade_scene_se = set_se;
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
	void set_area_data(String set_name, int set_w, int set_h, String set_zone,String set_bgm) {
		area_datas.push_back(Area_Data(set_name, set_w, set_h, set_zone, set_bgm));
	}

	//まとめて音楽を設定します
	void set_zone_bgm(String set_zone,String set_bgm) {

		for (auto& data : area_datas) {
			if (data.belong_zone == set_zone) {
				data.bgm = set_bgm;
			}
		}
	}


	int area_wide = 0;
	int area_height = 0;

	void reset_area() {

		items.clear();
		bullet_enemys.clear();
		my_effects.clear();

		load_area_data();
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
		

		//スクロール制限

		//マップが画面より広い・同じ場合の端

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

		//マップが画面より狭い場合

		if (area_wide < 1920) {
			//Print << U"area_wide::" << area_wide;
			scroll.x = area_wide / 2;
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
	void update_player(float d_time) {

		player.update(d_time);

		if (player.get_se_jump() == true) {
			
			play_se(U"se_jump");
		}
	}
	void draw_player()const {

		//プレイヤーと点滅表示
		{

			const ScopedCustomShader2D shader{ psRed };

			cbRed->strength = player.get_red();

			Graphics2D::SetConstantBuffer(ShaderStage::Pixel, 1, cbRed);

			player.draw();
		}

		//player.get_rect().drawFrame(5, Palette::Orange);
		
	}

	LightBloom player_light_bloom;

	//別のスクロールで描画(別のレンダーテクスチャを使うので)
	void draw_player_light()const {

		if (player.get_violet()>0) {


			{
				{
					auto t = camera.createTransformer();

					ScopedLightBloom target{ player_light_bloom };

					draw_player_violet();
				}

				player_light_bloom.draw(player.get_violet());

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

	LightBloom dash_effect_light_bloom;

	void draw_dash_effect_light()const {

		{
			ScopedLightBloom target{ dash_effect_light_bloom };

			{
				auto t = camera.createTransformer();

				for (auto& effect : dash_effects) {

					{
						const ScopedCustomShader2D shader{ psViolet };

						cbViolet->strength = 1;

						Graphics2D::SetConstantBuffer(ShaderStage::Pixel, 1, cbViolet);

						effect.draw();
					}

				}
			}
		}

		dash_effect_light_bloom.draw(player.get_violet());
	}

	LightBloom jump_effect_light_bloom;

	void draw_jump_effect_light()const {

		{
			ScopedLightBloom target{ jump_effect_light_bloom };

			{
				auto t = camera.createTransformer();

				for (auto& effect : jump_effects) {
					{
						const ScopedCustomShader2D shader{ psViolet };

						cbViolet->strength = 1;

						Graphics2D::SetConstantBuffer(ShaderStage::Pixel, 1, cbViolet);

						effect.draw();
					}

				}
			}


		}

		jump_effect_light_bloom.draw(player.get_violet());
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

		{
			const ScopedCustomShader2D shader{ psWhite };

			for (auto& enemy : enemys) {

				cbWhite->strength = enemy->get_white() * 2;

				Graphics2D::SetConstantBuffer(ShaderStage::Pixel, 1, cbWhite);
				enemy->draw();

			}
		}

		/*
		for (auto& enemy : enemys) {
			enemy->get_hit_rect().drawFrame(10, Palette::Red);
		}*/
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

	//特殊オブジェクト
	class Special_Object {

	public:

		Special_Object(){}

		Special_Object(String set_name,float set_x, float set_y,String set_color) {

			name = set_name;
			pos = { set_x,set_y };
			color = set_color;
		}

		Special_Object(String set_name, float set_x, float set_y) {

			name = set_name;
			pos = { set_x,set_y };
		}

		void draw()const {

			String image_name = U"special_object_" + name;

			TextureAsset(image_name).draw(pos.x * 72, pos.y * 72);
		}

		String get_color()const { return color; }
		String get_name()const { return name; }
		Vec2 get_pos()const { return pos; }

	private:

		String name;
		Vec2 pos;
		String color = U"no";
	};
	Array<Special_Object> special_objects;

	LightBloom object_bloom;

	void draw_special_objects_light()const {

		{
			auto t = camera.createTransformer();

			ScopedLightBloom target{ object_bloom };

			//色をつけて描画
			for (auto& object : special_objects) {

				if (U"red" == object.get_color()) {

					const ScopedCustomShader2D shader{ psRed };

					cbRed->strength = 1;

					Graphics2D::SetConstantBuffer(ShaderStage::Pixel, 1, cbRed);

					object.draw();
				}
				else if (U"green" == object.get_color()) {

					const ScopedCustomShader2D shader{ psGreen };

					cbGreen->strength = 1;

					Graphics2D::SetConstantBuffer(ShaderStage::Pixel, 1, cbGreen);

					object.draw();
				}
				else if (U"brown" == object.get_color()) {

					const ScopedCustomShader2D shader{ psBrown };

					cbBrown->strength = 1;

					Graphics2D::SetConstantBuffer(ShaderStage::Pixel, 1, cbBrown);

					object.draw();
				}
				else if (U"white" == object.get_color()) {

					const ScopedCustomShader2D shader{ psWhite };

					cbWhite->strength = 1;

					Graphics2D::SetConstantBuffer(ShaderStage::Pixel, 1, cbWhite);

					object.draw();
				}
			}
		}

		//発光描画
		object_bloom.draw(1);
	}

	void draw_special_object()const {

		for (auto& object : special_objects) {

			object.draw();
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

		Block_Name(String set_name, int set_x, int set_y) {
			name = set_name;
			x = set_x;
			y = set_y;
		}

		int x = 0;
		int y = 0;
		String name = U"";
	};
	Array<Block_Name> block_names;

	void set_block_name(String name,int x,int y){

		block_names.push_back(Block_Name(name, x, y));
	}

	void make_stage();

	void make_stage_back();

	void make_stage_plus();

	//Action
	Stick stick;

	

	void attack() {


		String direction = player.get_direction();
		float x = player.get_rect().x + player.get_rect().w / 2;
		float y = player.get_rect().y;

		if (KeyX.down() == true) {

			if (player.get_have_stick() == true) {

				if (false == player.get_action_lock() and false == game_over_flag and player.get_attack()) {


					stick.make_attack(direction, x, y);

					player.set_attack_cool_time();

					play_se(U"se_swing4");
				}
			}
		}

		//お祓い棒関係の描画補正
		if (stick.get_exist()) {

			

			stick.set_pos_draw(x,y);


			//プレイヤーの描画用

			player.set_state(U"attack");

			int page = stick.get_page();
			player.set_attack_page(page);

		}

		//あたり判定の調整
		stick.update_attack(direction, x, y);
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

	


	//各種地形データからオブジェクトを生成
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


		int life_left_x = 72;
		int life_left_y = 6;

		TextureAsset(U"life_bar_bottom").draw(life_left_x, life_left_y);
		TextureAsset(U"life_bar_white")(0, 0, hp_white_v, 60).draw(life_left_x, life_left_y);


		float v = 450 * status.get_life() / status.get_life_max();

		if (v > 450) {
			v = 450;
		}

		TextureAsset(U"life_bar_red")(0, 0, v, 60).draw(life_left_x, life_left_y);
		TextureAsset(U"life_bar_frame").draw(life_left_x, life_left_y);

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

		int soul_left_x = 72;
		int soul_left_y = 80;

		for (int i = 0; i < status.get_power_max(); i++) {
			TextureAsset(U"power_soul_empty").draw(soul_left_x + (i * 70), soul_left_y);
		}

		for (int i = 0; i < status.get_power(); i++) {
			TextureAsset(U"power_soul").draw(soul_left_x + (i * 70), soul_left_y);
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

		//財布
		int purse_left_x = 72;

			TextureAsset(U"purse").draw(purse_left_x, 175, ColorF(1, fade));

			const double outlineScale = 0.5;
			const ColorF outlineColor = ColorF(0, 0, 0, fade);

			//fontSDF_40(status.get_money()).draw(TextStyle::Outline(outlineScale, outlineColor), 70+100, 160+2,ColorF(1,fade));
			fontSDF_40(status.get_money()).draw(TextStyle::Outline(outlineScale, outlineColor), purse_left_x + 100, 160 + 2, ColorF(1, 1, 1, fade));
		


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

		play_se(U"アイテム入手");
	}

	







	//Event

	Event_Super event_super;

	float Ev_Delta_Time;

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

	int ev_x = 0;
	int ev_y = 0;

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

						//x,y
						ev_x = event.get_rect().x;
						ev_y = event.get_rect().y;
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

			if (true == message_box.check_end()) {
				ev_scene++;
				z_common();
			}
			else {
				message_box.show_all_text();
			}

			
		}
	}

	void z(int v) {

		if (KeyZ.down()) {

			if (true == message_box.check_end()) {
				ev_scene = v;
				z_common();
			}
			else {
				message_box.show_all_text();
			}
		}
	}

	void z_common() {

		message_box.reset();
	}

	void end() {

		end_common();

		player.set_speed_x_zero();
	}

	void end_common() {

		ev_scene = 0;

		message_box_on = false;

		scene = U"game";

		ev_shop = false;
	}

	void pass() {

		end_common();
	}

	void change_bg(String set_bg) {

		change_bg_common(set_bg);
	}

	void change_bgm(String set_bgm) {

		stop_bgm();
		play_bgm(set_bgm);
	}

	void change_bg_and_bgm(String set_bg,String set_bgm) {

		change_bg_common(set_bg);
		fade_scene_bgm = set_bgm;
	}

	void change_bg_common(String set_bg) {

		initialize_fade_long();
		fade_scene_type = U"bg";
		fade_scene_bg = set_bg;

	}

	void reset_ev_image() {

		//特殊処理
		ev_image = false;
		ev_image_name = U"";
		ev_alpha = 0;
	}

	void next() {
		ev_scene++;
		message_box.reset();
	}
	void next(int v) {
		ev_scene = v;
		message_box.reset();
	}

	float ev_wait_count = 0;

	void wait(float v) {

		ev_wait_count += Delta_Time;

		if (ev_wait_count > v) {
			next();
			ev_wait_count = 0;
		}
	}

	void set_var(String name,int v) {

		event_super.set_var(name, v);
	}

	int get_var(String name) {

		return event_super.get_var(name);
	}

	void go_area(String go_name,int x,int y) {

		go_area_common(go_name, x, y);
		fade_scene_direction = U"none";
	}

	void go_area(String go_name, int x, int y,String direction) {

		go_area_common(go_name, x, y);
		fade_scene_direction = direction;
	}

	void go_area_common(String go_name, int x, int y) {

		initialize_fade();
		go_area_core(go_name, x, y);
	}

	void go_area_long_and_direction_and_color(String go_name, int x, int y, String direction, String color) {

		go_area_common_long(go_name, x, y);
		fade_scene_direction = direction;
		fade_scene_color = color;

	}

	void go_area_common_long(String go_name, int x, int y) {

		initialize_fade_long();
		go_area_core(go_name, x, y);
	}

	void go_area_core(String go_name, int x, int y) {

		fade_scene_type = U"area";
		fade_scene_go_area = go_name;
		fade_scene_go_area_pos = { x * 72,((y + 1) * 72) };

	
	}


	



	void set_bg(String set_bg) {
		ev_bg = set_bg;
	}

	void clear_bg() {
		ev_bg = U"";
	}

	bool ev_image = false;
	String ev_image_name = U"";
	int ev_image_x = 0;
	int ev_image_y = 0;
	float ev_alpha = 0;

	bool ev_plus_text = false;
	String ev_plus_text_text = U"";

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

	void ev_down_under();
	void ev_up_rooftop();



	void ev_enter_first_toilet();
	void ev_exit_first_toilet();
	void ev_enter_second_toilet();
	void ev_exit_second_toilet();
	void ev_enter_third_toilet();
	void ev_exit_third_toilet();
	void ev_enter_fourth_toilet();
	void ev_exit_fourth_toilet();
	void ev_enter_fifth_toilet();
	void ev_exit_fifth_toilet();
	void ev_enter_sixth_toilet();
	void ev_exit_sixth_toilet();

	void ev_enter_okaken();
	void ev_exit_okaken();

	void ev_enter_bunngei();
	void ev_exit_bunngei();

	void ev_enter_sinnbun();
	void ev_exit_sinnbun();

	void ev_enter_housou();
	void ev_exit_housou();

	void ev_enter_tennmon();
	void ev_exit_tennmon();

	void ev_enter_enngeki();
	void ev_exit_enngeki();



	void ev_goback_world_A_1();
	void ev_go_world_A_2();

	

	void ev_talk_test();


	void ev_get_stick();


	//Story
	void ev_story_1();

	void ev_story_2();








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

	void initialize_fade_long();

	void initialize_fade_common();


	void function_fade_game_over();
	void fuction_fade_scene();
	void function_fade_area();
	void function_fade_bg();



	bool fade_scene_on = false;

	int fade_scene = 0;
	float fade_scene_alpha = 0;
	float fade_scene_count = 0;
	float fade_change_time = 0.3;


	String fade_scene_type = U"";

	String fade_scene_go_scene = U"";

	String fade_scene_go_area = U"";
	Point fade_scene_go_area_pos = { 0,0 };

	String fade_scene_direction = U"";

	
	int fade_go_scene_plus_layer = 0;
	String fade_go_scene_plus_scene = U"";

	String fade_scene_bg = U"";

	String fade_scene_bgm = U"none";

	String fade_scene_se = U"none";

	String fade_scene_color = U"black";
	

	//Shader

	PixelShader psWhite;
	mutable ConstantBuffer<WhiteEffectConstants> cbWhite;

	PixelShader psRed;
	mutable ConstantBuffer<WhiteEffectConstants> cbRed;

	PixelShader psViolet;
	mutable ConstantBuffer<WhiteEffectConstants> cbViolet;

	PixelShader psGreen;
	mutable ConstantBuffer<WhiteEffectConstants> cbGreen;

	PixelShader psBrown;
	mutable ConstantBuffer<WhiteEffectConstants> cbBrown;

	//GameOver
	bool game_over_flag = false;
	float game_over_count = 0;
	int game_over_scene = 0;

	float game_over_count_v = 3;

	void check_game_over() {
		if (status.get_life() <= 0 or out_screen_gameover()) {

			if (status.get_life() <= 0) {
				game_over_count_v = 3;
			}
			else if (out_screen_gameover()) {
				game_over_count_v = 2;
			}

			game_over_flag = true;

			player.set_game_over_flag(true);
		}
	}

	void update_game_over(float d_time) {

		if (true == game_over_flag) {
			
			game_over_count += d_time;

			if (0 == game_over_scene) {

				bool go_fade = false;

				if (game_over_count >= game_over_count_v) {

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

	bool out_screen_gameover() {

		if (player.get_rect().topY()>=area_height) {
			return true;
		}
		else if (player.get_rect().bottomY() < 0) {
			return true;
		}

		if (player.get_rect().leftX() < 0) {
			return true;
		}
		else if (player.get_rect().leftX() >= area_wide) {
			return true;
		}

		return false;
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

		String adress = U"se/" + set_name + U".mp3";
		AudioAsset::Register(set_name, adress);
		AudioAsset::Load(set_name);

	}



	int bgm_volume = 5;
	int se_volume = 5;



	void play_se(String);
	void update_se_main();
	void play_se_main();


	String bgm_name = U"";
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

	//Spirit
	void draw_spirit_back()const {
		TextureAsset(U"spirit_back").draw(0, 0);
	}

	//Base
	String back_base_name = U"normal";
	void draw_back_base()const {

		if (back_base_name != U"world") {

			String image_name = U"back_base_" + back_base_name;

			TextureAsset(image_name).draw(0, 0);
		}
	}

	//Blue
	bool world_blue = false;

	//Title

	void update_title();
	void draw_title()const;

	Cur title_cur;
	Cur title_cur_2;


	int title_scene = 1000;
	int title_go =-1;
	bool title_selected = false;
	float title_wait = 0;
	


	//Respawn
	struct Respawn_Point {

		String area = U"";
		int x = 1920 / 2;
		int y = 1080 / 2;
	};

	Respawn_Point respawn_point;

	void update_respawn() {

		for (auto& object : special_objects) {

			if (object.get_name() == U"torii") {
				Rect rect(object.get_pos().x * 72, object.get_pos().y * 72, 6 * 72, 6 * 72);

				if (rect.intersects(player.get_rect())) {
					respawn_point.area = area;
					respawn_point.x = object.get_pos().x + 3;
					respawn_point.y = object.get_pos().y + 4;
					break;
				}
			}
			
		}
	}


	//死亡時にリトライ
	void respawn() {

		area = respawn_point.area;
		int x = (respawn_point.x) * 72 - player.get_rect().w / 2;
		int y = (respawn_point.y ) * 72;
	
		player.set_ground_pos(x, y);
		player.set_is_ground(true);
	}

	void retry();


	//Save
	void save_game() {

		//つづきからにする
		status.set_first_used();

		//再開場所を設定
		status.set_restart_point(area, ev_x, ev_y);

		//進行状況を保存

		//Event
		{

			String adress = U"save_data/event_super.bin";

			// バイナリファイルをオープン
			Serializer<BinaryWriter> writer{ adress };

			if (not writer) // もしオープンに失敗したら
			{
				throw Error{ U"Failed to open" + adress };
			}

			// シリアライズに対応したデータを記録
			writer(event_super);

		}

		//ステータス
		{

			String adress = U"save_data/status.bin";

			// バイナリファイルをオープン
			Serializer<BinaryWriter> writer{ adress };

			if (not writer) // もしオープンに失敗したら
			{
				throw Error{ U"Failed to open" + adress };
			}

			// シリアライズに対応したデータを記録
			writer(status);

		}



	}

	//Load

	void load_game() {

		//Event
		{

			String adress = U"save_data/event_super.bin";

			// バイナリファイルをオープン
			Deserializer<BinaryReader> reader{ adress };

			if (not reader) // もしオープンに失敗したら
			{
				throw Error{ U"Failed to open" + adress };
			}

			// バイナリファイルからシリアライズ対応型のデータを読み込む
			// （Array は自動でリサイズが行われる）
			reader(event_super);

		}

		//ステータス
		{

			String adress = U"save_data/status.bin";

			// バイナリファイルをオープン
			Deserializer<BinaryReader> reader{ adress };

			if (not reader) // もしオープンに失敗したら
			{
				throw Error{ U"Failed to open" + adress };
			}

			// バイナリファイルからシリアライズ対応型のデータを読み込む
			// （Array は自動でリサイズが行われる）
			reader(status);

		}
	}

	void start_game();

	void reset_save_data();
};
