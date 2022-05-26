#include "BilliardsMenu.h"
void InitBilliardUI()
{
    CreateBillardsMenu();
    CreateSettingsMenu();
    CreateGameMenu();
    CreatePauseMenu();
}

void CreateBillardsMenu()
{
    menuArray[menuCount];

    menuArray[menuCount].elementCount = 3;
    menuArray[menuCount].isActive = 1;//active by default
    menuArray[menuCount].menuID = 1;//used to identify this menu
    menuArray[menuCount].element = (GUI_Element *)malloc(sizeof(GUI_Element)*menuArray[menuCount].elementCount);

    //test buttons
    GUI_Element button2 = {0.5,0.6,80,30,"Exit"};
    button2.btn_CallBack = &CloseProgram;
    menuArray[menuCount].element[1] = button2;

    GUI_Element button1 = {0.5,0.5,80,30,"Settings"};
    button1.btn_CallBack = &OpenSettings;
    menuArray[menuCount].element[0] = button1;

    GUI_Element button3 = {0.5,0.4,80,30,"Start"};
    button3.btn_CallBack = &StartGame;
    menuArray[menuCount].element[2] = button3;
    menuCount++;
}

void CreateSettingsMenu()
{
    menuArray[menuCount].elementCount = 2;
    menuArray[menuCount].isActive = 0;//inactive by default
    menuArray[menuCount].menuID = 2;//used to identify this menu
    menuArray[menuCount].element = (GUI_Element *)malloc(sizeof(GUI_Element)*menuArray[menuCount].elementCount);

    GUI_Element button1 = {0.5,0.6,80,30,"Back"};
    button1.btn_CallBack = &OpenMainMenu;
    menuArray[menuCount].element[0] = button1;

    GUI_Element button2 = {0.5,0.5,80,30,"Test"};
    button2.btn_CallBack = &testCallback;
    menuArray[menuCount].element[1] = button2;
    menuCount++;
}

void CreateGameMenu()
{
    menuArray[menuCount].elementCount = 2;
    menuArray[menuCount].isActive = 0;//inactive by default
    menuArray[menuCount].menuID = 3;//used to identify this menu
    menuArray[menuCount].element = (GUI_Element *)malloc(sizeof(GUI_Element)*menuArray[menuCount].elementCount);

    GUI_Element pauseButton = {0.1,0.1,100,30,"Pause"};
    pauseButton.btn_CallBack = &OpenPauseMenu;
    menuArray[menuCount].element[0] = pauseButton;

    GUI_Element shotIndicator = {0.2,0.1,120,30,"0"};
    shotIndicator.btn_CallBack = &testCallback;
    menuArray[menuCount].element[1] = shotIndicator;
    menuCount++;
}

void CreatePauseMenu()
{
    menuArray[menuCount].elementCount = 3;
    menuArray[menuCount].isActive = 0;//inactive by default
    menuArray[menuCount].menuID = 4;//used to identify this menu
    menuArray[menuCount].element = (GUI_Element*)malloc(sizeof(GUI_Element) * menuArray[menuCount].elementCount);

    GUI_Element restartButton = { 0.1,0.1,110,30,"Restart" };
    restartButton.btn_CallBack = &RestartGame;
    menuArray[menuCount].element[0] = restartButton;

    GUI_Element closeButton = { 0.1,0.15,110,30,"Exit Game" };
    closeButton.btn_CallBack = &CloseProgram;
    menuArray[menuCount].element[1] = closeButton;

    GUI_Element backButton = { 0.1,0.2,110,30,"Close Menu" };
    backButton.btn_CallBack = &ClosePauseMenu;
    menuArray[menuCount].element[2] = backButton;
    menuCount++;
}

//###--Menu_Callback_Functions--###//
void testCallback()
{
    printf("TestCallback!");
}

void StartGame()
{
    //put stuff that starts gameplay here
    //GetUI(1)->isActive = 0;
    switchUI(3);

}

void CloseProgram()
{
    glutLeaveMainLoop();
    exit(0);
}
void OpenSettings()
{
    printf("opening settings\n");
    switchUI(2);
}

void OpenMainMenu()
{
    printf("opening main\n");
    switchUI(1);
}

void OpenPauseMenu() {
    switchUI(4);
}

void ClosePauseMenu() {
    switchUI(3);
}

void RestartGame() {
    //restart game code goes here
}
