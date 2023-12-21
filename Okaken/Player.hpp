#pragma once

class Player {

public:

	Player();

	void reset();

	void update(float);
	void draw()const;
	void draw_stick()const;

	void walk();
	void jump();
	void function_gravity();

	void move();

	//座標

	RectF get_rect()const { return RectF(m_pos.x, m_pos.y, m_wide, m_height); }
	RectF get_rect_old()const { return RectF(m_pos_old.x, m_pos_old.y, m_wide, m_height); }

	float get_wide()const { return m_wide; }
	float get_height()const { return m_height; }

	void set_x(float x) { m_pos.x = x; }
	void set_y(float y) { m_pos.y = y; }

	//座標補助
	void plus_pos(Vec2 v) { m_pos += v; }

	Vec2 get_center() { return get_rect().center(); }

	//スピード
	void set_speed_y_zero() { m_speed.y = 0; }
	void set_speed_x_zero() { m_speed.x = 0; }

	//地面
	void set_is_ground(bool v) { m_is_ground = v; }

	void function_ground() {

		set_is_ground(true);
		set_speed_y_zero();
		set_coyote_time();

		start_auto_jump();

		m_jump = false;
	}

	//ジャンプ共通処理
	void jump_common() {

		m_jump = true;

		//ジャンプバッファリング用
		m_jump_buffering_once = true;
		m_jump_buffering_scene = 0;
		m_jump_buffering_triger = false;
		m_now_jump = false;

	
	}

	//カメラ用
	void update_camera();

	Vec2 get_camera_target_pos() {return get_center() + m_camera_target; }


	//当たり判定用
	RectF get_hit_rect() { return RectF(m_pos.x + m_adjust_x, m_pos.y + m_adjust_y, m_adjust_w, m_adjust_h); }

	//ダメージ
	void damage() {
		m_muteki_count = 2;
		reset_dash();

		red = 0;
		red_count = 2;
		red_flag = true;
	}

	float get_muteki_count() { return m_muteki_count; }

	void update_muteki() {

		m_muteki_count -= m_d_time;
		if (m_muteki_count < 0) {
			m_muteki_count = 0;

		}

		if (red_count > 0) {
			red_count -= m_d_time;
		}

		if (red_count <= float(red_count_2 * 0.15) and 0 < red_count) {

			if (true == red_flag) {
				red_flag = false;
			}
			else if (false == red_flag) {
				red_flag = true;
			}

			
			red_count_2--;
		}


		if (red_count <= 0) {
			red_count = 0;
			red_flag = false;
			red_count_2 = 12;
		}
	}

	bool get_muteki() {
		if (0 < m_muteki_count) {
			return true;
		}
		return false;
	}

	//色々処理
	String get_direction() { return m_direction; }
	void set_coyote_time() { m_coyote_time = 0.2; }

	void start_auto_jump(){

		//自動ジャンプがオン
		if (true == m_jump_buffering_triger) {

			m_now_jump = true;
		}
	}

	void set_wall(String v) { m_wall_direction = v; }

	void set_slip() { m_slip = true; }

	void set_bound() { m_bound = true; }

	void set_ground_pos(int x, int y) { m_pos = { x,y - (m_height - 72) }; }

	void set_game_over_flag(bool v) { game_over_flag = v; }

	//ぶっとばす
	void set_knock_back(String direction){

		knock_back_direction = direction;
		knock_back_count = 0.6;
		knock_back = true;

		m_speed = { 0,0 };

		//上に飛ばす
		m_speed.y = -800;

		if (direction == U"left") {
			m_speed.x = -2300;

		}
		else if (direction == U"right") {
			m_speed.x = 2300;
		}

	}

	void update_knock_back() {

		if (true == knock_back) {

			

			
			{
				// 平滑化時間（小さいと速く目標値 (0.0) に近づく）
				const double smoothTime = 0.1;

				double m_v2 = 0.0;
				m_speed.y = Math::SmoothDamp(m_speed.y, 0.0, m_v2, smoothTime, unspecified, m_d_time);
			}

			{
				// 平滑化時間（小さいと速く目標値 (0.0) に近づく）
				const double smoothTime = 0.05;

				double m_v2 = 0.0;
				m_speed.x = Math::SmoothDamp(m_speed.x, 0.0, m_v2, smoothTime, unspecified, m_d_time);

			}
			//Print << U"m_spped.x::" << m_speed.x;

			/*
			if (m_speed.x < -1200) {
				Print << U"minus!!";
			}*/

			if (knock_back_count>0) {
				knock_back_count -= m_d_time;
			}

			if (knock_back_count <= 0) {
				knock_back = false;
			}
		}
		else {
			
		}

		//Print << U"m_speed_x::" << m_speed.x;
	}

