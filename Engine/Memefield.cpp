#include "Memefield.h"
#include <assert.h>
#include <random>
#include "SpriteCodex.h"
#include "Colors.h"

void Memefield::Tile::SpawnMeme()
{
	assert(!hasMeme);

	hasMeme = true;
}

bool Memefield::Tile::HasMeme() const
{
	return hasMeme;
}

void Memefield::Tile::Draw(const Vei2 & screenPos, Graphics & gfx) const
{
	switch (state) 
	{
		case State::Hidden:
			SpriteCodex::DrawTileButton(screenPos, gfx);
			break;
		case State::Flagged:
			SpriteCodex::DrawTileButton(screenPos, gfx);
			SpriteCodex::DrawTileFlag(screenPos, gfx);
			break;
		case State::Revealed:
			if(!hasMeme)
			{
				SpriteCodex::DrawTile0(screenPos, gfx);
			}
			else
			{
				SpriteCodex::DrawTileBomb(screenPos, gfx);
			}
			break;
		default:
			SpriteCodex::DrawTileButton(screenPos, gfx);
			break;
	}


}

void Memefield::Tile::Reveal()
{

	state = State::Revealed;
}

bool Memefield::Tile::IsRevealed() const
{
	return state == State::Revealed;
}

void Memefield::Tile::ToggleFlag()
{
	assert(!IsRevealed());

	if (!IsFlagged()) 
	{
		state = State::Flagged;
	}
	else
	{
		state = State::Hidden;
	}
}

bool Memefield::Tile::IsFlagged() const
{
	return state == State::Flagged;
}

void Memefield::Tile::SetNeighborMemeCount(int memeCount)
{
	assert(nNeighborMemes == -1);

	nNeighborMemes = memeCount;
}

Memefield::Memefield(int nMemes, const Vei2& in_startPos)
	:
	startPos(in_startPos)
{
	assert(nMemes > 0 && nMemes < width * height);

	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> xDist(0, width - 1);
	std::uniform_int_distribution<int> yDist(0, height - 1);

	for(int i = 0; i < nMemes; i++)
	{
		Vei2 spawnPos;

		do
		{
			spawnPos = Vei2(xDist(rng), yDist(rng));
		} 
		while (TileAt(spawnPos).HasMeme());

		TileAt(spawnPos).SpawnMeme();
	}

	for (Vei2 gridPos = { 0, 0 }; gridPos.y < height; gridPos.y++)
	{
		for (gridPos.x = 0; gridPos.x < width; gridPos.x++)
		{
			TileAt(gridPos).SetNeighborMemeCount(CountNeighborMemes(gridPos));
		}
	}
}

Memefield::Tile & Memefield::TileAt(const Vei2 gridPos)
{
	return field[(gridPos.y * height) + gridPos.x];
}

const Memefield::Tile & Memefield::TileAt(const Vei2 gridPos) const
{
	return field[(gridPos.y * height) + gridPos.x];
}

void Memefield::DrawMap(Graphics & gfx) const
{
	assert(startPos.x >= 0 && startPos.y >= 0);

	gfx.DrawRect(GetRect(), SpriteCodex::baseColor);

	for (Vei2 gridPos = {0, 0}; gridPos.y < height; gridPos.y++)
	{
		for(gridPos.x = 0; gridPos.x < width; gridPos.x++)
		{
			TileAt(gridPos).Draw((gridPos * SpriteCodex::tileSize) + startPos, gfx);
		}
	}
}

RectI Memefield::GetRect() const
{
	return RectI(startPos, width * SpriteCodex::tileSize, height * SpriteCodex::tileSize);
}

void Memefield::OnRevealClick(const Vei2 & screenPos)
{
	const Vei2 gridPos = ScreenToGrid(screenPos);
	assert(gridPos.x >= 0 && gridPos.x < width && gridPos.y >= 0 && gridPos.y < height);

	Tile& tile = TileAt(gridPos);
	if(!tile.IsRevealed())
	{
		tile.Reveal();
	}
}

void Memefield::OnFlagClick(const Vei2 & screenPos)
{
	const Vei2 gridPos = ScreenToGrid(screenPos);
	assert(gridPos.x >= 0 && gridPos.x < width && gridPos.y >= 0 && gridPos.y < height);

	Tile& tile = TileAt(gridPos);
	if(!tile.IsRevealed())
	{
		tile.ToggleFlag();
	}
}

Vei2 Memefield::ScreenToGrid(const Vei2 & mousePos) const
{
	return (mousePos - startPos)/SpriteCodex::tileSize;
}

int Memefield::CountNeighborMemes(const Vei2 & gridPos) const
{
	int memeCount = 0;
	const int startX = std::max(0, gridPos.x - 1);
	const int startY = std::max(0, gridPos.y - 1);
	const int endX = std::min(width - 1, gridPos.x + 1);
	const int endY = std::min(height - 1, gridPos.y + 1);

	for(Vei2 tilePos = Vei2(startX, startY); tilePos.y <= endY; tilePos.y++)
	{
		for(tilePos.x = startX; tilePos.x <= endX; tilePos.x++)
		{
			if(TileAt(tilePos).HasMeme())
			{
				memeCount++;
			}
		}
	}

	return memeCount;
}
