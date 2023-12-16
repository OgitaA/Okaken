#include"Game_Manager.hpp"

void Game_Manager::ev_update_shop() {

	ev_shop = true;
	start_message();

	shop_cur.update();






	if (KeyX.down()) {
		end();
		ev_shop = false;
	}
}

void Game_Manager::ev_draw_shop()const {

	TextureAsset(U"shop_box").draw(100, 100);



	const int edge_x = 100;
	const int edge_y = 100;

	const int blank_w = 100;
	const int blank_h = 100;

	for (auto& goods : shop_goods) {

		String image_name = U"item_" + goods.name;
		int x = edge_x + blank_w * goods.x;
		int y = edge_y + blank_h * goods.y;

		TextureAsset(image_name).scaled(0.5).draw(x, y);
		FontAsset(U"BIZ_30")(goods.price).draw(x, y);

	}
}
