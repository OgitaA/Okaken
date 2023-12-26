#pragma once

//eventとblockの処理省略

//Curにもdeltatime変更

//Shopの数が３以下など

//ウィルコインの上限処理




#include<Siv3D.hpp>

class Object {

public:

	Object(){}
	~Object(){}

	//関数
	/*
	void change_state(State s) {

		state = s;

		count = 0;
	}


	void update() {

		if (KeyZ.down()) {
			change_state(State::active);
		}

	}*/

private:

	enum State {

		sleep,
		active

	};

	State state;

	int count = 0;

};
