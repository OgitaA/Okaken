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

		m_hp = 32;

		state = State::wait;

		eyesight = 700;

		m_drop_soul = 1;
	}

	void update(const float d_time,const Player& player)override {


		update_common(d_time, player);

		


		function_gravity();

		m_speed.x = 0;

		
		if (State::wait == state) {

			if (search_distance_player() < eyesight) {
				change_state(State::find);
			}
		}
		else if (State::find == state) {


			if (m_count_A > 1) {

				direction = search_direction_player();

				m_speed.y = -750;
				change_state(State::active);

			}
		}
		else if (State::active==state) {

			//地面についた
			if (true == m_is_ground) {

			
				if (m_count_A > 1) {
					change_state(State::wait);
				}
			}
		}


		if (search_distance_player() >= eyesight) {
			change_state(State::wait);
		}

		
		//ジャンプ処理
		if (false == m_is_ground) {

			if (U"left" == direction) {
				m_speed.x = -300;
			}
			else if (U"right" == direction) {
				m_speed.x = 300;
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
