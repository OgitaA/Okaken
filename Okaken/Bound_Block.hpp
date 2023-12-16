#pragma once
#include"Block.hpp"

class Bound_Block : public Block {

public:

	Bound_Block(){}
	Bound_Block(String set_name,float set_x,float set_y) {

		x = set_x;
		y = set_y;

		m_pos = { set_x * 72,set_y * 72 };

		m_type = Block_Type::E_Bound;

		m_normal_colission = true;
	}

	void draw()const override{

		get_rect().draw(Palette::Orange);
	}

private:


};
