#include"Game_Manager.hpp"

void Game_Manager::update_event() {

	Ev_Delta_Time = Scene::DeltaTime();

	update_event_main();

	if (true == message_box_on) {

		message_box.update(Ev_Delta_Time);
	}
}

void Game_Manager::draw_event()const {

	if (ev_bg != U"") {
		String image_name = U"bg_" + ev_bg;
		TextureAsset(image_name).draw(0, 0);
	}

	if (true == ev_shop) {
		ev_draw_shop();
	}

	if (true == message_box_on) {
		message_box.draw();
	}

	//最初のロゴ用
	if (true == ev_image) {

		TextureAsset(ev_image_name).draw(ev_image_x, ev_image_y,ColorF(ev_alpha));
	}

	//最初の文字用
	if (true == ev_plus_text) {
		FontAsset(U"BIZ_MIN_50")(U"Zキーで次へ").draw(1400, 900);
	}
}

void Game_Manager::update_event_main() {

	//セーブポイント
	if (0 == event_ID) {
		ev_save_point();
	}
	//階段
	else if (1 == event_ID) {
		ev_up_first();
	}
	else if (2 == event_ID) {
		ev_up_second();
	}
	else if (3 == event_ID) {
		ev_up_third();
	}
	else if (4 == event_ID) {
		ev_up_fourth();
	}
	else if (5 == event_ID) {
		ev_up_fifth();
	}
	else if (6 == event_ID) {
		ev_up_sixth();
	}
	else if (11 == event_ID) {
		ev_down_first();
	}
	else if (12 == event_ID) {
		ev_down_second();
	}
	else if (13 == event_ID) {
		ev_down_third();
	}
	else if (14 == event_ID) {
		ev_down_fourth();
	}
	else if (15 == event_ID) {
		ev_down_fifth();
	}
	else if (16 == event_ID) {
		ev_down_sixth();
	}
	else if (17 == event_ID) {
		ev_down_under();
	}
	else if (18 == event_ID) {
		ev_up_rooftop();
	}
	else if (20 == event_ID) {
		ev_talk_test();
	}

	//トイレ
	//1階
	else if (21 == event_ID) {
		ev_enter_first_toilet();
	}
	else if (22 == event_ID) {
		ev_exit_first_toilet();
	}
	//2階
	else if (23 == event_ID) {
		ev_enter_second_toilet();
	}
	else if (24 == event_ID) {
		ev_exit_second_toilet();
	}
	//3階
	else if (25 == event_ID) {
		ev_enter_third_toilet();
	}
	else if (26 == event_ID) {
		ev_exit_third_toilet();
	}
	//4階
	else if (27 == event_ID) {
		ev_enter_fourth_toilet();
	}
	else if (28 == event_ID) {
		ev_enter_fourth_toilet();
	}
	//5階
	else if (29 == event_ID) {
		ev_enter_fifth_toilet();
	}
	else if (30 == event_ID) {
		ev_enter_fifth_toilet();
	}
	//6階
	else if (31 == event_ID) {
		ev_enter_sixth_toilet();
	}
	else if (32 == event_ID) {
		ev_enter_sixth_toilet();
	}

	//地下

	//Okaken
	else if (33 == event_ID) {
		ev_enter_okaken();
	}
	else if (34 == event_ID) {
		ev_exit_okaken();
	}
	//Bunngei
	else if (35 == event_ID) {
		ev_enter_bunngei();
	}
	else if (36 == event_ID) {
		ev_exit_bunngei();
	}
	//Sinnbun
	else if (37 == event_ID) {
		ev_enter_sinnbun();
	}
	else if (38 == event_ID) {
		ev_exit_sinnbun();
	}
	//Housou
	else if (39 == event_ID) {
		ev_enter_housou();
	}
	else if (40 == event_ID) {
		ev_exit_housou();
	}
	//Tennmon
	else if (41 == event_ID) {
		ev_enter_tennmon();
	}
	else if (42 == event_ID) {
		ev_exit_tennmon();
	}
	//Enngeki
	else if (43 == event_ID) {
		ev_enter_enngeki();
	}
	else if (44 == event_ID) {
		ev_exit_enngeki();
	}

	else if (100 == event_ID) {
		ev_get_stick();
	}

	else if (200 == event_ID) {
		ev_goback_world_A_1();
	}
	else if (201 == event_ID) {
		ev_go_world_A_2();
	}

	//Story
	else if (1001 == event_ID) {
		ev_story_1();
	}
	else if (1002 == event_ID) {
		ev_story_2();
	}
	else if (10000 == event_ID) {
		ev_update_shop();
	}
	else if (99999 == event_ID) {
		ev_talk_test();
	}
	else {
		pass();
	}
}

