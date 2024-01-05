#pragma once

#include<Siv3D.hpp>

class Stick {

public:

	Stick(){

		for (int i = 0; i < 5; i++) {
			m_hit_triangles.push_back(Triangle());
		}
	}



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

			/*
			//判定拡大
			if (page >= 2) {
				m_hit_rect = RectF(m_pos, 210, 200);
			}*/


			//時間経過で判定消滅
			
			if (m_delete_count < m_count) {
				exist = false;

				page = 0;
			}
		}
	}

	void update_attack(String direction, float x, float y);

	void draw()const {

		if (true == exist) {

			String image_name = U"attack_" + Format(page);

			if (U"left"==m_direction) {
				TextureAsset(image_name).draw(m_pos_draw);
			}
			else if (U"right" == m_direction) {
				TextureAsset(image_name).mirrored(true).draw(m_pos_draw);
			}

			//m_hit_rect.draw(Palette::Red);
		}
	}

	RectF get_hit_rect()const { return m_hit_rect; }

	Array<Triangle> get_hit_triangle()const{

		Array<Triangle> t;

		if (page>=2) {
			t = m_hit_triangles;
		}
		else {
			for (size_t i = 0; i < 3; i++) {
				t.push_back(Triangle(m_hit_triangles[i]));
			}
		}

		return t;
	}

	void make_attack(String direction, float x, float y);

	bool get_exist() { return exist; }

	String get_direction()const { return m_direction; }

	void set_pos_draw(float x, float y) {

		if (U"left" == m_direction) {
		
			m_pos_draw = {x - 210 ,y - 50};
		}
		else if (U"right" == m_direction) {

			m_pos_draw = {x,y - 50};
		}

		

	}

	int get_page() { return page; }

	void reset();
	void reset_action() {

		reset();

		exist = false;
	}

private:

	bool exist = false;

	float m_d_time;

	Vec2 m_pos;

	//描画用
	Vec2 m_pos_draw;

	RectF m_hit_rect;

	Array<Triangle> m_hit_triangles;

	float m_count = 0;

	const float m_delete_count = 0.3;

	String m_direction = U"left";

	//anime
	int page = 0;
	float page_count = 0;

	
};
