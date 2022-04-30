#include "Camera.h"

void viewingInit()
{
    //set up a perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(fov, aspect, nearVal, farVal);

    glMatrixMode(GL_MODELVIEW);
}
