#include "Memefield.h"
#include <assert.h>
#include <random>

void Memefield::Tile::SpawnMeme()
{
	assert(!hasMeme);

	hasMeme = true;
}

bool Memefield::Tile::HasMeme() const
{
	return hasMeme;
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
