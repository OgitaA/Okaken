#include"Player.hpp"

Player::Player()
{
	reset();
}

void Player::reset() {

	m_d_time = 0;

	m_pos = { 1920 / 2,900 - 200 };
	m_pos_old = m_pos;

	m_wide = 74;
	m_height = 150;

	m_direction = U"right";

	m_speed = { 0,0 };


	m_coyote_time = 0;

	m_jump_buffering_once = false;
	m_jump_buffering = 0;
	
	 m_jump = false;
	 m_jump_buffering_scene = 0;
     m_jump_buffering_triger = false;

	 m_now_jump = false;

	 m_is_ground = false;

	m_camera_target = { 0,0 };

	//当たり判定用
	m_adjust_w = 100;
	m_adjust_h = 100;


	//無敵
	m_muteki_count = 0;

	//壁ジャンプ
	m_wall_direction = U"none";

	//ダッシュ
	m_dash = U"none";
	m_dash_scene = 0;
	m_dash_count = 0;
	m_dash_cool_time = 0;

	//滑る用
	m_slip = false;

	//跳ねる
	m_bound = false;

	//ゲームオーバー用
	game_over_flag = false;

	//状態
	m_state = U"wait";

	//アニメ
	anime_page = 0;
	anime_count = 0;

	//ぶっとび
	knock_back = false;
	knock_back_count = 0;
	knock_back_direction = U"right";

	//シェーダー
	red = 0;
	red_flag = 0;
	red_count = 0;
	red_count_2 = 12;

}


void Player::update(float d_time) {

	m_d_time = d_time;

	//１フレーム前の座標を取得
	m_pos_old = m_pos;

	//操作をロックする
	action_lock = false;
	if (game_over_flag == true or knock_back == true) {
		action_lock = true;
	}

	if (false == knock_back) {
		walk();
	}

	function_gravity();

	if (false == knock_back) {
		jump();
	}

	update_knock_back();

	move();

	update_muteki();

	update_camera();
}

void Player::draw()const {

	//get_rect().draw(Palette::Red);

	String image_name = U"";



	if (U"wait" == m_state) {

		image_name = U"player_wait";

	}


	if (U"left" == m_direction) {
		TextureAsset(image_name).draw(m_pos);
	}
	else if (U"right" == m_direction) {
		TextureAsset(image_name).mirrored().draw(m_pos);
	}

	
}

void Player::walk() {

	if (false == m_slip) {

		// 平滑化時間（小さいと速く目標値 (0.0) に近づく）
		const double smoothTime = 0.05;

		if (KeyLeft.pressed() and false==action_lock)
		{
			m_speed.x -= (m_walk_speed * m_d_time);
			m_direction = U"left";
		}
		else if (KeyRight.pressed() and false==action_lock)
		{
			m_speed.x += (m_walk_speed * m_d_time);
			m_direction = U"right";
		}
		else
		{
			// 速度を緩やかに 0 に近づける
			double m_v2 = 0.0;
			m_speed.x = Math::SmoothDamp(m_speed.x, 0.0, m_v2, smoothTime, unspecified, m_d_time);
		}

	}
	else if (true == m_slip) {

		// 平滑化時間（小さいと速く目標値 (0.0) に近づく）
		const double smoothTime = 0.2;

		if (KeyLeft.pressed() and false == action_lock)
		{
			m_speed.x -= ((m_walk_speed+50) * m_d_time);
			m_direction = U"left";
		}
		else if (KeyRight.pressed() and false == action_lock)
		{
			m_speed.x += ((m_walk_speed+50) * m_d_time);
			m_direction = U"right";
		}
		else
		{
			// 速度を緩やかに 0 に近づける
			double m_v2 = 0.0;
			m_speed.x = Math::SmoothDamp(m_speed.x, 0.0, m_v2, smoothTime, unspecified, m_d_time);
		}

	
	}

	//滑り判定
	m_slip = false;
}

void Player::function_gravity() {

	//重力加速
	m_speed.y += m_gravity * m_d_time;
}

