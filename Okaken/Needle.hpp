#pragma once

#include"Block.hpp"

class Needle : public Block{

public:

	Needle(){}
	Needle(String set_name,float set_x,float set_y) {

		m_name = set_name;

		x = set_x;
		y = set_y;

		m_pos = { set_x * 72,set_y * 72 };

		m_type = Block_Type::E_Needle;

		adjust_h = 40;

		adjust_y = 72 - adjust_h;

		m_normal_colission = false;

		image_x = 5;
		image_y = 0;
	}

	void draw()const override {

		//TextureAsset(U"block_needle").draw(m_pos);
		const int32 index = (image_x + image_y * 20);
		TextureAsset(U"block_{}"_fmt(index)).draw(x * 72, y * 72);
	}

	RectF get_rect()const override { return RectF(m_pos.x, m_pos.y + adjust_y, m_wide, adjust_h); }


private:

	float adjust_y = 0;
	float adjust_h = 0;

};
