#pragma once

#include<Siv3D.hpp>

struct Block_Data {

	int x;
	int y;
	int image_x;
	int image_y;

	Block_Data(){}
	Block_Data(int set_x, int set_y, int set_image_x,int set_image_y) :
		x(set_x),
		y(set_y),
		image_x(set_image_x),
		image_y(set_image_y)
	{}
	~Block_Data() {};

	void draw()const {

		//String image_name = U"block_" + name;
		//TextureAsset(image_name).draw(x * 72, y * 72);

		//TextureAsset(U"block_tile")(image_x * 72, image_y * 72, 72, 72).draw(x * 72, y * 72);

		const int32 index = (image_x + image_y * 20);
		TextureAsset(U"block_{}"_fmt(index)).draw(x * 72, y * 72);
	}

	template <class Archive>
	void SIV3D_SERIALIZE(Archive& archive)
	{
		archive(x, y, image_x, image_y);
	}

};

struct Gimmick_Data {

	int x;
	int y;
	String name;
	

	Gimmick_Data() {}
	Gimmick_Data(int set_x, int set_y, String set_name) :
		x(set_x),
		y(set_y),
		name(set_name)
	{}
	~Gimmick_Data() {};

	void draw()const {

		String image_name = U"gimmick_" + name;
		TextureAsset(image_name).draw(x * 72, y * 72);


	}

	template <class Archive>
	void SIV3D_SERIALIZE(Archive& archive)
	{
		archive(x, y, name);
	}
};

struct Enemy_Data {

	int x;
	int y;
	String name;
	String direction;
	int pattern_A;
	int pattern_B;
	int pattern_C;
	float var_A;
	float var_B;
	float var_C;

	Enemy_Data() {}
	Enemy_Data(int set_x, int set_y, String set_name):
		x(set_x),
		y(set_y),
		name(set_name)
	{}
	Enemy_Data(int set_x, int set_y,String set_name,String set_direction,int set_pA,int set_pB,int set_pC,float set_vA,float set_vB,float set_vC) :
		x(set_x),
		y(set_y),
		name(set_name),
		direction(set_direction),
		pattern_A(set_pA),
		pattern_B(set_pB),
		pattern_C(set_pC),
		var_A(set_vA),
		var_B(set_vB),
		var_C(set_vC)
	{}
	~Enemy_Data(){}

	void draw()const {

		String image_name = U"enemy_" + name;
		TextureAsset(image_name).draw(x * 72, y * 72);


	}

	template <class Archive>
	void SIV3D_SERIALIZE(Archive& archive)
	{
		archive(x, y, name, direction, pattern_A, pattern_B, pattern_C, var_A, var_B, var_C);
	}

};

struct Tile_Data {

	int x;
	int y;
	int image_x;
	int image_y;


	Tile_Data() {}
	
	Tile_Data(int set_x, int set_y, int set_image_x, int set_image_y) :
		x(set_x),
		y(set_y),
		image_x(set_image_x),
		image_y(set_image_y)
	{}
	~Tile_Data() {};

	void draw()const {

		//String image_name = U"tile_" + name;
		//TextureAsset(image_name).draw(x * 72, y * 72);

		//TextureAsset(U"tile_tile")(image_x * 72, image_y * 72, 72, 72).draw(x * 72, y * 72);

		const int32 index = (image_x + image_y * 20);
		TextureAsset(U"tile_{}"_fmt(index)).draw(x * 72, y * 72);
	}

	template <class Archive>
	void SIV3D_SERIALIZE(Archive& archive)
	{
		archive(x, y,image_x, image_y);
	}
};

struct Deco_Data {

	int x;
	int y;
	int image_x;
	int image_y;

	Deco_Data() {}
	

	Deco_Data(int set_x,int set_y,int set_image_x,int set_image_y):
		x(set_x),
		y(set_y),
		image_x(set_image_x),
		image_y(set_image_y)
	{}

	~Deco_Data() {};

	void draw()const {

		//String image_name = U"deco_" + name;
		//TextureAsset(image_name).draw(x * 72, y * 72);


		//TextureAsset(U"deco_tile")(image_x * 72, image_y * 72, 72, 72).draw(x * 72, y * 72);

		const int32 index = (image_x + image_y * 20);
		TextureAsset(U"deco_{}"_fmt(index)).draw(x * 72, y * 72);
	}

	template <class Archive>
	void SIV3D_SERIALIZE(Archive& archive)
	{
		archive(x, y,image_x, image_y);
	}
};


struct Event_Data {

	int x;
	int y;
	
	int ID;//識別用

	bool mark = false;

	int image_x = 0;
	int image_y = 0;



	Event_Data() {}
	Event_Data(int set_x, int set_y,int set_image_x,int set_image_y) :
		x(set_x),
		y(set_y),
		image_x(set_image_x),
		ID(-1)
	{}
	~Event_Data() {};

	void draw()const {

		//String image_name = U"event_" + name;
		//TextureAsset(image_name).draw(x * 72, y * 72);

		if (0==image_x and 0==image_y) {

			TextureAsset(U"event_blue_box").draw(x * 72, y * 72);
		}
		else {
			//TextureAsset(U"event_tile")(image_x * 72, image_y * 72, 72, 72).draw(x * 72, y * 72);

			const int32 index = (image_x + image_y * 20);
			TextureAsset(U"event_{}"_fmt(index)).draw(x * 72, y * 72);
		}
	}

	template <class Archive>
	void SIV3D_SERIALIZE(Archive& archive)
	{
		archive(x, y, ID, image_x, image_y);
	}
};


//テストプレイ用初期位置
struct Player_Data {

	Player_Data(){}
	

	int x;
	int y;

	template <class Archive>
	void SIV3D_SERIALIZE(Archive& archive)
	{
		archive(x, y);
	}
};


