#include <FillPat.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <OrbitOled.h>
#include <OrbitOledGrph.h>
#include "GameState.h"
extern GameState mygame;

void GameScreenInit()
{
  OrbitOledInit();
  OrbitOledClear();
  OrbitOledClearBuffer();
  OrbitOledSetFillPattern(OrbitOledGetStdPattern(iptnSolid));
  OrbitOledSetDrawMode(modOledSet);
}

void GameStateInit(); 
void DrawPaddles()
{
  paddle aPaddle1 = mygame.paddle1;
  paddle aPaddle2 = mygame.paddle2;
  int paddle1_other_corner_x = aPaddle1.x_pos + aPaddle1.width;
  int paddle1_other_corner_y = aPaddle1.y_pos + aPaddle1.height;
  int paddle2_other_corner_x = aPaddle2.x_pos + aPaddle2.width;
  int paddle2_other_corner_y = aPaddle2.y_pos + aPaddle2.height;
  OrbitOledMoveTo(aPaddle1.x_pos, aPaddle1.y_pos);
  OrbitOledDrawRect (paddle1_other_corner_x, paddle1_other_corner_y);
  OrbitOledFillRect (paddle1_other_corner_x, paddle1_other_corner_y);
  OrbitOledMoveTo(aPaddle2.x_pos, aPaddle2.y_pos);
  OrbitOledDrawRect (paddle2_other_corner_x, paddle2_other_corner_y);
  OrbitOledFillRect (paddle2_other_corner_x, paddle2_other_corner_y);
  OrbitOledUpdate(); //remove this once frames/ticks are implemented 
}

void DrawBall()
{
  ball aBall_1 = mygame.ball1;
  int opp_corner_x = aBall_1.x_pos + aBall_1.diameter;
  int opp_corner_y = aBall_1.y_pos + aBall_1.diameter;
  OrbitOledSetFillPattern(OrbitOledGetStdPattern(iptnSolid));
  OrbitOledSetDrawMode(modOledSet);
  OrbitOledMoveTo(aBall_1.x_pos, aBall_1.y_pos);
  OrbitOledDrawRect(opp_corner_x, opp_corner_y);
  OrbitOledFillRect(opp_corner_x, opp_corner_y);
  OrbitOledUpdate(); //remove this once frames/ticks are implemented
}

void DrawScore()
{
  char score1[32];
  char score2[32];
  OrbitOledMoveTo(48, 2);
  //OrbitOledDrawString("0");
  OrbitOledDrawString(itoa(mygame.player1_score, score1, 10));
  OrbitOledMoveTo(80, 2);
  //OrbitOledDrawString("0");
  OrbitOledDrawString(itoa(mygame.player2_score, score2, 10));
  OrbitOledUpdate();
}
void DrawBorder()
{
}

//static void GameFrames() Rename this, too similar to GameFrame() in GameLogic
//{
//}
