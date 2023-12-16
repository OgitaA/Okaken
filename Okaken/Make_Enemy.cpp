#include"Game_Manager.hpp"

void Game_Manager::update_make_enemy() {

	struct Will_Make {
		String name = U"";
		int x = 0;
		int y = 0;
	};

	Array<Will_Make> will_makes;

	for (auto& enemy : enemys) {

		int x = enemy->get_center().x;
		int y = enemy->get_center().y;
		
		for (auto& make : enemy->get_make_enemy()) {

			String name = make;
			will_makes.push_back(Will_Make(make, x, y));
		}
	}

	for (auto& will_make : will_makes) {
		make_enemy(will_make.name, will_make.x, will_make.y);
	}
}

void Game_Manager::make_enemy(String name,int x,int y) {

	if (U"bake" == name) {
		enemys.push_back(std::make_unique<Bake>(x, y));
	}
	else if (U"kasa" == name) {
		enemys.push_back(std::make_unique<Kasa>(x, y));
	}
	else if (U"hitotume" == name) {
		enemys.push_back(std::make_unique<Hitotume>(x, y));
	}
	else if (U"tyoutin" == name) {
		enemys.push_back(std::make_unique<Tyoutin>(x, y));
	}

}
