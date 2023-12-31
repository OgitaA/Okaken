﻿#include"Game_Manager.hpp"

Game_Manager::Game_Manager() {

	//画面最大化
	// ウィンドウを最大化
	Scene::Resize(1920, 1080);
	Scene::SetResizeMode(ResizeMode::Keep);
	Window::SetFullscreen(true);

	initialize();

	scene = U"title";

	area = U"under_1";

	develop = true;

	//開発用
	if (true == develop) {

		//sceneもゲームから
		scene = U"game";

		//Editorを最初から使う
		edit = true;

		//Editor用初期化
		{
			load_area_data();

			make_area_edit();

			camera_edit.jumpTo({ scroll_edit.x + 1920 / 2,scroll_edit.y + 1080 / 2 }, 1.0);
		}

		//camera.jumpTo(player.get_camera_target_pos(), 1.0);

	}	
}

void Game_Manager::update() {

	if (KeyD.down()) {
		if (false == develop) {
			develop = true;
		}
		else if (true == develop) {
			develop = false;
		}
	}

	//開発中出ない場合カーソルを消す
	if (false == develop) {
		//Cursor::RequestStyle(CursorStyle::Hidden);
	}


	Delta_Time = Scene::DeltaTime() * Game_Speed;

	if (false == fade_scene_on) {//フェイド処理中は操作を受け付けない


		if (false == edit) {

			if (U"game" == scene) {

				update_game();
			}
			else if (U"menu" == scene) {

				update_menu();
			}

			if (U"event" == scene) {

				update_event();
				//Event状態更新
				update_event_state();
				update_UI();
			}

			if (U"title" == scene) {
				update_title();
			}
			
		}
		else if (true == edit) {

			update_edit();
		}

		//Editから切り替え
		if (KeyE.down()) {

			change_edit();

			if (false == edit) {
				//optimize_edit();
				make_stage();
				player.set_x(player_data.x);
				player.set_y(player_data.y);

			}
		}

	}
	else {
		update_fade();
	}


	update_se_main();

}

void Game_Manager::draw()const {
	
	if (false == edit) {

		if (U"game" == scene) {
			draw_game();
		}
		else if (U"menu" == scene) {
			draw_menu();
		}
		else if (U"event"==scene) {
			draw_game();
			draw_event();

		}

		if (U"title" == scene) {
			draw_title();
		}
		
	}
	else if (true == edit) {

		draw_edit();		
	}

	if (true == fade_scene_on) {

		draw_fade();
	}

}

void Game_Manager::update_game() {

	camera.update();

	float d_time = Delta_Time;

	

	update_blocks(d_time);

	//Player
	update_player(d_time);
	attack();
	stick.update(d_time);
	update_jump_effects(d_time);
	update_dash_effects(d_time);

	update_enemys(d_time);
	update_items(d_time);
	update_events(d_time);
	update_bullet_enemys(d_time);

	update_my_effects(d_time);
	update_soul_bigs(d_time);
	update_circle_effects(d_time);

	//blockとの処理
	vs();

	vs_player_enemy();
	vs_stick_enemy();
	vs_stick_block();

	delete_enemy();

	update_make_shot_enemy();

	delete_my_effects();
	delete_soul_bigs();
	delete_circle_effects();

	//Event起動
	start_event();
	//Event状態更新
	update_event_state();

	//Menu起動
	start_menu();

	//リスポーン登録
	update_respawn();



	//ゲームオーバー処理
	check_game_over();
	update_game_over(d_time);


	//スクロール処理
	control_scroll();
	//スクロール処理2
	camera.jumpTo(scroll, 1.0);

	//UIの更新
	update_UI();

	//クイックマップ
	update_show_quick_map();

	
}

