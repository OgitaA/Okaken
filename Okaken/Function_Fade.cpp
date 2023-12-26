#include"Game_Manager.hpp"

void Game_Manager::update_fade() {

	float d_time = Delta_Time;

	float change_time = 0.3;
	float wait_time = 0.1;

	//黒を増やす
	if (fade_scene == 0) {

		fade_scene_alpha += (1/change_time) * d_time;

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
			else if (fade_scene_type == U"scene") {





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

			}
			else if (fade_scene_type == U"area") {

				area = fade_scene_go_area;

				player.set_x(fade_scene_go_area_pos.x);
				player.set_y(fade_scene_go_area_pos.y);

				player.set_ground_pos(fade_scene_go_area_pos.x, fade_scene_go_area_pos.y);

				if (fade_scene_direction != U"none") {
					player.set_direction(fade_scene_direction);
				}

				load_area_data();
				make_stage();


				control_scroll();
				camera.jumpTo(scroll, 1.0);

				
			}

		}

	}

	//黒を減らす
	else if (fade_scene == 2) {

		fade_scene_alpha -= (1/change_time) * d_time;

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

	TextureAsset(U"black").draw(0, 0, ColorF(1, fade_scene_alpha));
}

void Game_Manager::initialize_fade() {

	fade_scene_on = true;

	fade_scene = 0;

	fade_scene_count = 0;
	fade_scene_alpha = 0;

	//Option
	fade_go_scene_plus_layer = -1;
	fade_go_scene_plus_scene = U"";
}

//ロード時も読み込みたい
void Game_Manager::retry() {

	for (auto& ability : status.get_have_ability()) {

		//お祓い棒をもっている
		if (U"stick" == ability) {
			player.set_have_stick();
		}
	}
}
