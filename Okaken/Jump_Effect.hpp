#pragma once

class Jump_Effect {

public:

	Jump_Effect(float set_x,float set_y) {
		pos = { set_x,set_y };
	}

	void update(float d_time) {

		count += d_time;
		page_count += d_time;

		fade -= float(1.8 / 0.3) * d_time;

		//Print << U"v::" << fade;

		if (page_count > float(0.3/4)) {
			page_count = 0;
			page++;

			if (page > 3) {
				page = 3;
			}
		}
	}

	bool get_delete() {

		if (count >= 0.3) {
			return true;
		}

		return false;
	}

	void draw()const {

		String image_name = U"player_jump_effect_";

		image_name += Format(page);

		TextureAsset(image_name).draw(pos, ColorF(1, fade));
	}

private:

	Vec2 pos;

	float count = 0;
	

	int page = 0;
	float page_count = 0;

	float fade = 1.8;
};
