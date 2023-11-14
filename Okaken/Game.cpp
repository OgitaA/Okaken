#include"Game.hpp"

Game::Game(const InitData& init)
	:IScene(init)
{}

void Game::update()
{
	game_manager.update();
}

void Game::draw()const
{
	game_manager.draw();
}
