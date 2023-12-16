#pragma once

#include<Siv3D.hpp>


class Bullet_Enemy {

public:

	Bullet_Enemy(){}
	Bullet_Enemy(String set_name,int set_x,int set_y,float set_r,float set_speed,float set_angle) {
		m_name = set_name;
		m_circle = Circle(set_x, set_y, set_r);
		m_speed = set_speed;
		m_angle = set_angle;
	}

	void update(const float d_time) {

		m_circle.x += cos(m_angle) * m_speed * d_time;
		m_circle.y += sin(m_angle) * m_speed * d_time;
	}

	void draw()const {
		String image_name = U"bullet_enemy_" + m_name;
		TextureAsset(image_name).draw(m_circle.x - m_circle.r, m_circle.y - m_circle.r);
	}

	Circle get_circle() { return m_circle; }

private:

	String m_name;

	float m_d_time;

	Circle m_circle;

	float m_speed = 0;

	float m_angle = 0;
};
