#pragma once

#include<Siv3D.hpp>

//ゲーム全体で持つ変数
struct Event_Var
{
	Event_Var(){}
	Event_Var(String set_name,int set_var) {
		name = set_name;
		var = set_var;
	}

	String name;
	int var;


	template <class Archive>
	void SIV3D_SERIALIZE(Archive& archive)
	{
		archive(name,var);
	}
};

//個々のイベント
struct Event_Sub{

	Event_Sub() {}
	Event_Sub(String v) {

	}

	template <class Archive>
	void SIV3D_SERIALIZE(Archive& archive)
	{
		archive(ID, scene);
	}



	//管理用のタグ
	String ID = U"none";

	//イベントシーン
	int scene = 0;


};

class Event_Super {

public:

	Event_Super(){}

	void plus_var(String set_name, int set_v) {

		m_e_v.push_back(Event_Var(set_name, set_v));
	}

	int get_var(String name) {
		for (auto& e_v : m_e_v) {

			if (e_v.name == name) {
				return e_v.var;
			}
		}
	}

	void set_var(String name,int v) {
		for (auto& e_v : m_e_v) {

			if (e_v.name == name) {
				e_v.var = v;
				break;
			}
		}
	}

	template <class Archive>
	void SIV3D_SERIALIZE(Archive& archive)
	{
		archive(m_e_v, m_e_sub);
	}

private:

	//変数を持つ
	Array<Event_Var> m_e_v;

	//個々のイベントのデータ
	Array<Event_Sub> m_e_sub;



};
