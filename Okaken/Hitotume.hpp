#pragma once

#include"Enemy.hpp"

class Hitotume : public Enemy {

public:

	Hitotume() {}
	Hitotume(float set_x, float set_y) : Enemy(set_x, set_y)
	{
		m_name = U"hitotume";
		m_is_air = false;

		adjust_w = 72;
		adjust_h = 72;

		m_hp = 5;

		state = State::wait;

		eyesight = 700;
	}

	void update(const float d_time,const Player& player)override {

		update_common(d_time, player);

		function_gravity();

		m_speed.x = 0;

		if (state == State::wait) {

			if (search_distance_player() < eyesight) {

				direction = search_direction_player();

				change_state(State::find);
			}
		}
		else if (state == State::find) {

			if (m_count_A > 1) {
				change_state(State::active);
			}
		}
		else if (state == State::active) {

			if (U"left" == direction) {
				m_speed.x = -300;
			}
			else if (U"right" == direction) {
				m_speed.x = 300;
			}

			if (m_count_A > 2) {
				change_state(State::wait);
			}
		}

		/*
		if (search_distance_player() > eyesight) {

			change_state(State::wait);
		}*/


		m_pos += m_speed * m_d_time;
	}

	void draw()const {

		String image_name = U"enemy_" + m_name;

		TextureAsset(image_name).draw(m_pos);
	}

private:


};
