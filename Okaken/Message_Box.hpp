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

		m_text = U"あああああああああああああああああああああああああああああああああああああああ";
	}

	void update(const float d_time) {

		if (true == m_on) {

		}
	}

	void draw()const {

		if (true == m_on) {

			TextureAsset(U"message_box").draw(m_pos);

			if (U""==face) {

				indent_drawer.draw(FontAsset(U"BIZ_50"), m_text, 1200, m_pos.x + (1300 - 1200) / 2, m_pos.y + 45, Palette::White, 30);
			}
			else  {
				String face_image = U"face_" + face;
				TextureAsset(face_image).draw(m_pos.x + 10, m_pos.y + 10);
				int w = 1200 - 280;
				indent_drawer.draw(FontAsset(U"BIZ_50"), m_text, w, m_pos.x + 280 + ((1300 - 280) - w) / 2 - 20, m_pos.y + 45, Palette::White, 30);
			}
		}

	}

	void on() { m_on = true; }
	void off() { m_on = false; }

	void set_text(String v) { m_text = v; }
	void set_face(String v) { face = v; }

private:

	bool m_on = false;

	Vec2 m_pos;

	String m_text = U"";

	Indent_Drawer indent_drawer;

	String face = U"";
};
