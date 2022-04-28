#include <stdio.h>
#include <stdlib.h>
#include <gl/freeglut.h>
#include "Vector.h"
#include "OFFFILE.h"
#include "Initializer.h"
#include "GameObject.h"
#include "HitBox.h"

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

void display(void);
void PhysicsUpdate(int num);

void collideBallz(GameObject *b1,GameObject *b2){
/*
    if(HitSphereSphere(b1->hitBox,b2->hitBox)== 1){
            vect3D iv1;
            iv1[0] = b1->velocity[0];
            iv1[1] = b1->velocity[1];
            iv1[2] = b1->velocity[2];
            vect3D iv2;
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

int main(int argc, char** argv)
{
    //go = malloc(sizeof(struct GameObject) * balls);
    int maxSpeed = 5;


    for(int i =0; i < balls;i++){
        GameObjInitialize(&go[i]);
        GameObjSetModel(&go[i],"bone.off");
        GameObjSetPosition(&go[i],rand()%200,100+(25*i),rand()%200);
        go[i].name[0] = 'p';

        //add physics boi

        go[i].hitBox->Radius = ballsize;

        go[i].velocity.x = rand()%maxSpeed;
        go[i].velocity.y = rand()%maxSpeed;
        go[i].velocity.z = rand()%maxSpeed;
    }

    //go.hitBox = &sphere;


    //###########--REQUIRED STUFF--###########//
    //need to initiaize glut before it can be used
    glutInit(&argc,argv);

    //initialize window properties
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0); // place window top left on display

    //create window and name it
    glutCreateWindow("poggers");

    //initailize project stuff
    init();

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


void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glClearColor(0.0,0.0,0.0,1);//black backdrop

    //set camera data - need to set to variables, perhps give game object data...
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(600,300,600,//pos
              0,0,0,//target
              0.0,1.0,0.0//whats up dog
              );

    //glutWireSphere(ballsize,20,20);
    drawAxis();//debug

    drawGridXZ(5);//debug
    //ScenePhysUpdate(&mainScene);
    for(int i=0;i< balls;i++){
        GameObjRender(&go[i]);
    }
    //SceneRenderUpdate(&mainScene);
    glutSwapBuffers();
}


PhysicsUpdate(int num){
    glutTimerFunc(40,PhysicsUpdate,0);

    for(int i=0;i<balls;i++){
            //printf("position: %f,%f,%f\n",go[i].center.x,go[i].center.y,go[i].center.z);
            //ball on ball collision
        for(int j=i; j< balls; j++){
            if(&go[i] != &go[j]){
                collideBallz(&go[i],&go[j]);
            }
        }

        //add velocity
        go[i].center.x+= go[i].velocity.x;
        go[i].center.y+= go[i].velocity.y;
        go[i].center.z+= go[i].velocity.z;

        //decrease velocity due to drag
        go[i].velocity.x /=drag;
        go[i].velocity.y /=drag;
        go[i].velocity.z /=drag;

        //bouncy boi
        if(go[i].center.y <= 12){
            go[i].velocity.y = abs(go[i].velocity.y)*friction;//bounce back up
        }else{
            go[i].velocity.y -= gravity;
        }

        //real fake walls
        if(abs(go[i].center.x) > boxSize){
            go[i].velocity.x *= -0.98;
        }
        if(abs(go[i].center.z) > boxSize){
            go[i].velocity.z *= -0.98;
        }
    }

    glutPostRedisplay();
}
