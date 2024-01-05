#pragma once

#include<Siv3D.hpp>

#include"Area_Data.hpp"

#include"My_GUI.hpp"

//エディタでのエリアを選択します。

class Area_Selecter {

public:

	Area_Selecter() {}

	void set_zone(const Array<String>& datas) {

		int x = 0;
		int y = 0;

		int page_count = 0;

		for (auto& data : datas) {

			zone_rects.push_back(Zone_Rect(page_count,data, x, y));

			x++;

			if (3 == x) {
				x = 0;
				y++;
			}

			if (y >= 5) {
				x = 0;
				y = 0;
				page_count++;
			}

		}
	}

	void set_area_first(String v) { select_area = v; }

	void set_area(const Array<Area_Data>& datas) {

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

		back_rect = Rect(50, 800, 100, 100);
		go_rect = Rect(50, 800 + 100 + 50, 100);
		left_rect = Rect(1920 / 2 - 300, 50, 100, 100);
		right_rect = Rect(1920 / 2 + 300 - 100, 50, 100, 100);
	}

	bool update() {

		bool back = false;

		//Zoneを選択
		if (0 == scene) {

			for (auto& rect : zone_rects) {

				if (rect.page == page) {

					if (rect.rect.leftClicked()) {
						select_zone = rect.name;
						scene++;
						break;
					}
				}
			}

			if (back_rect.leftClicked()) {
				back = true;
			}
		}
		//Areaを選択
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


		if (left_rect.leftClicked()) {
			page--;
			if (page < 0) {
				page = 0;
			}
		}
		else if (right_rect.leftClicked()) {
			page++;

			if (page > 5) {
				page = 5;
			}
		}




		return back;
	}


