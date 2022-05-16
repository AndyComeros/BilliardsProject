#include "GUI.h"

void initGUI()
{
    int menuCount = 0;
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
    GLfloat windowPosX = (element->posX * windowWidth) - element->lengthX/2;
    GLfloat windowPosY = (element->posY * windowHeight) - element->lengthY/2;

    //swap to 2D projection
    glMatrixMode(GL_PROJECTION);
    //save matrix state
    glPushMatrix();
    //reset matrix
    glLoadIdentity();
    //set 2d projection
    glOrtho(0.0,windowWidth,windowHeight,0.0,-1.0,10);
    //back to model view
    glMatrixMode(GL_MODELVIEW);
    //save state
    glPushMatrix();
    glLoadIdentity();

    glDisable(GL_CULL_FACE);//not sure...
    //draw HUDS

    glClear(GL_DEPTH_BUFFER_BIT);
    //DRAW TEXT
    glColor3f(0.0f, 1.0f, 0.0f);
    glRasterPos2i(windowPosX, windowPosY+element->lengthY/1.5);//trying to position text in center of button, probably needs to be something to do with font as well...
    glutBitmapString(GLUT_BITMAP_HELVETICA_18,element->Text);

    glBegin(GL_QUADS);
    glColor3f(1.0f, 0.0f, 0.0);

    glVertex2f(windowPosX,windowPosY);//top left
    glVertex2f(element->lengthX+windowPosX, windowPosY);//top-right
    glVertex2f(element->lengthX+windowPosX, element->lengthY+windowPosY);//bottom-right
    glVertex2f(windowPosX, element->lengthY+windowPosY);//bottom-left
    glEnd();

    //switch back to 3d
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

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
    GetUI(ID)->isActive = 1;
}
