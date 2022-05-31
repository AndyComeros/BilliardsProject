#ifndef BILLIARDSMENU_H_INCLUDED
#define BILLIARDSMENU_H_INCLUDED

#include "GUI.h"
#include "GameInput.h"

//initializes all menus
void InitBilliardUI();

//fills menu pointer with elements for billiards game.
void CreateBillardsMenu();

void CreateSettingsMenu();

void CreateGameMenu();

void CreatePauseMenu();

void CreateWinMenu();

//--button_callbacks--//
void testCallback();

void StartGame();

void CloseProgram();

void OpenSettings();

void OpenMainMenu();

void OpenPauseMenu();

void OpenWinMenu();

void ClosePauseMenu();

void RestartGame();

//settings menu callbacks
void op1ChangeShade();
void op2ChangeModel();

#endif // BILLIARDSMENU_H_INCLUDED
