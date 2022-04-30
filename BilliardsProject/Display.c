#include "Display.h"

#define balls 5
#define boxSize 200
#define drag 1.05
#define gravity 0.98
#define friction 0.98//bounciness??

#define ballsize 12 //hitbox of balls

//int balls = 1;
GameObject go[balls];
HitBox sphere;

HitBox floor;

void initGlut(void)
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

    viewingInit();
}

void initObjects()
{
    //go = malloc(sizeof(struct GameObject) * balls);
    int maxSpeed = 5;

    for (int i = 0; i < balls; i++) {
        GameObjInitialize(&go[i]);
        GameObjSetModel(&go[i], "bone.off");
        GameObjSetPosition(&go[i], rand() % 200, 100 + (25 * i), rand() % 200);
        go[i].name[0] = 'p';

        //add physics boi

        go[i].hitBox->Radius = ballsize;

        go[i].velocity.x = rand() % maxSpeed;
        go[i].velocity.y = rand() % maxSpeed;
        go[i].velocity.z = rand() % maxSpeed;
    }

    //go.hitBox = &sphere;
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glClearColor(0.0, 0.0, 0.0, 1);//black backdrop

    //set camera data - need to set to variables, perhps give game object data...
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(600, 300, 600,//pos
        0, 0, 0,//target
        0.0, 1.0, 0.0//whats up dog
    );

    //glutWireSphere(ballsize,20,20);
    drawAxis();//debug

    drawGridXZ(40);//debug
    //ScenePhysUpdate(&mainScene);
    for (int i = 0; i < balls; i++) {
        GameObjRender(&go[i]);
    }
    //SceneRenderUpdate(&mainScene);
    glutSwapBuffers();
}

void PhysicsUpdate(int num) {
    glutTimerFunc(40, PhysicsUpdate, 0);

    for (int i = 0; i < balls; i++) {
        //printf("position: %f,%f,%f\n",go[i].center.x,go[i].center.y,go[i].center.z);
        //ball on ball collision
        for (int j = i; j < balls; j++) {
            if (&go[i] != &go[j]) {
                collideBallz(&go[i], &go[j]);
            }
        }

        //add velocity
        go[i].center.x += go[i].velocity.x;
        go[i].center.y += go[i].velocity.y;
        go[i].center.z += go[i].velocity.z;

        //decrease velocity due to drag
        go[i].velocity.x /= drag;
        go[i].velocity.y /= drag;
        go[i].velocity.z /= drag;

        //bouncy boi
        if (go[i].center.y <= 12) {
            go[i].velocity.y = abs(go[i].velocity.y) * friction;//bounce back up
        }
        else {
            go[i].velocity.y -= gravity;
        }

        //real fake walls
        if (abs(go[i].center.x) > boxSize) {
            go[i].velocity.x *= -0.98;
        }
        if (abs(go[i].center.z) > boxSize) {
            go[i].velocity.z *= -0.98;
        }
    }

    glutPostRedisplay();
}

//debug stuff, not sure if it belongs here
void drawAxis()
{
    GLfloat axisCol[][3] = { {1.0,0.0,0.0},{0.0,1.0,0.0},{0.0,0.0,1.0} };
    const GLfloat bigNum = 999.0;
    const GLfloat farpointX[] = { bigNum,0.0,0.0 };
    const GLfloat farpointY[] = { 0.0,bigNum,0.0 };
    const GLfloat farpointZ[] = { 0.0,0.0,bigNum };
    const GLfloat origin[] = { 0.0,0.0,0.0 };

    glLineWidth(3.0);
    glBegin(GL_LINES);

    glColor3fv(axisCol[0]);
    glVertex3fv(origin);
    glVertex3fv(farpointX);

    glColor3fv(axisCol[1]);
    glVertex3fv(origin);
    glVertex3fv(farpointY);

    glColor3fv(axisCol[2]);
    glVertex3fv(origin);
    glVertex3fv(farpointZ);
    glEnd();
}


//debug stuff, not sure if it belongs here
void drawGridXZ(int size)
{
    /*
    GLfloat color[3] = { 1,1,1 };

    glLineWidth(0.2);
    for (GLfloat i = (1 - size); i < size; i++)
    {
        for (GLfloat j = (1 - size); j < size; j++)
        {
            glBegin(GL_LINES);
            glColor3fv(color);
            GLfloat point1[3] = { i,0,j };
            GLfloat point2[3] = { -i,0,j };
            glVertex3fv(point1);
            glVertex3fv(point2);
            glEnd();
            glBegin(GL_LINES);
            glColor3fv(color);
            GLfloat point3[3] = { i,0,j };
            GLfloat point4[3] = { i,0,-j };
            glVertex3fv(point3);
            glVertex3fv(point4);
            glEnd();
        }
    }
    */
    GLfloat i = 0.0;
    GLfloat gridscale = 20; // spacing between grid lines, depends on how close/far you are
    glColor3f(1.0, 1.0, 0.0);

    for (i = 0.0; i < size; i++)
    {
        // z direction
        glBegin(GL_LINES);
        glVertex3f(i * gridscale - size / 2, 0.0, 0.0 - size / 2);
        glVertex3f(i * gridscale - size / 2, 0.0, 1'000.0);
        glEnd();

        // x direction
        glBegin(GL_LINES);
        glVertex3f(0.0 - size / 2, 0.0, i * gridscale - size / 2);
        glVertex3f(1'000.0, 0.0, i * gridscale - size / 2);
        glEnd();
    }
}

void collideBallz(GameObject* b1, GameObject* b2) {
    /*
        if(HitSphereSphere(b1->hitBox,b2->hitBox)== 1){
                Vec3 iv1;
                iv1[0] = b1->velocity[0];
                iv1[1] = b1->velocity[1];
                iv1[2] = b1->velocity[2];
                Vec3 iv2;
                iv2[0] = b2->velocity[0];
                iv2[1] = b2->velocity[1];
                iv2[2] = b2->velocity[2];
                //printf("pos: %f, %f, %f\n",b1->center[0],b1->center[1],b1->center[2]);
            vectCrossProd(b1->velocity,iv2);
            vectCrossProd(b2->velocity,iv1);
            vectMultScalar(&b1->velocity,0.5);
            vectMultScalar(&b2->velocity,0.5);

        }
        */
}