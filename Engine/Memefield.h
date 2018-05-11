#pragma once
#include "Vei2.h"
#include "Graphics.h"

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
		void Draw(const Vei2& screenPos, Graphics& gfx) const;
	private:
		State state = State::Hidden;
		bool hasMeme = false;
	};
public:
	Memefield(int nMemes);
	Memefield::Tile& TileAt(const Vei2 mapPos);
	const Memefield::Tile& TileAt(const Vei2 mapPos) const;
	void DrawMap(const Vei2& startPos, Graphics& gfx ) const;
private:
	static constexpr int width = 16;
	static constexpr int height = 20;
	Tile field[width * height];
};