#pragma once
#include<Siv3D.hpp>


struct Area_Data {

	Area_Data(){}
	Area_Data(String set_name,int set_w,int set_h,String set_zone) {
		name = set_name;
		wide = set_w;
		height = set_h;
		belong_zone = set_zone;
	}

	Area_Data(String set_name, int set_w, int set_h, String set_zone,String set_bgm) {
		name = set_name;
		wide = set_w;
		height = set_h;
		belong_zone = set_zone;
		bgm = set_bgm;
	}


	String name;

	String belong_zone;

	int wide;
	int height;

	String bgm = U"";

};
