#pragma once

class Circle_Effect {

public:

	Circle_Effect(Vec2 set_pos,float set_radius,ColorF set_color) {

		first(set_pos, set_radius, set_color);	
	}

	Circle_Effect(Vec2 set_pos, float set_radius, ColorF set_color, float set_angle) {

		first(set_pos, set_radius, set_color);

		angle = set_angle * 3.14 / float(180);

		move = true;
	}


	void first(Vec2 set_pos, float set_radius, ColorF set_color) {

		pos = set_pos;
		radius = set_radius;
		color = set_color;

		circle = Circle(pos, radius);

		delete_count = 0.5;

		start_fade = 1.5;
		fade = start_fade;
	}

	


	void update(float d_time) {

		count += d_time;

		fade -= float(start_fade / delete_count) * d_time;

		if (move == false) {
			circle.r += 2 * d_time * 50;
		}
		if (move == true) {

			float speed = 400;

			circle.x += cos(angle) * speed * d_time;
			circle.y += sin(angle) * speed * d_time;
		}
	}

	void draw()const {

		circle.draw(ColorF(color, fade));
	}

	bool get_delete() {
		if (count > delete_count) {
			return true;
		}

		return false;
	}

private:

	Vec2 pos{ 0,0 };

	float radius = 1;

	float fade = 1;
	float start_fade = 1;

	Circle circle;

	ColorF color;

	float count = 0;
	float delete_count = 0;

	float angle = 0;

	bool move = false;
};
