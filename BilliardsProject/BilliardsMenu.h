#ifndef BILLIARDSMENU_H_INCLUDED
#define BILLIARDSMENU_H_INCLUDED

#include "GUI.h"
#include "GameInput.h"

	///initializes all billiards menus
void InitBilliardUI();	
	///fills menu pointer with elements for billiards game.
void CreateBillardsMenu();
	///Creates the settings menu
void CreateSettingsMenu();
	///Creates the game menu
void CreateGameMenu();
	///Creates the Pause menu
void CreatePauseMenu();
	///Creates the win menu
void CreateWinMenu();

//--button_callbacks for menu items--//
void testCallback();
	///Switches to Game menu
void StartGame();
	///Dispalys images of team AAAA
void OnCloseDisplay();
	///Closes the game window and Displays Team AAAA
void CloseProgram();
	///Opens the settings menu
void OpenSettings();
	///Opens the main menu
void OpenMainMenu();
	///Opens the pause menu
void OpenPauseMenu();
	///Opens the win menu
void OpenWinMenu();
	///Opens the pause menu
void ClosePauseMenu();
	///Resets the game and opens main menu
void RestartGame();

//--settings menu callbacks--//
	///Changes the shading model
void op1ChangeShade();
	///Changes the model of the Balls
void op2ChangeModel();

#endif // BILLIARDSMENU_H_INCLUDED