void Game_Manager::ev_save_point() {

	if (0 == ev_scene) {

		full_life_player();

		start_message();
		mes(U"・体力が回復した！！\n・セーブした！！");
		play_se(U"セーブ");


		save_game();

		respawn_point.x = ev_x;
		respawn_point.y = ev_y + 72;//足元なので下に合わせる


		next();
	}
	if (1 == ev_scene) {

		z();
	}
	else if (2 == ev_scene) {
		end();
	}
	
}


//移動系


void Game_Manager::ev_up_first() {
	go_area(U"first_1", 51, 9);
	end();
}

void Game_Manager::ev_up_second() {
	go_area(U"second_1", 51, 9);
	end();
}

void Game_Manager::ev_up_third() {
	go_area(U"third_1", 51, 9);
	end();
}

void Game_Manager::ev_up_fourth() {
	go_area(U"fourth_1", 51, 9);
	end();
}

void Game_Manager::ev_up_fifth() {
	go_area(U"fifth_1", 51, 9);
	end();
}

void Game_Manager::ev_up_sixth() {
	go_area(U"six_1", 51, 9);
	end();
}

void Game_Manager::ev_up_rooftop() {
	go_area(U"rooftop_1", 51, 9);
	end();
}






void Game_Manager::ev_down_first() {
	go_area(U"first_1", 45, 9);
	end();
}

void Game_Manager::ev_down_second() {
	go_area(U"second_1", 45, 9);
	end();
}

void Game_Manager::ev_down_third() {
	go_area(U"third_1", 45, 9);
	end();
}

void Game_Manager::ev_down_fourth() {
	go_area(U"fourth_1", 45, 9);
	end();
}

void Game_Manager::ev_down_fifth() {
	go_area(U"fifth_1", 45, 9);
	end();
}

void Game_Manager::ev_down_sixth() {
	go_area(U"sixth_1", 45, 9);
	end();
}

//地下に行く
void Game_Manager::ev_down_under() {
	go_area(U"under_1", 45, 9);
	end();
}

//トイレに行く処理

//1F
void Game_Manager::ev_enter_first_toilet() {
	go_area(U"first_toilet", 10, 9);
	end();
}

void Game_Manager::ev_exit_first_toilet() {
	go_area(U"first_1", 50, 9);
	end();
}

//2F
void Game_Manager::ev_enter_second_toilet() {
	go_area(U"second_toilet", 10, 9);
	end();
}

void Game_Manager::ev_exit_second_toilet() {
	go_area(U"second_1", 50, 9);
	end();
}

//3F
void Game_Manager::ev_enter_third_toilet() {
	go_area(U"third_toilet", 10, 9);
	end();
}

void Game_Manager::ev_exit_third_toilet() {
	go_area(U"third_1", 50, 9);
	end();
}

//4F
void Game_Manager::ev_enter_fourth_toilet() {
	go_area(U"fourth_toilet", 10, 9);
	end();
}

void Game_Manager::ev_exit_fourth_toilet() {
	go_area(U"fourth_1", 50, 9);
	end();
}

//5F
void Game_Manager::ev_enter_fifth_toilet() {
	go_area(U"fifth_toilet", 10, 9);
	end();
}

void Game_Manager::ev_exit_fifth_toilet() {
	go_area(U"fifth_1", 50, 9);
	end();
}

//6F
void Game_Manager::ev_enter_sixth_toilet() {
	go_area(U"sixth_toilet", 10, 9);
	end();
}

void Game_Manager::ev_exit_sixth_toilet() {
	go_area(U"sixth_1", 50, 9);
	end();
}

//Okaken
void Game_Manager::ev_enter_okaken() {
	go_area(U"okaken", 6, 9);
	end();
}

void Game_Manager::ev_exit_okaken() {
	go_area(U"under_1", 64, 9);
	end();
}

void Game_Manager::ev_enter_bunngei() {
	go_area(U"bunngei", 6, 9);
	end();
}

void Game_Manager::ev_exit_bunngei() {
	go_area(U"under_1", 79, 9);
	end();
}

void Game_Manager::ev_enter_sinnbun() {
	go_area(U"sinnbun", 6, 9);
	end();
}

void Game_Manager::ev_exit_sinnbun() {
	go_area(U"under_1", 32, 9);
	end();
}

