#include"Block_Manager.hpp"

Block_Manager::Block_Manager() {

	float center_x = 1920 / 2 - 50;
	float y = 900;

	blocks.push_back(std::make_unique<Block>(center_x, y));
	blocks.push_back(std::make_unique<Block>(center_x - 100, y));
	blocks.push_back(std::make_unique<Block>(center_x + 100, y));
	blocks.push_back(std::make_unique<Block>(center_x - 200, y));
	blocks.push_back(std::make_unique<Block>(center_x + 200, y));
	blocks.push_back(std::make_unique<Block>(center_x - 300, y));
	blocks.push_back(std::make_unique<Block>(center_x + 300, y));

	blocks.push_back(std::make_unique<One_Way_Floor>(center_x + 300, y-200));
}

void Block_Manager::update(const float d_time) {

	for (auto& block : blocks) {

		block->update(d_time);
	}
}

void Block_Manager::draw()const {

	for (auto& block : blocks) {

		block->draw();
	}
}

void Block_Manager::vs(const float d_time,Player& player) {

	//プレイヤーを空中に設定
	player.set_is_ground(false);




	//プレイヤーとブロック

	RectF p_rect = player.get_rect();
	RectF p_rect_old = player.get_rect_old();

	float move_x = float(p_rect.x - p_rect_old.x);
	float move_y = float(p_rect.y - p_rect_old.y);

	RectF p_rect_moved_x = p_rect_old.movedBy(move_x, 0);
	RectF p_rect_moved_y = p_rect_old.movedBy(0, move_y);

	for (auto& block : blocks) {

		//通常ブロックの場合
		if (block->get_type() == Block_Type::E_Normal) {

			RectF b_rect = block->get_rect();

			if (p_rect.intersects(b_rect)) {


				//プレイヤーが右に移動している時
				if (move_x > 0) {

					//X軸のみ動かしたプレイヤーとブロックの判定
					if (p_rect_moved_x.intersects(b_rect)) {

						player.set_x(b_rect.x - player.get_wide());
					}
				}

				//プレイヤーが左に移動している時
				else if (move_x < 0) {

					//X軸のみ動かしたプレイヤーとブロックの判定
					if (p_rect_moved_x.intersects(b_rect)) {

						player.set_x(b_rect.x + b_rect.w);
					}
				}


				//プレイヤーが下に移動している時
				if (move_y > 0) {

					//Y軸のみ動かしたプレイヤーとブロックの判定
					if (p_rect_moved_y.intersects(b_rect)) {

						player.set_y(b_rect.y - player.get_height());


						//プレイヤーが地面に接触
						player.set_is_ground(true);

						//重力加速度を無くす
						player.set_speed_y_zero();

					}
				}

				//プレイヤーが上に移動している時
				else if (move_y < 0) {

					//Y軸のみ動かしたプレイヤーとブロックの判定
					if (p_rect_moved_y.intersects(b_rect)) {

						player.set_y(b_rect.y + b_rect.h);


						//重力加速度を無くす
						player.set_speed_y_zero();
					}
				}
			}
		}

		//一方通行の足場の場合
		else if (block->get_type() == Block_Type::E_One_Way_Floor) {

			RectF b_rect = block->get_rect();

			if (p_rect.intersects(b_rect)) {


				//下方向のみ判定

				//プレイヤーが下に移動している時
				if (move_y > 0) {

					//Y軸のみ動かしたプレイヤーとブロックの判定
					if (p_rect_moved_y.intersects(b_rect)) {

						//ワープ対策
						if (p_rect_moved_y.bottomY() < b_rect.topY() + 10) {

							player.set_y(b_rect.y - player.get_height());


							//プレイヤーが地面に接触
							player.set_is_ground(true);

							//重力加速度を無くす
							player.set_speed_y_zero();




						}
					}
				}
			}
		}

		//移動床の場合
		else if (block->get_type() == Block_Type::E_Move_Floor) {

			RectF b_rect_old = block->get_rect_old();

			if (p_rect.intersects(b_rect_old)) {


				//下方向のみ判定

				//プレイヤーが下に移動している時
				if (move_y > 0) {

					//Y軸のみ動かしたプレイヤーと<移動前の>ブロックの判定
					if (p_rect_moved_y.intersects(b_rect_old)) {

						//ワープ対策
						if (p_rect_moved_y.bottomY() < b_rect_old.topY() + 10) {

							player.set_y(b_rect_old.y - player.get_height());


							//プレイヤーが地面に接触
							player.set_is_ground(true);

							//重力加速度を無くす
							player.set_speed_y_zero();


							//移動床の移動分をプレイヤーに加える

							RectF b_rect = block->get_rect();

							Vec2 move = b_rect.pos - b_rect_old.pos;

							player.plus_pos(move);



							//移動後の足場と判定

							//Y軸のみ動かしたプレイヤーと<移動後の>ブロックの判定
							if (p_rect_moved_y.intersects(b_rect)) {

								player.set_y(b_rect.y - player.get_height());
							}
						}
					}
				}
			}
		}
	}


}
