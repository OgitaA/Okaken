#pragma once

#include"Block.hpp"

#include"One_Way_Floor.hpp"

#include"Player.hpp"

class Block_Manager {

public:

	Block_Manager();

	void update(const float d_time);
	void draw()const;

	void vs(const float d_time,Player& player );

private:

	Array<std::shared_ptr<Block>> blocks;


};
