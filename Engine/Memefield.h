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
		void Draw(const Vei2& screenPos, bool isGameOver, Graphics& gfx) const;
		void Reveal();
		bool IsRevealed() const;
		void ToggleFlag();
		bool IsFlagged() const;
		void SetNeighborMemeCount(int memeCount);
	private:
		State state = State::Hidden;
		bool hasMeme = false;
		int nNeighborMemes = -1;
	};
public:
	Memefield(int nMemes, const Vei2& in_startPos);
	void DrawMap(Graphics& gfx ) const;
	RectI GetRect() const;
	void OnRevealClick(const Vei2& screenPos);
	void OnFlagClick(const Vei2& screenPos);
	bool IsGameWon() const;
	int GetGridWidth() const;
	int GetGridHeight() const;
private:
	Memefield::Tile& TileAt(const Vei2 gridPos);
	const Memefield::Tile& TileAt(const Vei2 gridPos) const;
	Vei2 ScreenToGrid(const Vei2& mousePos) const;
	int CountNeighborMemes(const Vei2& gridPos) const;
private:
	static constexpr int width = 16;
	static constexpr int height = 16;
	Tile field[width * height];
	const Vei2 startPos;
	int nSafeTilesRemaining;
	bool isGameOver = false;
	bool isGameWon = false;
	int borderPadding = 10;
};