#pragma once

#include"Enemy.hpp"

class Kasa : public Enemy {

public:

	Kasa() {}
	Kasa(float set_x, float set_y) : Enemy(set_x, set_y)
	{
		m_name = U"kasa";
		m_is_air = false;

		adjust_w = 72;
		adjust_h = 72;

		m_hp = 21;

		state = State::wait;

		eyesight = 700;

		//can_knock_back = false;

		knock_back_state = State::none;
		touch_player_state = State::none;

		m_drop_soul = 1;

		state = State::wait;
		
	}

	void update(const float d_time, const Player& player)override {


		update_common(d_time, player);




		function_gravity();


		/*
		if (State::wait == state) {

			if (search_distance_player() < eyesight) {
				change_state(State::find);
			}
		}
		else if (State::drift == state) {

			if (m_count_A > 1) {

				//地面についてる
				if (true == m_is_ground) {

					direction = search_direction_player();

					m_speed.y = -700;


					if (U"left" == direction) {
						m_speed.x = -300;
					}
					else if (U"right" == direction) {
						m_speed.x = 300;
					}

					change_state(State::active);
				}
			}
		}
		else if (State::find == state) {

			if (m_count_A > 1) {

				//地面についてる
				if (true == m_is_ground) {

					direction = search_direction_player();

					m_speed.y = -700;
					

					if (U"left" == direction) {
						m_speed.x = -300;
					}
					else if (U"right" == direction) {
						m_speed.x = 300;
					}

					change_state(State::active);
				}
			}
		}
		else if (State::active == state) {

			//地面についた
			if (true == m_is_ground) {

				m_speed.x = 0;

				if (m_count_A > 1) {
					change_state(State::wait);
				}
			}
		}*/





		/*
		if (search_distance_player() >= eyesight) {
			change_state(State::wait);
		}*/

		if (State::wait == state) {

			if (search_distance_player() < eyesight) {
				change_state(State::find);
			}
		}
		if (State::find == state) {

			if (m_count_A > 0.6) {

				//地面についてる
				if (true == m_is_ground) {

					direction = search_direction_player();

					

					m_speed.y = -750;


					if (U"left" == direction) {
						m_speed.x = -300;
					}
					else if (U"right" == direction) {
						m_speed.x = 300;
					}

					change_state(State::active);
				}
			}
		}
		else if (State::active == state) {

			//地面についた
			if (true == m_is_ground) {

				m_speed.x = 0;

				if (m_count_A > 1) {
					change_state(State::wait);
				}
			}
		}

		m_pos += m_speed * m_d_time;
	}

	void draw()const {

		String image_name = U"enemy_" + m_name;

		TextureAsset(image_name).draw(m_pos);
	}

private:


};
