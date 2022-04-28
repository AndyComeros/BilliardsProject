
/*
This class contains useful functions related to reading OFFFiles
*/
#include "ObjectFileLib.h"
#include <stdio.h>
#include "VectorMath.h"

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
    (*data).center[0] = 0;
    (*data).center[1] = 0;
    (*data).center[2] = 0;

    for(int i = 0; i < data->nVert; i++)
    {
        fscanf(inFile,"%f %f %f",&data->vertecies[i][0],&data->vertecies[i][1],&data->vertecies[i][2]);

        (*data).center[0]+= (*data).vertecies[i][0];
        (*data).center[1]+= (*data).vertecies[i][1];
        (*data).center[2]+= (*data).vertecies[i][2];
    }

    (*data).center[0] /= (*data).nVert;
    (*data).center[1] /= (*data).nVert;
    (*data).center[2] /= (*data).nVert;


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

        point3D tri[3];
        glColor3f(0,0,1);
        if(i > object3D->nFace/2)
        {
            glColor3f(1,0,0);
        }

        for(int j = 0; j<3; j++)
        {
            tri[j][0] = object3D->vertecies[object3D->faces[i][j]][0];
            tri[j][1] = object3D->vertecies[object3D->faces[i][j]][1];
            tri[j][2] = object3D->vertecies[object3D->faces[i][j]][2];
        }

        //modifiers
        vectAddVect(&tri[0],offset);
        vectAddVect(&tri[1],offset);
        vectAddVect(&tri[2],offset);

        vectMultScalars(tri[0],scale[0],scale[1],scale[2]);
        vectMultScalars(tri[1],scale[0],scale[1],scale[2]);
        vectMultScalars(tri[2],scale[0],scale[1],scale[2]);
        //end modifiers

        glVertex3fv(tri[2]);
        glVertex3fv(tri[0]);
        glVertex3fv(tri[1]);

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
            point3D point1 = {i,0,j};
            point3D point2 = {-i,0,j};
            glVertex3fv(point1);
            glVertex3fv(point2);
            glEnd();
            glBegin(GL_LINES);
            glColor3fv(color);
            point3D point3 = {i,0,j};
            point3D point4 = {i,0,-j};
            glVertex3fv(point3);
            glVertex3fv(point4);
            glEnd();
        }
    }
}
