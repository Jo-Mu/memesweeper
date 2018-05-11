#pragma once
#include "Vei2.h"


class Memefield
{
private:
	class Tile
	{
	public:
		enum class State
		{
			Hidden,
			Flagged,
			Revealed
		};
	public:
		void SpawnMeme();
		bool HasMeme() const;
	private:
		State state = State::Hidden;
		bool hasMeme = false;
	};
public:
	Memefield(int nMemes);
	Memefield::Tile& TileAt(const Vei2 mapPos);
private:
	static constexpr int width = 20;
	static constexpr int height = 16;
	Tile field[width * height];
};