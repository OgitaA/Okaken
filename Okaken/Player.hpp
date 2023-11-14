#pragma once

class Player {

public:

	Player();

	void update(float);
	void draw()const;

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

	//スピード
	void set_speed_y_zero() { m_speed.y = 0; }

	//地面
	void set_is_ground(bool v) { m_is_ground = v; }

	//debug用
	void reset_pos() { m_pos = { 1920 / 2,800 }; }

private:

	float m_d_time;

	//座標

	Vec2 m_pos;
	Vec2 m_pos_old;

	float m_wide;
	float m_height;

	//移動
	Vec2 m_speed;

	const float m_speed_x_max = 300;
	const float m_speed_x_min = -300;
	const float m_speed_y_max = 800;

	//walk
	const float m_walk_speed = 800;

	//jump
	const float m_jump_speed = -600;

	//重力
	const float m_gravity = 800;


	//地面
	bool m_is_ground = false;




};