void Game_Manager::ev_enter_housou() {
	go_area(U"housou", 6, 9);
	end();
}

void Game_Manager::ev_exit_housou() {
	go_area(U"under_1", 17, 9);
	end();
}

void Game_Manager::ev_enter_tennmon() {
	go_area(U"tennmon", 6, 9);
	end();
}

void Game_Manager::ev_exit_tennmon() {
	go_area(U"under_1", 92, 9);
	end();
}

void Game_Manager::ev_enter_enngeki() {
	go_area(U"tennmon", 6, 9);
	end();
}

void Game_Manager::ev_exit_enngeki() {
	go_area(U"under_1", 4, 9);
	end();
}

//World_A
void Game_Manager::ev_goback_world_A_1() {
	go_area(U"world_A_1", 72, 10, U"left");
	play_se(U"教室の戸を開ける");
	end();
}

void Game_Manager::ev_go_world_A_2() {
	go_area(U"world_A_2", 6, 8, U"right");
	play_se(U"教室の戸を開ける");
	end();
}

void Game_Manager::ev_get_stick() {

	if (get_var(U"end_got_stick") == 0) {

		if (0 == ev_scene) {

			start_message();
			mes(U"<お祓い棒>を手に入れた！！");
			player.set_have_stick();
			get_item(U"お祓い棒");
			event_super.set_var(U"got_stick", 1);
			next();
		}
		else if (1 == ev_scene) {
			z();
		}
		else if (2 == ev_scene) {

			set_var(U"end_got_stick", 1);
			end();
		}
	}
	else {
		pass();
	}
}



void Game_Manager::ev_talk_test() {

	if (0 == ev_scene) {

		start_message();
		mes(U"テスト用の文字列だったり、改行を見るためにちょっと長めだったりしたり・・・ああああああああああああああああああああああああああああああああああああああ");

		mes(U"sakura", U"テスト用の文字列だったり、改行を見るためにちょっと長めだったりしたり");

		next();
	}
	if (1 == ev_scene) {

		z();
	}
	else if (2 == ev_scene) {
		end();
	}
}


