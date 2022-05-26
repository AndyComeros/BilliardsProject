#include "OffFile.h"
#include <stdio.h>

const char* getFileName()
{
	printf("Please Enter Filename of .off file: ");
	const char* c = malloc(sizeof(c)*80);
	scanf("%s", c);
	return c;
}

void readOffFile(char* filename, OffModel* obj)
{
	FILE* fptr = fopen(filename, "r");

	if (fptr == NULL)
	{
		printf("Unable to open file, Program will now exit\n");
		exit(1);
	}

	//check if OFF firstline is there
	char* offHeader[3];
	fscanf(fptr, "%s", offHeader);

	if (strcmp(offHeader, "OFF") != 0)
	{
		printf("***OFF File is invalid!***");
		exit(-1);
	}

	//gets verts faces and edge amounts
	fscanf(fptr, "%d %d %d", &obj->nVert, &obj->nFace, &obj->nEdge);
	size_t lenVec3 = sizeof(Vec3), lenFace = sizeof(Face);

	obj->vertice = (Vec3*)malloc(lenVec3 * obj->nVert);
	obj->faces = (Face*)malloc(lenFace * obj->nFace);

	for (int i = 0; i < obj->nVert; i++)
	{
		fscanf(fptr, "%f %f %f", &obj->vertice[i].x, &obj->vertice[i].y, &obj->vertice[i].z);
	}

	for (int i = 0; i < obj->nFace; i++)
	{
		int *v1 = malloc(sizeof(int)), *v2 = malloc(sizeof(int)), *v3 = malloc(sizeof(int));
		fscanf(fptr, "%d %d %d", v1, v2, v3);
		obj->faces[i].p1 = &obj->vertice[*v1];
		obj->faces[i].p2 = &obj->vertice[*v2];
		obj->faces[i].p3 = &obj->vertice[*v3];
	}

	fclose(fptr);
}

void FreeObject(OffModel* obj)
{
	free(obj->faces);
	free(obj->vertice);
}