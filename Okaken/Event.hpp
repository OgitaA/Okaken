#pragma once

#include<Siv3D.hpp>

class Event {

public:

	Event(){}
	Event(float set_x,float set_y,int set_ID,int set_image_x,int set_image_y) {
		image_x = set_image_x;
		image_y = set_image_y;
		m_pos = { set_x*72,set_y*72 };
		m_ID = set_ID;
	}

	void update(const float d_time) {

	}

	void draw()const {

		
		TextureAsset(U"event_tile")(image_x * 72, image_y * 72, 72, 72).draw(m_pos);
	}

	RectF get_rect() { return RectF(m_pos, 72, 72); }
	int get_ID() { return m_ID; }

	String get_start_type() { return start_type; }

	int get_image_x() { return image_x; }
	int get_image_y() { return image_y; }

	void set_image_x(int v) { image_x = v; }
	void set_image_y(int v) { image_y = v; }


	//使う前にmemo確認
	bool get_collision() { return collision; }
	//RectF get_rect() { return RectF(m_pos.x, m_pos.y, 72, 72); }

private:

	

	Vec2 m_pos;

	int m_ID = 0;

	int m_scene;

	String start_type = U"check";

	//checkで調べると始まる
	//autoは自動でスタート

	int image_x = 0;
	int image_y = 0;

	//当たり判定
	bool collision = false;
};
