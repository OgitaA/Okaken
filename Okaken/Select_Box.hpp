#pragma once

#include"My_Slider.hpp"

class Select_Box {

public:

	Select_Box(){}
	Select_Box(String type,int x,int y) {

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

			m_board = RoundRect(200, 200, wide, height,5);

			m_corner_x = m_board.x + 50;
			m_corner_y = m_board.y + 50;
		}

		if (U"block" == type) {
			m_name = U"wood";
		}
		else if (U"enemy" == type) {
			m_name = U"bake";
		}
		else if (U"tile"==type) {
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
			else if (MouseL.down() and ! m_board.leftClicked()) {

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
						int y = ((pos.y - m_corner_y)+scroll_y) / 72;

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


			if (m_type==U"enemy") {

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


		datas.push_back(Data(name,x,y));

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

	Array<String> get_data_names(){

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
		Data(String set_name,int set_x,int set_y):
			name(set_name),
			x(set_x),
			y(set_y)
		{
		}

		Data(String set_name, int set_x, int set_y,int set_image_x,int set_image_y) :
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
