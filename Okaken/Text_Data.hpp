#pragma once

#include<Siv3D.hpp>

class Text_Charm {

public:


	Text_Charm(){}
	Text_Charm(String set_name,String set_text){

		name = set_name;
		text = set_text;
	}

	String get_name()const { return name; }
	String get_text()const { return text; }

private:


	String name = U"";
	String text = U"";


};


class Text_Maga {

public:


	Text_Maga() {}
	Text_Maga(String set_name, String set_text) {

		name = set_name;
		text = set_text;
	}

	String get_name()const { return name; }
	String get_text()const { return text; }

private:


	String name = U"";
	String text = U"";


};


class Text_Weapon {

public:


	Text_Weapon() {}
	Text_Weapon(String set_name, String set_text) {

		name = set_name;
		text = set_text;
	}

	String get_name()const { return name; }
	String get_text()const { return text; }

private:


	String name = U"";
	String text = U"";


};


class Text_Item {

public:


	Text_Item() {}
	Text_Item(String set_name, String set_text) {

		name = set_name;
		text = set_text;
	}

	String get_name()const { return name; }
	String get_text()const { return text; }

private:


	String name = U"";
	String text = U"";


};
