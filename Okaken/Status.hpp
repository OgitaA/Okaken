#pragma once
#include<Siv3D.hpp>

struct Have_Maga {

	Have_Maga(){}
	Have_Maga(String set_name, int set_x) {
		name = set_name;
		x = set_x;
	}

	String name = U"";
	int x = 0;

	template <class Archive>
	void SIV3D_SERIALIZE(Archive& archive)
	{
		archive(name, x);
	}
};


struct Equip_Charm {

	Equip_Charm() {}
	Equip_Charm(String set_name, int set_x) {
		name = set_name;
		x = set_x;
	}

	String name;
	int x;

	template <class Archive>
	void SIV3D_SERIALIZE(Archive& archive)
	{
		archive(name, x);
	}

};


struct Have_Charm {

	Have_Charm() {}
	Have_Charm(String set_name, int set_x, int set_y) :
		name(set_name),
		x(set_x),
		y(set_y)
	{
	}

	String name;
	int x;
	int y;


	template <class Archive>
	void SIV3D_SERIALIZE(Archive& archive)
	{
		archive(name, x, y);
	}
};


struct Have_Item {

	Have_Item() {}
	Have_Item(String set_name, int set_x, int set_y) :
		name(set_name),
		x(set_x),
		y(set_y)
	{
	}

	String name;
	int x;
	int y;

	void plus_number(int v) {

		number += v;

		if (number > number_max) {
			number = number_max;
		}
	}

	bool minus_number(int v) {

		number -= v;

		if (number < 0) {
			number = 0;
		}

		return true;
	}

	int get_number() { return number; }

	template <class Archive>
	void SIV3D_SERIALIZE(Archive& archive)
	{
		archive(name, x, y, number);
	}



private:

	int number = 0;
	int number_max = 99;

};

struct Restart_Point {

	String area;

	int x;
	int y;

	template <class Archive>
	void SIV3D_SERIALIZE(Archive& archive)
	{
		archive(area, x, y);
	}

};







//Saveにもつかうよ！！
class Status {

public:


	Status(){
		
	}

	

	//Money

	int get_money()const {return m_money; }

	void plus_money(int v) {
		m_money += v;
		if (m_money > m_money_max) {
			m_money = m_money_max;
		}
	}

	void minus_money(int v) {
		m_money -= v;
		if (m_money < 0) {
			m_money = 0;
		}
	}

	bool use_money(int v){

		//使用するお金の方が大きい
		if (m_money < v) {

			return false;
		}

		m_money -= v;

		if (m_money < 0) {
			m_money = 0;
		}

		return true;
	}

	void set_money(int v) { m_money = v; }

	//Life
	int get_life()const { return m_life; }
	int get_life_max()const { return m_life_max; }

	void minus_life(int v) {
		m_life -= v;
		if (m_life < 0) {
			m_life = 0;
		}
	}

	void plus_life(int v) {
		m_life += v;
		if (m_life_max < m_life) {
			m_life = m_life_max;
		}
	}

	void full_life() {
		m_life = m_life_max;
	}



	//Power
	float get_power()const { return m_power; }
	int get_power_max()const { return m_power_max; }

	void plus_power(int v) {
		m_power += v;
		if (m_power > m_power_max) {
			m_power = m_power_max;
		}
	}

	void minus_power(int v) {
		m_power -= v;
		if (m_power < 0) {
			m_power = 0;
		}
	}


	//Charm
	Array<Have_Charm> get_have_charms()const {
		return have_charms;
	}

	void plus_have_charm(String name) {

		bool exist = false;

		

		//まだない
		if (false == exist) {

			int memo_x = -1;
			int memo_y = -1;

			bool go_break = false;

			for (int y = 0; y < 3; y++) {
				for (int x = 0; x < 8; x++) {

					bool exist = false;

					for (auto& charm : have_charms) {

						//ある
						if (x == charm.x and y == charm.y) {
							exist = true;
							break;
						}
					}

					//無い
					if (false == exist) {
						memo_x = x;
						memo_y = y;

						go_break = true;
						break;
					}
				}

				if (true == go_break) {
					break;
				}
			}


			if (-1 == memo_x and -1 == memo_y) {
				Print << U"満杯です！！";
			}
			else {
				have_charms.push_back(Have_Charm(name, memo_x, memo_y));
			}

		}



	}

	void plus_have_charm(String set_name, int set_x, int set_y) {

		have_charms.push_back(Have_Charm(set_name, set_x, set_y));
	}

	bool minus_have_charm(String name) {

		have_charms.remove_if([&](Have_Charm charm) {

			if (name == charm.name) {
				return true;
			}

		return false;


		});


		return true;
	}

