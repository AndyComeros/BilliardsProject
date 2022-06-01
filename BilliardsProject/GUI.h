#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED
#include <gl/freeglut.h>

/**
* @todo - renderUI, have glOrtho take in window size dynamically, currently built in
* @todo - make color value in button struct
* @todo - have button change on hover?
* @todo - have add button func, add this to create billiards menu func, should help stop out of bounds error- not necessary tho
* @todo - make coordinates relative to center?- poistioning buttons is kinda scuff rn.
*/

typedef struct
{
    //position ratio relative to top left
    //e.g 0.5,0.5 is center; 0,0 is top left, 1,1 is top right
    GLfloat posX;
    GLfloat posY;
    //clickable area of button
    GLfloat lengthX;
    GLfloat lengthY;

    //text of button
    char Text[40];

    //behaviour of button
    void(*btn_CallBack)();
} GUI_Element;

typedef struct
{
    int menuID;//unique ID of menu-technically not guarneteed...
    int elementCount;
    int isActive;//0 means inactive 1 means active
    GUI_Element * element;
} Menu;

//global variables storing all menus
int menuCount;
int activeMenu;

//max 10 menus, saves acllocating memory...
Menu menuArray[10];

int windowHeight;
int windowWidth;

//call in initialize method to setup menu variables correctly
void initGUI();

//put in mouse callback function, call if menu state is active.
void handleMenuInput(int Button,int state,int x,int y);

//window reshape function- dont forget to put in glut reshape callback
void reshapeGUI(int w, int h);

//calls renderUIElement for all elements in all active menus, put in display function after scene renders
void renderMenus();

//renders individual element
void renderUIElement(GUI_Element * element);

//get a reference to a menu based on ID
Menu * GetUI(int ID);

//closes all other UIS, sets one to active
void switchUI(int ID);

#endif // GUI_H_INCLUDED
