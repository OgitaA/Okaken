#pragma once

class My_Button {

public:

	My_Button(){}
	My_Button(String set_name,int x,int y,int w,int h) {
		m_name = set_name;
		m_rect = Rect(x, y, w, h);
	}

	void update() {

		click = false;
		press = false;

		if (m_rect.leftClicked()) {
			click = true;
		}

		if (m_rect.leftPressed()) {
			press = true;
		}
	}

	void draw()const {

		m_rect.rounded(3).draw(Palette::White);

		FontAsset(U"BIZ_30")(m_name).drawAt({ m_rect.x + m_rect.w / 2,m_rect.y + m_rect.h / 2 }, Palette::Black);
	
	}

	bool get_click() { return click; }

	bool get_press() { return press; }

	String get_name() { return m_name; }

private:

	String m_name;

	RectF m_rect;

	bool click = false;

	bool press = false;
};
