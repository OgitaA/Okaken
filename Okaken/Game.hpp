#pragma once

#include"Common.hpp"

#include"Game_Manager.hpp"

class Game : public App::Scene {

public:

	Game(const InitData& init);

	void update() override;

	void draw()const override;

private:

	Game_Manager game_manager;

	String go_scene;

	bool once_initialize = false;


};
