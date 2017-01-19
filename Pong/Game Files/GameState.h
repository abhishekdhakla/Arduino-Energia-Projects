#ifndef GAMESTATE_H
#define GAMESTATE_H
// END HEADERGUARD OPENER
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <OrbitOled.h>
#include <OrbitOledGrph.h>
#include <stdbool.h>

//#include "GlobalVars.c"

typedef struct paddle 
{
  int width;
  int height;
  int x_pos;
  int y_pos;
  bool is_moving;
  int moving_direction;
  //int paddle_other_corner_x; // = paddle_curs_x + paddle_width;
  //int paddle_other_corner_y; // = paddle_curs_y + paddle_height;
} paddle;

typedef struct ball // actually a rectangle
{
  int diameter;
  int x_pos;
  int y_pos;
  //int new_x_pos;
  //int new_y_pos;
  int x_velocity;
  int y_velocity;
} ball;


typedef struct border
{
} border;

typedef struct GameState
{
  paddle paddle1;
  paddle paddle2;
  ball ball1;
  bool ball_in_play;
  int player1_score;
  int player2_score;
} GameState;

#endif