void Game_Manager::draw_game()const {

	/*
	// レンダーテクスチャを黒色でクリア
	renderTexture.clear(ColorF{ 0.0 });

	{//アンチエイリアスを消すためにレンダーテクスチャを使う
		const ScopedRenderStates2D states{ SamplerState::ClampNearest };
		const ScopedRenderTarget2D target{ renderTexture };

		//特殊な背景
		draw_back_base();

		{
			auto t = camera.createTransformer();

			draw_tiles();
			draw_decos();
			draw_blocks();

			draw_events();
		}
	}


	renderTexture.draw();
    */

	//特殊な背景
	draw_back_base();

	{
		auto t = camera.createTransformer();

		draw_tiles();
		draw_decos();
		draw_blocks();

		draw_events();
	}

	if (true == world_blue) {
		Rect blue(0, 0, 1920, 1080);
		blue.draw(ColorF(0, 0, 1, 0.1));
	}


	//発光するオブジェクト
	draw_special_objects_light();
	{
		auto t = camera.createTransformer();
		draw_special_object();
	}

	

	{
		auto t = camera.createTransformer();
		draw_bullet_enemys();
	}

	//ダッシュエフェクト
	//draw_dash_effect_light();
	{
		auto t = camera.createTransformer();
		draw_dash_effects();
	}


	//ジャンプエフェクト
	//draw_jump_effect_light();
	{
		auto t = camera.createTransformer();
		draw_jump_effects();
	}

	draw_player_light();


	{
		auto t = camera.createTransformer();

		draw_player();

		//player.get_rect().draw(ColorF(1, 0, 0, 0.5));
		
		draw_circle_effects();

		draw_enemys();

		stick.draw();
	
		player.draw_stick();

		draw_items();

		draw_my_effects();
		
	}
	
	
	

	draw_UI();

	draw_show_quick_map();

	if (true == develop) {

		//カメラデバッグ用
		{
			Circle circle(1920 / 2, 1080 / 2, 5);
			circle.draw(Palette::Green);
		}
	}

	
}


void Game_Manager::vs() {

	//block
	vs_player();
	vs_enemys();
	vs_items();
	vs_bullets();

	vs_player_enemy();
	vs_player_item();
}

