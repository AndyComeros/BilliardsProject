#include "Camera.h"

CameraViewing camView;



void viewingInit()
{
    //set up a perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    camView.fov = 30;		// degrees
    camView.aspect = 1;		// aspect ratio aspect = height/width
    camView.nearVal = 0.5;     // near and far clipping planes
    camView.farVal = 5000;

    gluPerspective(camView.fov, camView.aspect, camView.nearVal, camView.farVal);

    glMatrixMode(GL_MODELVIEW);
}

//changes size of viewport when window size changes. use as callback function
//for when it does change//not my code. removed stuff.
void changeSize(int w, int h)
{
    float ratio = 1.0 * w / h;
    camView.aspect = ratio;

    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);

    // Reset Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set the correct perspective.
    gluPerspective(camView.fov, camView.aspect, camView.nearVal, camView.farVal);

    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}
