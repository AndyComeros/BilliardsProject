#include "Camera.h"

void updateCameraViewing(const CameraViewing* c)
{
    //set up a perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(c->fov, c->aspect, c->nearVal, c->farVal);

    glMatrixMode(GL_MODELVIEW);
}


