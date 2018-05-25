#pragma once
#include "Vei2.h"
#include "Graphics.h"
#include "RectI.h"

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
		void Reveal();
		bool IsRevealed() const;
		void ToggleFlag();
		bool IsFlagged() const;
	private:
		State state = State::Hidden;
		bool hasMeme = false;
	};
public:
	Memefield(int nMemes);
	Memefield::Tile& TileAt(const Vei2 mapPos);
	const Memefield::Tile& TileAt(const Vei2 mapPos) const;
	void DrawMap(const Vei2& startPos, Graphics& gfx ) const;
	RectI GetRect(const Vei2& startPos) const;
	void OnRevealClick(const Vei2& screenPos);
	void OnFlagClick(const Vei2& screenPos);
private:
	static constexpr int width = 16;
	static constexpr int height = 16;
	Tile field[width * height];
	Vei2 ScreenToGrid(const Vei2& mousePos) const;
};