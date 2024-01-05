#pragma once

#include<Siv3D.hpp>

class Cur {

public:

	Cur(){}
	Cur(int set_x_max,int set_y_max) {
		x_max = set_x_max;
		y_max = set_y_max;
	}

	Cur(int set_x_max, int set_y_max, bool lock_x, bool lock_y) {
		x_max = set_x_max;
		y_max = set_y_max;
		turn_x = lock_x;
		turn_y = lock_y;
	}

	void set_off_turn_x() { turn_x = false;}
	void set_off_turn_y() { turn_y = false; }
	void set_x_max(int v) { x_max = v; }
	void set_y_max(int v) { y_max = v; }

	void set_x_zero() { x = 0; }
	void set_y_zero() { y = 0; }

	void update(int se_volume) {

		bool sound = false;

		float d_time = Scene::DeltaTime();

		if (0 < interval_x) {
			interval_x -= d_time;
		}

		if (0 < interval_y) {
			interval_y -= d_time;
		}

		if (not KeyLeft.pressed() and not KeyRight.pressed()) {
			interval_x = 0;
		}

		if (not KeyUp.pressed() and not KeyDown.pressed()) {
			interval_y = 0;
		}

		bool naname_guard = false;

		if (KeyLeft.pressed() or KeyRight.pressed()) {
			if (KeyUp.pressed() or KeyDown.pressed()) {
				naname_guard = true;
			}
		}

		if (false == naname_guard) {

			if (interval_x <= 0) {

				bool key = false;

				if (KeyLeft.pressed()) {
					x--;
					key = true;
					sound = true;
				}
				else if (KeyRight.pressed()) {
					x++;
					key = true;
					sound = true;
				}

				if (true == key) {
					interval_x = interval_v;
				}
			}

			if (interval_y <= 0) {

				bool key = false;

				if (KeyUp.pressed()) {
					y--;
					key = true;
					sound = true;
				}
				else if (KeyDown.pressed()) {
					y++;
					key = true;
					sound = true;
				}

				if (true == key) {
					interval_y = interval_v;
				}
			}

		}
		
		//切り替えし処理

		if (true == turn_x) {

			if (x < 0) {
				x = x_max;
				
			}

			if (x_max < x) {
				x = 0;
			}
		}
		else if (false == turn_x) {

			if (x_max<x) {
				x = x_max;
				sound = false;
			}

			if (x < 0) {
				x = 0;
				sound = false;
			}
		}

		if (true == turn_y) {

			if (y < 0) {
				y = y_max;
			}

			if (y_max < y) {
				y = 0;
			}
		}
		else if (false == turn_y) {

			if (y_max < y) {
				y = y_max;
				sound = false;
			}

			if (y < 0) {
				y = 0;
				sound = false;
			}
		}

		if (true == sound) {

			double volume = double(se_volume) / double(10);

			AudioAsset(U"カーソル").playOneShot(volume);
		}

	}

	int get_x()const { return x; }
	int get_y()const { return y; }

private:

	int x = 0;
	int y = 0;

	float interval_x = 0;
	float interval_y = 0;

	float interval_v = 0.3;

	int x_max = 10;
	int y_max = 10;

	bool turn_x = true;
	bool turn_y = true;

};
