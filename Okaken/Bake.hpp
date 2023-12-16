﻿#pragma once

#include"Enemy.hpp"

class Bake : public Enemy {

public:

	Bake(){}
	Bake(float set_x,float set_y) : Enemy(set_x,set_y)
	{
		m_name = U"bake";
		m_is_air = true;

		adjust_w = 72;
		adjust_h = 72;

		m_hp = 3;

		m_drop_heart = 1;
		m_drop_soul = 1;

		m_drop_coin_10 = 3;

		state = State::wait;
		eyesight = 700;
	}

	void update(const float d_time,const Player& player)override {

		update_common(d_time, player);

	
		if (false == knock_back) {

			if (State::wait == state) {

				if (search_distance_player() < eyesight) {
					change_state(State::find);
				}
			}
			else if (State::find == state) {

				m_count_A += m_d_time;

				if (m_count_A > 1) {

					state = State::chase;

					m_count_A = 0;
				}

				if (search_distance_player() >= eyesight) {
					change_state(State::wait);
				}
			}
			else if (State::chase == state) {

				float speed = 150;


				m_angle = search_angle_player();

				m_pos.x += cos(m_angle) * speed * d_time;
				m_pos.y += sin(m_angle) * speed * d_time;


				if (search_distance_player() >= eyesight) {
					change_state(State::wait);
				}
			}



		}



	}

	void draw()const {

		String image_name = U"enemy_" + m_name;

		TextureAsset(image_name).draw(m_pos);
	}

private:


};
