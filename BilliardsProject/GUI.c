#include "GUI.h"

void initGUI()
{
    int menuCount = 0;
    activeMenu = 0;
    windowHeight = glutGet(GLUT_WINDOW_HEIGHT);
    windowWidth = glutGet(GLUT_WINDOW_WIDTH);
    printf("height: %d", windowHeight);
    printf("width: %d", windowWidth);
}

//needs to be called on window reshape
void reshapeGUI(int w, int h)
{
    windowHeight = h;
    windowWidth = w;
}

//might seperate into a helper function for cleaner code
//only supports one active menu at once
void handleMenuInput(int Button,int state,int x,int y)
{
    if(state  == GLUT_DOWN)
    {
        printf("Mouse Location: (%d,%d)\n", x,y);
        int activeIndex = -1;//index of active menu
        for(int i=0; i<menuCount; i++)
        {
            if(menuArray[i].isActive != 0)
            {
                activeIndex = i;
            }
        }

        //only run if there is an active menu
        if(activeIndex > -1)
        {
            for(int j=0; j<menuArray[activeIndex].elementCount; j++)
            {
                
                GLfloat xlength = menuArray[activeIndex].element[j].lengthX / 2;
                GLfloat ylength = menuArray[activeIndex].element[j].lengthY / 2;
                GLfloat xCoord = menuArray[activeIndex].element[j].posX * (windowWidth);
                GLfloat yCoord = menuArray[activeIndex].element[j].posY * (windowHeight) - ylength;

                //if mouse if over button
                if(y < yCoord + ylength && y > yCoord - ylength && x < xCoord + xlength && x > xCoord - xlength)
                {
                    menuArray[activeIndex].element[j].btn_CallBack();
                }
            }
        }
    }
}


//renderMenu(menu,1);
void renderMenus()
{
    for(int i =0; i< menuCount; i++)
    {
        if(menuArray[i].isActive == 1)
        {
            for(int j=0; j< menuArray[i].elementCount; j++)
            {
                renderUIElement(&menuArray[i].element[j]);

            }
        }
    }

}

void renderUIElement(GUI_Element * element)
{
    GLfloat border = 3;
    GLfloat windowPosX = (element->posX * windowWidth) - element->lengthX/2;
    GLfloat windowPosY = (element->posY * windowHeight) - element->lengthY/2;
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(0.0,windowWidth,windowHeight,0.0,-1.0,10);

    //back to model view
    glMatrixMode(GL_MODELVIEW);
    //save state
    glPushMatrix();
    glLoadIdentity();
    
    //has issues when not in smooth shading
    unsigned int shadeMode;
    glGetIntegerv(GL_SHADE_MODEL, &shadeMode);
    glShadeModel(GL_SMOOTH);

    //glDisable(GL_CULL_FACE);//not sure...
    glClear(GL_DEPTH_BUFFER_BIT);

    //DRAW TEXT
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2i(windowPosX+5, windowPosY+element->lengthY/1.5);//trying to position text in center of button, probably needs to be something to do with font as well...
    glutBitmapString(GLUT_BITMAP_HELVETICA_18,element->Text);

    //inner bit
    glBegin(GL_QUADS);
    glColor3f(0.98f, 0.51f, 0.25f);
    glVertex2f(windowPosX, windowPosY);//top left
    glVertex2f(element->lengthX + windowPosX, windowPosY);//top-right
    glColor3f(0.2f, 0.0f, 0.0);
    glVertex2f(element->lengthX + windowPosX, element->lengthY + windowPosY);//bottom-right
    glVertex2f(windowPosX, element->lengthY + windowPosY);//bottom-left
    glEnd();
    
    //outer bit
    glBegin(GL_QUADS);
    glColor3f(0.25f, 0.25f, 0.25f);
    glVertex2f(windowPosX - border,windowPosY - border);//top left
    glVertex2f(element->lengthX+windowPosX + border, windowPosY - border);//top-right
    glColor3f(0.0f, 0.0f, 0.0f);
    glVertex2f(element->lengthX+windowPosX + border, element->lengthY+windowPosY + border);//bottom-right
    glVertex2f(windowPosX - border, element->lengthY+windowPosY + border);//bottom-left
    glEnd();

    glShadeModel(shadeMode);//switch back to old shade mode
    //switch back to 3d
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glEnable(GL_LIGHTING);
    //glutSolidCone(100,700,20,30);
}


Menu * GetUI(int ID)
{
    for(int i=0; i<menuCount; i++)
    {
        if(menuArray[i].menuID == ID)
        {
            return &menuArray[i];
        }
    }
    return NULL;//uuummm not too sure
}

void switchUI(int ID)
{
    for(int i=0; i< menuCount; i++)
    {
        if(menuArray[i].menuID != ID)
        {
            //printf("Deactivate!!: %d, looking for ID %d\n",i,ID);
            menuArray[i].isActive = 0;

        }
    }
    activeMenu = ID;
    GetUI(ID)->isActive = 1;
}
