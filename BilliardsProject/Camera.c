#include "Camera.h"

void initCam(const Camera *c)
{
    //set camera data - need to set to variables, perhps give game object data...
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(c->pos.x, c->pos.y, c->pos.z,//position
        c->look.x, c->look.y, c->look.z,// look at target
        c->up.x, c->up.y, c->up.z //camera up vector
    );
}

void updateCameraViewing(const CameraViewing*c)
{
    //set up a perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(c->fov, c->aspect, c->nearVal, c->farVal);

    glMatrixMode(GL_MODELVIEW);
}

void updateCamera(const Camera *c)
{
    gluLookAt(c->pos.x, c->pos.y, c->pos.z,//position
        c->look.x, c->look.y, c->look.z,// look at target
        c->up.x, c->up.y, c->up.z //camera up vector
    );
}




