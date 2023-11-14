#include"Common.hpp"

#include"Title.hpp"
#include"Game.hpp"

void Main()
{
	// シーンマネージャーを作成
	App manager;

	manager.add<Title>(State::Title);
	manager.add<Game>(State::Game);
	//manager.add<Title>(State::Title);

	//最初のシーン
	manager.init(State::Game);


	//画面最大化
	// ウィンドウを最大化
	Scene::Resize(1920, 1080);
	Scene::SetResizeMode(ResizeMode::Keep);
	Window::SetFullscreen(true);

	while (System::Update())
	{
		if (not manager.update())
		{
			break;
		}
	}
}

//
// - Debug ビルド: プログラムの最適化を減らす代わりに、エラーやクラッシュ時に詳細な情報を得られます。
//
// - Release ビルド: 最大限の最適化でビルドします。
//
// - [デバッグ] メニュー → [デバッグの開始] でプログラムを実行すると、[出力] ウィンドウに詳細なログが表示され、エラーの原因を探せます。
//
// - Visual Studio を更新した直後は、プログラムのリビルド（[ビルド]メニュー → [ソリューションのリビルド]）が必要な場合があります。
//
