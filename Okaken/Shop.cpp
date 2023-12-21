#include"Game_Manager.hpp"

void Game_Manager::ev_update_shop() {

	ev_shop = true;




	

	if (0 == shop_scene) {

		//Cur

		int amount = shop_goods.size() - 1;

		shop_cur.set_y_max(amount);
		shop_cur.update();

		//Print << U"y::" << shop_cur.get_y();

		

		for (auto& goods : shop_goods) {

			int x = shop_cur.get_x();
			int y = shop_cur.get_y();

			if (goods.x == x and goods.y == y) {

				shop_select = goods.name;
				shop_price = goods.price;
				break;
			}
		}

		//Print << U"shop_select::" << shop_select;

		//選択
		if (KeyZ.down()) {

			
			
			//減少中じゃない
			if (will_money_scene == 0) {

				//お金がある
				if (status.get_money() >= shop_price) {
					shop_scene = 1;
				}
			}
			else {

				if (will_money_goal >= shop_price) {
					shop_scene = 1;
				}
			}

		}
		else if (KeyX.down()) {
			end();
			ev_shop = false;
		}
	}
	//はい、か、いいえ
	else if (1 == shop_scene) {

		if (KeyZ.down()) {

			//購入
			if (0 == shop_cur_yes_no) {

				//Print << U"shop_price::" << shop_price;
				minus_will_money(shop_price);

				get_item(shop_select);

				shop_goods.remove_if([&](Shop_Goods goods) {

					if (goods.name == shop_select) {
						return true;
					}

				return false;

					});



				int count = 0;

				for (auto& goods : shop_goods) {
					goods.y = count;
					count++;
				}

				shop_scene = 2;
			}
			//キャンセル
			else if (1 == shop_cur_yes_no) {
				shop_scene = 0;
				shop_cur_yes_no = 0;
			}

		}
		else if (KeyX.down()) {
			shop_scene = 0;
		}
	}
	//購入処理中
	else if (2 == shop_scene) {

		shop_bought_count += Delta_Time;

		if (shop_bought_count >=1.5) {

			shop_bought_count = 0;
			shop_scene = 0;
		}
		else if (KeyZ.down()) {

			shop_bought_count = 0;
			shop_scene = 0;
		}
	}
}

void Game_Manager::ev_draw_shop()const {

	int box_edge_x = 1920 - 50 - 1300;
	int box_edge_y = 20;

	TextureAsset(U"shop_box").draw(box_edge_x, box_edge_y);

	

	const int edge_x = 100;
	const int edge_y = 100;

	const int blank_w = 100;
	const int blank_h = 100;

	int shop_up = shop_cur.get_y() - 2;
	int shop_bottom = shop_cur.get_y() + 2;

	/*
	if (shop_up < 3) {
		shop_bottom = shop_cur.get_y() + 3;
	}*/

	int center_y = box_edge_y + (1040 / 2) - (250 * 0.6 / 2);

	for (auto& goods : shop_goods) {

		if (shop_up <= goods.y and goods.y <= shop_bottom) {

			//中央からどのくらい離れているか
			int display_v = goods.y - shop_cur.get_y();


			String image_name = U"item_" + goods.name;

			int display_x = box_edge_x + 100;
			int display_y = center_y + display_v * ((250 * 0.6) + 20);

			//アイテム
			TextureAsset(image_name).scaled(0.6).draw(display_x, display_y);

			String price_text = Format(goods.price)+U"円";
			FontAsset(U"Mur_50")(price_text).drawAt(display_x + 300, display_y + ((250 * 0.6)/2), Palette::White);

		}

	}

	TextureAsset(U"shop_cur").scaled(0.6).draw(box_edge_x + 100, center_y);

	//上にある
	if (0 < shop_cur.get_y() - 2) {
		TextureAsset(U"shop_top").draw(box_edge_x + 100, 20 + 30 - 1);
	}

	//下にある
	if (shop_cur.get_y()+2<shop_goods.size()-1) {
		TextureAsset(U"shop_under").draw(box_edge_x+100, 1080 - 20 - 50 - 35);
	}




	//右側表示
	String display_text = U"";

	for (auto& good : shop_goods) {

		if (good.name == shop_select) {
			display_text = good.text;
			break;
		}
	}

	//名前
	FontAsset(U"BIZ_40")(shop_select).drawAt(1500, 100, Palette::White);

	if (0 == shop_scene) {
		//説明文
		int text_x = 1300;
		int text_y = 500;
		indent_drawer.draw(FontAsset(U"BIZ_40"), display_text, 800, text_x, text_y, Palette::White, 0);
	}
	else if (1 == shop_scene) {

		FontAsset(U"BIZ_40")(U"買う？？").drawAt(1500, 100, Palette::White);

		FontAsset(U"BIZ_40")(U"はい").drawAt(1500, 100, Palette::White);
		FontAsset(U"BIZ_40")(U"いいえ").drawAt(1500, 100, Palette::White);


	}
	else if (2 == shop_scene) {

		FontAsset(U"BIZ_40")(U"買った！！").drawAt(1500, 100, Palette::White);
	}
}
