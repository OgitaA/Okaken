#pragma once

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
			line.draw(3,Palette::Red);

		}

		
	}
};
