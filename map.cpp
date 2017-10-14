#include "curses.h"
#include "map.h"
#define MAP_WIDTH			100
#define MAP_HEIGHT			25
#define TILE_FLOOR			0
#define TILE_WALL			1
#define TILE_OPEN_DOOR		2
#define TILE_CLOSED_DOOR    3

void Map::DrawMap(int* nMapArray) {
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			// Draw the tile
			switch (nMapArray[y][x])
			{
			case TILE_FLOOR:
				//add color eventually
				mvaddch(y, x, '.');
				break;
			case TILE_WALL:
				mvaddch(y, x, '#');
				break;
			case TILE_OPEN_DOOR:
				mvaddch(y, x, '+');
				break;
			case TILE_CLOSED_DOOR:
				mvaddch(y, x, '-');
				break;
			}
		} // end of for loop
	} // end of for loop

}


