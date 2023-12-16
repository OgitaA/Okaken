#include"Game_Manager.hpp"


//SE予約
void Game_Manager::play_se(String name) {

	se_wills << name;
}



//更新
void Game_Manager::update_se_main() {

	float d_time = Delta_Time;

	//Lock
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



	for (auto& will : se_wills) {

		bool is_lock = false;

		for (auto& lock : se_locks) {

			if (lock.count <= 0) {

				if (lock.name == will) {
					is_lock = true;
					lock.count = 0.1;
					break;
				}
			}
		}

		if (is_lock == false) {
			//音を鳴らす
			AudioAsset(will).playOneShot(volume);
		}
	}

	se_wills.clear();	
}






//BGMスタート
void Game_Manager::play_bgm(String name) {

	AudioAsset(name).play();
}


//BGM止める
void Game_Manager::stop_bgm() {

	for (auto& bgm : bgm_list) {

		AudioAsset(bgm).stop();
	}

}

