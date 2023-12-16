#pragma once

#include"Block.hpp"

class Needle : public Block{

public:

	Needle(){}
	Needle(String set_name,float set_x,float set_y) {

		m_name = set_name;

		m_pos = { set_x * 72,set_y * 72 };

		m_type = Block_Type::E_Needle;

		adjust_h = 40;

		adjust_y = 72 - adjust_h;

		m_normal_colission = false;
	}

	void draw()const override {

		TextureAsset(U"block_needle").draw(m_pos);
	}

	RectF get_rect()const override { return RectF(m_pos.x, m_pos.y + adjust_y, m_wide, adjust_h); }


private:

	float adjust_y = 0;
	float adjust_h = 0;

};
