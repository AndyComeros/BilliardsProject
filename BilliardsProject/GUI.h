#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED
#include <gl/freeglut.h>
    /**
    *   @brief Stores information on a single element in
    *   a menu. Each element can be clicked to execute its callback.
    * 
    */
typedef struct
{
        ///X position relative to top left
    GLfloat posX;
        ///Y position relative to top left
    GLfloat posY;
        ///clickable area of button along x axis
    GLfloat lengthX;
        ///clickable area of button along Y axis
    GLfloat lengthY;
        ///text of button
    char Text[500];
        ///behaviour of button
    void(*btn_CallBack)();
} GUI_Element;
    /**
    *   @brief Menus encapsulate an array of GUI elements. Tracks if
    *   its elements should be shown
    */
typedef struct
{
        ///unique ID of menu-technically not guarneteed to be unique...
    int menuID;
        ///Amount of UI elements in the element array
    int elementCount;
        ///If this menu should be displayed and usable
    int isActive;
        ///Array of GUI elements in menu
    GUI_Element * element;
} Menu;

///global variables storing all menu info
    ///Tracks amount of menus currently in menuArray
int menuCount;
    ///Index of currently active menu
int activeMenu;
    ///Menu count capped at 10, may make this dynamic later
Menu menuArray[10];
    ///Tracks the current height of the window
int windowHeight;
    ///Tracks the current Width of the window
int windowWidth;
    /**
    *   @brief Sets default global menu variables
    *   call this before entering GLUTs main loop
    *   @return void
    */
void initGUI();
    /**
    *   @brief Mouse callback function for the menu system
    *   checks if the mouse is within a buttons clickable area
    *   and executes its callback function.
    *   @param Button - mouse button being clicked
    *   @param state - state of Button
    *   @param x - mouse x coord
    *   @param y- mouse y coord
    *   @return void
    */
void handleMenuInput(int Button,int state,int x,int y);
    /**
    *   @breif enusres menu uses correct window dimensions on window size change
    *   call in window reshape function.
    *   @param w - new window width
    *   @param h - new window height
    *   @return void
    */
void reshapeGUI(int w, int h);
//calls renderUIElement for all elements in all active menus, put in display function after scene renders
    /**
    *   @brief renders all UI elements for the active menu, call this function in the
    *   main display function
    *   @return void
    */
void renderMenus();
    /**
    *   @brief Renders a single GUI element to the screen
    *   @param element - GUI element to be displayed
    *   @return void
    */
void renderUIElement(GUI_Element * element);
    /**
    *   @brief Returns a reference to a menu from the global menu array
    *   based on its ID.
    *   @param ID - the ID number of the menu to be returned
    *   @return Menu* - pointer to a menu item
    */
Menu * GetUI(int ID);
    /**
    *   @brief changes the active menu to a menu with a specified ID
    *   @param ID - ID of menu to switch to
    *   @return void
    */
void switchUI(int ID);

#endif // GUI_H_INCLUDED