#include"Game_Manager.hpp"

void Game_Manager::update_make_shot_enemy() {

	for (auto& enemy : enemys) {

		for (auto& shot : enemy->get_make_shot()) {

			make_shot_enemy(shot, enemy->get_center().x, enemy->get_center().y);
			enemy->reset_make_shot();
		}

	}
}

void Game_Manager::make_shot_enemy(int type,int set_x,int set_y) {//座標は敵の中央を取得


	//提灯お化けの自機狙いショット
	if (0 == type) {

		String name = U"fire";
		int x = set_x;
		int y = set_y;
		float r = 30;
		float speed = 300;

		float angle = convert_radian_to_angle(search_angle_player(set_x, set_y));

		make_bullet_enemy(name, x, y, r, speed, angle);
	}
}

void Game_Manager::make_bullet_enemy(String set_name,int set_x,int set_y,float set_r,float set_speed,float set_angle) {

	float angle_v = convert_angle_to_radian(set_angle);

	bullet_enemys.push_back(Bullet_Enemy(set_name, set_x, set_y, set_r, set_speed, angle_v));
}

float Game_Manager::search_angle_player(int e_x,int e_y) {

	Vec2 p_pos = player.get_center();
	return atan2(p_pos.y - e_y, p_pos.x - e_x);

}

float Game_Manager::convert_radian_to_angle(float radian_v) {

	return radian_v * 180 / 3.14;
}

float Game_Manager::convert_angle_to_radian(float angle_v) {

	return angle_v * 3.14 / 180;
}