void Game_Manager::vs_player() {

	//プレイヤーを空中に設定
	player.set_is_ground(false);




	//プレイヤーとブロック

	RectF p_rect = player.get_rect();
	RectF p_rect_old = player.get_rect_old();

	float move_x = float(p_rect.x - p_rect_old.x);
	float move_y = float(p_rect.y - p_rect_old.y);

	RectF p_rect_moved_x = p_rect_old.movedBy(move_x, 0);
	RectF p_rect_moved_y = p_rect_old.movedBy(0, move_y);

	for (auto& block : blocks) {

		//通常ブロックの場合
		if (block->get_type() == Block_Type::E_Normal or block->get_normal_colission()) {

			RectF b_rect = block->get_rect();

			if (p_rect.intersects(b_rect)) {

				bool hit_x = false;
				bool hit_y = false;

				//プレイヤーが右に移動している時
				if (move_x > 0) {

					//X軸のみ動かしたプレイヤーとブロックの判定
					if (p_rect_moved_x.intersects(b_rect)) {

						player.set_x(b_rect.x - player.get_wide());

						player.set_speed_x_zero();

						player.set_wall(U"right");

						hit_x = true;
					}
				}

				//プレイヤーが左に移動している時
				else if (move_x < 0) {

					//X軸のみ動かしたプレイヤーとブロックの判定
					if (p_rect_moved_x.intersects(b_rect)) {

						player.set_x(b_rect.x + b_rect.w);

						player.set_speed_x_zero();

						player.set_wall(U"left");

						hit_x = true;
					}
				}


				//プレイヤーが下に移動している時
				if (move_y > 0) {

					//Y軸のみ動かしたプレイヤーとブロックの判定
					if (p_rect_moved_y.intersects(b_rect)) {

						player.set_y(b_rect.y - player.get_height());

						player.function_ground();

						vs_player_plus_down(block->get_type());

						hit_y = true;
					}
				}

				//プレイヤーが上に移動している時
				else if (move_y < 0) {

					//Y軸のみ動かしたプレイヤーとブロックの判定
					if (p_rect_moved_y.intersects(b_rect)) {

						player.set_y(b_rect.y + b_rect.h);


						//重力加速度を無くす
						player.set_speed_y_zero();


						

						hit_y = true;
					}
				}

				//1フレーム前のX軸とY軸のみ、ずらした結果、どちらも当たってない（角付近の判定）
				if (false == hit_x and false == hit_y) {

					//角かチェック
					{
						//このブロックの配置座標は？
						int x = block->get_x();
						int y = block->get_y();

						//上からの移動チェック
						if (move_y > 0) {

							//一個上は
							int v_x = x;
							int v_y = y - 1;

							bool exist = false;

							for (auto& v_b : blocks) {

								//あったら
								if (v_x == v_b->get_x() and v_y == v_b->get_y()) {

									exist = true;
									break;
								}
							}

							//無い
							if (false==exist) {

								//上に押し出し

								player.set_y(b_rect.y - player.get_height());


								player.function_ground();
							}

						}
						//下からの移動チェック
						else if (move_y < 0) {

							//一個下は
							int v_x = x;
							int v_y = y + 1;

							bool exist = false;

							for (auto& v_b : blocks) {

								//あったら
								if (v_x == v_b->get_x() and v_y == v_b->get_y()) {

									exist = true;
									break;
								}
							}

							//無い
							if (false == exist) {

								player.set_y(b_rect.y + b_rect.h);


								//重力加速度を無くす
								player.set_speed_y_zero();
							}

							
						}
					}

				

				}
			}
		}

		//一方通行の足場の場合
		else if (block->get_type() == Block_Type::E_One_Way_Floor) {

			RectF b_rect = block->get_rect();

			if (p_rect.intersects(b_rect)) {


				//下方向のみ判定

				//プレイヤーが下に移動している時
				if (move_y > 0) {

					//Y軸のみ動かしたプレイヤーとブロックの判定
					if (p_rect_moved_y.intersects(b_rect)) {

						//ワープ対策
						if (p_rect_moved_y.bottomY() < b_rect.topY() + 10) {

							player.set_y(b_rect.y - player.get_height());

							player.function_ground();

						}
					}
				}
			}
		}

		//移動床の場合
		else if (block->get_type() == Block_Type::E_Move_Floor) {



			RectF b_rect_old = block->get_rect_old();

			if (p_rect.intersects(b_rect_old)) {



				//下方向のみ判定

				//プレイヤーが下に移動している時
				if (move_y > 0) {

					//Y軸のみ動かしたプレイヤーと<移動前の>ブロックの判定
					if (p_rect_moved_y.intersects(b_rect_old)) {

						//ワープ対策
						if (p_rect_moved_y.bottomY() < b_rect_old.topY() + 10) {

							player.set_y(b_rect_old.y - player.get_height());


							player.function_ground();

							//移動床の移動分をプレイヤーに加える

							RectF b_rect = block->get_rect();

							Vec2 move = b_rect.pos - b_rect_old.pos;

							player.plus_pos(move);



							//移動後の足場と判定

							//Y軸のみ動かしたプレイヤーと<移動後の>ブロックの判定
							if (p_rect_moved_y.intersects(b_rect)) {

								player.set_y(b_rect.y - player.get_height());
							}
						}
					}
				}
			}
		}

		//トゲなら
		else if (block->get_type() == Block_Type::E_Needle) {

			RectF b_rect = block->get_rect();

			//当たったら
			if (p_rect.intersects(b_rect)) {
				damage_player(1, U"none");
			}
		}
	}







	//Eventのブロックとも判定(角の処理省略)
	for (auto& event : events) {

		if (event.get_collision()) {

			RectF e_rect = event.get_rect();

			if (p_rect.intersects(e_rect)) {

				bool hit_x = false;
				bool hit_y = false;

				//プレイヤーが右に移動している時
				if (move_x > 0) {

					//X軸のみ動かしたプレイヤーとブロックの判定
					if (p_rect_moved_x.intersects(e_rect)) {

						player.set_x(e_rect.x - player.get_wide());

						player.set_speed_x_zero();

						player.set_wall(U"right");

						hit_x = true;
					}
				}

				//プレイヤーが左に移動している時
				else if (move_x < 0) {

					//X軸のみ動かしたプレイヤーとブロックの判定
					if (p_rect_moved_x.intersects(e_rect)) {

						player.set_x(e_rect.x + e_rect.w);

						player.set_speed_x_zero();

						player.set_wall(U"left");

						hit_x = true;
					}
				}


				//プレイヤーが下に移動している時
				if (move_y > 0) {

					//Y軸のみ動かしたプレイヤーとブロックの判定
					if (p_rect_moved_y.intersects(e_rect)) {

						player.set_y(e_rect.y - player.get_height());

						player.function_ground();

						//vs_player_plus_down(block->get_type());

						hit_y = true;
					}
				}

				//プレイヤーが上に移動している時
				else if (move_y < 0) {

					//Y軸のみ動かしたプレイヤーとブロックの判定
					if (p_rect_moved_y.intersects(e_rect)) {

						player.set_y(e_rect.y + e_rect.h);


						//重力加速度を無くす
						player.set_speed_y_zero();




						hit_y = true;
					}
				}

				/*

				//1フレーム前のX軸とY軸のみ、ずらした結果、どちらも当たってない（角付近の判定）
				if (false == hit_x and false == hit_y) {

					//角かチェック
					{
						//このブロックの配置座標は？
						int x = block->get_x();
						int y = block->get_y();

						//上からの移動チェック
						if (move_y > 0) {

							//一個上は
							int v_x = x;
							int v_y = y - 1;

							bool exist = false;

							for (auto& v_b : blocks) {

								//あったら
								if (v_x == v_b->get_x() and v_y == v_b->get_y()) {

									exist = true;
									break;
								}
							}

							//無い
							if (false == exist) {

								//上に押し出し

								player.set_y(b_rect.y - player.get_height());


								player.function_ground();
							}

						}
						//下からの移動チェック
						else if (move_y < 0) {

							//一個下は
							int v_x = x;
							int v_y = y + 1;

							bool exist = false;

							for (auto& v_b : blocks) {

								//あったら
								if (v_x == v_b->get_x() and v_y == v_b->get_y()) {

									exist = true;
									break;
								}
							}

							//無い
							if (false == exist) {

								player.set_y(b_rect.y + b_rect.h);


								//重力加速度を無くす
								player.set_speed_y_zero();
							}


						}
					}



				}*/
			}
		}
	}

}