void Player::jump() {

	bool can_jump = false;

	if (true == m_is_ground) {
		can_jump = true;
	}

	//コヨーテタイム
	if (m_coyote_time > 0) {

		m_coyote_time -= m_d_time;
		can_jump = true;
	}

	//ジャンプ先行入力
	if (true == m_jump) {//ジャンプ中

		if (true == m_jump_buffering_once) {

			if (0 == m_jump_buffering_scene) {

				if (!KeyZ.pressed()) {//指を離した
					m_jump_buffering_scene++;
				}
			}
			else if (1 == m_jump_buffering_scene) {//入力開始

				if (KeyZ.down() and false==action_lock) {

					m_jump_buffering_scene++;
					m_jump_buffering = m_jump_buffering_count;
					m_jump_buffering_triger = true;//自動ジャンプする
				}
			}
			else if (2 == m_jump_buffering_scene) {//入力中

				//受付時間減る
				m_jump_buffering -= m_d_time;

				if (m_jump_buffering <= 0) {
					m_jump_buffering_once = false;
				}

				//ジャンプ離したら
				if (not KeyZ.pressed()) {
					m_jump_buffering_once = false;
				}
			}
		}

		if (false == m_jump_buffering_once) {
			m_jump_buffering_triger = false;
		}
		
	}

	
	//ジャンプと先行入力の自動ジャンプ
	if ((KeyZ.down() or true == m_now_jump or true==m_bound) and false == action_lock) {

		if (true == can_jump) {

			bool high_jump = false;

			//ハイジャンプ
			if (KeyZ.down() or true == m_now_jump) {
				if (true == m_bound) {
					high_jump = true;
				}
			}

			if (false == high_jump) {
				m_speed.y = m_jump_speed;
			}
			else if (true == high_jump) {
				m_speed.y = m_jump_speed * 1.3;
			}
			

			jump_common();
		}
	}

	

	//壁キック

	if (false == m_is_ground) {

		if (U"left" == m_wall_direction or U"right" == m_wall_direction) {

			if (KeyZ.down() and false == action_lock) {

				if (U"left" == m_wall_direction) {

					m_speed.y = m_jump_speed;
					jump_common();
					m_speed.x = +500;
				}
				else if (U"right" == m_wall_direction) {

					m_speed.y = m_jump_speed;
					jump_common();
					m_speed.x = -500;
				}
			}
		}
	}

	//ダッシュ
	if (0 == m_dash_scene) {

		if (0 < m_dash_cool_time) {
			m_dash_cool_time -= m_d_time;
		}

		if (KeyC.down() and false == action_lock) {

			if (m_dash_cool_time <= 0) {

				if (U"left" == m_direction) {
					m_dash = U"left";

				}
				else if (U"right" == m_direction) {
					m_dash = U"right";

				}

				m_dash_scene++;
			}
		}

	}
	if (1 == m_dash_scene) {

		float dash_speed = 1200;

		if (U"left" == m_dash) {
			m_pos.x -= dash_speed * m_d_time;
		}
		else if (U"right" == m_dash) {
			m_pos.x += dash_speed * m_d_time;
		}


		m_dash_count += m_d_time;

		bool end = false;

		//終了処理
		if (0.3 < m_dash_count) {
			end = true;
		}
		else if (U"left" == m_dash and U"left"==m_wall_direction) {
			end = true;
		}
		else if (U"right" == m_dash and U"right" == m_wall_direction) {
			end = true;
		}



		if (true == end) {

			m_dash_scene = 0;
			m_dash_count = 0;
			m_dash = U"none";

			m_speed.y = 0;

			m_dash_cool_time = 0.4;
		}

	}
	
	
	

	//空中操作

	if (m_is_ground == 0) {

		//上昇中andボタンを離している
		if (m_speed.y < 0 and not KeyZ.pressed() and false==action_lock) {

			// 平滑化時間（小さいと速く目標値 (0.0) に近づく）
			const double smoothTime = 0.1;

			double m_v2 = 0.0;
			m_speed.y = Math::SmoothDamp(m_speed.y, 0.0, m_v2, smoothTime, unspecified, m_d_time);

		}
	}



	//壁キック判定
	m_wall_direction = U"none";
	//バウンド
	m_bound = false;
}


void Player::move() {



	if (U"none" == m_dash) {

		if (false == knock_back) {

			// 速度を -maxSpeed ～ maxSpeed の範囲に抑える
			m_speed.x = Clamp(double(m_speed.x), double(-m_walk_speed_max), double(m_walk_speed_max));


			if (m_speed_y_max < m_speed.y) {

				m_speed.y = m_speed_y_max;
			}

		}
		

        //速度分の移動
		m_pos += m_speed * m_d_time;
	}
}

void Player::update_camera() {

	//左右に60の幅をもたせる
	m_camera_target.x = Clamp(m_camera_target.x + Math::Sign(m_speed.x) * 120 * m_d_time, -60.0, 60.0);

	//m_camera_target.x = m_camera_target.x + Math::Sign(m_speed.x) * 120 * m_d_time;

	

	

}
