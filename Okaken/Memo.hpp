#pragma once

//eventとblockの処理省略

//Curにもdeltatime変更

//Shopの数が３以下など

//ウィルコインの上限処理

/*
	//自動読み込み
	for (auto& box : select_boxs) {

		if (U"block" == box.get_type()) {

			for (auto& block : box.get_data_names()) {

				String name = block;
				String adress = U"image/block/" + name + U".png";

				String block_name = U"block_" + name;

				TextureAsset::Register(block_name, adress);
				TextureAsset::Load(block_name);
			}
		}

		if (U"tile" == box.get_type()) {

			for (auto& tile : box.get_data_names()) {

				String name = tile;
				String adress = U"image/tile/" + name + U".png";

				String tile_name = U"tile_" + name;

				TextureAsset::Register(tile_name, adress);
				TextureAsset::Load(tile_name);
			}
		}

		/*
		if (U"deco" == box.get_type()) {

			for (auto& deco : box.get_data_names()) {

				String name = deco;
				String adress = U"image/deco/" + name + U".png";

				String deco_name = U"deco_" + name;

				TextureAsset::Register(deco_name, adress);
				TextureAsset::Load(deco_name);
			}
		}
	}*/


#include<Siv3D.hpp>

class Object {

public:

	Object(){}
	~Object(){}

	//関数
	/*
	void change_state(State s) {

		state = s;

		count = 0;
	}


	void update() {

		if (KeyZ.down()) {
			change_state(State::active);
		}

	}*/

private:

	enum State {

		sleep,
		active

	};

	State state;

	int count = 0;

};
