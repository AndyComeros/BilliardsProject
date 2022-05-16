#ifndef BILLIARDSMENU_H_INCLUDED
#define BILLIARDSMENU_H_INCLUDED

#include "GUI.h"

void InitBilliardUI();

//fills menu pointer with elements for billiards game.
void CreateBillardsMenu();

void CreateSettingsMenu();

//--button_callbacks--//
void testCallback();

void StartGame();

void CloseProgram();

void OpenSettings();

void OpenMainMenu();
#endif // BILLIARDSMENU_H_INCLUDED
