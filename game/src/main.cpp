#include <iostream>
#include <cstdlib>
#include <ctime>
#include <raylib.h>
#include <string>
#include <fstream>
using namespace std;
Color red = Color{ 250, 6, 36, 255 };
Color glossRed = Color{ 200, 34, 70, 255 };
Color green = Color{ 72, 190, 120, 255 };
Color glossGreen = Color{ 255, 255, 255, 0 };
Color blue = Color{ 57, 197, 239, 255 };
Color grey = Color{ 236, 241, 242, 255 };
Color gloss = Color{ 255, 255, 255, 100 };
int compShips = 5;
string mode = "start screen";
// ship orientation for battle phase
int v5x = -1, v5y = -1, vp5x = -1, vp5y = -1, h5x = -1, h5y = -1, hp5x = -1, hp5y = -1;
int v4x = -1, v4y = -1, vp4x = -1, vp4y = -1, h4x = -1, h4y = -1, hp4x = -1, hp4y = -1;
int v3x = -1, v3y = -1, vp3x = -1, vp3y = -1, h3x = -1, h3y = -1, hp3x = -1, hp3y = -1;
int v32x = -1, v32y = -1, vp32x = -1, vp32y = -1, h32x = -1, h32y = -1, hp32x = -1, hp32y = -1;
int v2x = -1, v2y = -1, vp2x = -1, vp2y = -1, h2x = -1, h2y = -1, hp2x = -1, hp2y = -1;
bool horizontalShip = 1;
char userName[26];
const int screenHeight = 800;
const int screenWidth = 1200;
const int rows = 10;
const int cols = 10;
int playerMoves = 100;
bool userNameState = false;
int selectedOption = 0; // for color selection
int sizeOfShip = 0;
int shipType = 0;
int mouseX, mouseY;
int numOfShips = 5;
int hit = 0, direction = 0;
int charCount = 0;
string turn = "player turn";
const int sqLength = 50;
// flag for ship selection
bool flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0, flag5 = 0;
bool sizeSelected = false;
int gridXStart = screenWidth / 4 + 60;
int gridXEnd = (screenWidth / 4 + 60) + 10 * sqLength;
int gridYStart = screenHeight / 4 + 20;
int gridYEnd = (screenHeight / 4 + 20) + 10 * sqLength;
bool deleteState = false;
void MouseCoordinates()
{
	mouseX = GetMouseX();
	mouseY = GetMouseY();
}
void resetVars()
{
	userName[0] = '\0';
	playerMoves = 100;
	numOfShips = 5;
	flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0, flag5 = 0;
	hit = 0;
	v5x = -1, v5y = -1, vp5x = -1, vp5y = -1;
	v4x = -1, v4y = -1, vp4x = -1, vp4y = -1;
	v3x = -1, v3y = -1, vp3x = -1, vp3y = -1;
	v32x = -1, v32y = -1, vp32x = -1, vp32y = -1;
	v2x = -1, v2y = -1, vp2x = -1, vp2y = -1;
	h5x = -1, h5y = -1, hp5x = -1, hp5y = -1;
	h4x = -1, h4y = -1, hp4x = -1, hp4y = -1;
	h3x = -1, h3y = -1, hp3x = -1, hp3y = -1;
	h32x = -1, h32y = -1, hp32x = -1, hp32y = -1;
	h2x = -1, h2y = -1, hp2x = -1, hp2y = -1;
	charCount = 0;
	direction = 0;
	selectedOption = 0;
	userNameState = false;
	turn = "player turn";
	mode = "start screen";
}
void clearOptions()
{
	numOfShips--;
	if (shipType == 1)
		flag1 = 1;
	else if (shipType == 2)
		flag2 = 1;
	else if (shipType == 3)
		flag3 = 1;
	else if (shipType == 4)
		flag4 = 1;
	else if (shipType == 5)
		flag5 = 1;
}

