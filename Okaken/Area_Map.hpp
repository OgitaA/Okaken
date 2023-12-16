#pragma once

#include<Siv3D.hpp>

class Area_Map {

public:

	Area_Map(){}

	void draw()const {

		String image_name = U"area_map_" + name;
		TextureAsset(image_name).draw(0, 0);
	}

private:

	String name;

};
