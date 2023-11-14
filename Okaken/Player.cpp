#include"Player.hpp"

Player::Player()
{
	m_d_time = 0;

	m_pos = { 1920 / 2,900 - 200 };
	m_pos_old = m_pos;

	m_wide = 100;
	m_height = 100;

	m_speed = { 0,0 };
}


void Player::update(float d_time) {

	m_d_time = d_time;

	//１フレーム前の座標を取得
	m_pos_old = m_pos;


	walk();
	function_gravity();
	jump();

	move();
}

void Player::draw()const {

	get_rect().draw(Palette::Red);
}

void Player::walk() {

	if (KeyRight.pressed()) {
		m_speed.x += m_walk_speed * m_d_time;
	}
	else if (KeyLeft.pressed()) {
		m_speed.x -= m_walk_speed * m_d_time;
	}
}

void Player::function_gravity() {

	//重力加速
	m_speed.y += m_gravity * m_d_time;
}

void Player::jump() {

	bool can_jump = false;

	if (true == m_is_ground) {
		can_jump = true;
	}

	if (KeyZ.down()) {

		if (true == can_jump) {

			m_speed.y = m_jump_speed;
		}
	}
}


void Player::move() {

	//速度分の移動

	//速度制限
	if (m_speed_x_max < m_speed.x) {

		m_speed.x = m_speed_x_max;
	}
	else if (m_speed_x_min > m_speed.x) {

		m_speed.x = m_speed_x_min;
	}

	if (m_speed_y_max < m_speed.y) {

		m_speed.y = m_speed_y_max;
	}

	m_pos += m_speed * m_d_time;
}
