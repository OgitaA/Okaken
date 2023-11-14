#pragma once

#include"Player.hpp"
#include"Block_Manager.hpp"

class Game_Manager {

public:

	Game_Manager();

	void update();
	void draw()const;

private:

	Player player;
	Block_Manager block_manager;


};
