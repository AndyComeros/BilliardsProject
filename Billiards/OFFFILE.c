
/*
This class contains useful functions related to reading OFFFiles
*/
#include "OFFFILE.h"
#include <stdio.h>
#include "Vector.h"

//free offile memory
void freeOFFile(struct OFFFile *off)
{
    free(off->vertecies);
    free(off->faces);
    free(off);
}

//Read in OFF file to a OFFFile struct
void readOFFFile(struct OFFFile *data, char *fileName)
{
    strcpy(data->modelName, fileName);
    //open file
    FILE  *inFile = fopen(fileName,"r");

    //check if file exist/can be opened
    if(inFile == NULL)
    {
        printf("Could not open file!");
        exit(1);
    }

    //check if OFF firstline is there
    char *offHeader[3];
    fscanf(inFile,"%s",offHeader);

    if(strcmp(offHeader,"OFF") != 0)
    {
        printf("***OFF File is invalid!***");
        //needs an exit condiiton
    }

    //gets verts faces and edge amounts
    fscanf(inFile,"%d %d %d",&data->nVert,&data->nFace,&data->nEdge);

    //reads in vertecies and calulates center based on data
    data->vertecies = (GLfloat *)malloc(sizeof(GLfloat)*3*(data->nVert));
    (*data).center.x = 0;
    (*data).center.y = 0;
    (*data).center.z = 0;

    for(int i = 0; i < data->nVert; i++)
    {
        fscanf(inFile,"%f %f %f",&data->vertecies[i].x,&data->vertecies[i].y,&data->vertecies[i].z);

        (*data).center.x+= (*data).vertecies[i].x;
        (*data).center.y+= (*data).vertecies[i].y;
        (*data).center.z+= (*data).vertecies[i].z;
    }

    (*data).center.x /= (*data).nVert;
    (*data).center.y /= (*data).nVert;
    (*data).center.z /= (*data).nVert;


    //reads in triangles/faces
    data->faces = (int *)malloc(sizeof(int)*3*(data->nFace));

    for(int i = 0; i < data->nFace; i++)
    {
        fscanf(inFile,"%*d %d %d %d",&data->faces[i][0],&data->faces[i][1],&data->faces[i][2]);
    }
    fclose(inFile);
}

void renderOFF(struct OFFFile *object3D,vect3D offset,vect3D scale)
{
    //printf("wWADSADSD : %f\n",offset[2]);
    GLfloat color[][3] = {{1.0,0.0,0.0},{0.0,1.0,0.0},{0.0,0.0,1.0}};

    for(int i = 0; i < (object3D->nFace)-1; i++)
    {
        glBegin(GL_TRIANGLES);


        glColor3f(0,0,1);
        if(i > object3D->nFace/2)
        {
            glColor3f(1,0,0);
        }

        point3D tri[3];

        for(int j = 0; j<3; j++)
        {
            tri[j].x = object3D->vertecies[object3D->faces[i][j]].x;
            tri[j].y = object3D->vertecies[object3D->faces[i][j]].y;
            tri[j].z = object3D->vertecies[object3D->faces[i][j]].z;
        }

        //modifiers

        tri[0] = vectAddVect(tri[0],offset);
        tri[1] = vectAddVect(tri[1],offset);
        tri[2] = vectAddVect(tri[2],offset);
/*
        tri[0] = vectMultScalars(tri[0],scale.x,scale.x,scale.x);
        tri[1] = vectMultScalars(tri[1],scale.y,scale.y,scale.y);
        tri[2] = vectMultScalars(tri[2],scale.z,scale.z,scale.z);
        //end modifiers
        */
        GLfloat vert1[3] = {tri[2].x,tri[2].y,tri[2].z};
        GLfloat vert2[3] = {tri[0].x,tri[0].y,tri[0].z};
        GLfloat vert3[3] = {tri[1].x,tri[1].y,tri[1].z};


        glVertex3fv(vert1);
        glVertex3fv(vert2);
        glVertex3fv(vert3);

        glEnd();
    }

}

GLfloat CalcRadius(){




}

void printOFFInfo(struct OFFFile *data){
    printf("3D File Name: %s\n",data->modelName);
}


//debug stuff, not sure if it belongs here
void drawAxis()
{
    GLfloat axisCol[][3] = {{1.0,0.0,0.0},{0.0,1.0,0.0},{0.0,0.0,1.0}};
    const GLfloat bigNum = 999.0;
    const GLfloat farpointX[] = {bigNum,0.0,0.0};
    const GLfloat farpointY[] = {0.0,bigNum,0.0};
    const GLfloat farpointZ[] = {0.0,0.0,bigNum};
    const GLfloat origin[] = {0.0,0.0,0.0};

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
    GLfloat color[3] = {1,1,1};

    glLineWidth(0.2);
    for(GLfloat i = (1-size); i<size; i++)
    {
        for(GLfloat j = (1-size); j<size; j++)
        {
            glBegin(GL_LINES);
            glColor3fv(color);
            GLfloat point1[3] = {i,0,j};
            GLfloat point2[3] = {-i,0,j};
            glVertex3fv(point1);
            glVertex3fv(point2);
            glEnd();
            glBegin(GL_LINES);
            glColor3fv(color);
            GLfloat point3[3] = {i,0,j};
            GLfloat point4[3] = {i,0,-j};
            glVertex3fv(point3);
            glVertex3fv(point4);
            glEnd();
        }
    }
}