void Game_Manager::vs_enemys() {

	for (auto& enemy : enemys) {

		//敵を空中に設定
		enemy->set_is_ground(false);



		//エネミーとブロック

		RectF e_rect = enemy->get_rect();
		RectF e_rect_old = enemy->get_rect_old();

		float move_x = float(e_rect.x - e_rect_old.x);
		float move_y = float(e_rect.y - e_rect_old.y);

		RectF e_rect_moved_x = e_rect_old.movedBy(move_x, 0);
		RectF e_rect_moved_y = e_rect_old.movedBy(0, move_y);


		//各種設定
		bool turn = false;


		for (auto& block : blocks) {

			//通常ブロックの場合
			if (block->get_type() == Block_Type::E_Normal or block->get_normal_colission()) {

				RectF b_rect = block->get_rect();

				if (e_rect.intersects(b_rect)) {

					bool hit_x = false;
					bool hit_y = false;

					//エネミーが右に移動している時
					if (move_x > 0) {

						//X軸のみ動かしたプレイヤーとブロックの判定
						if (e_rect_moved_x.intersects(b_rect)) {

							enemy->set_x(b_rect.x - enemy->get_wide());

							enemy->set_wall(U"right");

							turn = true;

							hit_x = true;
						}
					}

					//エネミーが左に移動している時
					else if (move_x < 0) {

						//X軸のみ動かしたエネミーとブロックの判定
						if (e_rect_moved_x.intersects(b_rect)) {

							enemy->set_x(b_rect.x + b_rect.w);

							enemy->set_wall(U"left");

							turn = true;

							hit_x = true;
						}
					}


					//エネミーが下に移動している時
					if (move_y > 0) {

						//Y軸のみ動かしたエネミーとブロックの判定
						if (e_rect_moved_y.intersects(b_rect)) {

							enemy->set_y(b_rect.y - enemy->get_height());


							//エネミーが地面に接触
							enemy->set_is_ground(true);

							//重力加速度を無くす
							enemy->set_speed_y_zero();

							hit_y = true;
						}
					}

					//エネミーが上に移動している時
					else if (move_y < 0) {

						//Y軸のみ動かしたエネミーーとブロックの判定
						if (e_rect_moved_y.intersects(b_rect)) {

							enemy->set_y(b_rect.y + b_rect.h);


							//重力加速度を無くす
							enemy->set_speed_y_zero();

							hit_y = true;
						}
					}

					//1フレーム前のX軸とY軸のみ、ずらした結果、どちらも当たってない（角付近の判定）
					if (false == hit_x and false == hit_y) {

						//角かチェック
						{
							//このブロックの配置座標は？
							int x = block->get_x();
							int y = block->get_y();

							//上からの移動チェック
							if (move_y > 0) {

								//一個上は
								int v_x = x;
								int v_y = y - 1;

								bool exist = false;

								for (auto& v_b : blocks) {

									//あったら
									if (v_x == v_b->get_x() and v_y == v_b->get_y()) {

										exist = true;
										break;
									}
								}

								//無い
								if (false == exist) {

									//上に押し出し

									enemy->set_y(b_rect.y - enemy->get_height());


									//エネミーーが地面に接触
									enemy->set_is_ground(true);

									//重力加速度を無くす
									enemy->set_speed_y_zero();
								}

							}
							//下からの移動チェック
							else if (move_y < 0) {

								//一個下は
								int v_x = x;
								int v_y = y + 1;

								bool exist = false;

								for (auto& v_b : blocks) {

									//あったら
									if (v_x == v_b->get_x() and v_y == v_b->get_y()) {

										exist = true;
										break;
									}
								}

								//無い
								if (false == exist) {

									enemy->set_y(b_rect.y + b_rect.h);


									//重力加速度を無くす
									enemy->set_speed_y_zero();
								}


							}
						}



					}
				}
			}

			//一方通行の足場の場合
			else if (block->get_type() == Block_Type::E_One_Way_Floor) {

				RectF b_rect = block->get_rect();

				if (e_rect.intersects(b_rect)) {


					//下方向のみ判定

					//プレイヤーが下に移動している時
					if (move_y > 0) {

						//Y軸のみ動かしたプレイヤーとブロックの判定
						if (e_rect_moved_y.intersects(b_rect)) {

							//ワープ対策
							if (e_rect_moved_y.bottomY() < b_rect.topY() + 10) {

								enemy->set_y(b_rect.y - enemy->get_height());


								//プレイヤーが地面に接触
								enemy->set_is_ground(true);

								//重力加速度を無くす
								enemy->set_speed_y_zero();




							}
						}
					}
				}
			}

			//移動床の場合
			else if (block->get_type() == Block_Type::E_Move_Floor) {



				RectF b_rect_old = block->get_rect_old();

				if (e_rect.intersects(b_rect_old)) {



					//下方向のみ判定

					//プレイヤーが下に移動している時
					if (move_y > 0) {

						//Y軸のみ動かしたプレイヤーと<移動前の>ブロックの判定
						if (e_rect_moved_y.intersects(b_rect_old)) {

							//ワープ対策
							if (e_rect_moved_y.bottomY() < b_rect_old.topY() + 10) {

							    enemy->set_y(b_rect_old.y - enemy->get_height());


								//プレイヤーが地面に接触
								enemy->set_is_ground(true);

								//重力加速度を無くす
								enemy->set_speed_y_zero();


								//移動床の移動分をプレイヤーに加える

								RectF b_rect = block->get_rect();

								Vec2 move = b_rect.pos - b_rect_old.pos;

								//player.plus_pos(move);



								//移動後の足場と判定

								//Y軸のみ動かしたプレイヤーと<移動後の>ブロックの判定
								if (e_rect_moved_y.intersects(b_rect)) {

									enemy->set_y(b_rect.y - enemy->get_height());
								}
							}
						}
					}
				}
			}
		}

		//向きを変える
		if (true == turn) {

			enemy->turn_direction();
		
		}

	}
}

