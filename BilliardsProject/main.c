#include <stdio.h>
#include <stdlib.h>
#include <gl/freeglut.h>
#include "Display.h"

int main(int argc, char** argv)
{
    //###########--REQUIRED STUFF--###########//
    //need to initiaize glut before it can be used
    glutInit(&argc,argv);

    //initialize window properties
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0); // place window top left on display

    //create window and name it
    glutCreateWindow("Billiards Game");

    //initailize Glut project
    initGlut();
    // init starting objects
    initObjects();

    //specify function to be called when display is opened or asked to redisplay
    glutDisplayFunc(display);

    //initiaize the main loop which uses bunch of callbacks for IO
    glutTimerFunc(100,PhysicsUpdate,0);
    glutReshapeFunc(changeSize);
    //glutKeyboardFunc(keyboard);
    //glutSpecialFunc(processSpecialKeys);

    //main event loop, callbacks made here
    glutMainLoop();
    return 0;

}
