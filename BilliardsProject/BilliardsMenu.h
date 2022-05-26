#ifndef BILLIARDSMENU_H_INCLUDED
#define BILLIARDSMENU_H_INCLUDED

#include "GUI.h"
#include "GameInput.h"
#include "Display.h"

//initializes all menus
void InitBilliardUI();

//fills menu pointer with elements for billiards game.
void CreateBillardsMenu();

void CreateSettingsMenu();

void CreateGameMenu();

void CreatePauseMenu();

//--button_callbacks--//
void testCallback();

void StartGame();

void CloseProgram();

void OpenSettings();

void OpenMainMenu();

void OpenPauseMenu();

void ClosePauseMenu();

void RestartGame();


#endif // BILLIARDSMENU_H_INCLUDED
