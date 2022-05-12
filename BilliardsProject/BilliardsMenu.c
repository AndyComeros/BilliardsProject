#include "BilliardsMenu.h"
void InitBilliardUI()
{
    CreateBillardsMenu();
    CreateSettingsMenu();
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

    GUI_Element button2 = {0.5,0.5,80,30,"Crash"};
    menuArray[menuCount].element[1] = button2;
    menuCount++;
}

//###--Menu_Callback_Functions--###//

void StartGame()
{
    //put stuff that starts gameplay here
    GetUI(1)->isActive = 0;
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
