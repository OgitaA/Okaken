#pragma once

#include"Block_Type.hpp"

class Block {

public:

	Block(){}
	Block(String set_name,int set_x, int set_y,int set_image_x,int set_image_y) {

		x = set_x;
		y = set_y;

		m_pos = { x * 72,y * 72 };
		m_pos_old = m_pos;

		m_wide = 72;
		m_height = 72;

		m_name = set_name;

		m_type = Block_Type::E_Normal;

		image_x = set_image_x;
		image_y = set_image_y;
	}

	virtual void update(float d_time) {

		m_d_time = d_time;
	}

	virtual void draw()const {

		//TextureAsset(U"block_tile")(image_x * 72, image_y * 72, 72, 72).draw(x * 72, y * 72);

		/*
		if (Block_Type::E_Normal == m_type) {

			String image_name = U"block_" + m_name;
			TextureAsset(image_name).draw(m_pos);
		}*/

		const int32 index = (image_x + image_y * 20);
		TextureAsset(U"block_{}"_fmt(index)).draw(x * 72, y * 72);
	}

	virtual RectF get_rect()const { return RectF(m_pos, m_wide, m_height); }
	virtual RectF get_rect_old()const { return RectF(m_pos_old, m_wide, m_height); }

	Block_Type get_type() {return m_type; }

	//特殊な処理
	int get_x() { return x; }
	int get_y() { return y; }

	bool get_normal_colission() { return m_normal_colission; }

protected:

	float m_d_time;

	Vec2 m_pos;
	Vec2 m_pos_old;

	float m_wide = 72;
	float m_height = 72;

	String m_name;

	Block_Type m_type;


	//特殊な判定用
	int x = 0;
	int y = 0;

	//仮想のブロック用
	bool m_normal_colission = false;

	int image_x = 0;
	int image_y = 0;

};
