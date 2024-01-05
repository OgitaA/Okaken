#include"Stick.hpp"

void Stick::make_attack(String direction, float x, float y) {

	exist = true;
	m_direction = direction;

	//初期化



	reset();
}


void Stick::update_attack(String direction, float x, float y) {

	if (true == exist) {

		if (U"left" == m_direction) {

			m_pos = { x - 30 ,y + 60 };
		}
		else if (U"right" == m_direction) {
			m_pos = { x + 30,y + 60 };
		}



		//m_hit_rect = RectF(m_pos, 172, 263);

		m_hit_rect = RectF(m_pos, 210, 200 / 2);

		if (U"right" == m_direction) {

			//上の△
			m_hit_triangles[0] = Triangle(Vec2{ m_pos.x + 125, m_pos.y - 113 }, Vec2{ m_pos.x + 125,m_pos.y }, Vec2{ m_pos.x, m_pos.y });

			{
				Vec2 p = { m_pos.x + 125, m_pos.y - 113 };//一番上の頂点
				m_hit_triangles[1] = Triangle(Vec2{ p }, Vec2{ p.x + 48,p.y + 113 }, Vec2{ p.x,p.y + 113 });
			}

			{
				Vec2 p = { m_pos.x + 125, m_pos.y - 113 };
				m_hit_triangles[2] = Triangle(Vec2{ p.x + 30,p.y + 40 }, Vec2{ m_pos.x + 160 + 13, m_pos.y }, Vec2{ p });
			}


			//下の△
			{
				m_hit_triangles[3] = Triangle(Vec2{ m_pos.x + 160, m_pos.y }, Vec2{ m_pos.x + 160, m_pos.y + 80 }, Vec2{ m_pos.x, m_pos.y });
			}

			{
				m_hit_triangles[4] = Triangle(Vec2{ m_pos.x + 160 + 13, m_pos.y }, Vec2{ m_pos.x + 160, m_pos.y + 80 }, Vec2{ m_pos.x + 160, m_pos.y });
			}

		}
		else if (U"left" == m_direction) {

			//上の△
			m_hit_triangles[0] = Triangle(Vec2{ m_pos.x - 125, m_pos.y - 113 }, Vec2{ m_pos.x - 125,m_pos.y }, Vec2{ m_pos.x, m_pos.y });

			{
				Vec2 p = { m_pos.x - 125, m_pos.y - 113 };//一番上の頂点
				m_hit_triangles[1] = Triangle(Vec2{ p }, Vec2{ p.x - 48,p.y + 113 }, Vec2{ p.x,p.y + 113 });
			}

			{
				Vec2 p = { m_pos.x - 125, m_pos.y - 113 };
				m_hit_triangles[2] = Triangle(Vec2{ p.x - 30,p.y + 40 }, Vec2{ m_pos.x - 160 - 13, m_pos.y }, Vec2{ p });
			}


			//下の△
			{
				m_hit_triangles[3] = Triangle(Vec2{ m_pos.x - 160, m_pos.y }, Vec2{ m_pos.x - 160, m_pos.y + 80 }, Vec2{ m_pos.x, m_pos.y });
			}

			{
				m_hit_triangles[4] = Triangle(Vec2{ m_pos.x - 160 - 13, m_pos.y }, Vec2{ m_pos.x - 160, m_pos.y + 80 }, Vec2{ m_pos.x - 160, m_pos.y });
			}
		}
	}
}

void Stick::reset() {

	//初期化

	m_count = 0;


	page = 0;
	page_count = 0;
}
