#pragma once

#include"Block.hpp"

class Move_Floor : public Block {

public:

	Move_Floor() {}

	Move_Floor(String name,float x, float y) {

		m_name = name;

		m_pos = { x,y };

		m_type = Block_Type::E_Move_Floor;

		m_height = 30;

		m_normal_colission = false;
	}

	void update(float d_time)override {

		m_pos_old = m_pos;

		//m_pos.x += 200 * d_time;

		m_pos.y += 72 * d_time;
	}

	void draw()const override {

		get_rect().draw(Palette::Blue);
	}



};
