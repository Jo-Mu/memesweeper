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

Memefield::Memefield(int nMemes)
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
}

Memefield::Tile & Memefield::TileAt(const Vei2 mapPos)
{
	return field[(mapPos.y * height) + mapPos.x];
}

const Memefield::Tile & Memefield::TileAt(const Vei2 mapPos) const
{
	return field[(mapPos.y * height) + mapPos.x];
}

void Memefield::DrawMap(const Vei2 & startPos, Graphics & gfx) const
{
	assert(startPos.x >= 0 && startPos.y >= 0);

	gfx.DrawRect(startPos.x, startPos.y, 
		startPos.x + (width * SpriteCodex::tileSize), startPos.y + (height * SpriteCodex::tileSize),
			Colors::Gray);

	for (Vei2 gridPos = {0, 0}; gridPos.y < height; gridPos.y++)
	{
		for(gridPos.x = 0; gridPos.x < width; gridPos.x++)
		{
			TileAt(gridPos).Draw((gridPos * SpriteCodex::tileSize) + startPos, gfx);
		}
	}
}
