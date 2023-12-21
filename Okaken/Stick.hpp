#pragma once

#include<Siv3D.hpp>

class Stick {

public:

	Stick(){}



	void update(const float d_time) {

		m_d_time = d_time;

		if (true == exist) {

			m_count += m_d_time;

			page_count += m_d_time;

			float change_count = float(0.3 / (4 + 1));

			change_count = 0.06;

			//Print << U"change_count::"<<change_count;

			if (page_count > change_count) {
				page_count = 0;
				page++;
			}

			//ページ最大
			if (page > 3) {
				page = 3;
			}

			//判定拡大
			if (page >= 2) {
				m_hit_rect = RectF(m_pos, 210, 200);
			}


			//時間経過で判定消滅
			if (m_delete_count < m_count) {
				exist = false;

				page = 0;
			}
		}
	}

	void draw()const {

		if (true == exist) {

			String image_name = U"attack_" + Format(page);

			if (U"left"==m_direction) {
				TextureAsset(image_name).draw(m_pos);
			}
			else if (U"right" == m_direction) {
				TextureAsset(image_name).mirrored(true).draw(m_pos);
			}

			//m_hit_rect.draw(Palette::Red);
		}
	}

	RectF get_hit_rect() { return m_hit_rect; }

	void make_attack(String direction,float x,float y) {

		exist = true;
		m_direction = direction;

		if (U"left" == m_direction) {
			m_pos = { x-210 ,y - 50 };
		}
		else if (U"right" == m_direction) {
			m_pos = { x,y - 50 };
		}

	

		//m_hit_rect = RectF(m_pos, 172, 263);

		m_hit_rect = RectF(m_pos, 210, 200/2);





		//初期化

		m_count = 0;

		m_delete_count = 0.3;

		page = 0;
		page_count = 0;
	}

	bool get_exist() { return exist; }

	String get_direction()const { return m_direction; }

	void set_pos(float x, float y) {

		if (U"left" == m_direction) {
			m_pos = { x - 210 ,y - 50 };
		}
		else if (U"right" == m_direction) {
			m_pos = { x,y - 50 };
		}

		

	}

	int get_page() { return page; }

private:

	bool exist = false;

	float m_d_time;

	Vec2 m_pos;

	RectF m_hit_rect;

	float m_count = 0;

	float m_delete_count = 0;

	String m_direction = U"left";

	//anime
	int page = 0;
	float page_count = 0;

	
};
