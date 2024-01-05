#pragma once

#include<Siv3D.hpp>

class Indent_Drawer {

public:

	Indent_Drawer(){}

	void draw(FontAsset my_font, String my_text, int my_indent_v, float my_set_x, float my_set_y, ColorF color,int plus_h)const {

		Font font = my_font;

		const Vec2 basePos{ my_set_x, my_set_y };
		Vec2 penPos{ basePos };

		//横幅をカウント
		float my_wide = 0;

		
	
		// 文字単位で描画を制御するためのループ
		for (const auto& glyph : font.getGlyphs(my_text))
		{
		

			// 改行文字なら
			if (glyph.codePoint == U'\n')
			{
				//幅リセット
				my_wide = 0;

				// ペンの X 座標をリセット
				penPos.x = basePos.x;

				// ペンの Y 座標をフォントの高さ分進める+補助
				penPos.y += font.height() + plus_h;

				continue;
			}

			// 文字のテクスチャをペンの位置に文字ごとのオフセットを加算して描画
			// FontMethod がビットマップ方式の場合に限り、Math::Round() で整数座標にすると品質が向上
			glyph.texture.draw(Math::Round(penPos + glyph.getOffset()), color);

			// ペンの X 座標を文字の幅の分進める
			penPos.x += glyph.xAdvance;

			//移動した分カウント
			my_wide += glyph.xAdvance;

			if (my_indent_v <= my_wide) {

				//幅リセット
				my_wide = 0;

				// ペンの X 座標をリセット
				penPos.x = basePos.x;

				// ペンの Y 座標をフォントの高さ分進める+補助
				penPos.y += font.height() + plus_h;
			}
			
		}
	}

};