void compAttack(int playerGrid[][10])
{
	static int x, y, startXPos, startYPos, direction = 0, totalShips = 5;
	bool attacked = false;
	while (attacked == false)
	{
		if (hit == 0)
		{
			x = rand() % 10, y = rand() % 10;
			if (playerGrid[x][y] == 1 || playerGrid[x][y] == 2 || playerGrid[x][y] == 3 || playerGrid[x][y] == 4 || playerGrid[x][y] == 5)
			{
				hit++;
				startXPos = x, startYPos = y;
				playerGrid[x][y] = 10; // hit = 10
				attacked = true;
				turn = "player turn";
			}
			else if (playerGrid[x][y] == 0) // water 0
			{
				playerGrid[x][y] = -1; // miss = -1
				attacked = true;
				turn = "player turn";
			}
		}
		else
		{ // After hitting a ship, continue in the same direction
			int newX = x, newY = y;
			bool validDirection = false;
			// Continue attacking in the same direction until the ship is sunk or blocked
			if (direction == 0 && y + 1 < 10 && playerGrid[x][y + 1] != 10 && playerGrid[x][y + 1] != -1)
			{ // Right
				newY = y + 1;
				validDirection = true;
			}
			else if (direction == 1 && y - 1 >= 0 && playerGrid[x][y - 1] != 10 && playerGrid[x][y - 1] != -1)
			{ // Left
				newY = y - 1;
				validDirection = true;
			}
			else if (direction == 2 && x + 1 < 10 && playerGrid[x + 1][y] != 10 && playerGrid[x + 1][y] != -1)
			{ // Down
				newX = x + 1;
				validDirection = true;
			}
			else if (direction == 3 && x - 1 >= 0 && playerGrid[x - 1][y] != 10 && playerGrid[x - 1][y] != -1)
			{ // Up
				newX = x - 1;
				validDirection = true;
			}
			// If a valid direction is found, attack in that direction
			if (validDirection)
			{
				x = newX, y = newY;
				if (playerGrid[x][y] == 1 || playerGrid[x][y] == 2 || playerGrid[x][y] == 3 || playerGrid[x][y] == 4 || playerGrid[x][y] == 5)
				{ // Ship hit
					playerGrid[x][y] = 10;
					hit++;
					attacked = true;
					turn = "player turn";
				}
				else if (playerGrid[x][y] == 0)
				{ // Water (miss)
					playerGrid[x][y] = -1;
					if (direction == 0)
					{
						x = startXPos, y = startYPos;
						direction = 1;
					}
					else if (direction == 1)
					{
						x = startXPos, y = startYPos;
						direction = 2;
					}
					else if (direction == 2)
					{
						x = startXPos, y = startYPos;
						direction = 3;
					}
					else if (direction == 3)
					{
						hit = 0;
						direction = 0; // Reset direction
						startXPos = 0, startYPos = 0;
						x = 0, y = 0;
						totalShips--;
					}

					attacked = true;
					turn = "player turn";
				}
			}
			else
			{
				if (direction == 0)
				{
					direction = 1;
					x = startXPos, y = startYPos;
				}
				else if (direction == 1)
				{
					direction = 2;
					x = startXPos, y = startYPos;
				}
				else if (direction == 2)
				{
					direction = 3;
					x = startXPos, y = startYPos;
				}
				else
				{
					// Reset direction
					hit = 0;
					direction = 0;
					startXPos = 0, startYPos = 0;
					x = 0, y = 0;
					totalShips--;
				}
				attacked = true;
			}
		}
	}
}
// screen top left corner as origin. x increases as we move right and y increases as we move down
void drawGrid(int grid[][10])
{
	int squareY = screenHeight / 4 + 20;
	for (int i = 0; i < rows; i++, squareY += sqLength)
	{
		int squareX = screenWidth / 4 + 60;
		for (int j = 0; j < cols; j++, squareX += sqLength)
		{
			if (i + 1 < 10 && grid[i + 1][j] == 1 && grid[i][j] == 1 && v5x == -1 && v5y == -1)
			{
				v5x = squareX;
				v5y = squareY;
			}
			if (j + 1 < 10 && grid[i][j + 1] == 1 && grid[i][j] == 1 && h5x == -1 && h5y == -1)
			{
				h5x = squareX;
				h5y = squareY;
			}
			if (i + 1 < 10 && grid[i + 1][j] == 2 && grid[i][j] == 2 && v4x == -1 && v4y == -1)
			{
				v4x = squareX;
				v4y = squareY;
			}
			if (j + 1 < 10 && grid[i][j + 1] == 2 && grid[i][j] == 2 && h4x == -1 && h4y == -1)
			{
				h4x = squareX;
				h4y = squareY;
			}
			if (i + 1 < 10 && grid[i + 1][j] == 3 && grid[i][j] == 3 && v3x == -1 && v3y == -1)
			{
				v3x = squareX;
				v3y = squareY;
			}
			if (i + 1 < 10 && grid[i + 1][j] == 4 && grid[i][j] == 4 && v32x == -1 && v32y == -1)
			{
				v32x = squareX;
				v32y = squareY;
			}
			if (j + 1 < 10 && grid[i][j + 1] == 3 && grid[i][j] == 3 && h3x == -1 && h3y == -1)
			{
				h3x = squareX;
				h3y = squareY;
			}
			if (j + 1 < 10 && grid[i][j + 1] == 4 && grid[i][j] == 4 && h32x == -1 && h32y == -1)
			{
				h32x = squareX;
				h32y = squareY;
			}
			if (i + 1 < 10 && grid[i + 1][j] == 5 && grid[i][j] == 5 && v2x == -1 && v2y == -1)
			{
				v2x = squareX;
				v2y = squareY;
			}
			if (j + 1 < 10 && grid[i][j + 1] == 5 && grid[i][j] == 5 && h2x == -1 && h2y == -1)
			{
				h2x = squareX;
				h2y = squareY;
			}
			DrawRectangle(squareX, squareY, sqLength - 1, sqLength - 1, grey);
		}
	}
}
void drawBattleGrid(int compGrid[][10], int playerGrid[][10])
{
	int square2Y = screenHeight / 4;
	for (int i = 0; i < rows; i++, square2Y += sqLength)
	{
		int square2X = sqLength;
		for (int j = 0; j < cols; j++, square2X += sqLength)
		{
			Color cell;
			if (i + 1 < 10 && compGrid[i + 1][j] == 1 && compGrid[i][j] == 1 && v5x == -1 && v5y == -1)
			{
				v5x = square2X;
				v5y = square2Y;
			}
			if (j + 1 < 10 && compGrid[i][j + 1] == 1 && compGrid[i][j] == 1 && h5x == -1 && h5y == -1)
			{
				h5x = square2X;
				h5y = square2Y;
			}
			if (i + 1 < 10 && compGrid[i + 1][j] == 2 && compGrid[i][j] == 2 && v4x == -1 && v4y == -1)
			{
				v4x = square2X;
				v4y = square2Y;
			}
			if (j + 1 < 10 && compGrid[i][j + 1] == 2 && compGrid[i][j] == 2 && h4x == -1 && h4y == -1)
			{
				h4x = square2X;
				h4y = square2Y;
			}
			if (i + 1 < 10 && compGrid[i + 1][j] == 3 && compGrid[i][j] == 3 && v3x == -1 && v3y == -1)
			{
				v3x = square2X;
				v3y = square2Y;
			}
			if (i + 1 < 10 && compGrid[i + 1][j] == 4 && compGrid[i][j] == 4 && v32x == -1 && v32y == -1)
			{
				v32x = square2X;
				v32y = square2Y;
			}
			if (j + 1 < 10 && compGrid[i][j + 1] == 3 && compGrid[i][j] == 3 && h3x == -1 && h3y == -1)
			{
				h3x = square2X;
				h3y = square2Y;
			}
			if (j + 1 < 10 && compGrid[i][j + 1] == 4 && compGrid[i][j] == 4 && h32x == -1 && h32y == -1)
			{
				h32x = square2X;
				h32y = square2Y;
			}
			if (i + 1 < 10 && compGrid[i + 1][j] == 5 && compGrid[i][j] == 5 && v2x == -1 && v2y == -1)
			{
				v2x = square2X;
				v2y = square2Y;
			}
			if (j + 1 < 10 && compGrid[i][j + 1] == 5 && compGrid[i][j] == 5 && h2x == -1 && h2y == -1)
			{
				h2x = square2X;
				h2y = square2Y;
			}
			if (compGrid[i][j] == 1 || compGrid[i][j] == 2 || compGrid[i][j] == 3 || compGrid[i][j] == 4 || compGrid[i][j] == 5)
				cell = grey;
			if (compGrid[i][j] == 10)
				cell = glossGreen;
			else if (compGrid[i][j] == -1)
				cell = glossRed;
			else if (compGrid[i][j] == 0)
				cell = grey;
			DrawRectangle(square2X + 1, square2Y + 1, sqLength - 1, sqLength - 1, cell);
		}
	}
	int square3Y = screenHeight / 4;
	for (int i = 0; i < rows; i++, square3Y += sqLength)
	{
		int square3X = 12 * sqLength + 50;
		for (int j = 0; j < cols; j++, square3X += sqLength)
		{
			Color cell;
			if (i + 1 < 10 && playerGrid[i + 1][j] == 1 && playerGrid[i][j] == 1 && vp5x == -1 && vp5y == -1)
			{
				vp5x = square3X;
				vp5y = square3Y;
			}
			if (j + 1 < 10 && playerGrid[i][j + 1] == 1 && playerGrid[i][j] == 1 && hp5x == -1 && hp5y == -1)
			{
				hp5x = square3X;
				hp5y = square3Y;
			}
			if (i + 1 < 10 && playerGrid[i + 1][j] == 2 && playerGrid[i][j] == 2 && vp4x == -1 && vp4y == -1)
			{
				vp4x = square3X;
				vp4y = square3Y;
			}
			if (j + 1 < 10 && playerGrid[i][j + 1] == 2 && playerGrid[i][j] == 2 && hp4x == -1 && hp4y == -1)
			{
				hp4x = square3X;
				hp4y = square3Y;
			}
			if (i + 1 < 10 && playerGrid[i + 1][j] == 3 && playerGrid[i][j] == 3 && vp3x == -1 && vp3y == -1)
			{
				vp3x = square3X;
				vp3y = square3Y;
			}
			if (j + 1 < 10 && playerGrid[i][j + 1] == 3 && playerGrid[i][j] == 3 && hp3x == -1 && hp3y == -1)
			{
				hp3x = square3X;
				hp3y = square3Y;
			}
			if (i + 1 < 10 && playerGrid[i + 1][j] == 4 && playerGrid[i][j] == 4 && vp32x == -1 && vp32y == -1)
			{
				vp32x = square3X;
				vp32y = square3Y;
			}
			if (j + 1 < 10 && playerGrid[i][j + 1] == 4 && playerGrid[i][j] == 4 && hp32x == -1 && hp32y == -1)
			{
				hp32x = square3X;
				hp32y = square3Y;
			}
			if (i + 1 < 10 && playerGrid[i + 1][j] == 5 && playerGrid[i][j] == 5 && vp2x == -1 && vp2y == -1)
			{
				vp2x = square3X;
				vp2y = square3Y;
			}
			if (j + 1 < 10 && playerGrid[i][j + 1] == 5 && playerGrid[i][j] == 5 && hp2x == -1 && hp2y == -1)
			{
				hp2x = square3X;
				hp2y = square3Y;
			}
			if (playerGrid[i][j] == 1 || playerGrid[i][j] == 2 || playerGrid[i][j] == 3 || playerGrid[i][j] == 4 || playerGrid[i][j] == 5)
				cell = GRAY;
			else if (playerGrid[i][j] == 10)
				cell = glossGreen;
			else if (playerGrid[i][j] == -1)
				cell = glossRed;
			else if (playerGrid[i][j] == 0)
				cell = grey;
			DrawRectangle(square3X + 1, square3Y + 1, sqLength - 1, sqLength - 1, cell);
		}
	}
}
// w = 0 ; s = ship
// initializing computer's grid as empty in the start
void initialize(int compGrid[10][10], int playerGrid[][10], const int size)
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			compGrid[i][j] = 0;
			playerGrid[i][j] = 0;
		}
	}
}
void compShipPlacement(int compGrid[10][10], const int shipSize, const int shipType = 0)
{
	// changing the seed by using system's time. every second, the seed changes.
	srand(time(0));
	int x, y, orientation;
	bool isPlaced = false; // running a loop till a ship is placed successfuly
	while (isPlaced == false)
	{
		// generating a random value from 0-9 for the co-ordinates on grid for placement
		x = rand() % 10;
		y = rand() % 10;
		orientation = rand() % 2; // 1 horizontal, 0 vertical
		// horizontal placement. checking if total ship size is within bounds
		if (orientation == 1 && y + shipSize <= 10)
		{
			bool freeSpace = true;
			for (int i = 0; i < shipSize && freeSpace == true; i++)
			{
				// checking along cols to make sure we have free space for the ship
				if (compGrid[x][y + i] != 0)
				{
					freeSpace = false;
				}
			}
			if (freeSpace == true)
			{
				// place the ship horizontally
				for (int i = 0; i < shipSize; i++)
				{
					compGrid[x][y + i] = shipType;
				}
				isPlaced = true;
			}
		}
		// vertical placement. same logic
		else if (orientation == 0 && x + shipSize <= 10)
		{
			bool freeSpace = true;
			for (int i = 0; i < shipSize && freeSpace == true; i++)
			{
				// checking for space along rows
				if (compGrid[x + i][y] != 0)
				{
					freeSpace = false;
				}
			}
			if (freeSpace == true)
			{
				for (int i = 0; i < shipSize; i++)
				{
					compGrid[x + i][y] = shipType;
				}
				isPlaced = true;
			}
		}
	}
}
void playerShipPlacement(int playerGrid[][10])
{
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		MouseCoordinates();
		if ((mouseX >= gridXStart && mouseX <= gridXEnd) && (mouseY >= gridYStart && mouseY <= gridYEnd) && horizontalShip)
		{
			int targetCellX = ((mouseX - gridXStart) / sqLength);
			int targetCellY = ((mouseY - gridYStart) / sqLength);
			// horizontal placemnet
			{
				if (targetCellX + sizeOfShip <= 10)
				{
					bool freeSpace = true;
					for (int i = 0; i < sizeOfShip && freeSpace == true; i++)
					{
						// checking along cols to make sure we have free space for the ship
						if (playerGrid[targetCellY][targetCellX + i] != 0)
						{
							freeSpace = false;
							DrawRectangle(gridXStart + (sqLength * targetCellX + i), gridYStart + (sqLength * targetCellY), sqLength, sqLength, RED);
						}
					}
					if (freeSpace == true)
					{
						// place the ship horizontally
						for (int i = 0; i < sizeOfShip; i++)
						{
							playerGrid[targetCellY][targetCellX + i] = shipType;
						}
						clearOptions();
					}
				}
				else
					DrawRectangle(gridXStart + (sqLength * targetCellX), gridYStart + (sqLength * targetCellY), sqLength, sqLength, RED);
			}
			sizeSelected = false;
			shipType = 0;
		}

		else if ((mouseX >= gridXStart && mouseX <= gridXEnd) && (mouseY >= gridYStart && mouseY <= gridYEnd) && !horizontalShip)
		{
			int targetCellX = ((mouseX - gridXStart) / sqLength);
			int targetCellY = ((mouseY - gridYStart) / sqLength);
			{
				if (targetCellY + sizeOfShip <= 10)
				{
					bool freeSpace = true;
					for (int i = 0; i < sizeOfShip && freeSpace == true; i++)
					{
						// checking along cols to make sure we have free space for the ship
						if (playerGrid[targetCellY + i][targetCellX] != 0)
						{
							freeSpace = false;
							DrawRectangle(gridXStart + (sqLength * targetCellX), gridYStart + (sqLength * targetCellY + i), sqLength, sqLength, RED);
						}
					}
					if (freeSpace == true)
					{
						// place the ship horizontally
						for (int i = 0; i < sizeOfShip; i++)
						{
							playerGrid[targetCellY + i][targetCellX] = shipType;
						}
						clearOptions();
					}
				}
				else
					DrawRectangle(gridXStart + (sqLength * targetCellX), gridYStart + (sqLength * targetCellY), sqLength, sqLength, RED);
			}
			sizeSelected = false;
			shipType = 0;
		}
	}
}
void drawPreview(const int playerGrid[][10])
{
	MouseCoordinates();
	if ((mouseX >= gridXStart && mouseX <= gridXEnd) && (mouseY >= gridYStart && mouseY <= gridYEnd))
	{
		int targetCellX = ((mouseX - gridXStart) / sqLength);
		int targetCellY = ((mouseY - gridYStart) / sqLength);

		if (horizontalShip)
		{
			if ((targetCellX + sizeOfShip) > 10)
			{
				int extra = (targetCellX + sizeOfShip) - 10;
				DrawRectangle(gridXStart + (sqLength * targetCellX), gridYStart + (sqLength * targetCellY), sqLength * (sizeOfShip - extra), sqLength, glossRed);
			}
			else
			{
				bool freeSpace = true;
				for (int i = 0; i < sizeOfShip; i++)
				{
					if (playerGrid[targetCellY][targetCellX + i] == 1 || playerGrid[targetCellY][targetCellX + i] == 2 || playerGrid[targetCellY][targetCellX + i] == 3 || playerGrid[targetCellY][targetCellX + i] == 4 || playerGrid[targetCellY][targetCellX + i] == 5)
						freeSpace = false;
				}
				if (freeSpace == true)
					DrawRectangle(gridXStart + (sqLength * targetCellX), gridYStart + (sqLength * targetCellY), sqLength * (sizeOfShip), sqLength, green);
				else
					DrawRectangle(gridXStart + (sqLength * targetCellX), gridYStart + (sqLength * targetCellY), sqLength * (sizeOfShip), sqLength, glossRed);
			}
		}
		if (!horizontalShip)
		{
			if (targetCellY + sizeOfShip > 10)
			{
				int extra = (targetCellY + sizeOfShip) - 10;
				DrawRectangle(gridXStart + (sqLength * targetCellX), gridYStart + (sqLength * targetCellY), sqLength, sqLength * (sizeOfShip - extra), glossRed);
			}
			else
			{
				bool freeSpace = true;
				for (int i = 0; i < sizeOfShip; i++)
				{
					if (playerGrid[targetCellY + i][targetCellX] == 1 || playerGrid[targetCellY + i][targetCellX] == 2 || playerGrid[targetCellY + i][targetCellX] == 3 || playerGrid[targetCellY + i][targetCellX] == 4 || playerGrid[targetCellY + i][targetCellX] == 5)
						freeSpace = false;
				}
				if (freeSpace == true)
					DrawRectangle(gridXStart + (sqLength * targetCellX), gridYStart + (sqLength * targetCellY), sqLength, sqLength * (sizeOfShip), green);
				else

					DrawRectangle(gridXStart + (sqLength * targetCellX), gridYStart + (sqLength * targetCellY), sqLength, sqLength * (sizeOfShip), glossRed);
			}
		}
	}
}
void playerAttack(int compGrid[][10])
{
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
	{
		MouseCoordinates();

		if ((mouseX >= (sqLength + 1) && mouseX <= (11 * sqLength) - 1) && (mouseY >= (screenHeight / 4 + 1) && mouseY <= ((screenHeight / 4 + (10 * sqLength))) - 1))
		{
			// x is col y is row. find target cell in array
			int targetCellX = ((mouseX - sqLength) / sqLength);
			int targetCellY = ((mouseY - screenHeight / 4) / sqLength);
			// key h is hit m is miss
			if (compGrid[targetCellY][targetCellX] != 0 && compGrid[targetCellY][targetCellX] != 10 && compGrid[targetCellY][targetCellX] != -1)
			{
				compGrid[targetCellY][targetCellX] = 10;
				turn = "computer turn";
				playerMoves--;
			}
			else if (compGrid[targetCellY][targetCellX] == 0)
			{
				compGrid[targetCellY][targetCellX] = -1;
				turn = "computer turn";
				playerMoves--;
			}
		}
	}
}
void computerwins(int playerGrid[][10])
{

	bool flag2 = true;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (playerGrid[i][j] == 1 || playerGrid[i][j] == 2 || playerGrid[i][j] == 3 || playerGrid[i][j] == 4 || playerGrid[i][j] == 5)
				flag2 = false;
		}
	}
	if (flag2 == true)
	{
		mode = "computer wins";
	}
}
void textInput()
{

	// taking only printable character ASCII 32-126if()
	int key = GetCharPressed();
	if ((key > 32 && key <= 125))
	{
		if (charCount < 25)
		{
			userName[charCount] = static_cast<char>(key);
			charCount++;
			userName[charCount] = '\0';
		}
	}
	if (deleteState == true && charCount > 0)
	{
		charCount--;
		userName[charCount] = '\0';
		deleteState = false;
	}
}
void drawOptions()
{
	int optionX = screenWidth - screenWidth / 8;
	int optionY = screenHeight / 4 + 40;
	int count = 1;
	while (count <= 5)
	{
		Color rectangleColor = gloss; // Default color

		// Check if the ship is placed
		if ((count == 1 && flag1 == 1) ||
			(count == 2 && flag2 == 1) ||
			(count == 3 && flag3 == 1) ||
			(count == 4 && flag4 == 1) ||
			(count == 5 && flag5 == 1))
		{
			rectangleColor = DARKGRAY; // Placed ships are dark gray
		}
		// Check if the ship is currently selected and sizeSelected is true
		else if (selectedOption == count && sizeSelected)
		{
			rectangleColor = LIGHTGRAY; // Selected ship is light gray
		}
		else
		{
			MouseCoordinates();
			// Highlight the option when the mouse is over it
			if (mouseX >= optionX && mouseX <= optionX + sqLength && mouseY >= optionY && mouseY <= optionY + sqLength)
			{
				rectangleColor = grey;
				// Allow selection of unplaced ships
				if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				{
					selectedOption = count;
					sizeSelected = false; // Reset selection state until size is picked
				}
			}
		}
		// Draw ship labels
		if (count == 1)
			DrawText("AIRCRAFT CARRIER", optionX - 80, optionY - 30, 20, grey);
		else if (count == 2)
			DrawText("BATTLESHIP", optionX - 40, optionY - 30, 20, grey);
		else if (count == 3)
			DrawText("SUBMARINE", optionX - 40, optionY - 30, 20, grey);
		else if (count == 4)
			DrawText("CRUISER", optionX - 20, optionY - 30, 20, grey);
		else if (count == 5)
			DrawText("DESTROYER", optionX - 40, optionY - 30, 20, grey);
		// Draw rectangle for the option
		DrawRectangle(optionX, optionY, sqLength, sqLength, rectangleColor);
		optionY += 100;
		count++;
	}
}
void clearShipPlacement(int playerGrid[][10], int const size)
{
	selectedOption = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
			playerGrid[i][j] = 0;
	}
	// Reset the corresponding flag
	flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0, flag5 = 0;
	v5x = -1, v5y = -1, v4x = -1, v4y = -1, v3x = -1, v3y = -1, v32x = -1, v32y = -1, v2x = -1, v2y = -1;
	h5x = -1, h5y = -1, h4x = -1, h4y = -1, h3x = -1, h3y = -1, h32x = -1, h32y = -1, h2x = -1, h2y = -1;
	numOfShips = 5;
}
void inputTest()
{
	MouseCoordinates();
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && charCount > 0 && mouseX >= screenWidth / 4 && mouseX <= (3 * screenWidth) / 4 && mouseY >= screenHeight / 4 + 50 && mouseY <= ((3 * screenHeight) / 8 + 50))
		mode = "load screen 1";
	if (mouseX >= (screenWidth / 4 + 50) && mouseX <= ((3 * screenWidth / 4 - 50) - 100) && mouseY >= (screenHeight / 2 + 250) && mouseY <= ((5 * screenHeight / 8) + 200))
	{
		SetMouseCursor(MOUSE_CURSOR_IBEAM);
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			userNameState = true;
	}
	else
		SetMouseCursor(MOUSE_CURSOR_DEFAULT);
	if (mouseX >= ((3 * screenWidth / 4) - 100) && mouseX <= ((3 * screenWidth / 4) - 50) && mouseY >= (screenHeight / 2 + 250) && mouseY <= ((5 * screenHeight / 8) + 200) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		userNameState = false;
	if (mouseX >= (3 * screenWidth / 4 - 150) && mouseX <= (3 * screenWidth / 4 - 100) && mouseY >= (screenHeight / 2 + 250) && mouseY <= ((5 * screenHeight / 8) + 200) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		deleteState = true;
	if (mouseX >= screenWidth / 4 && mouseX <= (3 * screenWidth / 4) && mouseY >= screenHeight / 2 && mouseY <= (5 * screenHeight / 8) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		mode = "Leaderboard";
}
void shipSize()
{
	// Check the selected box and ensure it is not already placed
	if (selectedOption == 1 && flag1 != 1)
	{
		shipType = 1;
		sizeSelected = true;
		sizeOfShip = 5; // Aircraft Carrier
	}
	else if (selectedOption == 2 && flag2 != 1)
	{
		shipType = 2;
		sizeSelected = true;
		sizeOfShip = 4; // Battleship
	}
	else if (selectedOption == 3 && flag3 != 1)
	{
		shipType = 3;
		sizeSelected = true;
		sizeOfShip = 3; // Submarine
	}
	else if (selectedOption == 4 && flag4 != 1)
	{
		shipType = 4;
		sizeSelected = true;
		sizeOfShip = 3; // Cruiser
	}
	else if (selectedOption == 5 && flag5 != 1)
	{
		shipType = 5;
		sizeSelected = true;
		sizeOfShip = 2; // Destroyer
	}
}
void readLeaderboard(string names[], int scores[], int& count)
{
	ifstream read("leaderboard.txt");
	count = 0;
	// we will create a file if it doesn't exist
	if (!read.is_open())
	{
		ofstream createFile("leaderboard.txt");
		if (!createFile.is_open())
		{
			// couldn't create the file
			return;
		}
		createFile.close();
		return;
	}
	// reads names n scores from the file and stores it in arrays
	while (read >> names[count] >> scores[count])
	{
		count++;
	}
	read.close();
}
void writeLeaderboard(string names[], int scores[], int count)
{
	ofstream write("leaderboard.txt");
	if (!write.is_open())
	{
		// unable to open file so it just returns
		return;
	}
	// writes data to the file
	for (int i = 0; i < count; i++)
	{
		write << names[i] << " " << scores[i] << endl;
	}
	write.close();
}
void sortLeaderboard(string names[], int scores[], int count)
{
	// sorting using bubblesort
	for (int i = 0; i < count - 1; i++)
	{
		for (int j = 0; j < count - i - 1; j++)
		{
			if (scores[j] < scores[j + 1])
			{
				int tempScore = scores[j];
				scores[j] = scores[j + 1];
				scores[j + 1] = tempScore;
				string tempName = names[j];
				names[j] = names[j + 1];
				names[j + 1] = tempName;
			}
		}
	}
}
void updateLeaderboard(string playerName, int playerScore)
{
	const int MAX_PLAYERS = 100;
	string names[MAX_PLAYERS];
	int scores[MAX_PLAYERS];
	int count;
	readLeaderboard(names, scores, count);
	// check if a player already exists
	bool playerExists = false;
	for (int i = 0; i < count && playerExists == false; i++)
	{
		if (names[i] == playerName)
		{
			if (scores[i] < playerScore) // updates score only when a player's score is higher
			{
				scores[i] = playerScore;
			}
			playerExists = true;
		}
	}
	// adds a new player if they don't exist in the leaderboard
	if (!playerExists && count < MAX_PLAYERS)
	{
		names[count] = playerName;
		scores[count] = playerScore;
		count++;
	}
	// sorting and writing it into file
	sortLeaderboard(names, scores, count);
	writeLeaderboard(names, scores, count);
}
void playerwins(int compGrid[][10])
{
	bool flag1 = true;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (compGrid[i][j] == 1 || compGrid[i][j] == 2 || compGrid[i][j] == 3 || compGrid[i][j] == 4 || compGrid[i][j] == 5)
				flag1 = false;
		}
	}
	if (flag1 == true)
	{
		mode = "player wins";
		string name(userName);
		int score = playerMoves;
		updateLeaderboard(name, score);
	}
}
int shipSunk(const int compGrid[][10])
{
	int count = 0;
	for (int k = 1; k < 6; k++)
	{
		bool flag2 = true;

		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (compGrid[i][j] == k)
					flag2 = false;
			}
		}
		if (flag2 == true)
			count++;
	}
	return 5 - count;
}
int main()
{
	const int MAX_PLAYERS = 100;
	string names[MAX_PLAYERS];
	int scores[MAX_PLAYERS];
	int count, topLimit;
	readLeaderboard(names, scores, count);
	const int size = 10;
	int playerGrid[size][size];
	int compGrid[size][size];
	initialize(compGrid, playerGrid, size);
	compShipPlacement(compGrid, 5, 1); // aircraft carrier
	compShipPlacement(compGrid, 4, 2); // battleship
	compShipPlacement(compGrid, 3, 3); // submarine
	compShipPlacement(compGrid, 3, 4); // cruiser
	compShipPlacement(compGrid, 2, 5); // destroyer
	InitWindow(screenWidth, screenHeight, "battleship");
	InitAudioDevice();
	Music bgm = LoadMusicStream("assets/bgm.mp3");
	Texture2D bge = LoadTexture("assets/bluee.PNG");
	Texture2D bge2 = LoadTexture("assets/test.PNG");
	Texture2D bge3 = LoadTexture("assets/fff.PNG");
	Texture2D vs5 = LoadTexture("assets/vship5.PNG");
	Texture2D hs5 = LoadTexture("assets/hship5.PNG");
	Texture2D vs4 = LoadTexture("assets/vship4.PNG");
	Texture2D hs4 = LoadTexture("assets/hship4.PNG");
	Texture2D vs3 = LoadTexture("assets/vship3.PNG");
	Texture2D hs3 = LoadTexture("assets/hship3.PNG");
	Texture2D vs2 = LoadTexture("assets/vship2.PNG");
	Texture2D hs2 = LoadTexture("assets/hship2.PNG");
	PlayMusicStream(bgm);
	//  set fps otherwise comp tries to run it as fast as it can
	SetTargetFPS(60);
	// game loop. runs as long as window remains open
	while (WindowShouldClose() == false)
	{
		UpdateMusicStream(bgm);
		BeginDrawing();
		// text,x coordinate, y coordinate, font size, color
		if (mode == "start screen")
		{
			DrawTexture(bge, 0, 0, RAYWHITE);
			int initTime = GetTime();
			DrawText("BATTLESHIP", 100, 50, 150, grey);
			MouseCoordinates();
			if (mouseX >= screenWidth / 4 && mouseX <= (3 * screenWidth) / 4 && mouseY >= screenHeight / 4 + 50 && mouseY <= (3 * screenHeight / 8) + 50 && charCount > 0)
				DrawRectangle(screenWidth / 4, screenHeight / 4 + 50, screenWidth / 2, screenHeight / 8, grey);
			else
				DrawRectangle(screenWidth / 4, screenHeight / 4 + 50, screenWidth / 2, screenHeight / 8, gloss);
			DrawText("START GAME", screenWidth / 4 + 120, screenHeight / 4 + 80, 50, BLACK);
			if (mouseX >= screenWidth / 4 && mouseX <= (3 * screenWidth) / 4 && mouseY >= screenHeight / 2 && mouseY <= (5 * screenHeight / 8))
				DrawRectangle(screenWidth / 4, screenHeight / 2, screenWidth / 2, screenHeight / 8, grey);
			else
				DrawRectangle(screenWidth / 4, screenHeight / 2, screenWidth / 2, screenHeight / 8, gloss);
			DrawText("LEADERBOARD", screenWidth / 4 + 120, screenHeight / 4 + 230, 50, BLACK);
			DrawRectangle(screenWidth / 4, screenHeight / 2 + 150, screenWidth / 2, screenHeight / 4, BLACK);
			DrawText("ENTER USERNAME", screenWidth / 4 + 70, screenHeight / 4 + 380, 50, grey);
			DrawRectangle(screenWidth / 4 + 50, screenHeight / 2 + 250, screenWidth / 2 - 100, screenHeight / 8 - 50, grey);
			inputTest();
			if (charCount == 0 && (initTime) % 2 == 0)
				DrawText("Enter username to begin", 280, 180, 50, BLACK);
			else if (charCount == 0 && (initTime) % 2 == 1)
				DrawText("Enter username to begin", 280, 180, 50, grey);
			if (userNameState == true)
				textInput();
			DrawText(userName, screenWidth / 4 + 52, screenHeight / 2 + 260, 30, BLACK);
			if (userNameState == false)
				DrawRectangle(screenWidth / 4 + 50, screenHeight / 2 + 250, screenWidth / 2 - 100, screenHeight / 8 - 50, grey);
			DrawRectangle((3 * screenWidth / 4) - 100, screenHeight / 2 + 250, 50, 50, green);
			DrawRectangle((3 * screenWidth / 4 - 50) - 100, screenHeight / 2 + 250, 50, 50, red);
			DrawText(">", (3 * screenWidth / 4) - 100 + 20, screenHeight / 2 + 255, 50, grey);
			DrawText("<", (3 * screenWidth / 4) - 150 + 20, screenHeight / 2 + 255, 50, grey);
			ClearBackground(blue);
		}
		else if (mode == "load screen 1")
		{
			// DrawTexture(bge, 0, 0, RAYWHITE);
			ClearBackground(blue);
			int initTime = GetTime();
			Color textColor = BLACK;
			DrawText("FLEET FORMATION", 100, 50, 100, grey);
			DrawRectangle(200, 200, 800, 400, grey);
			DrawRectangle(210, 210, 790, 390, BLACK);
			DrawText("Assemble a fleet of 5 ships", 250, 250, 50, blue);
			DrawText("Ships cannot be diagonal", 280, 300, 50, blue);
			DrawText("Left click to select ", 340, 350, 50, blue);
			DrawText("Left click to place ", 350, 400, 50, blue);
			DrawText("Right click to rotate", 330, 450, 50, blue);
			DrawText("Click Finish when ready", 300, 500, 50, blue);
			DrawRectangle(300, 700, 620, 50, grey);
			DrawRectangle(310, 710, 600, 30, BLACK);
			if (initTime % 2 == 0)
				textColor = grey;
			if (initTime % 2 == 0)
				DrawRectangle(315, 715, 150, 20, blue);
			else if (initTime % 3 == 0)
				DrawRectangle(315, 715, 300, 20, blue);
			else if (initTime % 4 == 0)
				DrawRectangle(315, 715, 450, 20, blue);
			else if (initTime % 5 == 0)
				DrawRectangle(315, 715, 590, 20, blue);
			DrawText("Press SPACE to continue", screenWidth / 2 - 320, 625, 50, textColor);
			if (IsKeyPressed(KEY_SPACE))
				mode = "fleet formation";
		}
		else if (mode == "fleet formation")
		{
			DrawTexture(bge3, 0, 0, RAYWHITE);
			DrawText("FLEET FORMATION", 100, 50, 100, grey);
			drawGrid(playerGrid);
			if (v5x != -1 && v5y != -1)
				DrawTexture(vs5, v5x, v5y, RAYWHITE);
			if (h5x != -1 && h5y != -1)
				DrawTexture(hs5, h5x, h5y, RAYWHITE);
			if (v4x != -1 && v4y != -1)
				DrawTexture(vs4, v4x, v4y, RAYWHITE);
			if (h4x != -1 && h4y != -1)
				DrawTexture(hs4, h4x, h4y, RAYWHITE);
			if (v3x != -1 && v3y != -1)
				DrawTexture(vs3, v3x, v3y, RAYWHITE);
			if (h3x != -1 && h3y != -1)
				DrawTexture(hs3, h3x, h3y, RAYWHITE);
			if (v32x != -1 && v32y != -1)
				DrawTexture(vs3, v32x, v32y, RAYWHITE);
			if (h32x != -1 && h32y != -1)
				DrawTexture(hs3, h32x, h32y, RAYWHITE);
			if (v2x != -1 && v2y != -1)
				DrawTexture(vs2, v2x, v2y, RAYWHITE);
			if (h2x != -1 && h2y != -1)
				DrawTexture(hs2, h2x, h2y, RAYWHITE);
			drawOptions();
			if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
				horizontalShip = !horizontalShip;
			shipSize();
			if (sizeSelected == true)
			{
				drawPreview(playerGrid);
				playerShipPlacement(playerGrid);
			}
			int playerGridX = screenWidth / 8;
			int playerGridY = screenHeight / 4;
			for (int row = 0; row < size; row++)
			{
				DrawText(TextFormat("%d", row), playerGridX + row * 50 + 230, playerGridY - 5, 20, grey);
				DrawText(TextFormat("%c", 'A' + row), playerGridX + 185, playerGridY + row * 50 + 35, 20, grey);
			}
			MouseCoordinates();
			if (mouseX >= screenWidth / 15 && mouseX <= (screenWidth / 15 + screenWidth / 8) && mouseY >= (screenHeight / 2 - 35) && mouseY <= (screenHeight / 2 + 15) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				clearShipPlacement(playerGrid, size);
			if (mouseX >= screenWidth / 15 && mouseX <= ((screenWidth / 15) + (screenWidth / 8)) && mouseY >= screenHeight / 2 - 35 && mouseY <= screenHeight / 2 + 15)
				DrawRectangle(screenWidth / 15, screenHeight / 2 - 35, screenWidth / 8, 50, grey);
			else
				DrawRectangle(screenWidth / 15, screenHeight / 2 - 35, screenWidth / 8, 50, gloss);
			DrawText("RESET", screenWidth / 15 + 25, screenHeight / 4 + 175, 30, BLACK);
			if (mouseX >= screenWidth / 15 && mouseX <= ((screenWidth / 15) + (screenWidth / 8)) && mouseY >= screenHeight / 2 + 35 && mouseY <= screenHeight / 2 + 85)
				DrawRectangle(screenWidth / 15, screenHeight / 2 + 35, screenWidth / 8, 50, grey);
			else
				DrawRectangle(screenWidth / 15, screenHeight / 2 + 35, screenWidth / 8, 50, gloss);
			DrawText("FINISH", screenWidth / 15 + 25, screenHeight / 4 + 245, 30, BLACK);
			if (mouseX >= screenWidth / 15 && mouseX <= (screenWidth / 15 + screenWidth / 8) &&
				mouseY >= screenHeight / 2 + 105 && mouseY <= screenHeight / 2 + 155)
				DrawRectangle(screenWidth / 15, screenHeight / 2 + 105, screenWidth / 8, 50, grey);
			else
				DrawRectangle(screenWidth / 15, screenHeight / 2 + 105, screenWidth / 8, 50, gloss);
			DrawText("RANDOMIZE", screenWidth / 15 + 10, screenHeight / 2 + 120, 22, BLACK);

			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && mouseX >= screenWidth / 15 && mouseX <= (screenWidth / 15 + screenWidth / 8) && mouseY >= screenHeight / 2 + 105 && mouseY <= screenHeight / 2 + 155)
			{
				clearShipPlacement(playerGrid, size);
				sizeSelected = false;
				compShipPlacement(playerGrid, 5, 1); // aircraft carrier
				compShipPlacement(playerGrid, 4, 2); // battleship
				compShipPlacement(playerGrid, 3, 3); // submarine
				compShipPlacement(playerGrid, 3, 4); // cruiser
				compShipPlacement(playerGrid, 2, 5); // destroyer
				flag1 = 1, flag2 = 1, flag3 = 1, flag4 = 1, flag5 = 1;
				numOfShips = 0;
			}
			else if (mouseX >= screenWidth / 15 && mouseX <= (screenWidth / 15 + screenWidth / 8) && mouseY >= (screenHeight / 2 + 35) && mouseY <= (screenHeight / 2 + 85) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && numOfShips == 0)
			{
				v5x = -1, v5y = -1, v4x = -1, v4y = -1, v3x = -1, v3y = -1, v32x = -1, v32y = -1, v2x = -1, v2y = -1;
				h5x = -1, h5y = -1, h4x = -1, h4y = -1, h3x = -1, h3y = -1, h32x = -1, h32y = -1, h2x = -1, h2y = -1;
				mode = "load screen 2";
			}
			ClearBackground(blue);
		}
		else if (mode == "load screen 2")
		{
			ClearBackground(blue);
			int initTime = GetTime();
			Color textColor = BLACK;
			DrawText("BATTLE PHASE", gridXStart - 160, screenHeight / 8 - 50, 100, grey);
			DrawRectangle(160, 170, 900, 400, grey);
			DrawRectangle(170, 180, 890, 390, BLACK);
			DrawText("Sink all the enemy ships before\n\t\t\t\t they sink your fleet", gridXStart - 160, 420, 50, blue);
			DrawText("Lock a target cell by clicking it", gridXStart - 150, 220, 50, blue);
			DrawText("Cell turns red for every miss", gridXStart - 120, 270, 50, blue);
			DrawText("Correct guess reveals the ship", gridXStart - 150, 320, 50, blue);
			DrawText("Unkown waters remain grey", gridXStart - 100, 370, 50, blue);
			DrawRectangle(300, 700, 620, 50, grey);
			DrawRectangle(310, 710, 600, 30, BLACK);
			if (initTime % 2 == 0)
				textColor = grey;
			if (initTime % 2 == 0)
				DrawRectangle(315, 715, 150, 20, blue);
			else if (initTime % 3 == 0)
				DrawRectangle(315, 715, 300, 20, blue);
			else if (initTime % 4 == 0)
				DrawRectangle(315, 715, 450, 20, blue);
			else if (initTime % 5 == 0)
				DrawRectangle(315, 715, 590, 20, blue);
			DrawText("Press SPACE to continue", screenWidth / 2 - 250, 600, 40, textColor);
			if (IsKeyPressed(KEY_SPACE))
				mode = "battle phase";
		}
		else if (mode == "battle phase")
		{
			DrawTexture(bge2, 0, 0, RAYWHITE);
			if (v5x != -1 && v5y != -1)
				DrawTexture(vs5, v5x, v5y, RAYWHITE);
			if (vp5x != -1 && vp5y != -1)
				DrawTexture(vs5, vp5x, vp5y, RAYWHITE);
			if (h5x != -1 && h5y != -1)
				DrawTexture(hs5, h5x, h5y, RAYWHITE);
			if (hp5x != -1 && hp5y != -1)
				DrawTexture(hs5, hp5x, hp5y, RAYWHITE);
			if (v4x != -1 && v4y != -1)
				DrawTexture(vs4, v4x, v4y, RAYWHITE);
			if (vp4x != -1 && vp4y != -1)
				DrawTexture(vs4, vp4x, vp4y, RAYWHITE);
			if (h4x != -1 && h4y != -1)
				DrawTexture(hs4, h4x, h4y, RAYWHITE);
			if (hp4x != -1 && hp4y != -1)
				DrawTexture(hs4, hp4x, hp4y, RAYWHITE);
			if (v3x != -1 && v3y != -1)
				DrawTexture(vs3, v3x, v3y, RAYWHITE);
			if (vp3x != -1 && vp3y != -1)
				DrawTexture(vs3, vp3x, vp3y, RAYWHITE);
			if (h3x != -1 && h3y != -1)
				DrawTexture(hs3, h3x, h3y, RAYWHITE);
			if (hp3x != -1 && hp3y != -1)
				DrawTexture(hs3, hp3x, hp3y, RAYWHITE);
			if (v32x != -1 && v32y != -1)
				DrawTexture(vs3, v32x, v32y, RAYWHITE);
			if (vp32x != -1 && vp32y != -1)
				DrawTexture(vs3, vp32x, vp32y, RAYWHITE);
			if (h32x != -1 && h32y != -1)
				DrawTexture(hs3, h32x, h32y, RAYWHITE);
			if (hp32x != -1 && hp32y != -1)
				DrawTexture(hs3, hp32x, hp32y, RAYWHITE);
			if (v2x != -1 && v2y != -1)
				DrawTexture(vs2, v2x, v2y, RAYWHITE);
			if (vp2x != -1 && vp2y != -1)
				DrawTexture(vs2, vp2x, vp2y, RAYWHITE);
			if (h2x != -1 && h2y != -1)
				DrawTexture(hs2, h2x, h2y, RAYWHITE);
			if (hp2x != -1 && hp2y != -1)
				DrawTexture(hs2, hp2x, hp2y, RAYWHITE);
			DrawText("BATTLE PHASE", gridXStart - 160, screenHeight / 8 - 50, 100, grey);
			drawBattleGrid(compGrid, playerGrid);
			const int gridSize = 10;
			int playerGridX = screenWidth / 8;
			int playerGridY = screenHeight / 4;
			int computerGridX = playerGridX + gridSize * 50 + 100;
			int computerGridY = playerGridY;
			for (int row = 0; row < gridSize; row++)
			{
				DrawText(TextFormat("%d", row), playerGridX + row * 50 - 83, playerGridY - 25, 20, grey);
				DrawText(TextFormat("%c", 'A' + row), playerGridX - 125, playerGridY + row * 50 + 20, 20, grey);
			}
			for (int row = 0; row < gridSize; row++)
			{
				DrawText(TextFormat("%d", row), computerGridX + row * 50 - 83, computerGridY - 25, 20, grey);
				DrawText(TextFormat("%c", 'A' + row), computerGridX - 125, computerGridY + row * 50 + 20, 20, grey);
			}
			DrawText("Your Grid", gridXStart + 490, screenHeight - 90, 30, grey);
			DrawText("Computer's Grid", gridXStart - 210 + sqLength / 2, screenHeight - 90, 30, grey);
			DrawText(TextFormat("Your Score: %d", playerMoves), screenWidth / 2 - 135, screenHeight / 4 - 60, 30, grey);
			DrawText(TextFormat("Ships Left: %d", shipSunk(compGrid)), 235, screenHeight - 60, 25, grey);
			if (turn == "player turn")
			{
				playerAttack(compGrid);
				playerwins(compGrid);
			}
			else if (turn == "computer turn")
			{
				compAttack(playerGrid);
				computerwins(playerGrid);
			}
			ClearBackground(blue);
		}
		else if (mode == "player wins")
		{
			MouseCoordinates();
			DrawText("You win!!!", screenWidth / 4 + 100, screenHeight / 2, 100, grey);
			DrawRectangle(screenWidth / 2 - 100, 3 * screenHeight / 4 - 90, 200, 80, grey);
			DrawText("  return\n to start", screenWidth / 2 - 75, 3 * screenHeight / 4 - 80, 30, green);
			if (mouseX >= screenWidth / 2 - 100 && mouseX <= screenWidth / 2 + 100 && mouseY >= 3 * screenHeight / 4 - 90 && mouseY <= 3 * screenHeight / 4 - 10 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				mode = "return to menu";
			ClearBackground(green);
		}
		else if (mode == "computer wins")
		{
			MouseCoordinates();
			DrawText("computer wins", screenWidth / 4 - 50, screenHeight / 2, 100, BLACK);
			DrawRectangle(screenWidth / 2 - 100, 3 * screenHeight / 4 - 90, 200, 80, grey);
			DrawText("  return\n to start", screenWidth / 2 - 75, 3 * screenHeight / 4 - 80, 30, BLACK);
			if (mouseX >= screenWidth / 2 - 100 && mouseX <= screenWidth / 2 + 100 && mouseY >= 3 * screenHeight / 4 - 90 && mouseY <= 3 * screenHeight / 4 - 10 && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				mode = "return to menu";
			ClearBackground(blue);
		}
		else if (mode == "Leaderboard")
		{
			DrawTexture(bge, 0, 0, grey);
			DrawText("Leaderboard", screenWidth / 8, 50, 150, grey);
			DrawText("<", 50, 10, 250, gloss);
			readLeaderboard(names, scores, count);
			int topLimit;
			if (count < 3)
				topLimit = count;
			else
				topLimit = 3;
			for (int i = 0; i < topLimit; i++)
			{
				int offset = 0;
				int yPosition = 200 + (i * 200);
				DrawRectangle(screenWidth / 4 - 150, yPosition + 50, 1000, 100, grey);
				string entry = to_string(i + 1) + ". " + names[i] + " - " + to_string(scores[i]);
				DrawText(entry.c_str(), screenWidth / 2 - 150, yPosition + 75, 60, BLACK);
				offset += 200;
			}
			MouseCoordinates();
			if (mouseX >= 45 && mouseX <= 130 && mouseY >= 55 && mouseY <= 195)
			{
				DrawText("<", 50, 10, 250, grey);

				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))

					mode = "start screen";
			}
			ClearBackground(blue);
		}
		else if (mode == "return to menu")
		{
			initialize(compGrid, playerGrid, size);
			compShipPlacement(compGrid, 5, 1); // aircraft carrier
			compShipPlacement(compGrid, 4, 2); // battleship
			compShipPlacement(compGrid, 3, 3); // submarine
			compShipPlacement(compGrid, 3, 4); // cruiser
			compShipPlacement(compGrid, 2, 5); // destroyer
			resetVars();
		}
		EndDrawing();
	}
	UnloadTexture(bge);
	UnloadTexture(bge2);
	UnloadTexture(bge3);
	UnloadTexture(vs5);
	UnloadTexture(hs5);
	UnloadTexture(vs4);
	UnloadTexture(hs4);
	UnloadTexture(vs3);
	UnloadTexture(hs3);
	UnloadTexture(vs2);
	UnloadTexture(hs2);
	UnloadMusicStream(bgm);
	CloseAudioDevice();
	CloseWindow();
	return 0;
}