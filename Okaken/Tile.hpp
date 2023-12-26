﻿#pragma once

class Tile {

public:

	Tile(){}
	
	Tile(int set_x, int set_y, int set_image_x, int set_image_y) {

		m_pos = { set_x * 72,set_y * 72 };
		image_x = set_image_x;
		image_y = set_image_y;
	}

	void draw()const {

		//String image_name = U"tile_" + m_name;

		//TextureAsset(image_name).draw(m_pos);

		//TextureAsset(U"tile_tile")(image_x * 72, image_y * 72, 72, 72).draw(m_pos);
		const int32 index = (image_x + image_y * 20);
		TextureAsset(U"tile_{}"_fmt(index)).draw(m_pos);
	}

	RectF get_rect()const { return RectF(m_pos, 72, 72); }


private:

	

	Vec2 m_pos;

	int image_x = 0;
	int image_y = 0;
};
