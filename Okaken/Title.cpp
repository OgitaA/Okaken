#include"Game_Manager.hpp"

void Game_Manager::update_title() {

	if (1000 == title_scene) {
		play_bgm(U"少女霊");
		title_scene = 999;
	}

	if (999 == title_scene) {

		if (KeyZ.down()) {
			title_scene = 0;
			play_se(U"決定");
		}
	}
	else if(0 == title_scene) {

		title_cur.update(se_volume);

		if (KeyZ.down()) {



			//さいしょから
			if (title_cur.get_y() == 0) {

				play_se(U"少女笑い声");

				title_go = 0;
				title_scene++;
			}
			//つづきから
			else if (title_cur.get_y() == 1) {

				play_se(U"少女笑い声");

				title_go = 1;
				title_scene++;
			}
			//せってい
			else if (title_cur.get_y() == 2) {
				title_scene = 3;
				title_cur_2.set_y_zero();
				play_se(U"決定");
			}
			//おしまい
			else if (title_cur.get_y() == 3) {
				play_se(U"キャンセル");
				System::Exit();

			}


		}
		else if (KeyControl.pressed() and KeyC.down()) {

			//develop

			reset_save_data();

			if (true == develop) {
				Print << U"Clear_Save_Data!!";
			}
		}

	}
	else if (1 == title_scene) {

		title_wait += Scene::DeltaTime();

		if (title_wait >= 2) {
			title_scene++;
			title_wait = 0;
		}
	}

	if (2 == title_scene) {

		if (0 == title_go) {

			event_ID = 1001;
			ev_scene = 0;

			set_bg(U"dark");

			//play_se(U"学校のチャイム");

			//つづきから用のbgm処理を行わない
			once_bgm = true;

			area = U"world_A_1";
			start_game();
			change_scene_and_bgm(U"event",U"stop");
		}
		else if (1 == title_go) {

			load_save_data();

			//セーブデータがある
			if (false == status.get_first()) {

				

				start_game();
				change_scene(U"game");
			}
			//セーブデータがない
			else if (true == status.get_first()) {

			}
		}
	}

	//設定
	else if (3==title_scene) {

		title_cur_2.update(se_volume);

		bool back = false;

		//BGM
		if (0 == title_cur_2.get_y()) {

			bool changed = false;


			if (KeyLeft.down()) {
				bgm_volume--;
				changed = true;
			}
			else if (KeyRight.down()) {
				bgm_volume++;
				changed = true;
			}

			if (bgm_volume < 0) {
				bgm_volume = 0;
				changed = false;
			}
			else if (bgm_volume > 10) {
				bgm_volume = 10;
				changed = false;
			}

			if (true == changed) {
				change_bgm_volume();
				play_se(U"カーソル");
			}
		}
		//SE
		else if (1 == title_cur_2.get_y()) {

			bool changed = false;

			if (KeyLeft.down()) {
				se_volume--;
				changed = true;
			}
			else if (KeyRight.down()) {
				se_volume++;
				changed = true;
			}

			if (se_volume < 0) {
				se_volume = 0;
				changed = false;
			}
			else if (se_volume > 10) {
				se_volume = 10;
				changed = false;
			}

			if (true == changed) {
				play_se(U"カーソル");
				//change_se_volume();
			}
		}
		else if (title_cur_2.get_y() == 2) {

			if (KeyZ.down()) {

				back = true;
				play_se(U"キャンセル");
			}
		}

		if (KeyX.down()) {
			back = true;
		}

		if (true == back) {
			title_scene = 0;
		}
	}
}

void Game_Manager::draw_title()const {

	TextureAsset(U"title_back").draw(0, 0);

	const int  edge_x = 1480;
	const int edge_y = 550;
	const int blank_y = 120;

	if (title_scene < 3) {

		TextureAsset(U"title_cur").draw(edge_x - 100, edge_y + blank_y * title_cur.get_y());

		{
			ColorF color = Palette::White;

			if (0 == title_go) {
				//color = ColorF(0.34,0,85);
				color = Palette::Red;
			}

			FontAsset(U"Mur_50")(U"はじめから").draw(edge_x, edge_y, color);
		}

		{
			ColorF color = Palette::White;

			if (1 == title_go) {
				//color = ColorF(0.14, 0, 55, 1);
				color = Palette::Red;
			}


			FontAsset(U"Mur_50")(U"つづきから").draw(edge_x, edge_y + blank_y, color);
		}


		FontAsset(U"Mur_50")(U"せってい").draw(edge_x, edge_y + blank_y * 2);

		FontAsset(U"Mur_50")(U"おしまい").draw(edge_x, edge_y + blank_y * 3);


	}
	else if (title_scene == 3) {

		TextureAsset(U"title_cur").draw(edge_x - 100, edge_y + blank_y * (title_cur_2.get_y() + 1));

		FontAsset(U"Mur_50")(U"左右キーで変更").drawAt(1920 - 640 + 320, edge_y + blank_y * 0 + 30, Palette::Yellow);

		FontAsset(U"Mur_50")(U"BGM").draw(edge_x, edge_y + blank_y * 1);
		FontAsset(U"Mur_50")(Format(bgm_volume)).draw(edge_x + 250, edge_y + blank_y * 1);

		FontAsset(U"Mur_50")(U"SE").draw(edge_x, edge_y + blank_y * 2);
		FontAsset(U"Mur_50")(Format(se_volume)).draw(edge_x + 250, edge_y + blank_y * 2);

		FontAsset(U"Mur_50")(U"もどる").draw(edge_x, edge_y + blank_y * 3);

	}
	else if (title_scene == 999) {

		FontAsset(U"Mur_50")(U"Zキーでスタート").drawAt(1920 - 640 + 320, edge_y + blank_y * 1.5);
	}

}