	void draw()const {

		//Zoneを描画
		if (0 == scene) {

			for (auto& r : zone_rects) {

				if (r.page == page) {

					if (r.name != select_zone) {
						r.rect.draw(Palette::White);
					}
					else {
						r.rect.draw(Palette::Yellow);
					}

					
					FontAsset(U"BIZ_45")(r.name).drawAt(r.rect.x + r.rect.w / 2, r.rect.y + r.rect.h / 2, Palette::Black);
				}
			}

			FontAsset(U"BIZ_45")(U"ページ_" + Format(page)).drawAt(1920 / 2, 100, Palette::White);

			if (page >= 1) {
				left_rect.draw(Palette::White);
				FontAsset(U"BIZ_45")(U"←").drawAt(left_rect.x + left_rect.w / 2, left_rect.y + left_rect.h / 2, Palette::Black);
			}

			if (page <= 4) {
				right_rect.draw(Palette::White);
				FontAsset(U"BIZ_45")(U"→").drawAt(right_rect.x + right_rect.w / 2, right_rect.y + right_rect.h / 2, Palette::Black);
			}
		}

		//Areaを描画
		else if (1 == scene) {

			for (auto& r : rects) {

				if (r.belong_zone == select_zone) {

					if (r.name != select_area) {
						r.rect.draw(Palette::White);
					}
					else {
						r.rect.draw(Palette::Yellow);
					}

				
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

	int page = 0;

	int zone_count = 0;

	String select_zone = U"";

	String select_area = U"";

	struct Zone_Rect {

		Zone_Rect(int set_page,String set_name, int set_x, int set_y) {

			page = set_page;
			name = set_name;
			x = set_x;
			y = set_y;
			rect = Rect(300 + x * (400 + 50), 200 + y * (100 + 50), 400, 100);
		}

		int page = 0;

		Rect rect;
		int x = 0;
		int y = 0;
		String name;
	};


	struct Select_Rect {

		Select_Rect(String set_name, int set_x, int set_y, String set_zone) {

			name = set_name;
			x = set_x;
			y = set_y;
			rect = Rect(300 + x * (400 + 50), 200 + y * (100 + 50), 400, 100);
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

	Rect left_rect;
	Rect right_rect;

};



//タイルの選択

class Select_Box {

public:

	Select_Box() {}
	Select_Box(String type, int x, int y) {

		m_type = type;

		//上に表示させるrect
		{
			const int wide = 150;
			const int height = 100;

			m_rect = RectF(x, y, wide, height);
		}

		//選択用のrect
		{
			const int wide = 75;
			const int height = 75;

			m_change_rect = RectF(x + 10, y + 10, wide, height);
		}

		//ボード設定
		{
			const int wide = 1600;
			const int height = 760;

			m_board = RoundRect(200, 200, wide, height, 5);

			m_corner_x = m_board.x + 50;
			m_corner_y = m_board.y + 50;
		}

		if (U"block" == type) {
			m_name = U"wood";
		}
		else if (U"enemy" == type) {
			m_name = U"bake";
		}
		else if (U"tile" == type) {
			m_name = U"gray_wall";
		}
		else if (U"deco" == type) {
			m_name = U"poster";
		}
		else if (U"event" == type) {
			m_name = U"save_point";
		}

		select_rect = Rect(0, 0, 0, 0);

		//縦スライダーを準備
		my_sliders.push_back(My_Slider(U"Y", 1750 - 100 + 80, 100 + 100 + 30, 700, 72 * 20 + 1080));
	}

	void update() {

		select = false;

		m_click = false;

		m_just_click = false;

		//離している状態
		if (not MouseL.pressed()) {
			m_close_click = false;
		}

		if (true == m_close_click) {
			m_click = true;
		}

		if (0 == state) {

			//変更
			if (m_change_rect.leftClicked()) {

				m_click = true;
				m_close_click = true;

				m_just_click = true;

				/*
				if (U"event"!=m_type) {
					state++;
				}*/

				state++;
			}
			//選択
			else if (m_rect.leftClicked()) {

				m_click = true;

				m_close_click = true;

				m_just_click = true;
			}


		}
		else if (1 == state) {

			m_click = true;

			m_close_click = true;

			bool press_slider = false;

			for (auto& slider : my_sliders) {

				scroll_y = slider.update();

				if (slider.get_click()) {
					press_slider = true;
				}
			}

			//アイコンクリック
			if (m_rect.leftClicked()) {
				state = 0;
			}

			//ボードの外をクリック
			else if (MouseL.down() and !m_board.leftClicked()) {

				state = 0;

			}
			//スライダーを触っている
			else if (press_slider) {



			}
			//ボードクリック
			else {

				if (U"enemy" == m_type) {

					for (auto& data : datas) {

						Rect rect(m_corner_x + data.x * 72, m_corner_y + data.y * 72, 72, 72);

						if (rect.leftClicked()) {
							m_name = data.name;

							plus_resent_data(data.name);

							m_just_click = true;
						}
					}

				}
				else {

					/*
					if (MouseL.down()) {
						Vec2 pos = Cursor::Pos();
						int x = (pos.x - m_corner_x) / 72;
						int y = (pos.y - m_corner_y) / 72;

						image_x = x;
						image_y = y;

						m_just_click = true;
					}*/

					if (0 == select_scene) {

						if (MouseL.down()) {

							Vec2 pos = Cursor::Pos();
							int x = (pos.x - m_corner_x) / 72;
							int y = ((pos.y - m_corner_y) + scroll_y) / 72;

							//image_x = x;
							//image_y = y;

							select_x = x;
							select_y = y;
							select_w = 1;
							select_h = 1;

							m_just_click = true;



							select_scene++;
						}
					}
					else if (1 == select_scene) {

						Vec2 pos = Cursor::Pos();
						int x = (pos.x - m_corner_x) / 72;
						int y = ((pos.y - m_corner_y) + scroll_y) / 72;

						select_w = x - select_x;
						select_h = y - select_y;
						select_w++;
						select_h++;


						if (MouseL.up()) {

							m_just_click = true;

							select_scene = 0;
						}
					}

				}

				/*
				for (auto& recent_data : recent_datas) {

					Rect rect(m_corner_x + recent_data.x * 72, m_corner_y + recent_data.y * 72 + 600, 72, 72);

					if (rect.leftClicked()) {
						m_name = recent_data.name;

						m_just_click = true;
					}
				}*/
			}
		}

		select_rect = Rect(m_corner_x + select_x * 72, m_corner_y + select_y * 72, select_w * 72, select_h * 72);


		//押されている間はEditを使わせない
		if (m_change_rect.leftPressed() or m_rect.leftPressed()) {
			m_click = true;
		}

	}

	void up_down(int v) {
		m_rect.moveBy(0, v);
		m_change_rect.moveBy(0, v);
	}

	void draw()const {

		m_rect.draw(Palette::White);
		m_rect.drawFrame(2, Palette::Gray);

		if (true == select) {
			m_rect.draw(Palette::Lightpink);
		}

		//FontAsset(U"MyFont")(m_type).draw(m_rect, Palette::Black);

		/*
		String image_name = m_type + U"_" + m_name;

		TextureAsset(image_name).draw(m_rect.x + 10, m_rect.y + 10);
		*/

		//表示
		if (m_type != U"enemy") {
			String image_name = m_type + U"_tile";

			TextureAsset(image_name)(select_x * 72, select_y * 72, 72, 72).draw(m_rect.x + 10, m_rect.y + 10);
		}

		if (0 == state) {


		}

		if (1 == state) {

			m_board.draw(Palette::Gray);
			m_board(Texture(TextureAsset(U"transparent"))(0, 0, 1200, 720)).draw();


			if (m_type == U"enemy") {

				for (auto& data : datas) {

					String image_name = m_type + U"_" + data.name;

					TextureAsset(image_name).draw(m_corner_x + data.x * 72, m_corner_y + data.y * 72);
				}

			}
			else {

				String image_name = m_type + U"_tile";

				TextureAsset(image_name)(0, 0 + scroll_y, 72 * 20, 650).draw(m_corner_x, m_corner_y);

				/*
				for (auto& data : datas) {

					TextureAsset(U"deco_tile")(data.image_x * 72, data.image_y * 72, 72, 72).draw(m_corner_x + data.x * 72, m_corner_y + data.y * 72);
				}*/
			}


			select_rect.movedBy(0, -scroll_y).drawFrame(3, Palette::Red);



			/*
			for (auto& recent_data : recent_datas) {

				String image_name = m_type + U"_" + recent_data.name;

				TextureAsset(image_name).draw(m_corner_x + recent_data.x * 72, m_corner_y + recent_data.y * 72 + 600);
			}*/
		}

		if (1 == state) {
			for (auto& slider : my_sliders) {
				slider.draw();
			}
		}
	}

	bool get_click() {
		return m_click;
	}

	bool get_just_click() {
		return m_just_click;
	}

	void plus_data(String name) {

		int x = 0;
		int y = 0;

		x = data_w;
		y = data_h;


		datas.push_back(Data(name, x, y));

		data_w++;

		if (data_w_max < data_w) {
			data_w = 0;
			data_h++;
		}
	}

	void plus_data(int set_x, int set_y) {

	}

	void plus_data(String set_name, int set_x, int set_y) {

	}

	String get_type() { return m_type; }

	String get_name() { return m_name; }

	void set_select() { select = true; }

	void plus_resent_data(String name) {

		recent_datas.push_back(Data(name, recent_x, 0));

		if (recent_x >= 10) {

			recent_datas.remove_if([&](Data r_data) {

				if (0 == r_data.x) {
					return true;
				}

			return false;
			});


			for (auto& recent_data : recent_datas) {
				recent_data.x--;
			}
		}



		if (recent_x < 10) {
			recent_x++;
		}
	}

	Array<String> get_data_names() {

		Array<String> names;
		for (auto& data : datas) {
			names << data.name;
		}
		return names;
	}



	int get_select_x() { return select_x; }
	int get_select_y() { return select_y; }
	int get_select_w() { return select_w; }
	int get_select_h() { return select_h; }

private:

	int state = 0;

	String m_type;


	RectF m_rect;
	RectF m_change_rect;

	RoundRect m_board;

	Array<My_Slider> my_sliders;

	float scroll_y = 0;

	struct Data
	{
		Data(String set_name, int set_x, int set_y) :
			name(set_name),
			x(set_x),
			y(set_y)
		{
		}

		Data(String set_name, int set_x, int set_y, int set_image_x, int set_image_y) :
			name(set_name),
			x(set_x),
			y(set_y),
			image_x(set_image_x),
			image_y(set_image_y)
		{
		}

		//Deco
		Data(int set_x, int set_y, int set_image_x, int set_image_y) :
			x(set_x),
			y(set_y),
			image_x(set_image_x),
			image_y(set_image_y)
		{
		}

		String name = U"";
		int x;
		int y;

		int image_x = 0;
		int image_y = 0;
	};

	Array<Data> datas;

	int recent_x = 0;
	Array<Data> recent_datas;



	int data_w = 0;
	int data_h = 0;
	const int data_w_max = 10;
	const int data_h_max = 5;

	String m_name = U"wood";

	bool m_click = false;

	bool m_close_click = false;

	bool m_just_click = false;

	int m_corner_x = 0;
	int m_corner_y = 0;

	bool select = false;








	//範囲選択
	Rect select_rect;
	int select_scene = 0;
	int select_x = 0;
	int select_y = 0;
	int select_w = 1;
	int select_h = 1;
};



//ツールを選択する

class Tool_Selecter {

public:

	Tool_Selecter() {

		set_tool(U"pen", 0);
		set_tool(U"bucket", 1);

		select_tool = U"pen";
	}

	void set_tool(String set_name, int y) {
		tool_rects.push_back(Tool_Rect(set_name, Rect(20, 280 + 30 + (y * (100 + 30)), 150, 100)));
	}



	bool update() {

		bool back = false;

		for (auto& tool : tool_rects) {
			if (tool.rect.leftClicked()) {

				select_tool = tool.name;
				back = true;
				break;
			}
		}

		if (false == back) {

			if (MouseL.down()) {
				back = true;
			}
		}

		return back;
	}

	void draw()const {

		for (auto& tool : tool_rects) {

			tool.rect.draw(Palette::White);
			FontAsset(U"BIZ_30")(tool.name).drawAt(tool.rect.x + tool.rect.w / 2, tool.rect.y + tool.rect.h / 2, Palette::Black);
		}
	}

	String get_tool() { return select_tool; }

private:


	String select_tool;

	struct Tool_Rect {

		Tool_Rect(String set_name, Rect set_rect) {
			name = set_name;
			rect = set_rect;
		}

		String name;
		Rect rect;
	};

	Array<Tool_Rect> tool_rects;

};



//イベントなどの詳細

class Detail_Setter {

public:

	Detail_Setter() {

		back_rect = Rect(100, 1080 - 300, 100, 100);

		int x = 0;
		int y = 0;

		clear_key = Rect(1000, 500 - (100 + 30), 100 * 2 + 30 * 1, 100);
		delete_key = Rect(1000 + 2 * (100 + 30), 500 - (100 + 30), 100, 100);


		for (int i = 1; i < 10; i++) {

			keys.push_back(Key(1000 + x * (100 + 30), 500 + y * (100 + 30), 100, 100, i));

			x++;

			if (3 == x) {
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

			copy_v.pop_back_N(size - 1);

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
		FontAsset(U"BIZ_30")(U"back").draw(back_rect.x + back_rect.w / 2 - 30, back_rect.y + back_rect.h / 2, Palette::Black);

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

		Key(int set_x, int set_y, int set_w, int set_h, int set_v) {
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


//グリッド

struct Editor_Grid {

	Array<Line> lines;
	const int wide = 1920;
	const int height = 1080;

	Editor_Grid() {

		//横生成

		int yoko_honsuu = 1080 / 72 + 1;

		for (int i = 0; i < yoko_honsuu; i++) {
			plus(U"width", 0, i * 72);
		}


		//縦生成

		int tate_honsuu = 1920 / 72 + 1;

		for (int i = 0; i < tate_honsuu; i++) {
			plus(U"length", i * 72, 0);
		}


	}

	void plus(String type, int x, int y) {


		if (U"width" == type) {

			lines.push_back(Line(x, y, x + wide, y));

		}
		else if (U"length" == type) {

			lines.push_back(Line(x, y, x, y + height));
		}
	}



	void draw()const {

		for (auto& line : lines) {
			line.draw(3, Palette::Red);

		}


	}
};
