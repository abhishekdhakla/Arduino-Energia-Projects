#include <OrbitOled.h>
#include <OrbitOledChar.h>
#include <OrbitOledGrph.h>
#include <FillPat.h>
#include <stdlib.h>
#include "GameState.h"

//#include "GlobalVars.c"

void GameScreenInit();
void DrawPaddles();
void PaddleTest();
void GameFrame();
//static void GameFrame();


void setup() {
  Serial.begin(9600);
  delay(100);
  GameScreenInit();
  SetupButtons();
}

void loop() {
    GameFrame();
    //TestOledDisplay();
    //DrawPaddles();
    //MoveBall();
    //PaddleTest();
    //TestOledDisplay();
    //OrbitOledUpdate();
    
}
