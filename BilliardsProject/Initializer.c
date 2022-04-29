#include "Initializer.h"
#include "OFFFILE.h"


   GLdouble fov	 = 30;		// degrees
    GLdouble aspect	 = 1;		// aspect ratio aspect = height/width
    GLdouble nearVal = 0.5;     // near and far clipping planes
    GLdouble farVal  = 5000;

void init(void)
{

    //GLUT_DOUBLE for double buffering, GLUT_DEPTH to create depth buffer
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    //setLight();

    //Face Culling
    glEnable(GL_DEPTH_TEST);//per pixex depth testing
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);


    /*---- attributes ----*/
    //size of points drawn
    glPointSize(2.0);
    //specifies default pixel color probs
    glClearColor(0.0, 0.0, 0.0, 1.0);

    //specifies the "current color" used to draw
    glColor3f(1.0, 0.0, 0.0); /* draw in red */
    //size of lines drawnS
    glLineWidth(2.0);

    //set up a perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();


    gluPerspective(fov, aspect, nearVal, farVal);

    glMatrixMode(GL_MODELVIEW);
}


//changes size of viewport when window size changes. use as callback function
//for when it does change//not my code. removed stuff.
void changeSize(int w, int h)
{

    float ratio = 1.0* w / h;

    // Use the Projection Matrix
    glMatrixMode(GL_PROJECTION);

    // Reset Matrix
    glLoadIdentity();

    // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

    // Set the correct perspective.
    gluPerspective(fov,ratio,nearVal,farVal);

    // Get Back to the Modelview
    glMatrixMode(GL_MODELVIEW);
}
