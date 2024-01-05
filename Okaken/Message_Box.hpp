#pragma once

#include"Indent_Drawer.hpp"

class Message_Box {

public:

	Message_Box() {

		float wide = 1800;

		//調整用
		int w = 1300;
		int h = 300;


		m_pos = { 1920 / 2 - w / 2,1080 - 72 * 5 + ((72 * 5 - h) / 2) };

		m_on = true;

		m_text = U"このテキストが見える？！\nあなた何者？！";
	}

	void update(const float d_time) {

		if (true == m_on) {

		}

		if (character_count < 100) {

			count += d_time;

			if (count >= 0.04) {
				character_count++;
				count = 0;
			}
		}

		display_text = m_text.substr(0, character_count);



		if (character_count > m_text.size()) {
			end = true;
		}

	}

	void draw()const {

		if (true == m_on) {

			TextureAsset(U"message_box").draw(m_pos);

			if (U""==face) {

				indent_drawer.draw(FontAsset(U"BIZ_50"), display_text, 1200, m_pos.x + (1300 - 1200) / 2, m_pos.y + 45, Palette::White, 30);
			}
			else  {
				String face_image = U"face_" + face;
				TextureAsset(face_image).draw(m_pos.x + 10, m_pos.y + 10);
				int w = 1200 - 280;
				indent_drawer.draw(FontAsset(U"BIZ_50"), display_text, w, m_pos.x + 280 + ((1300 - 280) - w) / 2 - 20, m_pos.y + 45, Palette::White, 30);
			}
		}

	}

	void on() { m_on = true; }
	void off() { m_on = false; }

	void set_text(String v) { m_text = v; }
	void set_face(String v) { face = v; }

	void reset() {
		count = 0;
		character_count = 0;
		end = false;
	}

	bool check_end()
	{
		
		return end;
	}

	

	void show_all_text() {
		character_count = m_text.size() + 1;
	}

private:

	bool m_on = false;

	Vec2 m_pos;

	String m_text = U"";
	String display_text = U"";

	Indent_Drawer indent_drawer;

	String face = U"";

	float count = 0;
	int character_count = 0;

	//textをすべて表示したか
	bool end = false;



};
