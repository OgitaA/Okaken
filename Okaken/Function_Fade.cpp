#include"Game_Manager.hpp"

void Game_Manager::update_fade() {

	float d_time = Delta_Time;

	float change_time = 0.3;
	float wait_time = 0.1;

	//黒を増やす
	if (fade_scene == 0) {

		fade_scene_alpha += (1 / fade_change_time) * d_time;

		if (fade_scene_alpha >= 1) {
			fade_scene++;

			fade_scene_alpha = 1;
		}
	}

	//黒い画面キープ
	else if (fade_scene == 1) {


		fade_scene_count += d_time;

		if (fade_scene_count >= wait_time) {

			fade_scene++;

			fade_scene_count = 0;

			//各種処理
			if (true == game_over_flag) {

				function_fade_game_over();
			}
			else if (fade_scene_type == U"scene") {

				fuction_fade_scene();
			}
			else if (fade_scene_type == U"area") {

				function_fade_area();	
			}
			else if (fade_scene_type == U"bg") {

				function_fade_bg();
			}

		}

	}

	//黒を減らす
	else if (fade_scene == 2) {

		fade_scene_alpha -= (1/fade_change_time) * d_time;

		//終了処理
		if (fade_scene_alpha <= 0) {

			fade_scene_on = false;

			fade_scene = 0;
			fade_scene_count = 0;
			fade_scene_alpha = 0;

		}
	}
}

void Game_Manager::draw_fade()const {

	/*
	Rect black_rect(0, 0, 1920, 1080);
	black_rect.draw(Color(1, 1, 1, fade_scene_alpha));
    */

	TextureAsset(fade_scene_color).draw(0, 0, ColorF(1, fade_scene_alpha));
}

void Game_Manager::initialize_fade() {

	fade_change_time = 0.6;

	initialize_fade_common();
}

void Game_Manager::initialize_fade_long() {

	fade_change_time = 1.5;

	initialize_fade_common();
}



void Game_Manager::initialize_fade_common() {

	fade_scene_on = true;

	fade_scene = 0;

	fade_scene_count = 0;
	fade_scene_alpha = 0;

	//BGM
	fade_scene_bgm = U"none";
	//SE
	fade_scene_se = U"none";

	//Color
	fade_scene_color = U"black";

	//Option
	fade_go_scene_plus_layer = -1;
	fade_go_scene_plus_scene = U"";
}

void Game_Manager::function_fade_game_over() {

	//体力かいふく
	status.full_life();
	//ゲームオーバー終了
	game_over_flag = false;
	game_over_count = 0;
	game_over_scene = 0;



	player.reset();

	player.set_game_over_flag(false);

	//リスポーン地点に移動
	respawn();
	//ステージデータを読み込み、ステージを再構成
	reset_area();
	//ゲームの進行状況を読み込み
	retry();

	control_scroll();
	//スクロール処理2
	camera.jumpTo(scroll, 1.0);
}



//シーンの変更
void Game_Manager::fuction_fade_scene() {

	//シーン設定
	scene = fade_scene_go_scene;

	if (-1 != fade_go_scene_plus_layer) {

		if (U"menu" == scene) {
			menu_layer = fade_go_scene_plus_layer;
		}
	}

	if (U"" != fade_go_scene_plus_scene) {

		if (U"menu" == scene) {
			menu_scene = fade_go_scene_plus_scene;
		}


	}

	//つづきからの場合、ステージに合わせて一回だけ音楽を変える

	if (false == once_bgm) {

		for (auto& data : area_datas) {
			if (data.name == area) {
			
				change_bgm(data.bgm);
				once_bgm = true;
				break;
			}
		}
	}
	//シーンの変化に合わせて音楽を変える
	else if (fade_scene_bgm != U"none") {

		if (fade_scene_bgm == U"stop") {

			stop_bgm();
		}
		else {
			change_bgm(fade_scene_bgm);
		}

	}

	if (fade_scene_se != U"none") {

		play_se(fade_scene_se);
	}


}


//エリアの変更
void Game_Manager::function_fade_area() {

	area = fade_scene_go_area;

	//player.set_x(fade_scene_go_area_pos.x);
	//player.set_y(fade_scene_go_area_pos.y);

	Print << U"fade_scene_go_area_pos.x::" << fade_scene_go_area_pos.x;
	Print << U"fade_scene_go_area_pos.y::" << fade_scene_go_area_pos.y;

	player.set_ground_pos(fade_scene_go_area_pos.x, fade_scene_go_area_pos.y);

	player.reset_action();

	if (fade_scene_direction != U"none") {
		player.set_direction(fade_scene_direction);
	}

	load_area_data();
	make_stage();

	jump_effects.clear();
	dash_effects.clear();

	stick.reset_action();


	control_scroll();
	camera.jumpTo(scroll, 1.0);

	String next_bgm = U"";

	for (auto& data : area_datas) {
		if (data.name == area) {
			next_bgm = data.bgm;
			break;
		}
	}

	//Print << U"bgm_name::" << bgm_name;
	//Print << U"next_bgm::" << next_bgm;

	//別の曲なら変更
	if (next_bgm != bgm_name) {
		change_bgm(next_bgm);
	}

}

void Game_Manager::function_fade_bg() {

	set_bg(fade_scene_bg);
	next();

	if (fade_scene_bgm != U"none") {
		stop_bgm();
		play_bgm(fade_scene_bgm);
		fade_scene_bgm = U"none";
	}

	//特殊処理
	reset_ev_image();
}

//ロード時も読み込みたい
void Game_Manager::retry() {


	for (auto& item : status.get_have_items()) {

		if (U"お祓い棒" == item.name) {
			player.set_have_stick();
		}
	}
}