void Game_Manager::vs_items() {

	for (auto& item : items) {

	



		//アイテムとブロック

		RectF i_rect = item.get_rect();
		RectF i_rect_old = item.get_rect_old();

		float move_x = float(i_rect.x - i_rect_old.x);
		float move_y = float(i_rect.y - i_rect_old.y);

		RectF i_rect_moved_x = i_rect_old.movedBy(move_x, 0);
		RectF i_rect_moved_y = i_rect_old.movedBy(0, move_y);


		


		for (auto& block : blocks) {

			//通常ブロックの場合
			if (block->get_type() == Block_Type::E_Normal or block->get_normal_colission()) {

				RectF b_rect = block->get_rect();

				if (i_rect.intersects(b_rect)) {

					bool hit_x = false;
					bool hit_y = false;

					//エネミーが右に移動している時
					if (move_x > 0) {

						//X軸のみ動かしたプレイヤーとブロックの判定
						if (i_rect_moved_x.intersects(b_rect)) {

							item.set_x(b_rect.x - item.get_wide());

							

							hit_x = true;
						}
					}

					//プレイヤーが左に移動している時
					else if (move_x < 0) {

						//X軸のみ動かしたプレイヤーとブロックの判定
						if (i_rect_moved_x.intersects(b_rect)) {

							item.set_x(b_rect.x + b_rect.w);

							

							hit_x = true;
						}
					}


					//プレイヤーが下に移動している時
					if (move_y > 0) {

						//Y軸のみ動かしたプレイヤーとブロックの判定
						if (i_rect_moved_y.intersects(b_rect)) {

							item.set_y(b_rect.y - item.get_height());


							//プレイヤーが地面に接触
							//item.set_is_ground(true);

							//重力加速度を無くす
							item.set_speed_y_zero();

							//横の加速も消す
							item.set_speed_x_zero();

							hit_y = true;
						}
					}

					//プレイヤーが上に移動している時
					else if (move_y < 0) {

						//Y軸のみ動かしたプレイヤーとブロックの判定
						if (i_rect_moved_y.intersects(b_rect)) {

							item.set_y(b_rect.y + b_rect.h);


							//重力加速度を無くす
							item.set_speed_y_zero();

							//横の加速も消す
							//item.set_speed_x_zero();

							hit_y = true;
						}
					}

					//1フレーム前のX軸とY軸のみ、ずらした結果、どちらも当たってない（角付近の判定）
					if (false == hit_x and false == hit_y) {

						//角かチェック
						{
							//このブロックの配置座標は？
							int x = block->get_x();
							int y = block->get_y();

							//上からの移動チェック
							if (move_y > 0) {

								//一個上は
								int v_x = x;
								int v_y = y - 1;

								bool exist = false;

								for (auto& v_b : blocks) {

									//あったら
									if (v_x == v_b->get_x() and v_y == v_b->get_y()) {

										exist = true;
										break;
									}
								}

								//無い
								if (false == exist) {

									//上に押し出し

									item.set_y(b_rect.y - player.get_height());


									//プレイヤーが地面に接触
									//enemy->set_is_ground(true);

									//重力加速度を無くす
									item.set_speed_y_zero();

									//横の加速も消す
									item.set_speed_x_zero();
								}

							}
							//下からの移動チェック
							else if (move_y < 0) {

								//一個下は
								int v_x = x;
								int v_y = y + 1;

								bool exist = false;

								for (auto& v_b : blocks) {

									//あったら
									if (v_x == v_b->get_x() and v_y == v_b->get_y()) {

										exist = true;
										break;
									}
								}

								//無い
								if (false == exist) {

									item.set_y(b_rect.y + b_rect.h);


									//重力加速度を無くす
									item.set_speed_y_zero();

									//横の加速も消す
									item.set_speed_x_zero();
								}


							}
						}



					}
				}
			}

			//一方通行の足場の場合
			else if (block->get_type() == Block_Type::E_One_Way_Floor) {

				RectF b_rect = block->get_rect();

				if (i_rect.intersects(b_rect)) {


					//下方向のみ判定

					//プレイヤーが下に移動している時
					if (move_y > 0) {

						//Y軸のみ動かしたプレイヤーとブロックの判定
						if (i_rect_moved_y.intersects(b_rect)) {

							//ワープ対策
							if (i_rect_moved_y.bottomY() < b_rect.topY() + 10) {

								item.set_y(b_rect.y - item.get_height());


								//プレイヤーが地面に接触
								//enemy->set_is_ground(true);

								//重力加速度を無くす
								item.set_speed_y_zero();

								//横の加速も消す
								item.set_speed_x_zero();


							}
						}
					}
				}
			}

			//移動床の場合
			else if (block->get_type() == Block_Type::E_Move_Floor) {



				RectF b_rect_old = block->get_rect_old();

				if (i_rect.intersects(b_rect_old)) {



					//下方向のみ判定

					//プレイヤーが下に移動している時
					if (move_y > 0) {

						//Y軸のみ動かしたプレイヤーと<移動前の>ブロックの判定
						if (i_rect_moved_y.intersects(b_rect_old)) {

							//ワープ対策
							if (i_rect_moved_y.bottomY() < b_rect_old.topY() + 10) {

								item.set_y(b_rect_old.y - item.get_height());


								//プレイヤーが地面に接触
								//item.set_is_ground(true);

								//重力加速度を無くす
								item.set_speed_y_zero();

								//横の加速も消す
								item.set_speed_x_zero();


								//移動床の移動分をプレイヤーに加える

								RectF b_rect = block->get_rect();

								Vec2 move = b_rect.pos - b_rect_old.pos;

								//player.plus_pos(move);



								//移動後の足場と判定

								//Y軸のみ動かしたプレイヤーと<移動後の>ブロックの判定
								if (i_rect_moved_y.intersects(b_rect)) {

									item.set_y(b_rect.y - item.get_height());
								}
							}
						}
					}
				}
			}
		}

	

	}
}

