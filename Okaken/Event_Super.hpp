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
		archive(m_e_v);
	}

private:

	//変数を持つ
	Array<Event_Var> m_e_v;

};
