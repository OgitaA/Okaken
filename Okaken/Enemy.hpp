#pragma once
#include<Siv3D.hpp>

#include"Player.hpp"




class Enemy {

public:

	//状態
	enum State {
		sleep,
		wait,
		drift,
		find,
		chase,
		active,
		A,
		B,
		C
	};

	Enemy(){}
	Enemy(float set_x,float set_y):
		m_pos({set_x,set_y})
	{
		m_pos = { set_x * 72,set_y * 72 };
		m_pos_old = m_pos;

		m_wide = 72;
		m_height = 72;
	}

	virtual void update(const float,const Player&);

	virtual void draw()const = 0;

	void function_gravity();


	void set_speed_y_zero() { m_speed.y = 0; }
	

	RectF get_rect() {return RectF (m_pos, m_wide, m_height); }
	RectF get_rect_old() {return RectF (m_pos_old, m_wide, m_height); }

	float get_wide()const { return m_wide; }
	float get_height()const { return m_height; }

	Vec2 get_center()const { return Vec2(m_pos.x + m_wide / 2, m_pos.y + m_height / 2); }

	void set_x(float x) { m_pos.x = x; }
	void set_y(float y) { m_pos.y = y; }

	//地面
	void set_is_ground(bool v) { m_is_ground = v; }

	void turn_direction() {

		if (true == m_is_turn) {

			if (U"left" == direction) {
				direction = U"right";
			}
			else if (U"right" == direction) {
				direction = U"left";
			}

			if (U"up" == direction) {
				direction = U"down";
			}
			else if (U"down" == direction) {
				direction = U"up";
			}

		}
	}

	RectF get_hit_rect() {

		return RectF(m_pos.x + adjust_x, m_pos.y + adjust_y, adjust_w, adjust_h);
	}

	void damage(int v) {

		m_hp -= v;
		if (m_hp < 0) {
			m_hp = 0;
		}

		muteki_count = 0.5;
		white_count = 0.5;
	}

	int get_hp() { return m_hp; }

	int get_drop_heart() { return m_drop_heart; }
	int get_drop_soul() { return m_drop_soul; }
	int get_drop_coin_10() { return m_drop_coin_10; }
	int get_drop_coin_50() { return m_drop_coin_10; }
	int get_drop_coin_100() { return m_drop_coin_10; }
	int get_drop_coin_500() { return m_drop_coin_10; }

	float search_angle_player();
	float search_distance_player();
	String search_direction_player();

	void touch_player() { state = State::wait; }
	void change_state(State s) { state = s; m_count_A = 0; }
	void set_state_wait() { change_state(State::wait); }

	void update_common(float d_time,const Player& player) {

		m_d_time = d_time;
		p_player = std::make_shared<Player>(player);

		m_pos_old = m_pos;

		m_count_A += m_d_time;

		if (muteki_count > 0) {
			muteki_count -= d_time;
		}

		if (true == knock_back) {

			{
				// 平滑化時間（小さいと速く目標値 (0.0) に近づく）
				const double smoothTime = 0.05;

				double m_v2 = 0.0;
				m_speed.x = Math::SmoothDamp(m_speed.x, 0.0, m_v2, smoothTime, unspecified, m_d_time);

			}

			m_pos += m_speed * d_time;
		}

		if (knock_back_count > 0) {
			knock_back_count -= d_time;
		}

		if (knock_back_count <= 0) {
			knock_back = false;
		}

		control_shader();
	}

	Array<int> get_make_shot()const { return make_shot; }
	Array<String> get_make_enemy()const { return make_enemy; }

	void reset_make_shot() { make_shot.clear(); }

	void shot(int v) { make_shot.push_back(int(v)); }


	void control_shader();
	float get_white() { return white_count; }

	bool get_muteki() {
		if (muteki_count > 0) {
			return true;
		}
		return false;
	}

	void set_knock_back(String direction) {

		knock_back = true;

		knock_back_count = 0.5;

		m_speed = { 0,0 };

		if (U"left" == direction) {
			m_speed.x = -1500;
		}
		else if (U"right" == direction) {
			m_speed.x = 1500;
		}

		
	}
	

protected:

	float m_d_time;

	String m_name;

	//座標

	Vec2 m_pos;
	Vec2 m_pos_old;

	float m_wide = 0;
	float m_height = 0;

	//移動系
	Vec2 m_speed = { 0,0 };
	float m_angle = 0;

	//重力
	const float m_gravity = 1200;


	//地面
	bool m_is_ground = false;


	//ターンする?
	bool m_is_turn = false;

	//浮いている系？
	bool m_is_air = false;

	//方向
	String direction = U"left";

	//当たり判定用の四角形

	float adjust_x = 0;
	float adjust_y = 0;
	float adjust_w = 0;
	float adjust_h = 0;

	//ステータス系
	int m_hp = 1;

	//アイテム
	int m_drop_heart = 0;
	int m_drop_soul = 0;
	int m_drop_coin_10 = 0;
	int m_drop_coin_100 = 0;
	int m_drop_coin_50 = 0;
	int m_drop_coin_500 = 0;

	//プレイヤーの中心座標
	//Vec2 m_p_pos;


	State state;


	//カウント
	float m_count_A = 0;


	//視覚
	float eyesight = 0;


	//弾
	Array<int> make_shot;

	//敵
	Array<String> make_enemy;

	//シェーダー
	
	float white_count = 0;

	//プレイヤーのポインタをもたせる
	std::shared_ptr<Player> p_player;

	//無敵カウント
	float muteki_count = 0;
	
	//ノックバック
	bool knock_back = false;
	float knock_back_count = 0;

};
