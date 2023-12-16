#pragma once

//管理表示用（無くても変わらない）

struct Event_List {

	Event_List(int set_ID,String set_name) {

		ID = set_ID;
		name = set_name;	
	}


	int ID;
	String name;
	

};
