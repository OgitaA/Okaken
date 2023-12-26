#pragma once

#include"Block.hpp"

class Break_Block : public Block {

public:

	Break_Block() {}
	Break_Block(String set_name, float set_x, float set_y) {

		x = set_x;
		y = set_y;

		m_pos = { set_x * 72,set_y * 72 };

		m_type = Block_Type::E_Break;

		m_normal_colission = true;

		image_x = 6;
		image_y = 0;
	}

	void draw()const override {

		//TextureAsset(U"block_tile")(image_x * 72, image_y * 72, 72, 72).draw(x * 72, y * 72);

		const int32 index = (image_x + image_y * 20);
		TextureAsset(U"block_{}"_fmt(index)).draw(x * 72, y * 72);

		//get_rect().draw(Palette::Darkgray);
	}


};
