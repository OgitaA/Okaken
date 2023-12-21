#pragma once
#include<Siv3D.hpp>

class Dash_Effect {

public:

	Dash_Effect(float set_x,float set_y,bool set_mirror) {
		pos = { set_x,set_y };
		mirror = set_mirror;

	}

	void update(float d_time) {

		count += d_time;

		fade -= float(1.5 / 0.5) * d_time;

		if (page_count > float()) {

			page++;
			page_count = 0;

		}

	}

	bool get_delete() {

		if (count >= 0.5) {
			return true;
		}

		return false;
	}

	void draw()const {

		String image_name=U"player_dash_effect_0";

		TextureAsset(image_name).mirrored(mirror).draw(pos, ColorF(1, fade));
	}

	float get_fade()const { return fade; }

private:

	Vec2 pos;

	float count = 0;

	float page_count = 0;
	int page = 0;

	float fade = 1.5;

	bool mirror = false;
};
