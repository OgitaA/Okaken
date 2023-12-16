#pragma once

#include"Enemy.hpp"

class Cleaner : public Enemy {

public:

	Cleaner() {}
	Cleaner(float set_x, float set_y) : Enemy(set_x, set_y)
	{
		m_name = U"Cleaner";
		m_is_air = false;

		adjust_w = 72;
		adjust_h = 72;

		m_hp = 5;

		state = State::wait;

		eyesight = 700;
	}

	void update(const float d_time,const Player& player)override {

		update_common(d_time, player);
	}

	void draw()const {

		String image_name = U"enemy_" + m_name;

		TextureAsset(image_name).draw(m_pos);
	}

private:


};
