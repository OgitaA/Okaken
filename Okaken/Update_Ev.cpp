#include"Game_Manager.hpp"

void Game_Manager::update_event() {

	update_event_main();
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
}

void Game_Manager::update_event_main() {

	if (0 == event_ID) {
		ev_save_point();
	}
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
	else if (20 == event_ID) {
		ev_talk_test();
	}
	else if (21 == event_ID) {
		ev_enter_first_toilet();
	}
	else if (22 == event_ID) {
		ev_exit_first_toilet();
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
	else if (10000 == event_ID) {
		ev_update_shop();
	}
	else if (99999 == event_ID) {
		ev_talk_test();
	}
	else {
		end();
	}
}

void Game_Manager::ev_save_point() {

	if (0 == ev_scene) {

		full_life_player();

		start_message();
		mes(U"・体力が回復した！！\n・セーブした！！");

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

void Game_Manager::ev_enter_first_toilet() {
	go_area(U"first_toilet", 10, 9);
	end();
}

void Game_Manager::ev_exit_first_toilet() {
	go_area(U"first_1", 50, 9);
	end();
}

void Game_Manager::ev_goback_world_A_1() {
	go_area(U"world_A_1", 72, 10, U"left");
	end();
}

void Game_Manager::ev_go_world_A_2() {
	go_area(U"world_A_2", 6, 8, U"right");
	end();
}

void Game_Manager::ev_get_stick() {

	if (0 == ev_scene) {

		start_message();
		mes(U"<お祓い棒>を手に入れた！！");
		player.set_have_stick();
		status.plus_have_ablity(U"stick");
		event_super.set_var(U"got_stick", 1);
		next();
	}
	else if (1 == ev_scene) {
		z();
	}
	else if (2 == ev_scene) {
		end();
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

		play_bgm(U"日光浴");
		set_bg(U"my_room");
		start_message();
		mes(U"テスト用の文字列だったり");
		next(100);
	}
	if (100 == ev_scene) {

		z();
	}
	else if (101 == ev_scene) {

		mes(U"二行目");
		z();
	}
	else if (102 == ev_scene) {

		mes(U"3行目");
		z();
	}

}


