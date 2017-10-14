#include "curses.h"
//screen goes from 0-80 across and 0-24 down Chnages between computers??
#define MAP_WIDTH			100
#define MAP_HEIGHT			25
#define TILE_FLOOR			0
#define TILE_WALL			1
#define TILE_OPEN_DOOR		2
#define TILE_CLOSED_DOOR    3


int nMapArray[MAP_HEIGHT][MAP_WIDTH] = {};
void ClrMessage(void) {
	mvaddstr(22, 10, "                                           ");
}
void DrawMap(void) {
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

bool isPassable(int x, int y) {
	int tile = nMapArray[y][x];
		if (x<0 || x>MAP_WIDTH -1|| y<0 || y>MAP_HEIGHT-1) {
			return false;
		}

		if (tile == TILE_FLOOR || tile == TILE_OPEN_DOOR) {
			return true;
		}
		return false;
		
}

int main() {
	// Start pdcurses
	{
		initscr();
		start_color();
		clear();
		noecho();
		cbreak();
		keypad(stdscr, TRUE);
		curs_set(0);
		}
	// Start the game loop

		// Initialize the player's on-screen location
		int nPlayerX = 10, nPlayerY = 10;
		char nPlayerch = '@';
		bool on = true;
		char exit = 'n';
		long int turn = 0;
		// Wipe the console clean
		clear();
		while (on == true)
		{
			DrawMap();

			// Output phase - Draw the player to the screen
			mvaddch(nPlayerY, nPlayerX, nPlayerch);

			// Input phase - Wait for the player to do something

			// Processing phase - Implement the player's command
			switch (getch())
			{
				//exiting NEEDS FIXING!!!
				{
			case KEY_BACKSPACE:
				mvaddstr(22, 10, "Are you sure you want to exit? y/n");
				exit = getch();
				ClrMessage();
				if (exit = 'y') {
					on = false;
				}
				else if (exit = 'n') {
					on = true;
				}
				else {
					mvaddstr(22, 10, "Please enter a valid answer!");
				}
				break;
				}
				//Movement
				{
				// Move down
			case KEY_DOWN:
				if (isPassable(nPlayerX, nPlayerY + 1)) {
					nPlayerY++;
				}
				break;

				// Move left
			case KEY_LEFT:
				if (isPassable(nPlayerX - 1, nPlayerY)) {
					nPlayerX--;
				}
				break;

				// Move right
			case KEY_RIGHT:
				if (isPassable(nPlayerX + 1, nPlayerY)) {
					nPlayerX++;
				}
				break;

				// Move up
			case KEY_UP:
				if (isPassable(nPlayerX, nPlayerY - 1)) {
					nPlayerY--;
				}
				break;
				}

				//Kicking
				{
			case 'k':
				mvaddstr(22, 10, "What direction do you want to kick in?");
				switch (getch())
				{
				case KEY_DOWN:
					ClrMessage();
					if (nMapArray[nPlayerY + 1][nPlayerX] == TILE_CLOSED_DOOR) {
						nMapArray[nPlayerY + 1][nPlayerX] = TILE_FLOOR;
						mvaddstr(22, 10, "You break down the door!                    ");
						getch();
					}
					else if (nMapArray[nPlayerY + 1][nPlayerX] == TILE_FLOOR || TILE_OPEN_DOOR) {
						mvaddstr(22, 10, "There is nothing there to kick!");
						getch();
					}
					else {
						mvaddstr(22, 10, "Don't kick the wall!                        ");
						getch();
					}
					break;
				case KEY_LEFT:
					ClrMessage();
					if (nMapArray[nPlayerY][nPlayerX - 1] == TILE_CLOSED_DOOR) {
						nMapArray[nPlayerY][nPlayerX - 1] = TILE_FLOOR;
						mvaddstr(22, 10, "You break down the door!                    ");
						getch();
					}
					else if (nMapArray[nPlayerY][nPlayerX - 1] == TILE_FLOOR || TILE_OPEN_DOOR) {
						mvaddstr(22, 10, "There is nothing there to kick!");
						getch();
					}
					else {
						mvaddstr(22, 10, "Don't kick the wall!                        ");
						getch();
					}
					break;
				case KEY_RIGHT:
					ClrMessage();
					if (nMapArray[nPlayerY][nPlayerX + 1] == TILE_CLOSED_DOOR) {
						nMapArray[nPlayerY][nPlayerX + 1] = TILE_FLOOR;
						mvaddstr(22, 10, "You break down the door!                    ");
						getch();
					}
					else if (nMapArray[nPlayerY][nPlayerX + 1] == TILE_FLOOR || TILE_OPEN_DOOR) {
						mvaddstr(22, 10, "There is nothing there to kick!");
						getch();
					}
					else {
						mvaddstr(22, 10, "Don't kick the wall!                        ");
						getch();
					}
					break;
				case KEY_UP:
					ClrMessage();
					if (nMapArray[nPlayerY - 1][nPlayerX] == TILE_CLOSED_DOOR) {
						nMapArray[nPlayerY - 1][nPlayerX] = TILE_FLOOR;
						mvaddstr(22, 10, "You break down the door!                    ");
						getch();
					}
					else if (nMapArray[nPlayerY - 1][nPlayerX] == TILE_FLOOR || TILE_OPEN_DOOR) {
						mvaddstr(22, 10, "There is nothing there to kick! ");
						getch();
					}
					else {
						mvaddstr(22, 10, "Don't kick the wall!                        ");
						getch();
					}
					break;
				}

				ClrMessage();
				DrawMap();
				break;
				}

				//Opening Door
				{
			case 'o':
				mvaddstr(22, 10, "What direction do you want to open in?");
				switch (getch()) {
				case KEY_DOWN:
					ClrMessage();
					if (nMapArray[nPlayerY + 1][nPlayerX] == TILE_CLOSED_DOOR) {
						nMapArray[nPlayerY + 1][nPlayerX] = TILE_OPEN_DOOR;
						mvaddstr(22, 10, "You opened the door!                    ");
						getch();
					}
					else {
						mvaddstr(22, 10, "There is nothing there to open.");
					}
					ClrMessage();
					break;
				case KEY_LEFT:
					ClrMessage();
					if (nMapArray[nPlayerY][nPlayerX - 1] == TILE_CLOSED_DOOR) {
						nMapArray[nPlayerY][nPlayerX - 1] = TILE_OPEN_DOOR;
						mvaddstr(22, 10, "You opened the door!                    ");
						getch();
					}
					else {
						mvaddstr(22, 10, "There is nothing there to open.");
						getch();
					}
					ClrMessage();
					break;
				case KEY_RIGHT:
					ClrMessage();
					if (nMapArray[nPlayerY][nPlayerX + 1] == TILE_CLOSED_DOOR) {
						nMapArray[nPlayerY][nPlayerX + 1] = TILE_OPEN_DOOR;
						mvaddstr(22, 10, "You opened the door!                    ");
						getch();
					}
					else {
						mvaddstr(22, 10, "There is nothing there to open.");
						getch();
					}
					ClrMessage();
					break;
				case KEY_UP:
					ClrMessage();
					if (nMapArray[nPlayerY - 1][nPlayerX] == TILE_CLOSED_DOOR) {
						nMapArray[nPlayerY - 1][nPlayerX] = TILE_OPEN_DOOR;
						mvaddstr(22, 10, "You opened the door!                    ");
						getch();
					}
					else {
						mvaddstr(22, 10, "There is nothing there to open.");
						getch();
					}
					ClrMessage();
					break;
				}

				ClrMessage();
				DrawMap();
				break;
				}
				
				//Closing Door
				{
			case 'c':
				mvaddstr(22, 10, "What direction do you want to close in");
				switch (getch()) {
				case KEY_DOWN:
					ClrMessage();
					if (nMapArray[nPlayerY + 1][nPlayerX] == TILE_OPEN_DOOR) {
						nMapArray[nPlayerY + 1][nPlayerX] = TILE_CLOSED_DOOR;
						mvaddstr(22, 10, "You closed the door!");
						getch();
					}
					else {
						mvaddstr(22, 10, "There is nothing there to close.");
					}
					ClrMessage();
					break;
				case KEY_LEFT:
					ClrMessage();
					if (nMapArray[nPlayerY][nPlayerX - 1] == TILE_OPEN_DOOR) {
						nMapArray[nPlayerY][nPlayerX - 1] = TILE_CLOSED_DOOR;
						mvaddstr(22, 10, "You closed the door!");
						getch();
					}
					else {
						mvaddstr(22, 10, "There is nothing there to close.");
						getch();
					}
					ClrMessage();
					break;
				case KEY_RIGHT:
					ClrMessage();
					if (nMapArray[nPlayerY][nPlayerX + 1] == TILE_OPEN_DOOR) {
						nMapArray[nPlayerY][nPlayerX + 1] = TILE_CLOSED_DOOR;
						mvaddstr(22, 10, "You closed the door!");
						getch();
					}
					else {
						mvaddstr(22, 10, "There is nothing there to close.");
						getch();
					}
					ClrMessage();
					break;
				case KEY_UP:
					ClrMessage();
					if (nMapArray[nPlayerY - 1][nPlayerX] == TILE_OPEN_DOOR) {
						nMapArray[nPlayerY - 1][nPlayerX] = TILE_CLOSED_DOOR;
						mvaddstr(22, 10, "You closed the door!");
						getch();
					}
					else {
						mvaddstr(22, 10, "There is nothing there to close.");
						getch();
					}
					ClrMessage();
					break;
				}

				ClrMessage();
				DrawMap();
				break;
				}
			default:
				break;
			}
			turn += 1;
		}

	// Clear pdcurses data structures
		 endwin();
	return 0;
}
