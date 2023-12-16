#pragma once

class Item {

public:

	Item(){}
	Item(String name,float x,float y) {

		m_image_name = U"item_" + name;

		m_name = name;
		m_pos = { x,y };
		adjust_first();
	}
	Item(String name,int v, float x, float y,float set_speed_x) {

		m_image_name = U"item_" + name + U"_" + Format(v);

		m_name = name;
		m_pos = { x,y };
		m_pos_old = m_pos;
		m_v = v;

		m_speed.x = set_speed_x;

		adjust_first();
	}

	void adjust_first() {

			m_pos.x -= TextureAsset(m_image_name).width() / 2;
			m_pos.y -= TextureAsset(m_image_name).height() / 2;

			m_wide = TextureAsset(m_image_name).width();
			m_height = TextureAsset(m_image_name).height();

		
	}

	void update(const float d_time) {

		m_pos_old = m_pos;

		//コインは落下処理
		if (U"coin" == m_name) {

			m_speed.y += m_gravity * d_time;

			//重力制限
			if (m_speed.y > 800) {
				m_speed.y = 800;
			}

			m_pos += m_speed * d_time;
		}
	}

	void draw()const {

		if (U"coin" != m_name) {
			String image_name = U"item_" + m_name;
			TextureAsset(image_name).draw(m_pos);
		}
		else {
			String image_name = U"item_" + m_name + U"_" + Format(m_v);
			TextureAsset(image_name).draw(m_pos);
		}


	}

	RectF get_rect() { return RectF(m_pos, m_wide, m_height); }
	RectF get_rect_old() { return RectF(m_pos_old, m_wide, m_height); }

	float get_wide()const { return m_wide; }
	float get_height()const { return m_height; }

	void set_x(float x) { m_pos.x = x; }
	void set_y(float y) { m_pos.y = y; }

	void set_speed_y_zero() { m_speed.y = 0; }
	void set_speed_x_zero() { m_speed.x = 0; }

	String get_name() { return m_name; }

	int get_v() { return m_v; }


private:

	Vec2 m_pos;
	String m_name;

	float m_wide;
	float m_height;

	String m_image_name;

	//お金用

	Vec2 m_pos_old;

	int m_v;

	float m_gravity = 1350;
	Vec2 m_speed = { 0,0 };
};
