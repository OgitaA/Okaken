#pragma once

#include"Block.hpp"

class One_Way_Floor : public Block {

public:

	One_Way_Floor(){}

	One_Way_Floor(float x,float y){

		m_pos = { x,y };

		m_type = Block_Type::E_One_Way_Floor;

		m_height = 30;
	}

	void draw()const override {

		get_rect().draw(Palette::Orange);
	}



};
