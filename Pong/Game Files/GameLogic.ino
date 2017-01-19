#include <stdlib.h>
#include <stdio.h>
#include "GameState.h"
extern GameState mygame;

const uint32_t SwitchCount = 2;
const uint32_t ButtonCount = 2;
const uint32_t Switches[SwitchCount] = { PA_7, PA_6 };
const uint32_t Buttons[ButtonCount] = { PD_2, PE_0 };
const uint32_t Potentiometer = PE_3;


struct ButtonState
{ 
  bool state;
  bool isRising;
};

static struct InputState
{
  bool                switches[2];
  struct ButtonState  buttons[2];
  float               potentiometer;
} gameInputState;

void SetupButtons() 
{
  for(int i = 0; i < SwitchCount; ++i )
    pinMode(Switches[i], INPUT);
  for(int i = 0; i < ButtonCount; ++i )
    pinMode(Buttons[i], INPUT);
}

static void uiInputTick()
{
  for(int i = 0; i < SwitchCount; ++i )
    gameInputState.switches[i] = digitalRead(Switches[i]);
  for(int i = 0; i < ButtonCount; ++i )
  {
    // Only look for Rising Edge Signals.
    bool previousState = gameInputState.buttons[i].state;
    gameInputState.buttons[i].state = digitalRead(Buttons[i]);
    gameInputState.buttons[i].isRising = (!previousState && gameInputState.buttons[i].state);
  }
}

void MoveBall()
{
  int oldx = mygame.ball1.x_pos;
  int oldy = mygame.ball1.y_pos;
  mygame.ball1.x_pos = oldx + mygame.ball1.x_velocity;
  mygame.ball1.y_pos = oldy + mygame.ball1.y_velocity;
    
}
void MovePaddles()
{
  if(mygame.paddle1.is_moving) {
    if ((mygame.paddle1.y_pos >= 0) && (mygame.paddle1.y_pos <= 32 - mygame.paddle1.height)) {
      mygame.paddle1.y_pos = mygame.paddle1.y_pos - mygame.paddle1.moving_direction;
    }
  }  
  if(mygame.paddle2.is_moving) {
    if ((mygame.paddle2.y_pos >= 0) && (mygame.paddle2.y_pos <= 32 - mygame.paddle2.height)) {
      mygame.paddle2.y_pos = mygame.paddle2.y_pos - mygame.paddle2.moving_direction;
    }
  }
  if(mygame.paddle1.y_pos == 0 || mygame.paddle1.y_pos == 32 - mygame.paddle1.height) mygame.paddle1.moving_direction = mygame.paddle1.moving_direction*-1;
  if(mygame.paddle2.y_pos == 0 || mygame.paddle2.y_pos == 32 - mygame.paddle2.height) mygame.paddle2.moving_direction = mygame.paddle2.moving_direction*-1;
}

void CheckCollisions()
{      
      int x_left = mygame.paddle1.x_pos + mygame.paddle1.width;
      int x_right = mygame.paddle2.x_pos;
      int y_left_top = mygame.paddle1.y_pos + mygame.paddle1.width;
      int y_left_bottom = mygame.paddle1.y_pos + mygame.paddle1.height + mygame.paddle1.width;
      int y_right_top = mygame.paddle2.y_pos;
      int y_right_bottom = mygame.paddle2.y_pos + mygame.paddle2.height;
      // Checking for collisions with paddles
      // Case 1: Collides with left paddle
      if((mygame.ball1.x_pos - x_left)>0&&(mygame.ball1.x_pos - x_left)<=2)
      {
        if((mygame.ball1.y_pos)>=y_left_top&&(mygame.ball1.y_pos)<=y_left_bottom)
        {
          mygame.ball1.x_velocity = (-1)*mygame.ball1.x_velocity;
        }
      }
      // Case 2: Collides with right paddle
      if((x_right - mygame.ball1.x_pos)>0&&(x_right - mygame.ball1.x_pos)<=4)
      {
        if((mygame.ball1.y_pos)>=y_right_top&&(mygame.ball1.y_pos)<=y_right_bottom)
        {
          mygame.ball1.x_velocity = (-1)*mygame.ball1.x_velocity;
        }
      }

      // Case 3: Doesn't collide with paddle. Points scored for opposing player
      if(mygame.ball1.x_pos == 0) {
        mygame.player2_score++;
        mygame.ball1.x_pos == 32;
        mygame.ball1.y_pos == 8;
        mygame.ball_in_play = false;
        DrawBall();
        return;
      }
      if(mygame.ball1.x_pos == 128) {
        mygame.player1_score++;
        mygame.ball1.x_pos == 32;
        mygame.ball1.y_pos == 8;
        DrawBall();
        mygame.ball_in_play = false;
        delay(200);
        return;
      }
      // Case 4: Collides with top border
      if((mygame.ball1.y_pos - 0) == 0 || (32 - mygame.ball1.y_pos) == 0) 
      {
        mygame.ball1.y_velocity = (-1) * mygame.ball1.y_velocity;      
      }
}

void InGameControlTick()
{
  uiInputTick();
  
  if(gameInputState.buttons[0].isRising) {
    if(mygame.paddle1.is_moving == 0) {
      mygame.paddle1.is_moving = 1;
    } else {
      mygame.paddle1.is_moving = 0;
    }
  }
  if(gameInputState.buttons[1].isRising) {
    if(mygame.paddle2.is_moving == 0) {
      mygame.paddle2.is_moving = 1;
    } else {
      mygame.paddle2.is_moving = 0;
    }
  }
  MovePaddles();
  /*if(gameInputState.switches[1]) {
    mygame.paddle1.moving_direction = 1;
  } else {
    mygame.paddle1.moving_direction = -1;
  }/*
  if(gameInputState.switches[1]) {
    mygame.paddle2.moving_direction = -1;
  } else {
    mygame.paddle2.moving_direction = 1;
  }*/
}

void StartGame()
{
  mygame.ball1.x_pos = 64;
  mygame.ball1.y_pos = 16;
  OrbitOledMoveTo(8, 24);
  OrbitOledDrawString("Press B1 or B2");
  DrawBall();
  DrawPaddles();
  OrbitOledUpdate();
  while(mygame.ball_in_play == false) {
    uiInputTick();
    if(gameInputState.buttons[1].isRising) {
        mygame.ball1.x_velocity = 1;
        mygame.ball_in_play = true;
        return;
    }
    if(gameInputState.buttons[0].isRising) {
        mygame.ball1.x_velocity = -1;
        mygame.ball_in_play = true;
        return;
    }
  } 
}
void GameFrame()
{
  
  if(mygame.ball_in_play == false) {
    DrawScore();
    StartGame();
  }
  while(mygame.ball_in_play == true) {
    InGameControlTick();
    DrawPaddles();
    DrawBall();
    MoveBall();
    CheckCollisions();
    OrbitOledClearBuffer();
    delay(20);
  }
}

