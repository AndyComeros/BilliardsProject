#include "BilliardsMenu.h"
#include "GameSession.h"
#include "Texture.h"


pixel** img_Andy;
pixel** img_Alan;
pixel** img_Azure;
pixel** img_Geoff;

void InitBilliardUI()
{
    activeMenu = 1;
    ballMode = 0;
    CreateBillardsMenu();
    CreateSettingsMenu();
    CreateGameMenu();
    CreatePauseMenu();
    CreateWinMenu();


   img_Andy = InputImage("images/andy.bmp", 100, 100);
   img_Alan = InputImage("images/alan.bmp", 100, 100);
   img_Azure = InputImage("images/azure.bmp", 100, 100);
   img_Geoff = InputImage("images/geoff.bmp", 100, 100);
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
    menuArray[menuCount].elementCount = 3;
    menuArray[menuCount].isActive = 0;//inactive by default
    menuArray[menuCount].menuID = 2;//used to identify this menu
    menuArray[menuCount].element = (GUI_Element *)malloc(sizeof(GUI_Element)*menuArray[menuCount].elementCount);

    GUI_Element button1 = {0.5,0.6,120,30,"Back"};
    button1.btn_CallBack = &OpenMainMenu;
    menuArray[menuCount].element[0] = button1;

    GUI_Element button2 = {0.5,0.5,120,30,"Shade Mode"};
    button2.btn_CallBack = &op1ChangeShade;
    menuArray[menuCount].element[1] = button2;

    GUI_Element button3 = { 0.5,0.4,120,30,"Model Mode" };
    button3.btn_CallBack = &op2ChangeModel;
    menuArray[menuCount].element[2] = button3;
    menuCount++;
    //op2ChangeModel
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

void CreateWinMenu()
{
    menuArray[menuCount].elementCount = 1;
    menuArray[menuCount].isActive = 0;//inactive by default
    menuArray[menuCount].menuID = 5;//used to identify this menu
    menuArray[menuCount].element = (GUI_Element*)malloc(sizeof(GUI_Element) * menuArray[menuCount].elementCount);

    GUI_Element winbutton = { 0.5,0.5,160,60,"     You WON!\n  Click to Restart!" };
    winbutton.btn_CallBack = &RestartGame;
    menuArray[menuCount].element[0] = winbutton;
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
    isHittable = 1;
    switchUI(3);

}

void OnCloseDisplay() {
    



    displayImage(img_Alan, 100, 100,100,700);
    displayImage(img_Andy, 100, 100,500, 700);
    displayImage(img_Azure, 100, 100,900, 700);
    displayImage(img_Geoff, 100, 100,1300, 700);

    glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0, windowWidth, windowHeight, 0.0, -1.0, 10);

    //back to model view
    glMatrixMode(GL_MODELVIEW);
    //save state
    glPushMatrix();
    glLoadIdentity();

    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2i(200, 250);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, "Alan");
    glRasterPos2i(600, 250);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, "Andy");
    glRasterPos2i(1000, 250);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, "Azure");
    glRasterPos2i(1400, 250);
    glutBitmapString(GLUT_BITMAP_HELVETICA_18, "Geoff");
    glFlush();
}

void CloseProgram()
{

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutHideWindow();
    glutInitWindowSize(500, 300);
    glutInitWindowPosition(500, 500);
    glutCreateWindow("AAAA Pool");

    glutDisplayFunc(OnCloseDisplay);
    //glutLeaveMainLoop();
    //exit(0);
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
    isHittable = 0;
    switchUI(4);
}

void OpenWinMenu()
{
    isHittable = 0;
    switchUI(5);
}

void ClosePauseMenu() {
    isHittable = 1;
    switchUI(3);
}

void RestartGame() {
    OpenMainMenu();
    setCamRotAngle(0.f);
    gameStartingSetup();
}

void op1ChangeShade(){
    unsigned int sMod;
    glGetIntegerv(GL_SHADE_MODEL,&sMod);
    if (sMod == GL_FLAT) {
        glShadeModel(GL_SMOOTH);
    }
    else {
        glShadeModel(GL_FLAT);
    }
}

void op2ChangeModel() {
    ballMode++;
    if (ballMode > 3)
        ballMode = 0;
}
