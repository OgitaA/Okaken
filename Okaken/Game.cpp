#include"Game.hpp"

Game::Game(const InitData& init)
	:IScene(init)	
{
	/*
	//一回だけ初期化
		if (false == once_initialize) {
		game_manager.initialize();
		once_initialize = true;
	}*/
}

void Game::update()
{
	String go_scene = game_manager.update();

	if (U"title" == go_scene) {
		changeScene(State::Title);
	}
}

void Game::draw()const
{
	game_manager.draw();
}
