#pragma once

#include<Siv3D.hpp>

class Stick {

public:

	Stick(){}



	void update(const float d_time) {

		m_d_time = d_time;

		if (true == exist) {

			m_count += m_d_time;

			if (m_delete_count < m_count) {
				exist = false;
			}
		}
	}

	void draw()const {

		if (true == exist) {

			if (U"left"==m_direction) {
				TextureAsset(U"stick_left").draw(m_pos);
			}
			else if (U"right" == m_direction) {
				TextureAsset(U"stick_right").draw(m_pos);
			}
		}
	}

	RectF get_hit_rect() { return m_hit_rect; }

	void make_attack(String direction,float x,float y) {

		exist = true;
		m_direction = direction;

		if (U"left" == m_direction) {
			m_pos = { x - 340,y - 100 };
		}
		else if (U"right" == m_direction) {
			m_pos = { x + 170,y - 100 };
		}

	

		m_hit_rect = RectF(m_pos, 172, 263);

		m_count = 0;

		m_delete_count = 0.5;
	}

	bool get_exist() { return exist; }

	String get_direction()const { return m_direction; }

private:

	bool exist = false;

	float m_d_time;

	Vec2 m_pos;

	RectF m_hit_rect;

	float m_count = 0;

	float m_delete_count = 0;

	String m_direction = U"left";

};
