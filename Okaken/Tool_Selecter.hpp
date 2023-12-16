#pragma once

#include<Siv3D.hpp>

class Tool_Selecter {

public:

	Tool_Selecter(){

		set_tool(U"pen", 0);
		set_tool(U"bucket", 1);

		select_tool = U"pen";
	}

	void set_tool(String set_name,int y) {
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

		if (false==back) {

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

		Tool_Rect(String set_name,Rect set_rect) {
			name = set_name;
			rect = set_rect;
		}

		String name;
		Rect rect;
	};

	Array<Tool_Rect> tool_rects;

};
