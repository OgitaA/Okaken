#include"Game_Manager.hpp"


//SE予約
void Game_Manager::play_se(String name) {

	bool exist = false;

	for (auto& will : se_wills) {

		if (will == name) {
			exist = true;
			break;
		}
	}

	//se_willに追加
	if (false == exist) {
		se_wills << name;
	}
}



//更新
void Game_Manager::update_se_main() {

	float d_time = Delta_Time;

	//Lockのカウントを減少させる
	for (auto& lock : se_locks) {

		if (lock.count > 0) {
			lock.count -= d_time;
		}
	}

	play_se_main();
}

//鳴らす
void Game_Manager::play_se_main() {

	double volume = double(se_volume) / double(10);

	/*
	//すべてのseを検索
	for (auto& will : se_wills) {

		bool is_lock = false;

		for (auto& lock : se_locks) {

			//ロックがかかっていない
			if (lock.count <= 0) {

				if (lock.name == will) {

					//ロックを設定
					lock.count = 0.001;
					break;
				}
			}
			//ロックがかかっている
			else {
				is_lock = true;
			}
		}

		if (is_lock == false) {
			//音を鳴らす

			//Print << U"pass::" << will;

			AudioAsset(will).playOneShot(volume);

			
		}
	}*/

	for (auto& will : se_wills) {

		AudioAsset(will).playOneShot(volume);
	}

	se_wills.clear();	
}






//BGMスタート
void Game_Manager::play_bgm(String name) {

	AudioAsset(name).play();

	bgm_name = name;
}


//BGM止める
void Game_Manager::stop_bgm() {

	for (auto& bgm : bgm_list) {

		AudioAsset(bgm).stop();
	}

}

void Game_Manager::change_bgm_volume() {

	double volume = double(bgm_volume) / double(10);

	for (auto& bgm : bgm_list) {

		AudioAsset(bgm).setVolume(volume);
	}

}

