#include"Title.hpp"

Title::Title(const InitData& init)
	:IScene(init)
{
	TextureAsset::Register(U"title_back", U"image/title/back.png");
	TextureAsset::Load(U"title_back");
}

void Title::update()
{
	if (KeyZ.down()) {
		changeScene(State::Game);
	}
}

void Title::draw()const
{
	TextureAsset(U"title_back").draw(0, 0);
}