	void reset_dash() {

		m_dash = U"none";
		m_dash_scene = 0;
		m_dash_count = 0;
		m_dash_cool_time = 0;
	}

	float get_red()const {

		if (true == red_flag) {
			return 0.5;
		}
		
		return 0;

	}

	bool get_action_lock() { return action_lock; }

	bool get_attack() {

		if (attack_count <= 0) {
			return true;
		}
		return false;
	}

	void set_attack_cool_time() { attack_count = 0.35; }

	void set_state(String set_v) {

		m_state = set_v;
	}

	void set_attack_page(int set_v) {
		attack_page = set_v;
	}

	bool get_just_double() { return just_double_jump; }

	bool get_dash()const { return be_dash; }
	float get_dash_count() { return dash_count; }
	int get_dash_effect_count() { return dash_effect_count; }
	void plus_dash_effect_count() { dash_effect_count++; }

	float get_violet()const { return violet; }

	//debug用
	void reset_pos() { m_pos = { 1920 / 2,800 }; }

private:

	float m_d_time;

	//座標

	Vec2 m_pos;
	Vec2 m_pos_old;

	float m_wide;
	float m_height;

	//向き
	String m_direction = U"right";

	//移動
	Vec2 m_speed;

	const float m_walk_speed_max = 300;

	const float m_speed_x_max = 300;
	const float m_speed_y_max = 800;

	//walk
	const float m_walk_speed = 800;

	//jump
	const float m_jump_speed = -850;
	

	//コヨーテタイム
	float m_coyote_time = 0;

	//ジャンプ・バッファリング
	bool m_jump_buffering_once = false;
	float m_jump_buffering = 0;
	const float m_jump_buffering_count = 0.3;
	bool m_jump = false;
	int m_jump_buffering_scene = 0;
	bool m_jump_buffering_triger = false;

	bool m_now_jump = false;

	//重力
	const float m_gravity = 1350;


	//地面
	bool m_is_ground = false;


	//カメラ用
	Vec2 m_camera_target;


	//当たり判定用
	float m_adjust_x = 0;
	float m_adjust_y = 0;
	float m_adjust_w = 0;
	float m_adjust_h = 0;

	//ダメージ＋無敵時間
	float m_muteki_count = 0;

	//壁キック
	String m_wall_direction = U"none";

	//ダッシュ
	String m_dash = U"none";
	int m_dash_scene = 0;
	float m_dash_count = 0;
	float m_dash_cool_time = 0;

	//滑る用
	bool m_slip = false;

	//跳ねる
	bool m_bound = false;

	//ゲームオーバー用
	bool game_over_flag = false;

	//状態
	String m_state = U"wait";

	//アニメ
	int anime_page = 0;
	float anime_count = 0;

	//ぶっとび
	bool knock_back = false;
	float knock_back_count = 0;
	String knock_back_direction = U"right";


	//shader用
	float red = 0;
	bool red_flag = 0;
	float red_count = 0;
	int red_count_2 = 12;


	//操作ロック
	bool action_lock = false;

	//2段ジャンプ
	int jump_count = 0;

	bool can_double_jump = true;

	//２段ジャンプエフェクト
	bool just_double_jump = false;

	//アタックカウント
	float attack_count = 0;

	//アタック中向き変更封じる
	bool direction_lock = false;

	//お祓い棒表示
	bool display_stick = true;

	//アタック段階
	int attack_page = 0;

	struct Stick {

		Vec2 pos;
		String name;
	};

	//ダッシュエフェクト
	bool be_dash = false;

	float dash_count = 0;
	int dash_effect_count = 0;

	//通常画像処理
	mutable int adjust_x = 0;
	mutable int adjust_y = 0;

	//紫発光
	float violet = 0;

	//歩行アニメ
	int walk_page = 0;

	//歩行アニメカウント
	float walk_count = 0;


};
