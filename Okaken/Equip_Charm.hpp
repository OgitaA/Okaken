#pragma once

#include<Siv3D.hpp>

struct Equip_Charm {

	Equip_Charm(){}
	Equip_Charm(String set_name,int set_x) {
		name = set_name;
		x = set_x;
	}

	String name;
	int x;

	template <class Archive>
	void SIV3D_SERIALIZE(Archive& archive)
	{
		archive(name, x);
	}

};