	void plus_equip_charm(String name) {

		if (equip_charms.size() < 3) {

			int v = 0;

			for (int x = 0; x < 3; x++) {

				bool exist = false;

				for (auto& charm : equip_charms) {

					//すでにある
					if (x == charm.x) {
						exist = true;
						break;
					}

				}

				//無かった→空き
				if (false == exist) {
					v = x;
					break;
				}

			}

			equip_charms.push_back(Equip_Charm(name, v));
		}

	}

	void minus_equip_charm(int v) {

		equip_charms.remove_if([&](Equip_Charm charm) {

			if (v == charm.x) {
				return true;
			}

		return false;

		});
	}

	Array<Equip_Charm> get_equip_charms()const { return equip_charms; }



	//Have_Maga
	void plus_maga(String set_name) {

		int x_max = 0;

		for (auto& have_maga : have_magas) {

			if (have_maga.x > x_max) {
				x_max = have_maga.x;
			}
		}

		have_magas.push_back(Have_Maga(set_name, x_max++));

	}



	Array<Have_Maga> get_have_magas()const { return have_magas; }


	//Have_Item

	void plus_have_item(String name,int v) {

		bool exist = false;

		//すでにある？？
		for (auto& item : have_items) {

			if (name == item.name) {
				exist = true;

				//数を増やす
				item.plus_number(v);

				break;
			}
		}

		//まだない
		if (false == exist) {

			int memo_x = -1;
			int memo_y = -1;



			bool end = false;

			for (int y = 0; y < 10; y++) {
				for (int x = 0; x < 10; x++) {

					bool exist = false;

					for (auto& item : have_items) {

						//場所が埋まっている
						if (x == item.x and y == item.y) {
							exist = true;
							break;
						}
					}

					//空きがあったら登録＋処理終了
					if (false == exist) {
						memo_x = x;
						memo_y = y;

						end = true;
						break;
					}


				}

				if (true == end) {
					break;
				}
			}


			if (-1 == memo_x and -1 == memo_y) {
				Print << U"満杯です！！";
			}
			else {

				//Print << U"memo_x::" << memo_x;
				//Print << U"memo_y::" << memo_y;

				have_items.push_back(Have_Item(name, memo_x, memo_y));
			}

		}

		

	}

	void plus_have_item(String set_name,int set_x,int set_y) {

		have_items.push_back(Have_Item(set_name, set_x, set_y));
	}

	bool minus_have_item(String name,int v) {

		int count = check_have_item(name);

		if (count<v) {

			//足りない
			return false;
 		}

		//減らす
		for (auto& item : have_items) {

			if (name == item.name) {
				item.minus_number(v);
			}
		}

		//0になったら除外
		have_items.remove_if([&](Have_Item item) {

			if (item.get_number() <= 0) {
				return true;
			}

		     return false;
         });


		return true;
	}

	int check_have_item(String name) {

		int count = 0;

		//すでにある？？
		for (auto& item : have_items) {

			if (name == item.name) {
				count++;
			}
		}

		return count;
	}

	Array<Have_Item> get_have_items()const { return have_items; }

	

	//Shop_Solds

	Array<String> get_shop_solds(){
		return shop_solds;
	}

	void plus_shop_solds(String data) {
		shop_solds.push_back(data);
	}

	void set_first_used() {
		first = false;
	}

	bool get_first() {
		return first;
	}

	void set_restart_point(String set_area,int set_x,int set_y) {
		restart_point.area = set_area;
		restart_point.x = set_x;
		restart_point.y = set_y;
	}

	String get_restart_point_area() {
		return restart_point.area;
	}

	int get_restart_point_x() {
		return restart_point.x;
	}

	int get_restart_point_y() {
		return restart_point.y;
	}

	template <class Archive>
	void SIV3D_SERIALIZE(Archive& archive)
	{
		archive(m_money, m_life, m_life_max, have_magas, equip_charms, have_charms, have_items, shop_solds, restart_point, first);
	}


private:

	int m_money = 0;
	const int m_money_max = 9999999;

	int m_life = 3;
	int m_life_max = 5;

	float m_power = 3;
	int m_power_max = 5;

	//Menu系統
	Array<Have_Maga> have_magas;

	Array<Equip_Charm> equip_charms;
	Array<Have_Charm> have_charms;

	Array<Have_Item> have_items;

	//すでに売られた商品
	Array<String> shop_solds;

	//リスタート場所
	Restart_Point restart_point;

	//初期化データか
	bool first = true;

};
