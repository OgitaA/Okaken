#pragma once

#include"Block_Type.hpp"

class Block {

public:

	Block(){}
	Block(float x,float y) {

		m_pos = { x,y };

		m_wide = 100;
		m_height = 100;

		m_type = Block_Type::E_Normal;
	}

	virtual void update(float d_time) {

		m_d_time = d_time;
	}

	virtual void draw()const {

		if (Block_Type::E_Normal == m_type) {
			get_rect().draw(Palette::White);
		}
		
	}

	RectF get_rect()const { return RectF(m_pos, m_wide, m_height); }
	RectF get_rect_old()const { return RectF(m_pos_old, m_wide, m_height); }

	Block_Type get_type() {return m_type; }

protected:

	float m_d_time;

	Vec2 m_pos;
	Vec2 m_pos_old;

	float m_wide = 100;
	float m_height = 100;

	Block_Type m_type;

};