void Game_Manager::vs_bullets() {

	bullet_enemys.remove_if([&](Bullet_Enemy bullet) {

		for (auto& block : blocks) {

			if (bullet.get_circle().intersects(block->get_rect())) {
				return true;
			}
		}

	    return false;

    });
}

void Game_Manager::vs_player_enemy() {

	for (auto& enemy : enemys) {

		if (player.get_rect().intersects(enemy->get_hit_rect())) {

			//エネミーの状態を変更する
			enemy->set_state();

			String direction = U"";

			if (enemy->get_hit_rect().x <= player.get_rect().x) {

				direction = U"right";
			}
			else {
				direction = U"left";
			}

			if (player.get_muteki_count() <= 0) {
				damage_player(1, direction);
			}
			break;
		}
	}
}

void Game_Manager::vs_player_item() {

	items.remove_if([&](Item item) {

		if (player.get_rect().intersects(item.get_rect())) {

			String name = item.get_name();

			if (U"heart" == name) {

				status.plus_life(1);
			}
			else if (U"soul" == name) {
				
				int soul_count = status.get_power();

				if (soul_count < 5) {

					status.plus_power(1);

					soul_bigs.push_back(My_Effect(U"soul_big", 72 + ((soul_count) * 70) + 2, 80));
				}

			}
			else if (U"coin" == name){

				int v = item.get_v();
			
				//status.plus_money(v);
				plus_will_money(v);

				play_se(U"お金");
			}
			else {
				//status.plus_item(item.get_name(), 1);
			}

			return true;
		}

	    return false;
	});
}

