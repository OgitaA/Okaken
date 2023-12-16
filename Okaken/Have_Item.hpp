#pragma once

#include<Siv3D.hpp>

struct Have_Item {

	Have_Item(){}
	Have_Item(String set_name,int set_x,int set_y):
		name(set_name),
		x(set_x),
		y(set_y)
	{
	}

	String name;
	int x;
	int y;

	void plus_number(int v) {

		number += v;

		if (number > number_max) {
			number = number_max;
		}
	}

	bool minus_number(int v) {

		number -= v;

		if (number < 0) {
			number = 0;
		}

		return true;
	}

	int get_number() { return number; }

	template <class Archive>
	void SIV3D_SERIALIZE(Archive& archive)
	{
		archive(name, x, y,number);
	}

	

private:

	int number = 0;
	int number_max = 99;

};
