#include"Game_Manager.hpp"

void Game_Manager::load_div_gragh(const String& name,const FilePath& path, const Size& size) {

	/*
	//イメージを読み込む
	const Image image(path);

	//分ける数
	const int w = image.size().x / size.x;
	const int h = image.size().y / size.y;



	
	Array<Texture> result;

	for (auto&& p : step(numDiv))

		result.emplace_back(image.clipped(size * p, size));



	TextureAsset::Register(U"block_tile", U"image/block/tile.png");
	TextureAsset::Load(U"block_tile");*/



	//イメージを読み込む
	const Image image(path);

	// 分割数

	const Size numDiv{ image.size().x / size.x, image.size().y / size.y};



	Array<Texture> result;

	result.reserve(numDiv.x * numDiv.y);



	for (auto&& p : step(numDiv)) {

		result.emplace_back(image.clipped(size * p, size));
	}

	for (auto& i : result) {

		String image_name = name;

		//TextureAsset::Register()
		//TextureAsset::Register(image_name, i);
		//TextureAsset::Load(image_name);
	}



}

