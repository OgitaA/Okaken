#pragma once

# include <Siv3D.hpp> // Siv3D v0.6.12

class My_Effect {

public:

	My_Effect(String _name, double _x, double _y) {
		name = _name;
		x = _x;
		y = _y;

		set_up();
	}

	My_Effect(String _name, double _x, double _y, String _layer) {
		name = _name;
		x = _x;
		y = _y;

		layer = _layer;

		set_up();
	}

	void update(double);
	void draw()const;

	void set_up();

	bool get_delete() {

		if (count > delete_count) {
			return true;
		}
		return false;
	}

	String get_layer() { return layer; }

private:

	String name = U"";


	double count = 0;
	double delete_count;

	double x = 0;
	double y = 0;
	double w = 0;
	double h = 0;

	double adjust_x = 0;
	double adjust_y = 0;

	double fade_v = 1;
	double fade_minus = 0;
	double fade_plus = 0;

	double size = 1;
	double size_up = 0;//一秒あたりの増加量
	double size_down = 0;

	String layer = U"back";

	//Anime
	bool anime_use = false;

	int page = 0;
	int page_max = 0;
	double page_count = 0;
	double page_change_count = 0;

};

