#pragma once

#include"Enemy.hpp"

class Tyoutin : public Enemy {

public:

	Tyoutin() {}
	Tyoutin(float set_x, float set_y) : Enemy(set_x, set_y)
	{
		m_name = U"tyoutin";
		m_is_air = true;

		adjust_w = 72;
		adjust_h = 72;

		m_hp = 5;

		state = State::wait;

		eyesight = 700;
	}

	void update(const float d_time, const Player& player)override {

		update_common(d_time, player);

		if (m_count_A > 2) {

			shot(0);

			m_count_A = 0;
		}
	}

	void draw()const {

		String image_name = U"enemy_" + m_name;

		TextureAsset(image_name).draw(m_pos);
	}

private:


};