void Game_Manager::vs_stick_enemy() {

	if (stick.get_exist() == true) {

		for (auto& enemy : enemys) {


			bool hit = false;

			for (auto& tri : stick.get_hit_triangle()) {

				if (tri.intersects(enemy->get_hit_rect())) {
					hit = true;
					break;
				}
			}

				
			if (true == hit) {

				if (enemy->get_muteki() == false) {

					int power = 10;

					float magnification = 1;

					magnification += 0.2 * status.get_power();

					power *= magnification;



					enemy->damage(power);
					enemy->set_knock_back(stick.get_direction());
				}
			}
		}
	}
}

void Game_Manager::vs_stick_block() {

	if (stick.get_exist() == true) {

		blocks.remove_if([&](const auto& block) {

			if (block->get_type() == Block_Type::E_Break) {

				bool hit = false;

				for (auto& tri : stick.get_hit_triangle()) {

					if (tri.intersects(block->get_rect())) {
						hit = true;
						break;
					}
				}



				if (true == hit) {

					RectF r = block->get_rect();

					my_effects.push_back(My_Effect(U"break_block", r.centerX() - 50, r.centerY() - 50));

					play_se(U"ブロック破壊");

					return true;
				}

			}

		return false;
		});

	}
}




void Game_Manager::vs_player_plus_down(Block_Type block_type) {

	if (block_type == Block_Type::E_Slip) {
		player.set_slip();
	}
	else if (block_type == Block_Type::E_Bound) {
		player.set_bound();
	}
}
