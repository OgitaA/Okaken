#pragma once

#include<Siv3D.hpp>

class Detail_Setter {

public:

	Detail_Setter(){

		back_rect = Rect(100, 1080 - 300, 100, 100);

		int x = 0;
		int y = 0;

		clear_key = Rect(1000, 500 - (100 + 30), 100 * 2 + 30 * 1, 100);
		delete_key = Rect(1000 + 2 * (100 + 30), 500 - (100 + 30), 100, 100);


		for (int i = 1; i < 10;i++) {

			keys.push_back(Key(1000 + x * (100 + 30), 500 + y * (100 + 30), 100, 100, i));

			x++;

			if (3==x) {
				x = 0;
				y++;
			}
		}

		key_zero = Rect(1000 + 0 * (100 + 30), 500 + 3 * (100 + 30), 100 * 3 + 30 * 2, 100);


	}

	bool update() {

		bool back = false;

	


		if (clear_key.leftClicked()) {
			v = U"";
		}

		if (delete_key.leftClicked()) {

			if (U"" != v) {
				v.pop_back();
			}
		}

		for (auto& key : keys) {
			if (key.rect.leftClicked()) {
				v += Format(key.v);
			}
		}

		if (key_zero.leftClicked()) {
			v += U"0";
		}

		if (v.size() >= 2) {

			String copy_v = v;
			size_t size = copy_v.size();

			copy_v.pop_back_N(size-1);
			
			if (copy_v == U"0") {
				v = U"0";
			}
		}

		/*
		if (back_rect.leftClicked()) {
			if (U"" != v) {
				back = true;
			}
		}*/

		if (back_rect.leftClicked()) {
			back = true;
		}

		return back;
	}


	void draw()const {

		back_rect.draw(Palette::White);
		FontAsset(U"BIZ_30")(U"back").draw(back_rect.x + back_rect.w / 2-30, back_rect.y + back_rect.h / 2, Palette::Black);

		clear_key.draw(Palette::White);
		FontAsset(U"BIZ_30")(U"clear").drawAt(clear_key.x + clear_key.w / 2, clear_key.y + clear_key.h / 2, Palette::Black);

		delete_key.draw(Palette::White);
		FontAsset(U"BIZ_30")(U"del").drawAt(delete_key.x + delete_key.w / 2, delete_key.y + delete_key.h / 2, Palette::Black);

		for (auto& key : keys) {

			Rect key_rect = key.rect;

			key_rect.draw(Palette::White);
			FontAsset(U"BIZ_30")(Format(key.v)).drawAt(key_rect.x + key_rect.w / 2, key_rect.y + key_rect.h / 2, Palette::Black);
		}

		key_zero.draw(Palette::White);
		FontAsset(U"BIZ_30")(Format(0)).drawAt(key_zero.x + key_zero.w / 2, key_zero.y + key_zero.h / 2, Palette::Black);

		FontAsset(U"BIZ_45")(v).draw(1000, 250, Palette::Yellow);
	}

	int get_v()const {


		int number = Parse<int32>(v);

		return number;
	}

	bool get_v_check_empty()const {

		if (v == U"") {
			return true;
		}

		return false;
	}

	void set_v(int set) {

		int tem_v = set;

		if (tem_v >= 0) {

			v = Format(set);
		}
		else {
			v = U"";
		}

	
	}

private:


	Rect back_rect;




	struct Key {

		Key(int set_x,int set_y,int set_w,int set_h,int set_v){
			rect = Rect(set_x, set_y, set_w, set_h);
			v = set_v;
		}

		Rect rect;
		int v;
	};


	Array<Key> keys;

	Rect key_zero;

	Rect clear_key;

	Rect delete_key;


	String v = U"";
};
