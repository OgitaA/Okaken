#include"Game_Manager.hpp"

Game_Manager::Game_Manager() {

}

void Game_Manager::update() {

	float d_time = float(Scene::DeltaTime());

	block_manager.update(d_time);

	player.update(d_time);

	block_manager.vs(d_time,player);
}

void Game_Manager::draw()const {

	block_manager.draw();

	player.draw();
}
