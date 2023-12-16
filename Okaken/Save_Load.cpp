#include"Game_Manager.hpp"



void Game_Manager::save_area_data() {

	//Block
	{

		String adress = U"stage_data/" + area + U"/block_data.bin";

		// バイナリファイルをオープン
		Serializer<BinaryWriter> writer{ adress };

		if (not writer) // もしオープンに失敗したら
		{
			throw Error{ U"Failed to open" + adress };
		}

		// シリアライズに対応したデータを記録
		writer(block_datas);

	}

	//Enemy
	{

		String adress = U"stage_data/" + area + U"/enemy_data.bin";

		// バイナリファイルをオープン
		Serializer<BinaryWriter> writer{ adress };

		if (not writer) // もしオープンに失敗したら
		{
			throw Error{ U"Failed to open" + adress };
		}

		// シリアライズに対応したデータを記録
		writer(enemy_datas);

	}

	//Tile
	{

		String adress = U"stage_data/" + area + U"/tile_data.bin";

		// バイナリファイルをオープン
		Serializer<BinaryWriter> writer{ adress };

		if (not writer) // もしオープンに失敗したら
		{
			throw Error{ U"Failed to open" + adress };
		}

		// シリアライズに対応したデータを記録
		writer(tile_datas);

	}

	//Event_Data
	{

		String adress = U"stage_data/" + area + U"/event_data.bin";

		// バイナリファイルをオープン
		Serializer<BinaryWriter> writer{ adress };

		if (not writer) // もしオープンに失敗したら
		{
			throw Error{ U"Failed to open" + adress };
		}

		// シリアライズに対応したデータを記録
		writer(event_datas);

	}

	//Deco_Data
	{

		String adress = U"stage_data/" + area + U"/deco_data.bin";

		// バイナリファイルをオープン
		Serializer<BinaryWriter> writer{ adress };

		if (not writer) // もしオープンに失敗したら
		{
			throw Error{ U"Failed to open" + adress };
		}

		// シリアライズに対応したデータを記録
		writer(deco_datas);

	}


	//Player_Data
	{

		String adress = U"stage_data/" + area + U"/player_data.bin";

		// バイナリファイルをオープン
		Serializer<BinaryWriter> writer{ adress };

		if (not writer) // もしオープンに失敗したら
		{
			throw Error{ U"Failed to open" + adress };
		}

		// シリアライズに対応したデータを記録
		writer(player_data);

	}
	
}

void Game_Manager::load_area_data() {

	//Block
	{

		String adress = U"stage_data/" + area + U"/block_data.bin";

		// バイナリファイルをオープン
		Deserializer<BinaryReader> reader{ adress };

		if (not reader) // もしオープンに失敗したら
		{
			throw Error{ U"Failed to open" + adress };
		}

		// バイナリファイルからシリアライズ対応型のデータを読み込む
		// （Array は自動でリサイズが行われる）
		reader(block_datas);

	}

	

	//Enemy
	{
		String adress = U"stage_data/" + area + U"/enemy_data.bin";

		// バイナリファイルをオープン
		Deserializer<BinaryReader> reader{ adress };

		if (not reader) // もしオープンに失敗したら
		{
			throw Error{ U"Failed to open" + adress };
		}

		// バイナリファイルからシリアライズ対応型のデータを読み込む
		// （Array は自動でリサイズが行われる）
		reader(enemy_datas);

	}

	

	//Tile
	{
		String adress = U"stage_data/" + area + U"/tile_data.bin";

		// バイナリファイルをオープン
		Deserializer<BinaryReader> reader{ adress };

		if (not reader) // もしオープンに失敗したら
		{
			throw Error{ U"Failed to open" + adress };
		}

		// バイナリファイルからシリアライズ対応型のデータを読み込む
		// （Array は自動でリサイズが行われる）
		reader(tile_datas);

	}

	
	
	//Event
	{
		String adress = U"stage_data/" + area + U"/event_data.bin";

		// バイナリファイルをオープン
		Deserializer<BinaryReader> reader{ adress };

		if (not reader) // もしオープンに失敗したら
		{
			throw Error{ U"Failed to open" + adress };
		}

		// バイナリファイルからシリアライズ対応型のデータを読み込む
		// （Array は自動でリサイズが行われる）
		reader(event_datas);

	}

	

	//Deco
	{
		String adress = U"stage_data/" + area + U"/deco_data.bin";

		// バイナリファイルをオープン
		Deserializer<BinaryReader> reader{ adress };

		if (not reader) // もしオープンに失敗したら
		{
			throw Error{ U"Failed to open" + adress };
		}

		// バイナリファイルからシリアライズ対応型のデータを読み込む
		// （Array は自動でリサイズが行われる）
		reader(deco_datas);

	}
	

	//Player
	{
		String adress = U"stage_data/" + area + U"/player_data.bin";

		// バイナリファイルをオープン
		Deserializer<BinaryReader> reader{ adress };

		if (not reader) // もしオープンに失敗したら
		{
			throw Error{ U"Failed to open" + adress };
		}

		// バイナリファイルからシリアライズ対応型のデータを読み込む
		// （Array は自動でリサイズが行われる）
		reader(player_data);

	}


}