void Game_Manager::ev_story_1() {

	if (0 == ev_scene) {

		ev_image = true;
		ev_image_name = U"title_call";

		wait(1);
	}
	else if (1 == ev_scene) {

		ev_alpha += Delta_Time * 0.3;

		if (ev_alpha > 1) {
			ev_alpha = 1;
		}

		if (ev_alpha > 0.1) {
			if (event_super.get_var(U"once_bell") == 0) {
				play_se(U"学校のチャイム");
				event_super.set_var(U"once_bell", 1);
			}
		}

		wait(3.6);
	}
	else if (2 == ev_scene) {

		next(3);	
	}
	else if (3 == ev_scene) {

		bool pass = false;

		ev_wait_count += Delta_Time;

	

		if (ev_wait_count >= (6.4 + 2)) {
			pass = true;
		}
		/*
		else if (KeyZ.down() or KeyX.down() or KeyC.down()) {
			pass = true;
		}*/

		if (true == pass) {
			next(5);
		}
		
	}
	else if (4 == ev_scene) {
	
	}
	else if (5 == ev_scene) {

		change_bg_and_bgm(U"my_room", U"日光浴");
	}
	else if (6 == ev_scene) {
		next(8);
	}
	else if (8 == ev_scene) {

		start_message();
		mes(U"憂鬱である…");
		next(10);
	}
	if (10 == ev_scene) {

		z();
	}
	else if (11 == ev_scene) {

		mes(U"なぜ憂鬱なのかというと\n今日が転校初日だからだ。");
		z();
	}
	else if (12 == ev_scene) {

		mes(U"お父さんの仕事の都合で\n転校には慣れているものの、\n憂鬱に変わりはない。");
		z();
	}
	else if (13 == ev_scene) {

		mes(U"しかも６年生で転校って\n始業式からといえども、\nあと１年しかないし…");
		z();
	}
	else if (14 == ev_scene) {

		mes(U"お父さんは\n「次の学校では最高の友だちができるぞ！」\nって言ってたけど");
		z();
	}
	else if (15 == ev_scene) {

		mes(U"どうなのかなー………");
		z();
	}
	else if (16 == ev_scene) {

		mes(U"「さくらー、もう時間よー！！」");
		z();
	}
	else if (17 == ev_scene) {

		mes(U"階段からお母さんの声が聞こえる。");
		z();
	}
	else if (18 == ev_scene) {

		mes(U"まあ、最後の小学生なんだし\n少しは楽しんでみよう。");
		z();
	}
	else if (19 == ev_scene) {

		mes(U"そんな感じで\n唯一変わらないランドセルを背負い\n学校へと向かった…");
		z();
	}
	else if (20 == ev_scene) {

		//mes(U"");
		//z();

		change_bg_and_bgm(U"class_room",U"先生おはようございます");
	}
	else if (21 == ev_scene) {

		mes(U"教室は渾沌としていた。");
		z();
	}
	else if (22 == ev_scene) {

		mes(U"確かに「自由」が、校風とは\n聞いていたけども\nここまでとは…");
		z();
	}
	else if (23 == ev_scene) {

		mes(U"ちょっと緊張して言った\n自己紹介も\n誰も聞いてなかったし…");
		z();
	}
	else if (24 == ev_scene) {

		mes(U"転校生なんだから\n少しは興味もってよ！！\nなんて…");
		z();
	}
	else if (25 == ev_scene) {

		mes(U"「ということでね、ホームルームはおしまい。今日は初日だからこれで解散です！！」");
		z();
	}
	else if (26 == ev_scene) {

		mes(U"どっと歓声が上がる。　　\n私も早く帰りたかったので\n心の中でガッツポーズ。");
		z();
	}
	else if (27 == ev_scene) {

		mes(U"んー何もしてないのに\nなんか疲れたなー\n帰ったら何しよう…");
		z();
	}
	else if (28 == ev_scene) {

		mes(U"そんなことを考えていると\n");
		z();
	}
	else if (29 == ev_scene) {

		set_bg(U"dark");
		stop_bgm();
		next();
	}
	else if (30 == ev_scene) {

		mes(U"突然、辺りが闇に包まれた。");
		z();
	}
	else if (31 == ev_scene) {

		mes(U"!？………\n停電とは違う、本当の暗闇。");
		z();
	}
	else if (32 == ev_scene) {

		mes(U"どうゆう状況？！………");
		z();

	}
	else if (33 == ev_scene) {

		player.set_ground_pos(6 * 72, 10 * 72);
		player.set_is_ground(true);

		control_scroll();
		camera.jumpTo(scroll, 1.0);

		next();
	}

	if (34 == ev_scene) {

		change_bg_and_bgm(U"",U"六花");
	}
	else if (35 == ev_scene) {

		mes(U"ここは………？!");
		z();
	}
	else if (36 == ev_scene) {

		end();
	}



}

void Game_Manager::ev_story_2() {

	if (0 == ev_scene) {
		go_area_long_and_direction_and_color(U"under_1", 10, 9, U"right", U"white");
		play_se(U"鏡移動");
		next();
	}
	else if (1 == ev_scene) {

		start_message();
		mes(U"帰ってきたみたいね………");
		next();
	}
	else if (2 == ev_scene) {
		z();
	}
	else if (3 == ev_scene) {
		mes(U"ここは、学校………？？");
		z();
	}
	else if (4 == ev_scene) {
		mes(U"初めまして、転校生ちゃん！！\nようこそオカルト研究部へ！！");
		z();
	}
	else if (5 == ev_scene) {
		mes(U"んー………んん？？\nオカルト研究部？？");
		z();
	}
	else if (6 == ev_scene) {
		mes(U"そう！オカルト研究部！！\n通称「オカ研」！！！");
		z();
	}
	else if (7 == ev_scene) {
		mes(U"心霊・都市伝説・超常現象\nありとあらゆるオカルトを研究しているわ！！");
		z();
	}
	else if (8 == ev_scene) {
		mes(U"そして、あなたの加入が決まった今！！\n「オカ研」は学校公認の部活へとレベルアップするわ！！");
		z();
	}
	else if (9 == ev_scene) {
		mes(U"おいてかないでー、なんの話？？\nそもそもさっきの空間は何？？");
		z();
	}
	else if (10 == ev_scene) {
		mes(U"おそらくソレは「霊界」でしょう。\nこの学校の七不思議の一つ「放課後の神隠し」が起きたのです！");
		z();
	}
	else if (11 == ev_scene) {
		mes(U"「神隠し」ねえ………\nこんなところで………");
		z();
	}
	else if (12 == ev_scene) {
		mes(U"さあ、色々わかったところで部室へGO！！");
		z();
	}
	else if (13 == ev_scene) {
		mes(U"あんまりわかってないよーな………");
		z();
	}
	else if (14 == ev_scene) {
		go_area(U"under",10,10);
		end();
	}

	


}

