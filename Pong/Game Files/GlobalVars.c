#include <stdio.h>
#include <stdlib.h>
#include "GameState.h"
//paddle paddle1;
//paddle paddle2;
//ball ball1;

GameState mygame =  
{
    {0, 10, 0, 0, 1, -1},      // width, height, x_pos, y_pos, is_moving, moving_direction
    {0, 10, 123, 0, 1, -1},    // width, height, x_pos, y_pos, is_moving, moving_direction
    {1, 90, 15, -1, 1}, // {Diameter, x_pos, y_pos, x_velocity, y_velocity}
    {false},
    {0},
    {0}
}; 
