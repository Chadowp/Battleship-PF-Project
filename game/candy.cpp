#include <iostream>
// rand srand func
#include <cstdlib>
#include <ctime>
#include <raylib.h>
using namespace std;
void compHit(char playerGrid[10][10])
{
    static int x, y, hit = 0, startXPos, startYPos, direction = -1, totalShips = 5, maxSize = 5;
    static int currentShipIndex = -1;
    bool attacked = false;; // flag to indicate if an attack was made

    while (attacked == false)
    {
        if (hit == 0)
        {
            x = rand() % 10;
            y = rand() % 10;
            if (playerGrid[x][y] == 's')
            {
                hit++;
                startXPos = x;
                startYPos = y;
                playerGrid[x][y] = 'h'; // marks as hit
                attacked = true;
            }
            else if (playerGrid[x][y] == 'w') // Mark empty cell as missed
            {
                playerGrid[x][y] = 'm';
                attacked = true; //but failed
            }
        }
        else
        {
            if (direction == -1) //as if all directions come out as wrong it places -1 on direction so it needs to be reset
            {
                direction = 0; // restarts the direction
            }


            int newX = x, newY = y;
            // checking which cell to attack
            if (direction == 0 && x + 1 < 10)
                newX = x + 1; // Right
            else if (direction == 1 && x - 1 >= 0)
                newX = x - 1; // Left
            else if (direction == 2 && y - 1 >= 0)
                newY = y - 1; // Up
            else if (direction == 3 && y + 1 < 10)
                newY = y + 1; // Down
            else
                direction++;

            if (direction > 3)
            {
                direction = -1; // when all directions have failed
                x = startXPos;
                y = startYPos;
            }
            else if (playerGrid[newX][newY] == 's')
            {
                playerGrid[newX][newY] = 'h';
                x = newX;
                y = newY;
                hit++;
                attacked = true;
            }
            else if (playerGrid[newX][newY] == 'w')
            {
                playerGrid[newX][newY] = 'm'; // marked as miss
                direction++;
            }

        }

        //makeshift code (to be changed) to see if ship has sunk
        if (hit > 0 && attacked == true)
        {
            //will write this tmrw IA
        }
    }
}
