#pragma once

#include<Siv3D.hpp>

struct Have_Charm {

	Have_Charm() {}
	Have_Charm(String set_name,int set_x,int set_y):
		name(set_name),
		x(set_x),
		y(set_y)
	{
	}

	String name;
	int x;
	int y;


	template <class Archive>
	void SIV3D_SERIALIZE(Archive& archive)
	{
		archive(name, x, y);
	}
};
