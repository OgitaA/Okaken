#pragma once
#include<Siv3D.hpp>


class Area_Selecter {

public:

	Area_Selecter(){}

	void set_zone(const Array<String>& datas) {

		int x = 0;
		int y = 0;

		for (auto& data : datas) {

			zone_rects.push_back(Zone_Rect(data, x, y));

			x++;

			if (3 == x) {
				x = 0;
				y++;
			}
		}
	}

	void set_area_first(String v) { select_area = v; }

	void set_area(const Array<Area_Data>& datas ) {

		for (auto& zone : zone_rects) {

			int x = 0;
			int y = 0;

			for (auto& data : datas) {

				String this_zone = data.belong_zone;

				if (this_zone == zone.name) {//所属しているゾーンなら

					String name = data.name;

					rects.push_back(Select_Rect(name, x, y, zone.name));

					x++;

					if (3 == x) {
						x = 0;
						y++;
					}

				}
			}


		}

		back_rect = Rect(50,800,100,100);
		go_rect = Rect(50, 800 + 100 + 50, 100);
	}

	bool update() {

		bool back = false;

		if (0 == scene) {

			for (auto& rect : zone_rects) {

				if (rect.rect.leftClicked()) {
					select_zone = rect.name;
					scene++;
					break;
				}
			}

			if (back_rect.leftClicked()) {
				back = true;
			}
		}
		else if (1 == scene) {

			for (auto& rect : rects) {

				if (rect.belong_zone == select_zone) {

					if (rect.rect.leftClicked()) {
						select_area = rect.name;
						break;
					}
				}
			}

			

			if (back_rect.leftClicked()) {
				scene = 0;
			}
			if (go_rect.leftClicked()) {
				back = true;
			}
		}



	

	

		return back;
	}


	void draw()const {

		if (0 == scene) {

			for (auto& r : zone_rects) {

				if (r.name != select_zone) {
					r.rect.draw(Palette::White);
				}
				else {
					r.rect.draw(Palette::Yellow);
				}

				int display_x = 200 + (r.x * 400) + 50;
				int display_y = 200 + (r.y * 150) + 50;


				//FontAsset(U"BIZ_45")(r.name).draw(display_x, display_y, Palette::Black);
				FontAsset(U"BIZ_45")(r.name).drawAt(r.rect.x + r.rect.w / 2, r.rect.y + r.rect.h / 2, Palette::Black);

			}
		}
		else if (1 == scene) {

			for (auto& r : rects) {

				if (r.belong_zone == select_zone) {

					if (r.name != select_area) {
						r.rect.draw(Palette::White);
					}
					else {
						r.rect.draw(Palette::Yellow);
					}

					int display_x = 200 + (r.x * 400) + 50;
					int display_y = 200 + (r.y * 100) + 50;


					//FontAsset(U"BIZ_45")(r.name).draw(display_x, display_y, Palette::Black);
					FontAsset(U"BIZ_45")(r.name).drawAt(r.rect.x + r.rect.w / 2, r.rect.y + r.rect.h / 2, Palette::Black);

				}
			}
		}

		back_rect.draw(Palette::White);
		FontAsset(U"BIZ_30")(U"back").drawAt(back_rect.x + back_rect.w / 2, back_rect.y + back_rect.h / 2, Palette::Black);

		go_rect.draw(Palette::White);
		FontAsset(U"BIZ_30")(U"Go").drawAt(go_rect.x + go_rect.w / 2, go_rect.y + go_rect.h / 2, Palette::Black);
	}

	String go_area() { return select_area; }



private:

	//Array<Area_Data> area_datas;

	String select_zone = U"";

	String select_area = U"";

	struct Zone_Rect {

		Zone_Rect(String set_name, int set_x, int set_y) {

			name = set_name;
			x = set_x;
			y = set_y;
			rect = Rect(200 + x * (400 + 50), 200 + y * (100 + 50), 400, 100);
		}

		Rect rect;
		int x = 0;
		int y = 0;
		String name;
	};


	struct Select_Rect {

		Select_Rect(String set_name,int set_x,int set_y,String set_zone) {

			name = set_name;
			x = set_x;
			y = set_y;
			rect = Rect(200 + x * (400 + 50), 200 + y * (100 + 50), 400, 100);
			belong_zone = set_zone;
		}

		Rect rect;
		int x = 0;
		int y = 0;

		//Area_Data area_data;

		String name;
		String belong_zone;
	};

	
	Array<Zone_Rect> zone_rects;

	Array<Select_Rect> rects;

	Rect back_rect;

	Rect go_rect;

	int scene = 0;

};
