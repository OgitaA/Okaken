#include"Enemy.hpp"

void Enemy::update(const float d_time,const Player& player) {

	m_d_time = d_time;

	p_player = std::make_shared<Player>(player);
}

void Enemy::draw()const {

	String image_name = U"enemy_" + m_name;

	TextureAsset(image_name).draw(m_pos);

}

void Enemy::function_gravity() {

	//重力加速
	m_speed.y += m_gravity * m_d_time;
}

float Enemy::search_angle_player() {

	//return atan2(m_p_pos.y - m_pos.y, m_p_pos.x - m_pos.x) * 180 / 3.14;

	return atan2(p_player->get_center().y - get_center().y, p_player->get_center().x - get_center().x);
}

float Enemy::search_distance_player() {

	return sqrt(std::pow(p_player->get_center().y - get_center().y, 2) + std::pow(p_player->get_center().x - get_center().x, 2));
}

String Enemy::search_direction_player() {

	String direction = U"none";

	if (p_player->get_center().x < m_pos.x) {
		direction = U"left";
	}
	else if (p_player->get_center().x > m_pos.x) {
		direction = U"right";
	}

	return direction;
}

void Enemy::control_shader() {

	if (white_count > 0) {
		white_count -= m_d_time;
		if (white_count < 0) {
			white_count = 0;
		}
	}

}
